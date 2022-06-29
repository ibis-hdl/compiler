//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iosfwd>

namespace ibis {

class buildinfo {
public:
    static std::ostream& print_on(std::ostream& os);
};

inline std::ostream& operator<<(std::ostream& os, buildinfo const& info)
{
    return info.print_on(os);
}

}  // namespace ibis
