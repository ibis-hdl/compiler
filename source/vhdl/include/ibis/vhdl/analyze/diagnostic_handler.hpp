#pragma once

#include <ibis/vhdl/diagnostic_handler.hpp>

namespace ibis::vhdl::analyze {

///
/// Syntax/Semantic error handler.
///
template <typename Iterator>
using diagnostic_handler = vhdl::diagnostic_handler<Iterator>;

using diagnostic_handler_type = diagnostic_handler<parser::iterator_type>;

}  // namespace ibis::vhdl::analyze
