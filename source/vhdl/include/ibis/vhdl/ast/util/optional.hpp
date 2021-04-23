#pragma once

#include <boost/optional.hpp>

namespace ibis::vhdl::ast {

/// convenience alias
template <typename T>
using optional = boost::optional<T>;

}  // namespace ibis::vhdl::ast
