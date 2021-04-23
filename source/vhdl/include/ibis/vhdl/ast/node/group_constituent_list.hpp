#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/character_literal.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using group_constituent = variant<ast::nullary, ast::name, ast::character_literal>;

using group_constituent_list = std::vector<ast::group_constituent>;

}  // namespace ibis::vhdl::ast
