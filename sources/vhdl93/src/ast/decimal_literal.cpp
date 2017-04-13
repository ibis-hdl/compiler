/*
 * decimal_literal.cpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/decimal_literal.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>
#include <eda/exception/exception.hpp>
#include <eda/vhdl93/utils/literal_ellipsis.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/exception/all.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


namespace parser {

    namespace detail {

        template <typename T>
        struct integer_policies : x3::real_policies<T>
        {
            static bool const allow_leading_dot = false;
            static bool const allow_trailing_dot = false;
            static bool const expect_dot = false;
            // ...
        };
    } // namespace parser.detail

    x3::real_parser<double, detail::integer_policies<double>> real_integer;
}



template<>
double get<double>(decimal_literal const& node)
{
    auto iter { std::begin(node.literal) };
    auto cend { std::cend(node.literal)  };

    double attr { std::numeric_limits<double>::quiet_NaN() } ;

    bool ok  = x3::parse(iter, cend, parser::real_integer, attr);

    if(ok && iter == cend) {
        return attr;
    }
    else if (ok && iter != cend) {
        // syntactically ok, but literal probably to long
        BOOST_THROW_EXCEPTION(
            eda::range_error(
                "VHDL93 Decimal Literal='"
                + literal_ellipsis(node.literal.to_string(), 15)
                + "' <double> Range Error")
        );
    }

    // 1st pass did pass characters which failed here to parse
    std::cout << "INVALID CODEPATH @'" << node.literal /* << node.hint */ << "'\n";
    cxx_bug_fatal("Invalid code path");
    return 0;
}


template<>
int get<int>(decimal_literal const& node)
{
    double attr = get<double>(node);

    if(   attr > std::numeric_limits<int32_t>::min()
       && attr < std::numeric_limits<int32_t>::max())
    {
        return static_cast<int32_t>(attr);
    }
    else {
        BOOST_THROW_EXCEPTION(
            eda::range_error(
                "VHDL93 Decimal Literal='"
                + literal_ellipsis(node.literal.to_string(), 15)
                + "' <integer> Range Error")
        );
    }

    cxx_bug_fatal("Invalid code path");
    return 0;
}



} } } // namespace eda.vhdl93.ast



