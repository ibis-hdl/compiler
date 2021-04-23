#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/type_definition.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct type_declaration : position_tagged {
    ast::identifier identifier;
    optional<ast::type_definition> type_definition;
};

}  // namespace ibis::vhdl::ast
