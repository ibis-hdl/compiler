/*
 * data_set.hpp
 *
 *  Created on: 28.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_DATA_SET_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_DATA_SET_HPP_


#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <boost/filesystem.hpp>

#include <vector>


namespace x3_test {


namespace fs = boost::filesystem;


class dataset_loader
{
public:
    typedef std::vector<fs::path>                       pathname_type;
    typedef std::vector<std::string>                    data_type;

public:
    pathname_type const& test_case_name() const { return m_test_case; }
    data_type const& input() const { return m_input; }
    data_type const& expect() const { return m_expected; }

public:
    dataset_loader(fs::path const& path);

private:
    void read_files(fs::path const& path);
    std::string read_file(fs::path const& file_path);

private:
    fs::path                                            m_source_dir;
    pathname_type                                       m_test_case;
    data_type                                           m_input;
    data_type                                           m_expected;
};


} // namespace x3_test




#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_DATA_SET_HPP_ */
