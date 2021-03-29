#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <eda/vhdl/ast/node/prefix.hpp>

namespace eda::vhdl::ast {

struct slice_name : position_tagged {
    ast::prefix prefix;
    ast::discrete_range discrete_range;
};

}  // namespace eda::vhdl::ast
