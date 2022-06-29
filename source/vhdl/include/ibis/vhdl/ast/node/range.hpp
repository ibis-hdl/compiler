//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/attribute_name.hpp>
#include <ibis/vhdl/ast/node/simple_expression.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

namespace ibis::vhdl::ast {

using range_attribute_name = ast::attribute_name;

struct range_expression : position_tagged {
    ast::simple_expression lhs;
    ast::keyword_token direction;
    ast::simple_expression rhs;
};

struct range : variant<range_attribute_name, range_expression> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
