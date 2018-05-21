/*
 * x3_integer_lambda_solution.cpp
 *
 *  Created on: 21.05.2018
 *      Author: olaf
 */


/*
 * Concept Check for VHDL digit separator using lambda for base specifier for SO
 */

#include <string>
#include <boost/spirit/home/x3.hpp>

namespace ast {
    struct literal {
        enum base_specifier { bin, oct, hex };

        base_specifier  base;
        std::string     literal;
    };
}

namespace x3 = boost::spirit::x3;


template<typename T>
auto as = [](auto p) { return x3::rule<struct _, T>{} = x3::as_parser(p); };


template <typename TargetT>
std::pair<bool, TargetT> convert(ast::literal const& node)
{
    auto const parse = [](ast::literal::base_specifier base, auto const& literal) {

        using base_specifier = ast::literal::base_specifier;

        auto const parser = [](base_specifier base) {
            switch(base) {
                case base_specifier::bin: return as<TargetT>( x3::bin );
                case base_specifier::oct: return as<TargetT>( x3::oct );
                case base_specifier::hex: return as<TargetT>( x3::hex );
                default:
                    abort();
            }
        };

        auto iter      = std::begin(literal);
        auto const end = std::cend(literal);
        TargetT attribute;

        bool parse_ok  = x3::parse(iter, end, parser(base), attribute);

        return std::make_tuple(parse_ok && (iter == end), attribute);
    };

    // other complex stuff here

    return parse(node.base, node.literal);
}


int main()
{
    ast::literal literal{ ast::literal::hex, "AFFE" };
    auto const [parse_ok, result] = convert<int32_t>(literal);
}
