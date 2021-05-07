#include <testsuite/util/basic_failure_diagnostic_fixture.hpp>
#include <testsuite/util/cli_args.hpp>

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

/// FixMe: This is a hack to avoid the depency to ibis::vhdl to
/// this project. This depends only on ibis::util::make_iomanip
/// header for failure_diagnostic_fixture
/// Hence it's a copy&paste of <ibis/util/make_iomanip.hpp>
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

basic_failure_diagnostic_fixture::basic_failure_diagnostic_fixture()
    : fixture_name{ "failure_diagnostic_fixture" }
{
}

void basic_failure_diagnostic_fixture::set_builtin(std::unique_ptr<compile_builtin> other)
{
    builtin = std::move(other);

    int argc = boost::unit_test::framework::master_test_suite().argc;
    char** argv = boost::unit_test::framework::master_test_suite().argv;

    cli_args::parse_cli(argc, argv);
    check_args();
    // cli_args::print_settings();
}

void basic_failure_diagnostic_fixture::setup()
{
    // nothings to do
}

void basic_failure_diagnostic_fixture::teardown()
{
    // nothings to do
}

bool basic_failure_diagnostic_fixture::current_test_passing()
{
    using namespace boost::unit_test;

    auto const id = framework::current_test_case().p_id;
    auto const test_results = results_collector.results(id);

    return test_results.passed();
}

// local helper to trim trailing spaces from test_input, boost::trim_right_copy doesn't work
// on string_view, hence we write our own
// FixMe: [C++20] next standard supports string_view iterator pair constructor.
auto const trim_right = [](std::string_view x) {
    // clang-format off
    return std::string_view(
        x.data(), // const CharT*
        std::find_if(x.rbegin(), x.rend(), [](char c) {
                        return !static_cast<bool>(std::isspace(c)); }
                    ).base() - x.begin()); // count
    // clang-format on
};

void basic_failure_diagnostic_fixture::failure_closure(std::string test_case_name,
                                                       std::string_view test_input,
                                                       std::string_view test_result)
{
    // render test_input and test_result on stream
    auto const display_closure = [&](std::ostream& os) {
        std::size_t const col_width{ 80 };

        auto hline = [&](std::string const& title, std::size_t col_width, char fill = '~') {
            return make_iomanip([this, &title, col_width, fill](std::ostream& os) {
                head_line(os, title, col_width, fill);
            });
        };

        // finally the nice rendered failure closure for diagnostic
        os << hline(" failure diagnostic closure: '" + test_case_name + "' ", col_width, '#')
           << hline(" INPUT ", col_width) << trim_right(test_input)  // input
           << hline(" RESULT ", col_width) << test_result            // output
           << hline("", col_width);                                  // footer
    };

    // if current test fail render closure to console and save test_result to filesystem
    if (!current_test_passing()) {
        if (cli_args::verbose_diagnostic()) {
            BOOST_TEST_MESSAGE(name() << ": save closure");
            // render on terminal
            display_closure(std::cerr);
        }

        // write on filesystem
        fs::path full_pathname = destination_dir / test_case_name;
        full_pathname = full_pathname.replace_extension(output_extension);

        write(full_pathname, test_result);
    }
}

void basic_failure_diagnostic_fixture::failure_closure(std::string test_case_name,
                                                       std::string_view test_input,
                                                       std::string_view test_expected,
                                                       std::string_view test_result)
{
    // render test_input and test_result on stream
    auto const display_closure = [&](std::ostream& os) {
        std::size_t const col_width{ 80 };

        auto hline = [&](std::string const& title, std::size_t col_width, char fill = '~') {
            return make_iomanip([this, &title, col_width, fill](std::ostream& os) {
                head_line(os, title, col_width, fill);
            });
        };

        // finally the nice rendered failure closure for diagnostic
        os << hline(" failure diagnostic closure: '" + test_case_name + "' ", col_width, '#')
           << hline(" INPUT ", col_width) << trim_right(test_input)        // input
           << hline(" EXPECTED ", col_width) << trim_right(test_expected)  // expected
           << hline(" RESULT ", col_width) << test_result                  // output
           << hline("", col_width);                                        // footer
    };

    // if current test fail render closure to console and save test_result to filesystem
    if (!current_test_passing()) {
        if (cli_args::verbose_diagnostic()) {
            BOOST_TEST_MESSAGE(name() << ": save closure");
            // render on terminal
            display_closure(std::cerr);
        }

        // write on filesystem
        fs::path full_pathname = destination_dir / test_case_name;

        full_pathname = full_pathname.replace_extension(input_extension);
        write(full_pathname, test_input);

        full_pathname = full_pathname.replace_extension(expected_extension);
        write(full_pathname, test_expected);

        full_pathname = full_pathname.replace_extension(output_extension);
        write(full_pathname, test_result);
    }
}

}  // namespace testsuite::util

