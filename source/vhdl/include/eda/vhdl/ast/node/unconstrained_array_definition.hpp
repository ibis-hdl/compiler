#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/index_subtype_definition.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct unconstrained_array_definition : position_tagged {
    std::vector<ast::index_subtype_definition> index_subtype_definitions;
    ast::subtype_indication element_subtype_indication;
};

}  // namespace eda::vhdl::ast
