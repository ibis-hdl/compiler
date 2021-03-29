#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/procedure_call.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct procedure_call_statement : position_tagged {
    optional<ast::label> label;
    ast::procedure_call procedure_call;
};

}  // namespace eda::vhdl::ast
