#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/component_specification.hpp>
#include <eda/vhdl/ast/node/binding_indication.hpp>

namespace eda::vhdl::ast {

struct configuration_specification : position_tagged {
    ast::component_specification component_specification;
    ast::binding_indication binding_indication;
};

}  // namespace eda::vhdl::ast
