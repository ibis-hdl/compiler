#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/component_specification.hpp>
#include <eda/vhdl/ast/node/binding_indication.hpp>
#include <eda/vhdl/ast/node/block_configuration.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct component_configuration : position_tagged {
    ast::component_specification component_specification;
    optional<ast::binding_indication> binding_indication;
    optional<ast::block_configuration> block_configuration;
};

}  // namespace eda::vhdl::ast
