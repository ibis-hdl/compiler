/*
 * testing_util.hpp
 *
 *  Created on: 07.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_TESTING_UTIL_HPP_
#define SOURCES_VHDL_TEST_TESTING_UTIL_HPP_

#include <boost/filesystem.hpp>

#include <sstream>
#include <iostream>


namespace x3_test {


namespace fs = boost::filesystem;

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

#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
    static constexpr std::wostream& cout{ std::wcout };
#else
    static constexpr std::ostream& cerr{ std::cerr };
    static constexpr std::ostream& cout{ std::cout };
#endif
};


} // namespace x3_test


#endif /* SOURCES_VHDL_TEST_TESTING_UTIL_HPP_ */
