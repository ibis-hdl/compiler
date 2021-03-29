#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/procedure_call.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct concurrent_procedure_call_statement : position_tagged {
    optional<ast::label> label;
    bool postponed;
    ast::procedure_call procedure_call;

    concurrent_procedure_call_statement()
        : postponed{}
    {
    }
};

}  // namespace eda::vhdl::ast
