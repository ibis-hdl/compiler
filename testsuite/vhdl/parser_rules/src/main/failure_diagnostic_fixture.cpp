#include <testsuite/vhdl_parser/failure_diagnostic_fixture.hpp>
#include <testsuite/util/cli_args.hpp>

#include <boost/test/unit_test.hpp>

#include <testsuite/vhdl_parser/compile_builtin.hpp>

namespace testsuite::vhdl_parser::util {

void failure_diagnostic_fixture::setup()
{
    fixture_name = "vhdl/parser_rules/failure_diagnostic_fixture";

    using testsuite::util::cli_args;

    if (cli_args::destination_dir().empty()) {
        BOOST_TEST_MESSAGE(  // --
            "INFO: <failure_diagnostic_fixture> use compiled builtin destination_dir "
            << testsuite::compile_builtin::default_destination_dir);
        destination_dir = testsuite::compile_builtin::default_destination_dir;
    }
    else {
        BOOST_TEST_MESSAGE(  // --
            "INFO: <failure_diagnostic_fixture> use command line <destination_dir> "
            << cli_args::destination_dir());
        destination_dir = cli_args::destination_dir();
    }

    if (cli_args::output_extension().empty()) {
        BOOST_TEST_MESSAGE(  // --
            "INFO: <failure_diagnostic_fixture> use compiled builtin output_extension "
            << testsuite::compile_builtin::default_output_extension);
        output_extension = testsuite::compile_builtin::default_output_extension;
    }
    else {
        BOOST_TEST_MESSAGE(  // --
            "INFO: <failure_diagnostic_fixture> use command line <output_extension> "
            << cli_args::output_extension());
        output_extension = cli_args::output_extension();
    }

    // post condition
    BOOST_TEST_REQUIRE(!destination_dir.empty());
    BOOST_TEST_REQUIRE(!output_extension.empty());
}

}  // namespace testsuite::vhdl_parser::util
