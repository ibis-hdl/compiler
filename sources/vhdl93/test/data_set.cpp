/*
 * data_set.cpp
 *
 *  Created on: 31.03.2017
 *      Author: olaf
 */

#include "data_set.hpp"
#include "app_mock.hpp"

#include <boost/filesystem/fstream.hpp>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;


dataset_loader::dataset_loader(fs::path const& path)
{
    fs::path source_dir{ R"(/home/olaf/work/CXX/IBIS_SOURCE/sources/vhdl93)" };

    std::cout << "dataset_loader load test files from " << path << '\n';
    read_files(source_dir / path);
}


int dataset_loader::read_files(fs::path const& path)
{
    try {
        if(fs::exists(path) && fs::is_directory(path)) {

            auto dir_iter = fs::directory_iterator(path);
            auto const& dir_end  = fs::directory_iterator();
            for( ; dir_iter != dir_end; dir_iter++) {

                if (fs::extension(dir_iter->path()) == ".input") {

                    m_file_path.emplace_back(dir_iter->path().native().c_str());

                    auto const input_path  = dir_iter->path();
                    auto expect_path = dir_iter->path();
                    expect_path.replace_extension(".expected");

                    m_input.emplace_back(   read_file(input_path) );
                    m_expected.emplace_back(read_file(expect_path));
                }
            }
        }
        else {
            std::cerr << "Directory: " << fs::absolute(path)
            << " does not exist.\n";
            return 1;
        }
    }
    catch(std::exception const& e) {
        std::cerr << "Caught " << e.what() << " exception\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Caught unexpected exception !!!\n";
        return 1;

    }
    return 0;
}


std::string dataset_loader::read_file(fs::path const& file_path)
{
    fs::ifstream file{ file_path };

    if(!file) {
        std::cerr << "ERROR: unable to open '" << file_path << "'\n";
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    if(file.fail() && !file.eof()) {
        std::cerr << "ERROR: unable to open '" << file_path << "'\n";
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


