#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/condition.hpp>
#include <ibis/vhdl/ast/node/parameter_specification.hpp>

namespace ibis::vhdl::ast {

struct iteration_scheme : variant<ast::nullary, ast::condition, ast::parameter_specification> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
