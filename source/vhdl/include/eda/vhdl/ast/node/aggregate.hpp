#pragma once

#include <eda/vhdl/ast/node/element_association.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct aggregate : std::vector<ast::element_association> {
};

}  // namespace eda::vhdl::ast
