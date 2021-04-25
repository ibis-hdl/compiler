#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>

#include <ibis/namespace_alias.hpp>

namespace ibis {

///
/// @brief The settings class using Boost property tree.
///
/// @todo Unfortunately RapidJSON has only a master branch in 2021, v1.1.0
/// is from 2016 and got compile errors using clang-11-win on Windows.
/// Sometimes the master branch compiles, sometimes not. So it's
/// decidet to get rid off RapidJSON and using boost's property_tree,
/// even if merging isn't support still with boost v1.75, see
/// [Future Development: Mathematical relations: ptree difference, union, intersection](
///  https://www.boost.org/doc/libs/1_75_0/doc/html/property_tree/appendices.html).
/// If comes relevant, try [How to diff two boost::property_tree?](
///  https://stackoverflow.com/questions/22914795/how-to-diff-two-boostproperty-tree).
///
class settings {
public:
    using type = pt::ptree;
    typedef pt::ptree& reference_type;

public:
    ///
    /// @brief Singleton like instance of boost property.
    ///
    /// @return pt::ptree& get reference to static instance variable, which
    /// **is** thread-safe starting with C++11.
    ///
    static reference_type instance()
    {
        static settings::type instance_;
        return instance_;
    }

    ///
    /// @brief Dump the settings as JSON on stream.
    ///
    /// @param os The stream to dump on.
    /// @return std::ostream&
    ///
    static std::ostream& dump(std::ostream& os);

    ///
    /// @brief add the settings given as JSON format
    ///
    /// @param json_sv The string view holding the JSON format settings.
    ///
    static void insert_json(std::string_view json_sv);

    /// FixMe: Implement secondary flags like
    /// `trigger_flag["--Wall"] = { "--Wunused", "--Wother" };`
    class option_trigger;

public:
    settings(settings const&) = delete;
    settings& operator=(settings const&) = delete;
    settings(settings&&) = delete;
    settings& operator=(settings&&) = delete;
};

}  // namespace ibis
