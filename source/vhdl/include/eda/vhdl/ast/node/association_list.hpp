#pragma once

#include <eda/vhdl/ast/node/association_element.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct association_list : std::vector<ast::association_element> {
};

}  // namespace eda::vhdl::ast
