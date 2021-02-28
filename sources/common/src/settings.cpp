/*
 * settings.cpp
 *
 *  Created on: 01.08.2018
 *      Author: olaf
 */

#include <eda/settings.hpp>

#include <algorithm>
#include <eda/support/cxx/overloaded.hpp>
#include <eda/util/string/icompare.hpp>
#include <eda/util/infix_ostream_iterator.hpp>
#include <iostream>
#include <vector>

namespace eda {

std::ostream& settings::dump(std::ostream& os) const
{
    using key_type = map_type::key_type;
    using value_type = map_type::mapped_type;
    using pair_type = std::pair<key_type, value_type>;
    using vector_type = std::vector<pair_type>;

    vector_type vec{ map.begin(), map.end() };

    std::sort(vec.begin(), vec.end(), [](pair_type const& p1, pair_type const& p2) {
        return util::icompare_less(p1.first, p2.first);
    });

    os << "(settings [N=" << vec.size() << "]\n";
    for (auto const & [ option_name, val ] : vec) {
        os << "    " << option_name << ": ";
        // clang-format off
        std::visit(util::overloaded{
            [&os](std::monostate /*unused*/) {  // NOLINT(readability-named-parameter)
                os << "N/A"; 
            },
            [&os](bool v) {
                os << std::boolalpha << v; 
            },
            [&os](long v) {
                os << v;
            },
            [&os](std::string const& v) {
                os << v; 
            },
            [&os](std::vector<std::string> const& v) {
                os << "[ ";
                std::copy(v.begin(), v.end(),
                          util::infix_ostream_iterator<std::string>(os, ", "));
                os << " ]";
            },
        }, val);
        // clang-format on
        os << '\n';
    }
    os << ")\n";

    return os;
}

std::ostream& settings::print(std::ostream& os, settings::option_value const& value)
{
    // clang-format off
    std::visit(util::overloaded{
        // <long> is (implicit converted) handled as boolean, as intended
        [&os](bool option) {
            os << std::boolalpha << option;
        },
        [&os](std::string const& option) {
            os << "\'" << option << "\'";
        },
        [&os](std::vector<std::string> const& option) {
            os << "[ ";
            std::copy(option.begin(), option.end(),
                      util::infix_ostream_iterator<std::string>(std::cout, ", "));
            os << " ]";
        },
        [&os](std::monostate /*unused*/) {  // NOLINT(readability-named-parameter)
            os << "N/A (std::monostate)";
        },
    }, value);
    // clang-format on

    return os;
}

void settings::debug_print(
    std::string const& option_name, settings::option_value const& value)
{
    std::cout << "lookup[" << option_name << "] = " << value << std::endl;
}

std::ostream& operator<<(std::ostream& os, settings::option_value const& value)
{
    return settings::print(os, value);
}

const settings::option_value settings::none;

} // namespace eda
