#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/entity_declarative_part.hpp>
#include <eda/vhdl/ast/node/entity_header.hpp>
#include <eda/vhdl/ast/node/entity_statement_part.hpp>
#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>

namespace eda::vhdl::ast {

struct entity_declaration : position_tagged {
    ast::identifier identifier;
    ast::entity_header header;
    ast::entity_declarative_part declarative_part;
    optional<ast::entity_statement_part> statement_part;
    optional<ast::simple_name> end_identifier;
};

}  // namespace eda::vhdl::ast
