#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/generic_clause.hpp>
#include <eda/vhdl/ast/node/port_clause.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct entity_header : position_tagged {
    optional<ast::generic_clause> formal_generic_clause;
    optional<ast::port_clause> formal_port_clause;
};

}  // namespace eda::vhdl::ast
