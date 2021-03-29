#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct index_subtype_definition : position_tagged {
    ast::name type_mark;
};

}  // namespace eda::vhdl::ast
