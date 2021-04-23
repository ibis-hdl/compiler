#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/node/entity_specification.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>

namespace ibis::vhdl::ast {

struct attribute_specification : position_tagged {
    ast::simple_name attribute_designator;
    ast::entity_specification entity_specification;
    ast::expression expression;
};

}  // namespace ibis::vhdl::ast
