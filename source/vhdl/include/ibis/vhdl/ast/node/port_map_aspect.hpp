#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/association_list.hpp>

namespace ibis::vhdl::ast {

struct port_map_aspect : position_tagged {
    ast::association_list association_list;
};

}  // namespace ibis::vhdl::ast
