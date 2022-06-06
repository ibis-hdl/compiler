//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/waveform.hpp>
#include <ibis/vhdl/ast/node/choices.hpp>
#include <vector>

namespace ibis::vhdl::ast {

// Non-BNF, artificial element for selected_waveforms
struct selected_waveform : position_tagged {
    ast::waveform waveform;
    ast::choices choices;
};

struct selected_waveforms : std::vector<selected_waveform> {};

}  // namespace ibis::vhdl::ast
