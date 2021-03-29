#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/parameter_specification.hpp>
#include <eda/vhdl/ast/node/condition.hpp>

namespace eda::vhdl::ast {

struct generation_scheme : variant<ast::nullary, ast::parameter_specification, ast::condition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
