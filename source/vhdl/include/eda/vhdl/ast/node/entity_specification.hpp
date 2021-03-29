#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/entity_name_list.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>

namespace eda::vhdl::ast {

struct entity_specification : position_tagged {
    ast::entity_name_list entity_name_list;
    ast::keyword_token entity_class;
};

}  // namespace eda::vhdl::ast
