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


namespace parser {
    x3::real_parser<double, detail::integer_policies<double>> real_integer;
}


std::ostream& operator<<(std::ostream& os, decimal_literal const& decimal)
{
    os << "lit='" << decimal.literal << "', tag='" << decimal.hint << "'\n";

    auto iter { std::begin(decimal.literal) };
    auto end  { std::end(decimal.literal)   };

    double attr { std::numeric_limits<double>::quiet_NaN() } ;

    bool ok  = x3::parse(iter, end, parser::real_integer, attr);

    if(ok && iter == end) {
        switch(decimal.hint) {
            case decimal_literal::tag::integer:
            {
                if(static_cast<int32_t>(attr) > std::numeric_limits<int32_t>::min() && static_cast<int32_t>(attr) < std::numeric_limits<int32_t>::max()) {
                    os << "i=" << static_cast<int32_t>(attr);
                } else {
                    os << "overflow<int32>";
                }
                break;
            }
            case decimal_literal::tag::real:
            {
                os << "d=" << attr;
                break;
            }
            default: os << "INVALID_TAG";
        }
    } else {
        // parser failed and shouldn't
        os << "INVALID";
    }


    return os;
}


} } } // namespace eda.vhdl93.ast



