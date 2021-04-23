#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/actual_part.hpp>
#include <ibis/vhdl/ast/node/formal_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct association_element : position_tagged {
    optional<ast::formal_part> formal_part;
    ast::actual_part actual_part;
};

}  // namespace ibis::vhdl::ast
