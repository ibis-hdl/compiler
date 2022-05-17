#pragma once

#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct entity_class_entry_list : std::vector<ast::keyword_token> {};

}  // namespace ibis::vhdl::ast
