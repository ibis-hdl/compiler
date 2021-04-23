#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/identifier_list.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct interface_constant_declaration : position_tagged {
    bool constant;
    ast::identifier_list identifier_list;
    bool in;
    ast::subtype_indication subtype_indication;
    optional<ast::expression> static_expression;

    interface_constant_declaration()
        : constant{}
        , in{}
    {
    }
};

}  // namespace ibis::vhdl::ast
