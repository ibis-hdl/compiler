//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/target.hpp>
#include <ibis/vhdl/ast/node/options.hpp>
#include <ibis/vhdl/ast/node/conditional_waveforms.hpp>

namespace ibis::vhdl::ast {

struct conditional_signal_assignment : position_tagged {
    ast::target target;
    ast::options options;
    ast::conditional_waveforms conditional_waveforms;
};

}  // namespace ibis::vhdl::ast
