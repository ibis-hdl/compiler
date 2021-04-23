#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/instantiation_list.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct component_specification : position_tagged {
    ast::instantiation_list instantiation_list;
    ast::name component_name;
};

}  // namespace ibis::vhdl::ast
