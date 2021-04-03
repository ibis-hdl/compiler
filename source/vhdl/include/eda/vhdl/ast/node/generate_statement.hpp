#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/block_declarative_part.hpp>
#include <eda/vhdl/ast/node/generation_scheme.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct concurrent_statement;  // forward due to cyclic dependency

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph generate_statement  {
///  concurrent_statement -> generate_statement;
///  generate_statement   -> concurrent_statement [ label=<<i>forward</i>>];
/// }
/// \enddot
///
struct generate_statement : position_tagged {
    ast::label label;
    ast::generation_scheme generation_scheme;
    ast::block_declarative_part block_declarative_parts;  // { block_declarative_item }
    std::vector<ast::concurrent_statement> concurrent_statements;
    optional<ast::label> end_label;
};

}  // namespace eda::vhdl::ast
