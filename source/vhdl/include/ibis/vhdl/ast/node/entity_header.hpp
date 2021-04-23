#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/generic_clause.hpp>
#include <ibis/vhdl/ast/node/port_clause.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct entity_header : position_tagged {
    optional<ast::generic_clause> formal_generic_clause;
    optional<ast::port_clause> formal_port_clause;
};

}  // namespace ibis::vhdl::ast
