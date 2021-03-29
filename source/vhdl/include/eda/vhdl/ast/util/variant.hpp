#pragma once

#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <eda/namespace_alias.hpp>

namespace eda::vhdl::ast {

template <typename... Types>
using variant = x3::variant<Types...>;

template <typename T>
using forward_ast = x3::forward_ast<T>;

}  // namespace eda::vhdl::ast
