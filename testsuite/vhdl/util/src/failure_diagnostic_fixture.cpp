#include <testsuite/util/failure_diagnostic_fixture.hpp>
#include <testsuite/util/cli_args.hpp>
#include <testsuite/util/compile_builtin.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/unit_test.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <sstream>
#include <system_error>

namespace  // anonymous
{

/// FixMe: This is a hack to avoid the depency to eda::vhdl to
/// this project. This depends only on eda::util::make_iomanip
/// header for failure_diagnostic_fixture
/// Hence it's a copy&paste of <eda/util/make_iomanip.hpp>
template <typename T>
struct A {
    T x;

    friend std::ostream& operator<<(std::ostream& os, A const& a)
    {
        a.x(os);
        return os;
    }
};

template <typename T>
A<std::decay_t<T>> make_iomanip(T&& x)
{
    return { std::forward<T>(x) };
}

}  // namespace

/// ---------------------------------------------------------------------------
///
/// failure_diagnostic_fixture implementation
///
/// ---------------------------------------------------------------------------
namespace testsuite::util {

void failure_diagnostic_fixture::setup()
{
    using util::cli_args;

    if (cli_args::destination_dir().empty()) {
        BOOST_TEST_MESSAGE(  // --
            "INFO(" << fixture_name << ") use compiled builtin <destination_dir> "
                    << compile_builtin::destination_dir);
        destination_dir = compile_builtin::destination_dir;
    }
    else {
        BOOST_TEST_MESSAGE(  // --
            "INFO(" << fixture_name << ") use command line <destination_dir> "
                    << cli_args::destination_dir());
        destination_dir = cli_args::destination_dir();
    }

    if (cli_args::output_extension().empty()) {
        BOOST_TEST_MESSAGE(  // --
            "INFO(" << fixture_name << ") use compiled builtin <output_extension> "
                    << compile_builtin::output_extension);
        output_extension = compile_builtin::output_extension;
    }
    else {
        BOOST_TEST_MESSAGE(  // --
            "INFO(" << fixture_name << ") use command line <output_extension> "
                    << cli_args::output_extension());
        output_extension = cli_args::output_extension();
    }

    // post condition
    BOOST_TEST_REQUIRE(!destination_dir.empty());
    BOOST_TEST_REQUIRE(!output_extension.empty());
}

void failure_diagnostic_fixture::teardown()
{
    // nothings to do
}

bool failure_diagnostic_fixture::current_test_passing()
{
    using namespace boost::unit_test;

    auto const id = framework::current_test_case().p_id;
    auto const test_results = results_collector.results(id);

    return test_results.passed();
}

void failure_diagnostic_fixture::failure_closure(std::string test_case_name,
                                                 std::string_view test_input,
                                                 std::string_view test_result)
{
    // render test_input and test_result on stream
    auto const display_closure = [&](std::ostream& os) {
        std::size_t const col_width{ 80 };

        // furnish a nice line with title in the middle
        auto hline = [&](std::string const& title, std::size_t col_width, char fill = '~') {
            return make_iomanip([&title, col_width, fill](std::ostream& os) {
                std::size_t const w{ (col_width - title.size()) / 2 };
                std::string const line(w, fill);
                os << '\n' << line << title << line << '\n';
            });
        };

        // trim trailing spaces from test_input, boost::trim_right_copy doesn't work
        // on string_view, hence we write our own
        // FixMe [C++20] next standard supports string_view iterator pair constructor
        // ([basic_string_view](https://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view)
        // (5)), so we can write inside lambda function body:
        // @code{.cpp}
        // return std::string_view(
        //   x.begin(), std::find_if(x.rbegin(), x.rend(), [](char c) { return !std::isspace(c);
        //   }).base());
        // @endcode
        auto const trim_right = [](std::string_view x) {
            // clang-format off
            return std::string_view(
                x.data(), // const CharT*
                std::find_if(x.rbegin(), x.rend(), [](char c) {
                                return !static_cast<bool>(std::isspace(c)); }
                            ).base() - x.begin()); // count
            // clang-format on
        };

        // finally the nice rendered failure closure for diagnostic
        os << hline(" failure diagnostic closure: '" + test_case_name + "'", col_width, '#')
           << hline(" INPUT ", col_width) << trim_right(test_input)  // input
           << hline(" RESULT ", col_width) << test_result            // output
           << hline("", col_width);                                  // footer
    };

    // if current test fail render closure to console and save test_result to filesystem
    if (!current_test_passing()) {
        BOOST_TEST_MESSAGE("INFO(" << fixture_name << ") save closure");
        // render on terminal
        display_closure(std::cerr);

        // write on filesystem
        fs::path full_pathname = destination_dir / test_case_name;
        full_pathname = full_pathname.replace_extension(output_extension);

        write(full_pathname, test_result);
    }
}

}  // namespace testsuite::util

// ---------------------------------------------------------------------------
//
// failure_diagnostic_fixture private writer functions implementation
//
// ---------------------------------------------------------------------------
using testsuite::util::cli_args;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_TEST_GLOBAL_FIXTURE(cli_args);

namespace testsuite::util {

void failure_diagnostic_fixture::write(fs::path const& full_pathname, std::string_view result)
{
    fs::path const write_path = full_pathname.parent_path();

    BOOST_TEST_REQUIRE(create_directories(write_path));
    BOOST_TEST_REQUIRE(write_file(full_pathname, result));
}

bool failure_diagnostic_fixture::create_directories(fs::path const& write_path)
{
    try {
        if (!fs::exists(write_path) || !fs::is_directory(write_path)) {
            BOOST_TEST_MESSAGE("INFO(" << fixture_name << ") create directories " << write_path
                                       << '\n');
            BOOST_TEST_REQUIRE(fs::create_directories(write_path));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << fixture_name << ") creating directory " << write_path
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    return true;
}

bool failure_diagnostic_fixture::write_file(fs::path const& filename, std::string_view contents)
{
    BOOST_TEST_MESSAGE("INFO(" << fixture_name << ") Write result to " << filename);
    // remove old result file if exist
    try {
        if (fs::exists(filename)) {
            BOOST_TEST_REQUIRE(fs::remove(filename));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << fixture_name << ") remove of older result file " << filename
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    try {
        std::ofstream ofs{ filename };
        ofs << contents;
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << fixture_name << ") writing to " << filename
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    return true;
}

}  // namespace testsuite::util
