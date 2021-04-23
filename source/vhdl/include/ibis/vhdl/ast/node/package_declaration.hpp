#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/package_declarative_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct package_declaration : position_tagged {
    ast::identifier identifier;
    ast::package_declarative_part declarative_part;
    optional<ast::identifier> end_identifier;
};

}  // namespace ibis::vhdl::ast
