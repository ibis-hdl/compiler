/*
 * testing_util.hpp
 *
 *  Created on: 07.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_


#include <sstream>
#include <string>

#include <boost/filesystem.hpp>

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
    std::string const& test_case_name,
    std::string const& input,
    std::string const& result
);


/**
 * Write the parsed result into file for later evaluation or use
 */
class test_case_result_writer
{
public:
    test_case_result_writer(std::string const& test_case);
    void write(std::string const& parse_result);

private:
    bool create_directory(fs::path const& p);
    bool write_file(fs::path const& p, std::string const& contents);

private:
    bool parse_for(std::string const& arg, std::string const& string, std::string& value);
    bool parse_command_line();

private:
    std::string                                     destination_prefix;
    std::string                                     testcase_name;
    std::string                                     write_extension;
    std::string const                               name_self;
};


} } } // namespace testsuite.vhdl_parser.util


#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_UTIL_HPP_ */
