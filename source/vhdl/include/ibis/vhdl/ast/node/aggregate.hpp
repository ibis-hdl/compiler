#pragma once

#include <ibis/vhdl/ast/node/element_association.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct aggregate : std::vector<ast::element_association> {
};

}  // namespace ibis::vhdl::ast
