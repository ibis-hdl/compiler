//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/delay_mechanism.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct options : position_tagged {
    bool guarded;
    optional<ast::delay_mechanism> delay_mechanism;

    options()
        : guarded{}
    {
    }
};

}  // namespace ibis::vhdl::ast
