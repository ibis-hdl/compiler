/*
 * failure_diagnostic_fixture.cpp
 *
 *  Created on: 19.08.2018
 *      Author: olaf
 */

#include <testsuite/common/failure_diagnostic_fixture.hpp>

#include <boost/test/framework.hpp>                 // for current_test_case
#include <boost/test/tree/test_unit.hpp>            // for master_test_suite, test...
#include <boost/test/unit_test_log.hpp>             // for BOOST_TEST_MESSAGE
#include <boost/test/utils/lazy_ostream.hpp>        // for lazy_ostream_impl, oper...
#include <boost/test/results_collector.hpp>         // for results_collector, resu...

#include <boost/filesystem/fstream.hpp>             // for ofstream
#include <boost/filesystem/operations.hpp>          // for filesystem_error, exists
#include <boost/filesystem/path.hpp>                // for path, operator<<, opera...
#include <boost/system/error_code.hpp>              // for error_code

#include <boost/algorithm/string/trim.hpp>          // for trim_right_copy

#include <eda/util/make_iomanip.hpp>

#include <testsuite/common/namespace_alias.hpp>     // IWYU pragma: keep'

#include <utility>                                  // for move
#include <iostream>


namespace testsuite {


/**
 * Write the parsed result into file for later evaluation or use
 */
class failure_diagnostic_fixture::writer
{
public:
    writer(std::string test_case);
    void write(std::string const& parse_result);

private:
    bool create_directory(fs::path const& write_path);
    bool write_file(fs::path const& filename, std::string const& contents);

    static bool parse_for(std::string_view arg, std::string_view str, std::string& value);
    bool parse_command_line();

private:
    std::string                                     destination_dir;
    std::string                                     testcase_name;
    std::string                                     write_extension;
    std::string const                               name_self;
};


} // namespace testsuite



/*
 * failure_diagnostic_fixture implementation
 */
namespace testsuite {


void failure_diagnostic_fixture::setup() { }
void failure_diagnostic_fixture::teardown() { }


/* [Detect if boost test case failed](
 *  https://stackoverflow.com/questions/18466857/detect-if-boost-test-case-failed?answertab=active#tab-top) */
bool failure_diagnostic_fixture::current_test_passing()
{
    using namespace boost::unit_test;
    auto const id = framework::current_test_case().p_id;
    auto const test_results = results_collector.results(id);
    return test_results.passed();
}


void failure_diagnostic_fixture::failure_closure(
    std::string const& test_case_name,
    std::string const& input,
    std::string const& result
)
{
    auto const display_closure = [&](std::ostream& os)
    {
        std::size_t const width{ 80 };

        auto header = [&](std::string const& title, std::size_t width) {
            using eda::util::make_iomanip;
            return make_iomanip([&title, width](std::ostream& os) {
                std::size_t const w{ (width - title.size()) / 2 };
                os << '\n' << std::string(w, '-') << title << std::string(w, '-') << '\n';
            });
        };

        os << header(" INPUT ", width)
           << boost::trim_right_copy(input)
           << header(" RESULT ", width)
           << result
           << header("", width);
    };

    if (!current_test_passing()) {
        BOOST_TEST_MESSAGE("INFO(failure_diagnostic_fixture): save closure");
        display_closure(std::cerr);
        failure_diagnostic_fixture::writer writer(test_case_name);
        writer.write(result);
    }
}


} // namespace testsuite



/*
 *  failure_diagnostic_fixture::writer implementation
 */
namespace testsuite {


/** Helper function to format all file path related messages unified. */
static inline
fs::path pretty_filepath(fs::path file_path) {
    return fs::canonical(file_path.make_preferred());
}


/**
 * failure_diagnostic_fixture::writer definition
 */
failure_diagnostic_fixture::writer::writer(std::string test_case)
: destination_dir{ "./testsuite_result" }
, testcase_name{ std::move(test_case) }
, write_extension{ ".result" }
, name_self { "testsuite::failure_diagnostic_fixture::writer" }
{
    parse_command_line();
}


bool failure_diagnostic_fixture::writer::create_directory(fs::path const& write_path)
{
    try {
        if(   !boost::filesystem::exists(write_path)
           || !boost::filesystem::is_directory(write_path)
        ) {
            BOOST_TEST_MESSAGE("INFO(" << name_self << ") "
                                << "create directories " << write_path << '\n');
            return fs::create_directories(write_path);
        }
    }
    catch(fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ") "
                             << "creating directory "
                             << pretty_filepath(write_path).string()
                             << " failed with:\n"
                             << e.code().message()
        );
        return false;
    }

    return true;
}


bool failure_diagnostic_fixture::writer::write_file(fs::path const& filename, std::string const& contents)
{
    BOOST_TEST_MESSAGE("INFO(" << name_self << ") "
                        << "Write result to " << filename << '\n');

    try {
        if(fs::exists(filename)) {
            fs::remove(filename);
        }
    }
    catch(fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ") "
             << "remove of older file "
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
        BOOST_TEST_MESSAGE("ERROR(" << name_self << ") "
                         << "writing to "
                         << pretty_filepath(filename).string()
                         << " failed with:\n"
                         << e.code().message()
        );
        return false;
    }

    return true;
}


void failure_diagnostic_fixture::writer::write(std::string const& parse_result)
{
    fs::path const full_pathname = fs::path(destination_dir) / "test_case" / testcase_name;
    fs::path const write_path = full_pathname.parent_path();

    if(!create_directory(write_path)) {
        return;
    }

    fs::path const filename = full_pathname.filename().replace_extension(write_extension);

    write_file(write_path / filename, parse_result);
}


bool failure_diagnostic_fixture::writer::parse_for(std::string_view arg, std::string_view str, std::string& value)
{
    auto const pos = str.find(arg);

    if(pos == std::string::npos) {
        return false;
    }

    value = str.substr(pos + arg.size());

    return true;
}


bool failure_diagnostic_fixture::writer::parse_command_line()
{
    unsigned const argc = boost::unit_test::framework::master_test_suite().argc;
    char** const argv = boost::unit_test::framework::master_test_suite().argv;

    bool destination_dir_arg{ false };

    for(unsigned i = 0; i != argc; i++) {

        std::string_view const argv_sv{ argv[i] }; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        //std::cout << "ArgValue[" << i << "]: " << argv_sv << '\n';

        if(parse_for("--destination-dir=", argv_sv, destination_dir)) {
           //std::cout << "--destination-dir = " << destination_prefix << '\n';
            destination_dir_arg = true;
        }

        if(parse_for("--write-extension=", argv_sv, write_extension)) {
            //std::cout << "--write-extension = " << write_extension << '\n';
        }

    }

    if(!destination_dir_arg) {
        std::cerr <<"WARNING(" << name_self << ") "
                  << argv[0] << " --destination-dir= must be given\n" // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                  << "fallback to default "
                  << destination_dir << '\n';
        return false;
    }

    return true;
}


} // namespace testsuite

