/*
 * bit_string_literal.cpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/bit_string_literal.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>
#include <eda/exception.hpp>
#include <eda/vhdl93/utils/literal_ellipsis.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/exception/all.hpp>

#include <array>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


std::ostream& operator<<(std::ostream& os, bit_string_literal::tag const& hint)
{
    switch(hint) {
        case bit_string_literal::tag::bin: os << "<bin>"; break;
        case bit_string_literal::tag::oct: os << "<oct>"; break;
        case bit_string_literal::tag::hex: os << "<hex>"; break;
        default:                           os << "INVALID";
    }

    return os;
}


template<>
int get<int32_t>(bit_string_literal const& node)
{
    auto iter { std::begin(node.literal) };
    auto cend { std::cend(node.literal)  };

    int32_t attr { 0 };
    bool ok { false };

    using tag = bit_string_literal::tag;

    switch(node.hint) {
    case tag::bin:
        ok  = x3::parse(iter, cend, x3::bin, attr);
        break;
    case tag::oct:
        ok  = x3::parse(iter, cend, x3::oct, attr);
        break;
    case tag::hex:
        ok  = x3::parse(iter, cend, x3::hex, attr);
        break;
    default:
        cxx_bug_fatal("Invalid bit_string_literal::tag");
    }

    if(ok && iter == cend) {
        return attr;
    }
    else if(ok && iter != cend) {

        static std::array<unsigned, 3> const length {
                8*sizeof(int32_t), // bin
                4*sizeof(int32_t), // oct
                2*sizeof(int32_t)  // hex
        };

        BOOST_THROW_EXCEPTION(
            eda::range_error(
                "VHDL93 Bit String Literal='"
                + literal_ellipsis(node.literal, length[static_cast<unsigned>(node.hint)])
                + "' <int32> Range Error")
        );
    }

    cxx_bug_fatal("Invalid code path");

    return 0;
}


template<>
double get<double>(bit_string_literal const& node)
{
    return static_cast<double>(get<int32_t>(node));
}



} } } // namespace eda.vhdl93.ast





