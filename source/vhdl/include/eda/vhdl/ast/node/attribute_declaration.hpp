#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct attribute_declaration : position_tagged {
    ast::identifier identifier;
    ast::name type_mark;
};

}  // namespace eda::vhdl::ast
