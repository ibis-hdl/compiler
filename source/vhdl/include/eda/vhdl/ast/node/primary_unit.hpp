#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/entity_declaration.hpp>
#include <eda/vhdl/ast/node/configuration_declaration.hpp>
#include <eda/vhdl/ast/node/package_declaration.hpp>

namespace eda::vhdl::ast {

struct primary_unit
    : variant<ast::nullary, ast::entity_declaration, ast::configuration_declaration,
              ast::package_declaration> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
