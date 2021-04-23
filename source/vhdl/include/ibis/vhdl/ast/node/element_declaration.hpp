#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier_list.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>

namespace ibis::vhdl::ast {

struct element_declaration : position_tagged {
    ast::identifier_list identifier_list;
    ast::subtype_indication element_subtype_definition;
};

}  // namespace ibis::vhdl::ast
