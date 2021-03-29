#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/scalar_type_definition.hpp>
#include <eda/vhdl/ast/node/composite_type_definition.hpp>
#include <eda/vhdl/ast/node/access_type_definition.hpp>
#include <eda/vhdl/ast/node/file_type_definition.hpp>

namespace eda::vhdl::ast {

struct type_definition
    : variant<ast::nullary, ast::scalar_type_definition, ast::composite_type_definition,
              ast::access_type_definition, ast::file_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
