#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>

namespace eda::vhdl::ast {

struct element_declaration : position_tagged {
    ast::identifier_list identifier_list;
    ast::subtype_indication element_subtype_definition;
};

}  // namespace eda::vhdl::ast
