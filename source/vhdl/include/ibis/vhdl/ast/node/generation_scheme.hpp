#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/parameter_specification.hpp>
#include <ibis/vhdl/ast/node/condition.hpp>

namespace ibis::vhdl::ast {

struct generation_scheme : variant<ast::nullary, ast::parameter_specification, ast::condition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
