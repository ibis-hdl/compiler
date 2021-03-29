#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/function_call.hpp>

namespace eda::vhdl::ast {

struct name;

struct prefix : variant<nullary, forward_ast<name>, function_call> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
