#pragma once

#include <testsuite/util/failure_diagnostic_fixture.hpp>

namespace testsuite::vhdl_parser::util {

class failure_diagnostic_fixture : public testsuite::util::failure_diagnostic_fixture {
public:
    ///
    /// @brief override fixture base to override compile time builtin settings.
    ///
    virtual void setup() override;
};

}  // namespace testsuite::vhdl_parser::util