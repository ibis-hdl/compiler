/*
 * decorator.hpp
 *
 *  Created on: 06.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_DECORATOR_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_DECORATOR_HPP_

#include <iosfwd>
#include <string>

namespace eda {
namespace color {

template <typename Tag> class message_decorator {
public:
    explicit message_decorator(std::string const& contents_)
        : contents{ contents_ }
    {
    }

    std::ostream& print(std::ostream& os) const
    {
        os << contents;
        return os;
    }

private:
    // clang-format off
    std::string const&                              contents;
    // clang-format on
};

} // namespace color
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_DECORATOR_HPP_ */
