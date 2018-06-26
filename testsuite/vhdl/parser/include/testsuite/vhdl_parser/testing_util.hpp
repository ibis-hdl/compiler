/*
 * testing_util.hpp
 *
 *  Created on: 07.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_

#include <boost/filesystem.hpp>

#include <sstream>

#include <testsuite/namespace_alias.hpp>


namespace testsuite { namespace vhdl_parser { namespace util {


/**
 * [Detect if boost test case failed](
 *  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top)
 */
bool current_test_passing();


/**
 * Write a report message in case of failure
 */
std::string report_diagnostic(
    fs::path const& test_case_name,
    std::string const& input,
    std::string const& result
);


/**
 * Write the parsed result into file for later evaluation or use
 */
class test_case_result_writer
{
public:
    typedef fs::path                                    pathname_type;

public:
    test_case_result_writer(fs::path const& test_case);
    void write(std::string const& parse_result);

private:
    bool create_directory(fs::path const& p);
    bool write_file(fs::path const& p, std::string const& contents);

private:
    fs::path                                            m_dest_dir;
    fs::path                                            m_test_case;
};



/**
 * String converting utilities
 *
 * Some modules of the boost library uses std::wstring or std::string on Windows
 * which results into compile errors on Windows/MinGW. Hence, some String convert
 * utlities are supplied to rule them. See
 * [UTF conversion functions in C++11](
 * https://stackoverflow.com/questions/38688417/utf-conversion-functions-in-c11?answertab=active#tab-top)
 */
namespace detail {

std::string to_utf8(std::wstring const& s);
std::wstring to_utf16(std::string const& s);

} // namespace detail

#if defined(_WIN32) || defined(_WIN64)
#define convert_string(s)   detail::to_utf16(s)
#else
#define convert_string(s)   s
#endif


} } } // namespace testsuite.vhdl_parser.util


#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_ */
