//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <string_view>

namespace ibis::frontend {

void register_signal_handlers();

std::string_view signal_name(int sig_num);

}  // namespace ibis::frontend
