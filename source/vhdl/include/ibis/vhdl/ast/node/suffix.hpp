//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/character_literal.hpp>
#include <ibis/vhdl/ast/node/operator_symbol.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>

namespace ibis::vhdl::ast {

struct suffix : variant<nullary, simple_name, character_literal, operator_symbol, keyword_token> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
