#pragma once

#include <boost/optional.hpp>

namespace eda::vhdl::ast {

/// convenience alias
template <typename T>
using optional = boost::optional<T>;

}  // namespace eda::vhdl::ast
