#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/generic_clause.hpp>
#include <ibis/vhdl/ast/node/port_clause.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct component_declaration : position_tagged {
    ast::identifier identifier;
    optional<ast::generic_clause> local_generic_clause;
    optional<ast::port_clause> local_port_clause;
    optional<ast::simple_name> name;
};

}  // namespace ibis::vhdl::ast
