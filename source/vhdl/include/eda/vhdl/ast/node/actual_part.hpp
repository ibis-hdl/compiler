#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/actual_designator.hpp>

namespace eda::vhdl::ast {

struct name;

struct actual_part_chunk {
    forward_ast<ast::name> context_tied_name;  // function_name | type_mark(name)
    ast::actual_designator actual_designator;
};

using actual_part = variant<actual_designator, actual_part_chunk>;

}  // namespace eda::vhdl::ast
