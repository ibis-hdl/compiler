#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/entity_declaration.hpp>
#include <ibis/vhdl/ast/node/configuration_declaration.hpp>
#include <ibis/vhdl/ast/node/package_declaration.hpp>

namespace ibis::vhdl::ast {

struct primary_unit
    : variant<ast::nullary, ast::entity_declaration, ast::configuration_declaration,
              ast::package_declaration> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
