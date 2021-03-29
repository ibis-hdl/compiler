#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/alias_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_specification.hpp>
#include <eda/vhdl/ast/node/constant_declaration.hpp>
#include <eda/vhdl/ast/node/disconnection_specification.hpp>
#include <eda/vhdl/ast/node/file_declaration.hpp>
#include <eda/vhdl/ast/node/group_declaration.hpp>
#include <eda/vhdl/ast/node/group_template_declaration.hpp>
#include <eda/vhdl/ast/node/signal_declaration.hpp>
#include <eda/vhdl/ast/node/subprogram_body.hpp>
#include <eda/vhdl/ast/node/subprogram_declaration.hpp>
#include <eda/vhdl/ast/node/subtype_declaration.hpp>
#include <eda/vhdl/ast/node/type_declaration.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/variable_declaration.hpp>
#include <vector>

namespace eda::vhdl::ast {

using entity_declarative_item =
    variant<nullary, alias_declaration, attribute_declaration, attribute_specification,
            constant_declaration, disconnection_specification, file_declaration, group_declaration,
            group_template_declaration,
            variable_declaration,  // shared_variable_declaration
            signal_declaration, subprogram_body, subprogram_declaration, subtype_declaration,
            type_declaration, use_clause>;

struct entity_declarative_part : std::vector<ast::entity_declarative_item> {
};

}  // namespace eda::vhdl::ast
