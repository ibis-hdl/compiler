#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/primary_unit.hpp>
#include <eda/vhdl/ast/node/secondary_unit.hpp>

namespace eda::vhdl::ast {

using library_unit = variant<ast::nullary, ast::primary_unit, ast::secondary_unit>;

}
