#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/entity_class_entry_list.hpp>

namespace ibis::vhdl::ast {

struct group_template_declaration : position_tagged {
    ast::identifier identifier;
    ast::entity_class_entry_list entity_class_entry_list;
};

}  // namespace ibis::vhdl::ast
