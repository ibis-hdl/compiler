#include <testsuite/vhdl/syntax/failure_diagnostic_fixture.hpp>

namespace testsuite::vhdl::syntax {

void failure_diagnostic_fixture::setup()
{
    set_name("vhdl/syntax/failure_diagnostic_fixture");

    set_builtin(std::make_unique<failure_diagnostic_fixture::compile_builtin>());
}

}  // namespace testsuite::vhdl::syntax
