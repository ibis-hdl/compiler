#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier_list.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

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

}  // namespace ibis::vhdl::ast
