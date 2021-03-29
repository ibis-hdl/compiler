#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>  // forward_ast

#include <eda/vhdl/ast/node/actual_parameter_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct name;

struct function_call : position_tagged {
    forward_ast<ast::name> function_name;
    boost::optional<ast::actual_parameter_part> actual_parameter_part;
};

}  // namespace eda::vhdl::ast
