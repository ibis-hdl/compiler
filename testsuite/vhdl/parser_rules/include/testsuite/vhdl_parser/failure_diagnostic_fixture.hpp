#pragma once

#include <testsuite/common/failure_diagnostic_fixture.hpp>

namespace testsuite::vhdl_parser::util {

class failure_diagnostic_fixture : public testsuite::failure_diagnostic_fixture {
public:
    ///
    /// @brief override ficture base to override compile time builtin settings.
    ///
    virtual void setup() override;
};

}  // namespace testsuite::vhdl_parser::util