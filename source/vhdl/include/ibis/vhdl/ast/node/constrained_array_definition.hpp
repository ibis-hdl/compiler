#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/index_constraint.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>

namespace ibis::vhdl::ast {

struct constrained_array_definition : position_tagged {
    ast::index_constraint index_constraint;
    ast::subtype_indication element_subtype_indication;
};

}  // namespace ibis::vhdl::ast
