#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/alias_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_specification.hpp>
#include <ibis/vhdl/ast/node/component_declaration.hpp>
#include <ibis/vhdl/ast/node/configuration_specification.hpp>
#include <ibis/vhdl/ast/node/constant_declaration.hpp>
#include <ibis/vhdl/ast/node/disconnection_specification.hpp>
#include <ibis/vhdl/ast/node/file_declaration.hpp>
#include <ibis/vhdl/ast/node/group_declaration.hpp>
#include <ibis/vhdl/ast/node/group_template_declaration.hpp>
#include <ibis/vhdl/ast/node/variable_declaration.hpp>
#include <ibis/vhdl/ast/node/signal_declaration.hpp>
#include <ibis/vhdl/ast/node/subprogram_body.hpp>
#include <ibis/vhdl/ast/node/subprogram_declaration.hpp>
#include <ibis/vhdl/ast/node/subtype_declaration.hpp>
#include <ibis/vhdl/ast/node/type_declaration.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using block_declarative_item =                 // --
    variant<ast::nullary,                      // --
            ast::alias_declaration,            // --
            ast::attribute_declaration,        // --
            ast::attribute_specification,      // --
            ast::component_declaration,        // --
            ast::configuration_specification,  // --
            ast::constant_declaration,         // --
            ast::disconnection_specification,  // --
            ast::file_declaration,             // --
            ast::group_declaration,            // --
            ast::group_template_declaration,   // --
            ast::variable_declaration,         // shared_variable_declaration
            ast::signal_declaration,           // --
            ast::subprogram_body,              // --
            ast::subprogram_declaration,       // --
            ast::subtype_declaration,          // --
            ast::type_declaration,             // --
            ast::use_clause                    // --
            >;

using block_declarative_part = std::vector<ast::block_declarative_item>;

}  // namespace ibis::vhdl::ast
