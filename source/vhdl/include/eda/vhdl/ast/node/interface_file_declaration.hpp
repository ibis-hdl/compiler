#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier_list.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>

namespace eda::vhdl::ast {

struct interface_file_declaration : position_tagged {
    ast::identifier_list identifier_list;
    ast::subtype_indication subtype_indication;
};

}  // namespace eda::vhdl::ast
