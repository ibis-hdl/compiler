#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/group_constituent_list.hpp>

namespace eda::vhdl::ast {

struct group_declaration : position_tagged {
    ast::identifier identifier;
    ast::name group_template_name;
    ast::group_constituent_list group_constituent_list;
};

}  // namespace eda::vhdl::ast
