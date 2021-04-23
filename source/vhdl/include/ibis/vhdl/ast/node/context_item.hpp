#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/library_clause.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>

namespace ibis::vhdl::ast {

using context_item = variant<ast::nullary, ast::library_clause, ast::use_clause>;

}
