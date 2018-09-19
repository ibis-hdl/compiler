/*
 * attribute.hpp
 *
 *  Created on: 18.09.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_COLOR_ATTRIBUTE_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_COLOR_ATTRIBUTE_HPP_

#include <cstdint>
#include <string_view>
#include <optional>

namespace eda {
namespace color {

enum class attribute : uint8_t {
    // Text attribute
    Attributes_Off = 0,
    Text_Bold = 1,
    Text_Underscore = 4,
    Text_Blink = 5,
    Text_Reverse = 7,
    Text_Concealed = 8,
    // Foreground colors
    Foreground_Black = 30,
    Foreground_Red = 31,
    Foreground_Green = 32,
    Foreground_Yellow = 33,
    Foreground_Blue = 34,
    Foreground_Magenta = 35,
    Foreground_Cyan = 36,
    Foreground_White = 37,
    // Background colors
    Background_Black = 40,
    Background_Red = 41,
    Background_Green = 42,
    Background_Yellow = 43,
    Background_Blue = 44,
    Background_Magenta = 45,
    Background_Cyan = 46,
    Background_White = 47,
};

std::optional<color::attribute> text_attr(std::string_view const& name);
std::optional<color::attribute> foreground_attr(std::string_view const& name);
std::optional<color::attribute> background_attr(std::string_view const& name);

} // namespace color
} // namespace eda



#endif /* SOURCES_COMMON_INCLUDE_EDA_COLOR_ATTRIBUTE_HPP_ */
