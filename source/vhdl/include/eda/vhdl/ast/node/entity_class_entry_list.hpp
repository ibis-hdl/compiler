#pragma once

#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct entity_class_entry_list : std::vector<ast::keyword_token> {
};

}  // namespace eda::vhdl::ast
