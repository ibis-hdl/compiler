#pragma once

#include <string_view>

namespace ibis::frontend {

void register_signal_handlers();

std::string_view signal_name(int sig_num);

}  // namespace ibis::frontend
