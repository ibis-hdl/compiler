#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/character_literal.hpp>
#include <ibis/vhdl/ast/node/identifier.hpp>

namespace ibis::vhdl::ast {

struct enumeration_literal : variant<nullary, identifier, character_literal> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
