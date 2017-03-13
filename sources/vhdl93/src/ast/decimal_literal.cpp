/*
 * decimal_literal.cpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/decimal_literal.hpp>

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



std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag)
{
    switch(tag) {
    case decimal_literal::tag::integer: os << "<int>";    break;
    case decimal_literal::tag::real:    os << "<double>"; break;
    default: os << "N/A";
    }
    return os;
}


x3::real_parser<double, detail::integer_policies<double>> int_exp;


std::ostream& operator<<(std::ostream& os, decimal_literal const& decimal)
{
    os << "lit='" << decimal.literal << "', ";

    auto iter { std::begin(decimal.literal) };
    auto end  { std::end(decimal.literal)   };

    auto const full_match = [](auto const& iter, auto const& end) { return iter == end; };

    switch(decimal.hint) {
        case decimal_literal::tag::integer: {
            int32_t attr { 0 };
            bool r = x3::parse(iter, end, x3::long_long, attr);
            os << "i1[" << std::boolalpha << r << ", " << (iter == end) << "]";
            if (r && full_match(iter, end)) {
                os << "(ok), ";
            }
            if (r && !full_match(iter, end)) {
                // fallback for integers like 1e6
                double d { std::numeric_limits<double>::quiet_NaN() } ;
                iter = std::begin(decimal.literal);
                r = x3::parse(iter, end, int_exp, d);
                os << "i2[" << std::boolalpha << r << ", " << (iter == end) << "]";
                if(   static_cast<int>(d) < std::numeric_limits<int32_t>::min()
                   || static_cast<int>(d) > std::numeric_limits<int32_t>::max()) {
                    os << "<d/int32> overflow";
                } else {
                    attr = static_cast<int>(d);
                }
            }
            if (!r && !full_match(iter, end)) {
                // failure or even overflow
                os << "<int32> overflow";
            } else {
                os << "i=" << attr;
            }
            break;
        }
        case decimal_literal::tag::real: {
            double attr { 0 };
            x3::parse(iter, end, x3::double_, attr);
            os << "d=" << attr;
            break;
        }
        default: os << "INVALID";
    }

    return os;
}


} } } // namespace eda.vhdl93.ast



