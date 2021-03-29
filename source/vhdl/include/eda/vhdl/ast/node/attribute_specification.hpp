#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/node/entity_specification.hpp>
#include <eda/vhdl/ast/node/expression.hpp>

namespace eda::vhdl::ast {

struct attribute_specification : position_tagged {
    ast::simple_name attribute_designator;
    ast::entity_specification entity_specification;
    ast::expression expression;
};

}  // namespace eda::vhdl::ast
