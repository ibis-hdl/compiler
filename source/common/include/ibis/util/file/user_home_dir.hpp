//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <initializer_list>
#include <filesystem>

#include <ibis/namespace_alias.hpp>

#if 0
namespace ibis {
    namespace fs = std::filesystem;
}
#endif

namespace ibis::util {

///
/// Lookup user's HOME environment to gather the absolute path of stringified path elements.
///
/// @param path_list list of path elements
/// @return fs::path absolute path
///
/// @todo This function requires rework. It's small and only used only in init.cpp.
/// Further the arguments list shall be a path self, instead an initializer list of
/// chars/strings. On Windows there is the warning: *'getenv' is deprecated:
/// This function or variable may be unsafe. Consider using _dupenv_s instead.
/// To disable deprecation, use _CRT_SECURE_NO_WARNINGS*. Setting these define
/// globally isn't wise. One solution on windows would be:
/// \code{.cpp}
/// char *buffer = nullptr;
/// _dupenv_s(&buffer, nullptr, "USERPROFILE");
/// const auto ptr = std::unique_ptr<char, decltype(&std::free)>(buffer, &std::free);
/// if (buffer != nullptr) {
///     return std::string{ buffer };
/// }
/// return std::string{};
/// @endcode
///
/// @see For Windows use [SHGetKnownFolderPath function](
///  https://docs.microsoft.com/en-us/windows/desktop/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath)
/// with example given at [SO](
///  https://stackoverflow.com/questions/24124851/getenvironmentvariablea-usage)
/// to avoid warnings from MSVC.
///
fs::path user_home_dir(std::initializer_list<char const*> path_list);

}  // namespace ibis::util
