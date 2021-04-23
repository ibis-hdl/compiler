#pragma once

#include <string_view>

namespace frontend {

void register_signal_handlers();

std::string_view signal_name(int sig_num);

}  // namespace frontend
