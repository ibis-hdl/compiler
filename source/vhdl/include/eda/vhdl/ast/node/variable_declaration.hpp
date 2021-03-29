#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct variable_declaration : position_tagged {
    bool shared;
    ast::identifier_list identifier_list;
    ast::subtype_indication subtype_indication;
    optional<ast::expression> expression;

    variable_declaration()
        : shared{}
    {
    }
};

}  // namespace eda::vhdl::ast
