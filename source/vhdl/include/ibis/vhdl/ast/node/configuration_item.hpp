//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct block_configuration;
struct component_configuration;

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph component_configuration  {
///  component_configuration -> block_configuration;
///  block_configuration     -> configuration_item;
///  configuration_item      -> component_configuration;
///  configuration_item      -> block_configuration [ label=<<i>forward</i>>];
/// }
/// \enddot
///
using configuration_item = variant<ast::nullary, forward_ast<ast::block_configuration>,
                                   forward_ast<ast::component_configuration> >;

}  // namespace ibis::vhdl::ast
