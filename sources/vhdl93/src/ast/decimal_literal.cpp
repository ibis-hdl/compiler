/*
 * decimal_literal.cpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/decimal_literal.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>
#include <eda/exception.hpp>
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

    /* FixMe: Is it really necessary to tag the literal, here the x3::double_
     *        is used! Further, how to get advantage from type tag?
     */

    if(ok && iter == cend) {
        return attr;
    }
    else if (ok && iter != cend) {
        // syntactically ok, but literal probably to long
        BOOST_THROW_EXCEPTION(
            eda::range_error(
                "VHDL93 Decimal Literal='"
                + literal_ellipsis(node.literal, 15)
                + "' <double> Range Error")
        );
    }

    // 1st pass did pass characters which failed here to parse
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
                + literal_ellipsis(node.literal, 15)
                + "' <integer> Range Error")
        );
    }

    cxx_bug_fatal("Invalid code path");
    return 0;
}


std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag)
{
    switch(tag) {
        case decimal_literal::tag::integer: os << "<int>";    break;
        case decimal_literal::tag::real:    os << "<double>"; break;
        default: cxx_bug_fatal("Invalid bit_string_literal::tag");
    }

    return os;
}


std::ostream& operator<<(std::ostream& os, decimal_literal const& node)
{
    using tag = decimal_literal::tag;

    try {
        switch(node.hint) {
        case tag::integer:
            os << get<int32_t>(node);
            break;
        case tag::real:
            os << get<double>(node);
            break;
        default:
            cxx_bug_fatal("Invalid decimal_literal::tag");
        }
    }
    catch(::eda::range_error const& e) {
        std::cerr << "Exception caught:\n"
                  << e.what() << '\n'
                  << "Diagnostic Details:\n"
                  << boost::current_exception_diagnostic_information();
        os << "INVALID";
    }

    return os;
}


} } } // namespace eda.vhdl93.ast



