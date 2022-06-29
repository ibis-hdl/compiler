//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <ibis/vhdl/ast/node/simple_expression.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using choice =                  // --
    variant<nullary,            // --
            simple_name,        // --
            discrete_range,     // --
            simple_expression,  // --
            keyword_token       // OTHERS
            >;

using choices = std::vector<choice>;

}  // namespace ibis::vhdl::ast
