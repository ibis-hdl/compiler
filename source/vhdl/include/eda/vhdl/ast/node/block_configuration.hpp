#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/block_specification.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
#include <eda/vhdl/ast/node/configuration_item.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct block_configuration : position_tagged {
    ast::block_specification block_specification;
    std::vector<ast::use_clause> use_clause_list;
    std::vector<ast::configuration_item> configuration_item_list;
};

}  // namespace eda::vhdl::ast
