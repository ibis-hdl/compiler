#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/character_literal.hpp>
#include <eda/vhdl/ast/node/operator_symbol.hpp>

namespace eda::vhdl::ast {

struct alias_designator : variant<nullary, identifier, character_literal, operator_symbol> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
