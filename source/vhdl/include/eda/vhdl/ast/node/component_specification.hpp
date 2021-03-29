#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/instantiation_list.hpp>
#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct component_specification : position_tagged {
    ast::instantiation_list instantiation_list;
    ast::name component_name;
};

}  // namespace eda::vhdl::ast
