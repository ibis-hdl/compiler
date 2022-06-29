//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/subprogram_declaration.hpp>
#include <ibis/vhdl/ast/node/type_declaration.hpp>
#include <ibis/vhdl/ast/node/subtype_declaration.hpp>
#include <ibis/vhdl/ast/node/constant_declaration.hpp>
#include <ibis/vhdl/ast/node/signal_declaration.hpp>
#include <ibis/vhdl/ast/node/variable_declaration.hpp>
#include <ibis/vhdl/ast/node/file_declaration.hpp>
#include <ibis/vhdl/ast/node/alias_declaration.hpp>
#include <ibis/vhdl/ast/node/component_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_specification.hpp>
#include <ibis/vhdl/ast/node/disconnection_specification.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <ibis/vhdl/ast/node/group_template_declaration.hpp>
#include <ibis/vhdl/ast/node/group_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using package_declarative_item =
    variant<ast::nullary, ast::subprogram_declaration, ast::type_declaration,
            ast::subtype_declaration, ast::constant_declaration, ast::signal_declaration,
            ast::variable_declaration,  // shared_variable_declaration
            ast::file_declaration, ast::alias_declaration, ast::component_declaration,
            ast::attribute_declaration, ast::attribute_specification,
            ast::disconnection_specification, ast::use_clause, ast::group_template_declaration,
            ast::group_declaration>;

using package_declarative_part = std::vector<ast::package_declarative_item>;

}  // namespace ibis::vhdl::ast
