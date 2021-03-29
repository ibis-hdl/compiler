#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/node/character_literal.hpp>
#include <eda/vhdl/ast/node/operator_symbol.hpp>

namespace eda::vhdl::ast {

using entity_tag = variant<nullary, simple_name, character_literal, operator_symbol>;

}
