#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/entity_name_list.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

namespace ibis::vhdl::ast {

struct entity_specification : position_tagged {
    ast::entity_name_list entity_name_list;
    ast::keyword_token entity_class;
};

}  // namespace ibis::vhdl::ast
