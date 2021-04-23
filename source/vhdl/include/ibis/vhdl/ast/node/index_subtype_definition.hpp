#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct index_subtype_definition : position_tagged {
    ast::name type_mark;
};

}  // namespace ibis::vhdl::ast
