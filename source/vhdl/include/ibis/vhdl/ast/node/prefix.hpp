#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/function_call.hpp>

namespace ibis::vhdl::ast {

struct name;

struct prefix : variant<nullary, forward_ast<name>, function_call> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
