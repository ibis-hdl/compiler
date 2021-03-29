#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/character_literal.hpp>
#include <vector>

namespace eda::vhdl::ast {

using group_constituent = variant<ast::nullary, ast::name, ast::character_literal>;

using group_constituent_list = std::vector<ast::group_constituent>;

}  // namespace eda::vhdl::ast
