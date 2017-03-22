/*
 * ellipsis_compress.cpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */


#include <iostream>
#include <string>
#include <cstring>
#include <utility>

std::string compress(std::string const& str)
{
    static std::size_t const len = 10;
    static const char* const ellipsis = "...";

    if(str.size() < len + 1)
        return str;

    std::size_t const offset = (len - strlen(ellipsis))/2;

    using range_t = std::pair<std::size_t, std::size_t>;

    range_t const left  { 0,                           offset       };
    range_t const right { (str.length() - offset - 1), str.length() };

    return std::string {
          str.substr(left.first, left.second)
        + ellipsis
        + str.substr(right.first, right.second)
    };
}

int main()
{
    for(auto const s : {
        "1",
        "12",
        "123",
        "1234",
        "12345",
        "123456",
        "1234567",
        "12345678",
        "123456789",
        "1234567890",
        "12345678901",
        "123456789012",
        "1234567890123",
        "12345678901234",
        "123456789012345",
        "1234567890123456",
    }) {
        std::cout <<  " - > " << compress(s) << "\n";
    }

    return 0;
}

