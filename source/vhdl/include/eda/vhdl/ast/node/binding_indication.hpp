#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/entity_aspect.hpp>
#include <eda/vhdl/ast/node/generic_map_aspect.hpp>
#include <eda/vhdl/ast/node/port_map_aspect.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct binding_indication : position_tagged {
    optional<ast::entity_aspect> entity_aspect;
    ast::generic_map_aspect generic_map_aspect;
    ast::port_map_aspect port_map_aspect;
};

}  // namespace eda::vhdl::ast
