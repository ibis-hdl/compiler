/*
 * bit_string_literal.cpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/bit_string_literal.hpp>

#include <boost/spirit/home/x3.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


namespace detail {

    template <typename T>
    struct integer_policies : x3::real_policies<T>
    {
        static bool const allow_leading_dot = false;
        static bool const allow_trailing_dot = false;
        static bool const expect_dot = false;
        // ...
    };
}



std::ostream& operator<<(std::ostream& os, bit_string_literal::tag const& tag)
{
    switch(tag) {
    case bit_string_literal::tag::bin: os << "<bin>";    break;
    case bit_string_literal::tag::oct: os << "<oct>"; break;
    case bit_string_literal::tag::hex: os << "<hex>"; break;
    default: os << "N/A";
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, bit_string_literal const& bit_literal)
{
    os << "lit='" << bit_literal.literal << "', tag='" << bit_literal.hint << "'\n";

    auto iter { std::begin(bit_literal.literal) };
    auto end  { std::cend(bit_literal.literal)  };

    int32_t attr { 0 };
    bool ok { false };

    switch(bit_literal.hint) {
    case bit_string_literal::tag::bin:
        ok  = x3::parse(iter, end, x3::bin, attr);
        break;
    case bit_string_literal::tag::oct:
        ok  = x3::parse(iter, end, x3::oct, attr);
        break;
    case bit_string_literal::tag::hex:
        ok  = x3::parse(iter, end, x3::hex, attr);
        break;
    default:
        os << "INVALID_TAG";
    }

    if(ok && iter == end) {
        os << "i=" << attr;
    }
    else {
        os << "INVALID";
    }

    return os;
}


} } } // namespace eda.vhdl93.ast





