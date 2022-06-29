//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <boost/optional.hpp>

namespace ibis::vhdl::ast {

/// convenience alias
template <typename T>
using optional = boost::optional<T>;

}  // namespace ibis::vhdl::ast
