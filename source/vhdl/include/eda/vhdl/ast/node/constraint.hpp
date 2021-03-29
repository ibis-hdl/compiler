#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/index_constraint.hpp>
#include <eda/vhdl/ast/node/range_constraint.hpp>

namespace eda::vhdl::ast {

struct constraint : variant<nullary, range_constraint, index_constraint> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
