/*
 * data_set.hpp
 *
 *  Created on: 28.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_DATA_SET_HPP_
#define SOURCES_VHDL_TEST_DATA_SET_HPP_


#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <boost/filesystem.hpp>

#include <vector>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;


class dataset_loader
{
public:
    typedef std::vector<fs::path>                       pathname_type;
    typedef std::vector<std::string>                    data_type;

public:
    pathname_type const& test_file_name() const { return m_file_path; }
    data_type const& input() const { return m_input; }
    data_type const& expect() const { return m_expected; }

public:
    dataset_loader(fs::path const& path);

private:
    void read_files(fs::path const& path);
    std::string read_file(fs::path const& file_path);

private:
    pathname_type                                       m_file_path;
    data_type                                           m_input;
    data_type                                           m_expected;

#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
    static constexpr std::wostream& cout{ std::wcout };
#else
    static constexpr std::ostream& cerr{ std::cerr };
    static constexpr std::ostream& cout{ std::cout };
#endif
};


} // namespace x3_test




#endif /* SOURCES_VHDL_TEST_DATA_SET_HPP_ */
