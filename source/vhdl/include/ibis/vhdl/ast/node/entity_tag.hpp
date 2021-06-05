#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/node/character_literal.hpp>
#include <ibis/vhdl/ast/node/operator_symbol.hpp>

namespace ibis::vhdl::ast {

using entity_tag = variant<nullary, simple_name, character_literal, operator_symbol>;

}