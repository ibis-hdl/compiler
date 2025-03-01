//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/syntax/dataset.hpp>
#include <testsuite/util/dataset_loader.hpp>

#include <string_view>
#include <memory>

namespace testsuite::vhdl::syntax {

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

}  // namespace testsuite::vhdl::syntax
