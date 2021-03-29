#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/library_clause.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>

namespace eda::vhdl::ast {

using context_item = variant<ast::nullary, ast::library_clause, ast::use_clause>;

}
