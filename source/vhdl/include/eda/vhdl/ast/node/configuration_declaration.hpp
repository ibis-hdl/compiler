#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/block_configuration.hpp>
#include <eda/vhdl/ast/node/configuration_declarative_part.hpp>
#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct configuration_declaration : position_tagged {
    ast::identifier identifier;
    ast::name entity_name;
    ast::configuration_declarative_part declarative_part;
    ast::block_configuration block_configuration;
    optional<ast::identifier> end_identifier;
};

}  // namespace eda::vhdl::ast
