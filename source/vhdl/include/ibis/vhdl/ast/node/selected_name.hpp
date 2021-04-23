#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/prefix.hpp>
#include <ibis/vhdl/ast/node/suffix.hpp>

namespace ibis::vhdl::ast {

struct selected_name : position_tagged {
    ast::prefix prefix;
    ast::suffix suffix;
};

}  // namespace ibis::vhdl::ast
