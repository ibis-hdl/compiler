#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/index_constraint.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>

namespace eda::vhdl::ast {

struct constrained_array_definition : position_tagged {
    ast::index_constraint index_constraint;
    ast::subtype_indication element_subtype_indication;
};

}  // namespace eda::vhdl::ast
