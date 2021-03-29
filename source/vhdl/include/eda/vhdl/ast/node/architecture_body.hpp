#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/architecture_declarative_part.hpp>
#include <eda/vhdl/ast/node/architecture_statement_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct architecture_body : position_tagged {
    ast::identifier identifier;
    ast::name entity_name;
    ast::architecture_declarative_part declarative_part;
    ast::architecture_statement_part statement_part;
    optional<ast::identifier> end_identifier;
};

}  // namespace eda::vhdl::ast
