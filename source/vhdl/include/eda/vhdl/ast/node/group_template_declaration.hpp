#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/entity_class_entry_list.hpp>

namespace eda::vhdl::ast {

struct group_template_declaration : position_tagged {
    ast::identifier identifier;
    ast::entity_class_entry_list entity_class_entry_list;
};

}  // namespace eda::vhdl::ast
