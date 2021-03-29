#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct interface_variable_declaration : position_tagged {
    bool VARIABLE;
    ast::identifier_list identifier_list;
    optional<ast::keyword_token> mode;
    ast::subtype_indication subtype_indication;
    optional<ast::expression> static_expression;

    interface_variable_declaration()
        : VARIABLE{}
    {
    }
};

}  // namespace eda::vhdl::ast
