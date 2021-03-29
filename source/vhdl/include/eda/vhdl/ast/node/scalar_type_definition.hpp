#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/enumeration_type_definition.hpp>
#include <eda/vhdl/ast/node/range_constraint.hpp>
#include <eda/vhdl/ast/node/physical_type_definition.hpp>

namespace eda::vhdl::ast {

struct scalar_type_definition
    : variant<ast::nullary, ast::enumeration_type_definition,
              ast::range_constraint,  // {integer,floating}_type_definition
              ast::physical_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
