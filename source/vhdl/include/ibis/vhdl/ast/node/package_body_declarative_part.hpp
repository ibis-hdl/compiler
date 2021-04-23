#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/subprogram_declaration.hpp>
#include <ibis/vhdl/ast/node/subprogram_body.hpp>
#include <ibis/vhdl/ast/node/type_declaration.hpp>
#include <ibis/vhdl/ast/node/subtype_declaration.hpp>
#include <ibis/vhdl/ast/node/constant_declaration.hpp>
#include <ibis/vhdl/ast/node/variable_declaration.hpp>
#include <ibis/vhdl/ast/node/file_declaration.hpp>
#include <ibis/vhdl/ast/node/alias_declaration.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <ibis/vhdl/ast/node/group_template_declaration.hpp>
#include <ibis/vhdl/ast/node/group_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using package_body_declarative_item =
    variant<ast::nullary, ast::subprogram_declaration, ast::subprogram_body, ast::type_declaration,
            ast::subtype_declaration, ast::constant_declaration,
            ast::variable_declaration,  // shared_variable_declaration
            ast::file_declaration, ast::alias_declaration, ast::use_clause,
            ast::group_template_declaration, ast::group_declaration>;

using package_body_declarative_part = std::vector<ast::package_body_declarative_item>;

}  // namespace ibis::vhdl::ast
