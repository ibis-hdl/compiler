/*
 * testing_util.cpp
 *
 *  Created on: 19.05.2018
 *      Author: olaf
 */

#include <testsuite/vhdl_parser/testing_util.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/results_collector.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/filesystem.hpp>

#include <eda/utils/make_iomanip.hpp>

#include <iostream>


namespace testsuite { namespace vhdl_parser { namespace util {


/** Helper function to format all file path related messages unified. */
static inline
fs::path pretty_filepath(fs::path file_path) {
    return fs::canonical(file_path.make_preferred());
}


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
    std::string const& test_case_name,
    std::string const& input,
    std::string const& result
)
{
    std::size_t const width{ 80 };
    std::stringstream ss;

    auto header = [](std::string const& title, std::size_t width) {
    	using eda::utils::make_iomanip;
        return make_iomanip([&title, width](std::ostream& os) {
        	std::size_t const w{ (width - title.size()) / 2 };
        	os << "\n" << std::string(w, '-') << title << std::string(w, '-') << "\n";
        });
    };

    ss << header(" INPUT ", width)
	   << boost::trim_right_copy(input)
 	   << header(" PARSE RESULT (AST) ", width)
	   << result
	   << header("", width);

    // only write in case of failed test
    if(!current_test_passing()) {
        test_case_result_writer result_writer(test_case_name);
        result_writer.write(result);
    }

    return ss.str();
}


/**
 * test_case_result_writer definition
 */
test_case_result_writer::test_case_result_writer(std::string const& test_case)
: destination_prefix{ "./testsuite_result" }
, testcase_name{ test_case }
, write_extension{ ".result" }
, name_self { "testsuite::test_case_result_writer" }
{
    BOOST_TEST_REQUIRE(parse_command_line(),
                       "--destination-prefix= must be given");

    // XXX simply warning, print defualt: destination_prefix ???
}


bool test_case_result_writer::create_directory(fs::path const& write_path)
{
    try {
        if(   !boost::filesystem::exists(write_path)
           || !boost::filesystem::is_directory(write_path)
        ) {
            BOOST_TEST_MESSAGE("create directories " << write_path << '\n');
            return fs::create_directories(write_path);
        }
    }
    catch(fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ")"
             << "creating directory "
             << pretty_filepath(write_path).string()
             << " failed with:\n"
             << e.code().message()
        );
        return false;
    }

    return true;
}


bool test_case_result_writer::write_file(fs::path const& filename, std::string const& contents)
{
    BOOST_TEST_MESSAGE("Write result to " << filename << "\n");

    try {
        if(fs::exists(filename)) {
            fs::remove(filename);
        }
    }
    catch(fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ")"
                "remove of older file "
             << pretty_filepath(filename).string()
             << " failed with:\n"
             << e.code().message()
        );
        return false;
    }

    try {
        fs::ofstream ofs{ filename };
        ofs << contents;
    }
    catch(fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ")"
                "writing to "
             << pretty_filepath(filename).string()
             << " failed with:\n"
             << e.code().message()
        );
        return false;
    }

    return true;
}


void test_case_result_writer::write(std::string const& parse_result)
{
    fs::path const full_pathname = fs::path(destination_prefix) / "test_case" / testcase_name;
    fs::path const write_path = full_pathname.parent_path();

    if(!create_directory(write_path)) {
        return;
    }

    fs::path const filename = full_pathname.filename().replace_extension(write_extension);

    write_file(write_path / filename, parse_result);
}


bool test_case_result_writer::parse_for(std::string const& arg, std::string const& str, std::string& value)
{
    auto const pos = str.find(arg);

    if(pos == std::string::npos) {
        return false;
    }

    value = str.substr(pos + arg.size());
    return true;
}


bool test_case_result_writer::parse_command_line()
{
    unsigned const argc = boost::unit_test::framework::master_test_suite().argc;
    char** const argv = boost::unit_test::framework::master_test_suite().argv;

    bool destination_prefix_arg{ false };

    for(unsigned i = 0; i != argc; i++) {
        //std::cout << "ArgValue[" << i << "]: " << argv[i] << "\n";

        if(parse_for("--destination-prefix=", argv[i], destination_prefix)) {
            //std::cout << "--destination-prefix = " << destination_prefix << "\n";
            destination_prefix_arg = true;
        }

        if(parse_for("--write-extension=", argv[i], write_extension)) {
            //std::cout << "--write-extension = " << write_extension << "\n";
        }

    }

    if(!destination_prefix_arg) {
        std::cerr <<"WARNING(" << name_self << ")"
                  << argv[0] << " --destination-prefix= must be given\n"
                  << "fallback to default "
                  << destination_prefix << "\n";
        return false;
    }

    return true;
}


} } } // namespace testsuite.vhdl_parser.util


