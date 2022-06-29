//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

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
