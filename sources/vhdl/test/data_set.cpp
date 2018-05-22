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


#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
    static constexpr std::wostream& cout{ std::wcout };
#else
    static constexpr std::ostream& cerr{ std::cerr };
    static constexpr std::ostream& cout{ std::cout };
#endif


/** Helper function to format all file path related messages unified. */
static inline
fs::path pretty_filepath(fs::path file_path) {
    return file_path.make_preferred();
}


dataset_loader::dataset_loader(fs::path const& path)
/* The prefix for the test case root directory structure is (unfortunately)
 * hard coded. I didn't found a way to give these as command line argument
 * to the boost.test runner. */
: m_source_dir{ BT_TEST_CASE_READ_PATH }
{
    BOOST_TEST_INFO("dataset_loader load test files from " << path);
    read_files(m_source_dir / path);
}


void dataset_loader::read_files(fs::path const& path)
{
    try {
        if(fs::exists(path) && fs::is_directory(path)) {

            std::vector<fs::path> dir_list { };
            std::copy(
                fs::directory_iterator(path),
                fs::directory_iterator(),
                std::back_inserter(dir_list)
            );

            std::sort(dir_list.begin(), dir_list.end());

            for(auto const& file : dir_list) {

                if (fs::extension(file) == ".input") {

                    m_test_case.emplace_back(
                        file.parent_path().filename() / file.stem()
                    );
                    //cerr << "INFO: read " << m_test_case.back() << "\n";

                    fs::path const input_file  = file;
                    fs::path const expect_file = fs::change_extension(file, ".expected");

                    m_input.emplace_back(   read_file(input_file ));
                    m_expected.emplace_back(read_file(expect_file));
                }
            }
        }
        else {
            cerr << "ERROR: Directory: " << fs::absolute(path)
                 << " does not exist!\n";
        }
    }
    catch(std::exception const& e) {
        cerr << "ERROR: Caught \"" << e.what() << "\" exception!\n";
        /* try to recover from error and continue; probably no {file}.expected
         * was found. */
        if(   m_test_case.size() == m_input.size()
           && m_input.size()    == m_expected.size() + 1
          ) {
            cerr << "WARNING: Remove test files at "
                 << pretty_filepath(m_test_case.back())
                 << " from data set\n";
            m_test_case.pop_back();
            m_input.pop_back();
        }
    }
    catch(...) {
        cerr << "ERROR: Caught unexpected exception!!!\n";

    }
}


std::string dataset_loader::read_file(fs::path const& file_path)
{
    fs::ifstream file{ file_path };

    if(!file) {
        cerr << "ERROR: unable to open " << pretty_filepath(file_path) << "!\n";
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    if(file.fail() && !file.eof()) {
        cerr << "ERROR: unable to open " << pretty_filepath(file_path) << "\n";
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}


} // namespace x3_test


