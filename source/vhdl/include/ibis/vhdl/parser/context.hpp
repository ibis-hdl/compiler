//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/context.hpp>

namespace ibis::vhdl::parser {

///
/// Parser context, e.g. {error, warnings} counter
///

// ToDo [XXX] get rid off this alias, use vhdl::vhdl_context direct
using context = vhdl::context;

}  // namespace ibis::vhdl::parser
