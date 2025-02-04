//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/buildinfo.hpp>
#include <ibis/buildinfo_static.hpp>

#include <format>
#include <iostream>

namespace ibis {

std::ostream& buildinfo::print_on(std::ostream& os)
{
    os << std::format(
        "platform: {0}\n"
        "type:     {1}\n"
        "system:   {2}\n"
        "compiler: {3}\n"
        "stdlib:   {4}\n"
        "libboost: {5}\n",
        build_info::platform,  // {0}
        build_info::type,      // {1}
        build_info::system,    // {2}
        build_info::compiler,  // {3}
        build_info::stdlib,    // {4}
        build_info::libboost   // {5}
    );

    return os;
}

}  // namespace ibis
