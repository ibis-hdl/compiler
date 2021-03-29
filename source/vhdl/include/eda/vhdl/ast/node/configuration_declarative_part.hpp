#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/attribute_specification.hpp>
#include <eda/vhdl/ast/node/group_declaration.hpp>
#include <vector>

namespace eda::vhdl::ast {

using configuration_declarative_item =     // --
    variant<ast::nullary,                  // --
            ast::use_clause,               // --
            ast::attribute_specification,  // --
            ast::group_declaration         // --
            >;

struct configuration_declarative_part : std::vector<ast::configuration_declarative_item> {
};

}  // namespace eda::vhdl::ast
