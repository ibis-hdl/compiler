#pragma once

#include <string_view>

namespace ibis {

void register_signal_handlers();

std::string_view signal_name(int sig_num);

}  // namespace ibis
