#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/interface_list.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct port_clause : position_tagged {
    ast::interface_list port_list;
};

}  // namespace eda::vhdl::ast
