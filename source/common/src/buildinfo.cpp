//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/buildinfo.hpp>
#include <ibis/buildinfo_static.hpp>

#include <iostream>
#include <string_view>

namespace ibis {

std::ostream& buildinfo::print_on(std::ostream& os)
{
    os << "platform: " << build_info::platform << '\n'
       << "type:     " << build_info::type << '\n'
       << "system:   " << build_info::system << '\n';

    os << "compiler: " << build_info::compiler << '\n'
       << "stdlib:   " << build_info::stdlib << '\n'
       << "libboost: " << build_info::libboost << '\n';

    return os;
}

}  // namespace ibis
