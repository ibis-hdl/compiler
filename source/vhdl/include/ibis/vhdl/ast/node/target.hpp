#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/aggregate.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct target : variant<nullary, name, aggregate> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
