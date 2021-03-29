#pragma once

#include <initializer_list>
#include <filesystem>

#include <eda/namespace_alias.hpp>

namespace eda::util {

fs::path user_home_dir(std::initializer_list<char const*> path_list);

}
