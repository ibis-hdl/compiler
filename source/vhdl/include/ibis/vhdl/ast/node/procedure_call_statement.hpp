#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/procedure_call.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct procedure_call_statement : position_tagged {
    optional<ast::label> label;
    ast::procedure_call procedure_call;
};

}  // namespace ibis::vhdl::ast
