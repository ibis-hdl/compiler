/*
 * data_set.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_
#define TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_


#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <boost/filesystem.hpp>

#include <vector>

#include <testsuite/namespace_alias.hpp>


namespace testsuite {


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
    dataset_loader(fs::path const& path,
        // Hack for boost.test missing command line args
        std::string const& relative_path,   // relative path from common/testsuite to this testsuite
        std::string const& input_extension  // test case file input file extension
    );

private:
    void read_files(fs::path const& path);
    std::string read_file(fs::path const& file_path);

private:
    fs::path                                            m_prefix_dir;
    pathname_type                                       m_test_case;
    data_type                                           m_input;
    data_type                                           m_expected;
    std::string                                         input_extension;
    std::string                                         expected_extension;
};


} // namespace testsuite


#endif /* TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_ */
