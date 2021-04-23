#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/index_constraint.hpp>
#include <ibis/vhdl/ast/node/range_constraint.hpp>

namespace ibis::vhdl::ast {

struct constraint : variant<nullary, range_constraint, index_constraint> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
