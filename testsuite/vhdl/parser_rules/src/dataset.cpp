//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/parser/dataset.hpp>
#include <testsuite/util/cli_args.hpp>

#include <testsuite/namespace_alias.hpp>

namespace testsuite::vhdl::parser {

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
dataset::~dataset() = default;

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
dataset::compile_builtin::~compile_builtin() = default;

dataset::dataset(std::string_view testcase_group)
    : testsuite::util::dataset_loader(testcase_group)
{
    set_builtin(std::make_unique<dataset::compile_builtin>());
}

}  // namespace testsuite::vhdl::parser
