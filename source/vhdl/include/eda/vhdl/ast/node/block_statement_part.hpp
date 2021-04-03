#pragma once

#include <vector>

namespace eda::vhdl::ast {

struct concurrent_statement;  // forward due to cyclic dependency

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph concurrent_statement  {
///  concurrent_statement -> block_statement;
///  block_statement      -> block_statement_part;
///  block_statement_part -> concurrent_statement [label=<<i>forward</i>>];
/// }
/// \enddot
///
struct block_statement_part : std::vector<ast::concurrent_statement> {
};

}  // namespace eda::vhdl::ast
