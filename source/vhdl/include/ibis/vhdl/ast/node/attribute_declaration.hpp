#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct attribute_declaration : position_tagged {
    ast::identifier identifier;
    ast::name type_mark;
};

}  // namespace ibis::vhdl::ast
