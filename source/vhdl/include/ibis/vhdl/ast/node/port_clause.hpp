#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/interface_list.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct port_clause : position_tagged {
    ast::interface_list port_list;
};

}  // namespace ibis::vhdl::ast
