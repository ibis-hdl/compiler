#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/prefix.hpp>
#include <eda/vhdl/ast/node/suffix.hpp>

namespace eda::vhdl::ast {

struct selected_name : position_tagged {
    ast::prefix prefix;
    ast::suffix suffix;
};

}  // namespace eda::vhdl::ast
