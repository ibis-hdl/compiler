//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <testsuite/util/basic_failure_diagnostic_fixture.hpp>

namespace testsuite {

class failure_diagnostic_fixture : public testsuite::util::basic_failure_diagnostic_fixture {
public:
    ///
    /// @brief override fixture base to override compile time builtin settings.
    ///
    void setup() override;

private:
    struct compile_builtin : testsuite::util::basic_failure_diagnostic_fixture::compile_builtin {
        compile_builtin() = default;
        ~compile_builtin() override = default;

        compile_builtin(compile_builtin&) = delete;
        compile_builtin(compile_builtin&&) = delete;
        compile_builtin operator=(compile_builtin&) = delete;
        compile_builtin operator=(compile_builtin&&) = delete;

        std::string_view input_extension() const override;
        std::string_view expected_extension() const override;

        std::string_view destination_dir() const override;
        std::string_view output_extension() const override;
    };
};

}  // namespace testsuite
