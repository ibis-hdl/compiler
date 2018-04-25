/*
 * data_set.cpp
 *
 *  Created on: 31.03.2017
 *      Author: olaf
 */

#include "data_set.hpp"
#include "test_case_path.hpp"

#include <boost/filesystem/fstream.hpp>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;


dataset_loader::dataset_loader(fs::path const& path)
{
    fs::path source_dir{ TEST_CASE_PATH };

    BOOST_TEST_INFO("dataset_loader load test files from " << path);
    read_files(source_dir / path);
}


int dataset_loader::read_files(fs::path const& path)
{
    try {
        if(fs::exists(path) && fs::is_directory(path)) {

            std::vector<fs::path> dir_list { };
            std::copy(
                fs::directory_iterator(path),
                fs::directory_iterator(),
                back_inserter(dir_list)
            );

            std::sort(dir_list.begin(), dir_list.end());

            for(auto const& file : dir_list) {

                if (fs::extension(file) == ".input") {

                    m_file_path.emplace_back(file.native().c_str());
                    //cerr << "INFO: read '" << m_file_path.back() << "'\n";

                    auto const input_path  = file;
                    auto expect_path = file;
                    expect_path.replace_extension(".expected");

                    m_input.emplace_back(   read_file(input_path) );
                    m_expected.emplace_back(read_file(expect_path));
                }
            }
        }
        else {
            cerr << "*** Directory: '" << fs::absolute(path)
                      << "' does not exist. ***\n";
            return 1;
        }
    }
    catch(std::exception const& e) {
        cerr << "*** Caught \"" << e.what() << "\" exception\n";
        /* try to recover from error and continue; probably no {file}.expected
         * was found. */
        if(   m_file_path.size() == m_input.size()
           && m_input.size()     == m_expected.size() + 1
          ) {
            cerr << "*** Remove file '" << m_file_path.back()
                      << "' from data set\n";
            m_file_path.pop_back();
            m_input.pop_back();
        }
    }
    catch(...) {
        cerr << "*** Caught unexpected exception !!!\n";
        return 1;

    }
    return 0;
}


dataset_loader::string_type dataset_loader::read_file(fs::path const& file_path)
{
    fs::ifstream file{ file_path };

    if(!file) {
        cerr << "ERROR: unable to open '" << file_path.native() << "'\n";
        throw std::ios_base::failure{ "file open error" };
    }

    std::basic_ostringstream<dataset_loader::char_type> ss{};
    ss << file.rdbuf();

    if(file.fail() && !file.eof()) {
        cerr << "ERROR: unable to open '" << file_path.native() << "'\n";
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}


dataset_loader::data_set dataset_loader::input() const
{
    return data_set(m_input);
}

dataset_loader::data_set dataset_loader::expect() const
{
    return data_set(m_expected);
}


dataset_loader::data_set dataset_loader::test_file_name() const
{
    return data_set(m_file_path);
}




} // namespace x3_test


