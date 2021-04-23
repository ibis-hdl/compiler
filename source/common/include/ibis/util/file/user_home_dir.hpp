#pragma once

#include <initializer_list>
#include <filesystem>

#include <ibis/namespace_alias.hpp>

namespace ibis::util {

fs::path user_home_dir(std::initializer_list<char const*> path_list);

}
