/*
 * testing_util.cpp
 *
 *  Created on: 19.05.2018
 *      Author: olaf
 */

#include "testing_util.hpp"
#include "test_case_path.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/results_collector.hpp>

#include <boost/algorithm/string.hpp>
#include <iostream>

#include <locale>
#include <codecvt>


namespace x3_test {


#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
    static constexpr std::wostream& cout{ std::wcout };
#else
    static constexpr std::ostream& cerr{ std::cerr };
    static constexpr std::ostream& cout{ std::cout };
#endif


/**
 * [Detect if boost test case failed](
 *  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top)
 */
bool current_test_passing()
{
  using namespace boost::unit_test;
  auto const id = framework::current_test_case().p_id;
  auto const test_results = results_collector.results(id);
  return test_results.passed();
}


/**
 * report_diagnostic
 */
std::string report_diagnostic(
    fs::path const& test_case_name,
    std::string const& input,
    std::string const& result
)
{
    std::size_t const width{ 80 };
    std::string const title{ " PARSER INPUT/OUTPUT " };
    std::size_t const w{ (width - title.size()) / 2 };
    std::stringstream ss;

    ss << "\n" << std::string(w, '-') << title << std::string(w, '-') << "\n"
       << boost::trim_right_copy(input)
       << '\n' << std::string(width, '-') << '\n'
       << result
       << '\n' << std::string(width, '-') << '\n';

    // only write in case of failed test
    if(!x3_test::current_test_passing()) {
        test_case_result_writer result_writer(test_case_name);
        result_writer.write(result);
    }

    return ss.str();
}


/**
 * test_case_result_writer definition
 */
test_case_result_writer::test_case_result_writer(fs::path const& test_case)
/* The prefix for the test case output root directory structure is (unfortunately)
 * hard coded. I didn't found a way to give these as command line argument
 * to the boost.test runner. */
: m_dest_dir{ BT_TEST_CASE_WRITE_PATH }
, m_test_case{ test_case }
{ }


bool test_case_result_writer::create_directory(fs::path const& write_path)
{
    try {
        if(   !boost::filesystem::exists(write_path)
           || !boost::filesystem::is_directory(write_path)
        ) {
            cout << "create directories " << write_path << '\n';
            return fs::create_directories(write_path);
        }
    }
    catch(fs::filesystem_error const& e) {
        cerr << "creating directory "
             << write_path
             << " failed with:\n"
             << convert_string(e.code().message())
             << "\n";
        return false;
    }

    return true;
}


bool test_case_result_writer::write_file(fs::path const& filename, std::string const& contents)
{
    cout << "Write result to " << filename << "\n";

    try {
        if(fs::exists(filename)) {
            fs::remove(filename);
        }
    }
    catch(fs::filesystem_error const& e) {
        cerr << "remove of older file "
             << filename
             << " failed with:\n"
             << convert_string(e.code().message())
             << "\n";
        return false;
    }

    try {
        fs::ofstream ofs{ filename };
        ofs << contents;
    }
    catch(fs::filesystem_error const& e) {
        cerr << "writing to "
             << filename
             << " failed with:\n"
             << convert_string(e.code().message())
             << "\n";
        return false;
    }

    return true;
}


void test_case_result_writer::write(std::string const& parse_result)
{
    fs::path const full_pathname = m_dest_dir / "test_case" / m_test_case;
    fs::path const write_path = full_pathname.parent_path();

#if 0
    std::string const ext{ ".parsed" };
#else // for 'easy' GOLD expected file generation
    std::string const ext{ ".expected" };
#endif

    if(!create_directory(write_path)) {
        return;
    }

    fs::path const filename = full_pathname.filename().replace_extension(ext);

    write_file(write_path / filename, parse_result);
}


} // namespace x3_test


/**
 * String converting utilities
 */
namespace x3_test { namespace detail {


std::string to_utf8(std::wstring const& s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    return convert.to_bytes(s);
}

std::wstring to_utf16(std::string const& s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    return convert.from_bytes(s);
}


} } // x3_test.detail

