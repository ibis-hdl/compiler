#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/subtype_indication.hpp>

namespace eda::vhdl::ast {

struct access_type_definition : position_tagged {
    ast::subtype_indication subtype_indication;
};

}  // namespace eda::vhdl::ast