// ---------------------------------------------------------------------------
//
// failure_diagnostic_fixture private (utility) function implementation
//
// ---------------------------------------------------------------------------
namespace testsuite::util {

void basic_failure_diagnostic_fixture::check_args()
{
    //
    // file extension of input files
    //
    if (cli_args::input_extension().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <input_extension> "
                                  << builtin->input_extension());
        input_extension = builtin->input_extension();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <input_extension> "
                                  << cli_args::input_extension());
        input_extension = cli_args::input_extension();
    }

    //
    // file extension of expected files
    //
    if (cli_args::expected_extension().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <expected_extension> "
                                  << builtin->expected_extension());
        expected_extension = builtin->expected_extension();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <expected_extension> "
                                  << cli_args::expected_extension());
        expected_extension = cli_args::expected_extension();
    }

    //
    // output dir for result files
    //
    if (cli_args::destination_dir().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <destination_dir> "
                                  << builtin->destination_dir());
        destination_dir = builtin->destination_dir();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <destination_dir> "
                                  << cli_args::destination_dir());
        destination_dir = cli_args::destination_dir();
    }

    //
    // file extensions for result files
    if (cli_args::output_extension().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <output_extension> "
                                  << builtin->output_extension());
        output_extension = builtin->output_extension();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <output_extension> "
                                  << cli_args::output_extension());
        output_extension = cli_args::output_extension();
    }

    //
    // check post conditions
    //
    if (input_extension.empty()) {
        throw std::logic_error("empty cli parameter <input_extension>");
    }
    if (expected_extension.empty()) {
        throw std::logic_error("empty cli parameter <expected_extension>");
    }
    if (destination_dir.empty()) {
        throw std::logic_error("empty cli parameter <destination_dir>");
    }
    if (output_extension.empty()) {
        throw std::logic_error("empty cli parameter <output_extension>");
    }
}

std::string_view basic_failure_diagnostic_fixture::name() const { return fixture_name; }

void basic_failure_diagnostic_fixture::head_line(std::ostream& os, std::string_view title,
                                                 std::size_t col_width, char fill)
{
    std::size_t const w = (col_width - title.size()) / 2;
    std::string const line(w, fill);
    os << '\n' << line << title << line << '\n';
}

void basic_failure_diagnostic_fixture::write(fs::path const& full_pathname, std::string_view result)
{
    fs::path const write_path = full_pathname.parent_path();

    BOOST_TEST_REQUIRE(create_directories(write_path));
    BOOST_TEST_REQUIRE(write_file(full_pathname, result));
}

bool basic_failure_diagnostic_fixture::create_directories(fs::path const& write_path)
{
    try {
        if (!fs::exists(write_path) || !fs::is_directory(write_path)) {
            BOOST_TEST_MESSAGE(name() << ": create directories " << write_path << '\n');
            BOOST_TEST_REQUIRE(fs::create_directories(write_path));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE(name() << ": creating directory " << write_path << " failed with:\n"
                                  << e.code().message());
        return false;
    }

    return true;
}

bool basic_failure_diagnostic_fixture::write_file(fs::path const& filename,
                                                  std::string_view contents)
{
    BOOST_TEST_MESSAGE(name() << ": Write result to " << filename);
    // remove old result file if exist
    try {
        if (fs::exists(filename)) {
            BOOST_TEST_REQUIRE(fs::remove(filename));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE(name() << ": remove of older result file " << filename
                                  << " failed with:\n"
                                  << e.code().message());
        return false;
    }

    try {
        std::ofstream ofs{ filename };
        ofs << contents;
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE(name() << ": writing to " << filename << " failed with:\n"
                                  << e.code().message());
        return false;
    }

    return true;
}

}  // namespace testsuite::util
