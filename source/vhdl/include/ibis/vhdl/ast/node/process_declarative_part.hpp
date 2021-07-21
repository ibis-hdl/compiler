#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/alias_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_declaration.hpp>
#include <ibis/vhdl/ast/node/attribute_specification.hpp>
#include <ibis/vhdl/ast/node/constant_declaration.hpp>
#include <ibis/vhdl/ast/node/file_declaration.hpp>
#include <ibis/vhdl/ast/node/group_declaration.hpp>
#include <ibis/vhdl/ast/node/group_template_declaration.hpp>
#include <ibis/vhdl/ast/node/subprogram_body.hpp>
#include <ibis/vhdl/ast/node/subprogram_declaration.hpp>
#include <ibis/vhdl/ast/node/subtype_declaration.hpp>
#include <ibis/vhdl/ast/node/type_declaration.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <ibis/vhdl/ast/node/variable_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using process_declarative_item =
    variant<nullary, alias_declaration, attribute_declaration, attribute_specification,
            constant_declaration, file_declaration, group_declaration, group_template_declaration,
            subprogram_body, subprogram_declaration, subtype_declaration, type_declaration,
            use_clause, variable_declaration>;

using process_declarative_part = std::vector<ast::process_declarative_item>;

}  // namespace ibis::vhdl::ast
