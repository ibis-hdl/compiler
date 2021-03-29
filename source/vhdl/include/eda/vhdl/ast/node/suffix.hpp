#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/character_literal.hpp>
#include <eda/vhdl/ast/node/operator_symbol.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>

namespace eda::vhdl::ast {

struct suffix : variant<nullary, simple_name, character_literal, operator_symbol, keyword_token> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
