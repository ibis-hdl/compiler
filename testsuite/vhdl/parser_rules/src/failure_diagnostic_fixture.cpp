#include <testsuite/vhdl/parser/failure_diagnostic_fixture.hpp>

namespace testsuite::vhdl::parser {

void failure_diagnostic_fixture::setup()
{
    set_name("vhdl/parser_rules/failure_diagnostic_fixture");

    set_builtin(std::make_unique<failure_diagnostic_fixture::compile_builtin>());
}

}  // namespace testsuite::vhdl::parser
