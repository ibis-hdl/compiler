//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>  // forward_ast

#include <ibis/vhdl/ast/node/actual_parameter_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct name;

struct function_call : position_tagged {
    forward_ast<ast::name> function_name;
    boost::optional<ast::actual_parameter_part> actual_parameter_part;
};

}  // namespace ibis::vhdl::ast
