#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/component_specification.hpp>
#include <ibis/vhdl/ast/node/binding_indication.hpp>

namespace ibis::vhdl::ast {

struct configuration_specification : position_tagged {
    ast::component_specification component_specification;
    ast::binding_indication binding_indication;
};

}  // namespace ibis::vhdl::ast
