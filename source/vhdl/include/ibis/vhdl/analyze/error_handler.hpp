#pragma once

#include <ibis/vhdl/error_handler.hpp>

namespace ibis::vhdl::analyze {

///
/// Syntax/Semantic error handler.
///
template <typename Iterator>
using error_handler = vhdl::error_handler<Iterator>;

using error_handler_type = error_handler<parser::iterator_type>;

}  // namespace ibis::vhdl::analyze
