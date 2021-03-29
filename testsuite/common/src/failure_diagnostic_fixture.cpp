#include <testsuite/common/failure_diagnostic_fixture.hpp>
#include <testsuite/common/cli_args.hpp>
#include <testsuite/common/compile_builtin.hpp>

#include <testsuite/common/namespace_alias.hpp>  // IWYU pragma: keep

#include <eda/util/make_iomanip.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <sstream>
#include <system_error>

namespace testsuite {

///
/// @brief Write the parsed result into file
///
/// FixMe: written to fs::path(destination_dir) / "test_case" / testcase_name;
///
/// @todo Make the path to the destination/write folder configurable, also
/// the file extension for the result.
///
class failure_diagnostic_fixture::writer {
public:
    ///
    /// @brief Construct a new writer object
    ///
    /// @param name is the prefixed name for printing messages.
    ///
    writer(std::string_view name)
        : writer_name{ name }
    {
    }

    ///
    /// @brief Member function to write the contents of result
    /// into filesystem.
    ///
    /// @param full_pathname holds the path/filename to write to
    /// @param result holds the data to be written.
    ///
    void write(fs::path const& full_pathname, std::string_view result);

private:
    ///
    /// @brief Create a directory object
    ///
    /// @param write_path for the file to write. If the path doesn't exist
    /// it is created.
    /// @return true on success, directory does exist or is created successfull.
    /// @return false on failure on creating the directory.
    ///
    bool create_directories(fs::path const& write_path);

    ///
    /// @brief Write the contents into file.
    ///
    /// If a file with the same name exist it will be removed from
    /// filesstem and new created.
    ///
    /// @param filename is the name of the file to be written.
    /// @param contents to be written.
    /// @return true if successfully written.
    /// @return false on failure.
    ///
    bool write_file(fs::path const& filename, std::string_view contents);

private:
    std::string_view const writer_name;
};

}  // namespace testsuite

/// ---------------------------------------------------------------------------
///
/// failure_diagnostic_fixture implementation
///
/// ---------------------------------------------------------------------------
namespace testsuite {

void failure_diagnostic_fixture::setup()
{
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
            using eda::util::make_iomanip;
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

        failure_diagnostic_fixture::writer writer{ fixture_name };
        writer.write(full_pathname, test_result);
    }
}

}  // namespace testsuite

/// ---------------------------------------------------------------------------
///
/// failure_diagnostic_fixture::writer implementation
///
/// ---------------------------------------------------------------------------
using testsuite::cli_args;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_TEST_GLOBAL_FIXTURE(cli_args);

namespace testsuite {

void failure_diagnostic_fixture::writer::write(fs::path const& full_pathname,
                                               std::string_view result)
{
    fs::path const write_path = full_pathname.parent_path();

    BOOST_TEST_REQUIRE(create_directories(write_path));
    BOOST_TEST_REQUIRE(write_file(full_pathname, result));
}

bool failure_diagnostic_fixture::writer::create_directories(fs::path const& write_path)
{
    try {
        if (!fs::exists(write_path) || !fs::is_directory(write_path)) {
            BOOST_TEST_MESSAGE("INFO(" << writer_name << ") create directories " << write_path
                                       << '\n');
            BOOST_TEST_REQUIRE(fs::create_directories(write_path));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << writer_name << ") creating directory " << write_path
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    return true;
}

bool failure_diagnostic_fixture::writer::write_file(fs::path const& filename,
                                                    std::string_view contents)
{
    BOOST_TEST_MESSAGE("INFO(" << writer_name << ") Write result to " << filename);
    // remove old result file if exist
    try {
        if (fs::exists(filename)) {
            BOOST_TEST_REQUIRE(fs::remove(filename));
        }
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << writer_name << ") remove of older result file " << filename
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    try {
        std::ofstream ofs{ filename };
        ofs << contents;
    }
    catch (fs::filesystem_error const& e) {
        BOOST_TEST_MESSAGE("ERROR(" << writer_name << ") writing to " << filename
                                    << " failed with:\n"
                                    << e.code().message());
        return false;
    }

    return true;
}

}  // namespace testsuite
