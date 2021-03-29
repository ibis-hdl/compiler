#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/discrete_range.hpp>

namespace eda::vhdl::ast {

struct parameter_specification : position_tagged {
    ast::identifier identifier;
    ast::discrete_range discrete_range;
};

}  // namespace eda::vhdl::ast
