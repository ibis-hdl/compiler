//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/indent_stream.hpp>

namespace ibis::util {

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
indent_sbuf::~indent_sbuf()
{
    // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall) -- functionally intended
    overflow('\n');  // start at column 0 again
}

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
indent_ostream::~indent_ostream() = default;

}  // namespace ibis::util
