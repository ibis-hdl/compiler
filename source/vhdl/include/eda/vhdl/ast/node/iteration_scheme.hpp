#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/condition.hpp>
#include <eda/vhdl/ast/node/parameter_specification.hpp>

namespace eda::vhdl::ast {

struct iteration_scheme : variant<ast::nullary, ast::condition, ast::parameter_specification> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
