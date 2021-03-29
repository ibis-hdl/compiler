#include <eda/util/file/user_home_dir.hpp>

//#include <eda/compiler/compiler_support.hpp> // IWYU pragma: keep
#include <eda/platform.hpp>
//#include <eda/namespace_alias.hpp>

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <initializer_list>
#include <system_error>

namespace eda::util {

///
/// @brief Lookup user's HOME environment to gather the absolute path
/// of stringified path elements
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
fs::path user_home_dir(std::initializer_list<char const *> path_list)
{
    std::string const HOME_ENV = []() {
        if constexpr (eda::build_platform == platform::Unix) {
            return std::getenv("HOME");
        }
        else if constexpr (eda::build_platform == platform::Win32) {
            return std::getenv("USERPROFILE");
        }
        else {
            // FixMe: hopefully, this will be correct, static_assert doesn't work here
            throw std::runtime_error("Platform support bug: It's not Unix or Win32.");
            // return std::getenv("HOME");
        }
    }();

    // FixMe: throwing exceptions should not be a viable solution here ...

    if (HOME_ENV.empty()) {
        throw std::runtime_error("No viable environment variable for user's home.");
    }

    fs::path path{ HOME_ENV };

    std::error_code ec;

    // The HOME directory must exist and must be a directory

    if (!fs::exists(path, ec)) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    if (!fs::is_directory(path, ec)) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    for (const auto *const dir : path_list) {
        path /= dir;
    }

    return path;
}

}  // namespace eda::util
