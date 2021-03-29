#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/primary_unit_declaration.hpp>
#include <eda/vhdl/ast/node/range_constraint.hpp>
#include <eda/vhdl/ast/node/secondary_unit_declaration.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct physical_type_definition : position_tagged {
    ast::range_constraint range_constraint;
    ast::primary_unit_declaration primary_unit_declaration;
    std::vector<ast::secondary_unit_declaration> secondary_unit_declarations;
    optional<ast::simple_name> physical_type_simple_name;
};

}  // namespace eda::vhdl::ast
