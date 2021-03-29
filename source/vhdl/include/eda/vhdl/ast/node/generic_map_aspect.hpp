#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/association_list.hpp>

namespace eda::vhdl::ast {

struct generic_map_aspect : position_tagged {
    ast::association_list association_list;
};

}  // namespace eda::vhdl::ast
