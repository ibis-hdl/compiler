/*
 * decimal_literal.cpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */


#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace ast {

    struct decimal_literal {
        enum class tag { integer, real };
        std::string                 literal;
        tag                         hint;
        void get();
    };

    std::ostream& operator<<(std::ostream& os, decimal_literal const& decimal);
    std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag);
    using boost::fusion::operator<<;
    
    namespace detail {
        namespace x3 = boost::spirit::x3;
        
        template <typename T>
        struct integer_policies : x3::real_policies<T>
        {
            static bool const allow_leading_dot = false;
            static bool const allow_trailing_dot = false;
            static bool const expect_dot = false;
            // ...
        };
    }
}

BOOST_FUSION_ADAPT_STRUCT(
    ast::decimal_literal,
    (std::string,                   literal)
    (ast::decimal_literal::tag,     hint)
)


namespace parser {

   namespace x3 = boost::spirit::x3;

   using x3::char_;

   template<typename T>
   auto as_rule = [](auto p) { return x3::rule<struct _, T>{} = x3::as_parser(p); };

   auto const integer = x3::rule<struct _, std::string> {} =
       x3::lexeme[ +char_("0-9") >> *(-x3::lit("_") >> char_("0-9")) ]
       ;

   auto const exponent = x3::rule<struct exponent_class, std::string> { "exponent" } =
       x3::lexeme[
           char_("Ee") >> -char_("+-") >> integer
       ]
       ;

   auto const decimal_literal_real = as_rule<std::string>( 
       x3::lexeme[ (integer >> char_('.') >> integer >> -exponent) ]);

   auto const decimal_literal_int = as_rule<std::string>(
       x3::lexeme[ (integer >> -exponent) ]);

   auto const decimal_literal = x3::rule<struct based_literal_class, ast::decimal_literal> { "decimal_literal" } =
         decimal_literal_real >> x3::attr(ast::decimal_literal::tag::real)
       | decimal_literal_int  >> x3::attr(ast::decimal_literal::tag::integer)
       ;
}

int main()
{
   namespace x3 = boost::spirit::x3;

   for(std::string const str: {
           // Integer literals
           "12", "0", "1e6", "123_456",
           // Real literals
           "12.0", "0.0", "0.456", "3.14_159_26",
           // Real literals with exponents
           "1.34E-12", "1.0E+6", "6.023_46E+2_4",
           "12345678901234567890"
   }) {
     auto iter = str.begin(), end = str.end();

     ast::decimal_literal attr;
     //std::string attr;
     bool r = x3::phrase_parse(iter, end, parser::decimal_literal, x3::space, attr);

     std::cout << "parse '" << str << "': ";
     if (r && iter == end) {
       std::cout << "succeeded: '" << attr << "'\n";
       if(attr.literal.find('\0') != std::string::npos) {
           std::cout << "found '\\0'\n";
       }
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}


namespace ast {
    std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag) {
        switch(tag) {
        case decimal_literal::tag::integer: os << "<int>";    break;
        case decimal_literal::tag::real:    os << "<double>"; break;
        default: os << "N/A";
        }
        return os;
    }
    
    namespace x3 = boost::spirit::x3;

    x3::real_parser<double, detail::integer_policies<double>> int_exp;

    std::ostream& operator<<(std::ostream& os, decimal_literal const& decimal) {
        namespace x3 = boost::spirit::x3;

        os << "lit='" << decimal.literal << "', ";
        
        auto iter { std::begin(decimal.literal) };
        auto end  { std::end(decimal.literal)   };
        
        auto const int_1 = [&os](auto& iter, auto const& end, auto&& attr) {
            bool ok = x3::parse(iter, end, x3::long_long, attr);
            os << "i1[" << std::boolalpha << ok << ", " << (iter == end) << "]";
            return std::make_tuple(ok,  iter == end);
        };
        
        auto const int_2 = [&os](auto& iter, auto const& end, auto&& attr) {
            double d { std::numeric_limits<double>::quiet_NaN() } ;
            bool ok = x3::parse(iter, end, int_exp, d);
            os << "i2[" << std::boolalpha << ok << ", " << (iter == end) << "]";
            if(   static_cast<int>(d) > std::numeric_limits<int32_t>::min() 
               || static_cast<int>(d) < std::numeric_limits<int32_t>::max()) {
                    attr = static_cast<int>(d);
            } else {
                os << "<d/int32> overflow";
                ok = false;
            }
            return std::make_tuple(ok,  iter == end);
        };
        
        switch(decimal.hint) {
        case decimal_literal::tag::integer: {
            int32_t attr { 0 };
            bool ok, full_match;
            std::tie(ok, full_match) = int_1(iter, end, attr);
            if (ok && full_match) {
                os << "(ok), ";
            }
            else if (ok && !full_match) {
                // fallback for integers like 1e6
                iter = std::begin(decimal.literal); // restore iter
                std::tie(ok, full_match) = int_2(iter, end, attr);
            }
            else {
                os << "NO <int32>";
            }
            os << "i=" << attr;
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
}

