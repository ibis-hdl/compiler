#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/block_configuration.hpp>
#include <ibis/vhdl/ast/node/configuration_declarative_part.hpp>
#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct configuration_declaration : position_tagged {
    ast::identifier identifier;
    ast::name entity_name;
    ast::configuration_declarative_part declarative_part;
    ast::block_configuration block_configuration;
    optional<ast::identifier> end_identifier;
};

}  // namespace ibis::vhdl::ast
