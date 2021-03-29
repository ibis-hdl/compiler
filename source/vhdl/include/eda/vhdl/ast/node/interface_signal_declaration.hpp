#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct interface_signal_declaration : position_tagged {
    bool signal;
    ast::identifier_list identifier_list;
    optional<ast::keyword_token> mode;
    ast::subtype_indication subtype_indication;
    bool bus;
    optional<ast::expression> static_expression;

    interface_signal_declaration()
        : signal{}
        , bus{}
    {
    }
};

}  // namespace eda::vhdl::ast
