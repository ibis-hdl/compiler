#pragma once

#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::ast {

/// convenience alias
template <typename... Types>
using variant = x3::variant<Types...>;

/// convenience alias
template <typename T>
using forward_ast = x3::forward_ast<T>;

}  // namespace ibis::vhdl::ast