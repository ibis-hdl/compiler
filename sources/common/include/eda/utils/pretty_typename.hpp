/*
 * pretty_typename.hpp
 *
 *  Created on: 21.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_PRETTY_TYPENAME_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_PRETTY_TYPENAME_HPP_

#include <boost/type_index.hpp>
#include <regex>
#include <string>


namespace eda { namespace utils {


template<typename T>
class pretty_typename
{
public:
    pretty_typename() = default;

    pretty_typename(std::string const& pattern_)
    : pattern{ pattern_ }
    { }

    pretty_typename(pretty_typename const&) = delete;
    pretty_typename const& operator=(pretty_typename const&) = delete;

public:
    std::ostream& print(std::ostream& os) const
    {
        std::string name{ boost::typeindex::type_id<T>().pretty_name() };
        os << std::regex_replace(name, pattern, "");
        return os;
    }

private:
    std::regex                      pattern{ "::|boost|spirit|x3|eda|vhdl|ast" };
};


template<typename T>
std::ostream& operator<<(std::ostream& os, pretty_typename<T> const& printer) {
    return printer.print(os);
}

} } // namespace eda.utils


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_PRETTY_TYPENAME_HPP_ */
