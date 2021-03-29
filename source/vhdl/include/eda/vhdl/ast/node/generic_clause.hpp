#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/interface_list.hpp>

namespace eda::vhdl::ast {

struct generic_clause : position_tagged {
    ast::interface_list generic_list;
};

}  // namespace eda::vhdl::ast
