//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/grammar/failure_diagnostic_fixture.hpp>

namespace testsuite {

void failure_diagnostic_fixture::setup()
{
    set_name("vhdl/grammar/failure_diagnostic_fixture");

    set_builtin(std::make_unique<failure_diagnostic_fixture::compile_builtin>());
}

}  // namespace testsuite