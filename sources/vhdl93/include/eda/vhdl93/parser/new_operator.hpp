/*
 * operator.hpp
 *
 *  Created on: 19.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_


#include <eda/vhdl93/ast/operator_token.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <boost/spirit/home/x3/string/symbols.hpp>
#include <eda/vhdl93/parser/namespace_alias.hpp>


/*
 * VHDL operators
 */
namespace eda { namespace vhdl93 { namespace parser {


/*
 * Rule IDs
 */
struct logical_operator_class;
struct logical_operator_option_class;
struct logical_operator_option_class;
struct unary_miscellaneous_operator_class;
struct multiplying_operator_class;
struct shift_operator_class;


/*
 * Rule Types
 */
typedef x3::rule<logical_operator_class, ast::operator_token> logical_operator_type;
typedef x3::rule<logical_operator_option_class, ast::operator_token> logical_operator_option_type;
typedef x3::rule<unary_miscellaneous_operator_class, ast::operator_token> unary_miscellaneous_operator_type;
typedef x3::rule<multiplying_operator_class, ast::operator_token> multiplying_operator_type;
typedef x3::rule<shift_operator_class, ast::operator_token> shift_operator_type;
typedef x3::symbols<ast::operator_token> relational_operator_type;
typedef x3::symbols<ast::operator_token> binary_miscellaneous_operator_type;
typedef x3::symbols<ast::operator_token> adding_operator_type;
typedef x3::symbols<ast::operator_token> sign_operator_type;


BOOST_SPIRIT_DECLARE(logical_operator_type);
BOOST_SPIRIT_DECLARE(logical_operator_option_type);
BOOST_SPIRIT_DECLARE(relational_operator_type);
BOOST_SPIRIT_DECLARE(unary_miscellaneous_operator_type);
BOOST_SPIRIT_DECLARE(binary_miscellaneous_operator_type);
BOOST_SPIRIT_DECLARE(adding_operator_type);
BOOST_SPIRIT_DECLARE(multiplying_operator_type);
BOOST_SPIRIT_DECLARE(shift_operator_type);
BOOST_SPIRIT_DECLARE(sign_operator_type);


} } } // namespace eda.vhdl93.parser


/*
 * VHDL operators API
 */
namespace eda { namespace vhdl93 { namespace parser { namespace api {

    logical_operator_type const& logical_operator();
    logical_operator_option_type const& logical_operator_option();
    relational_operator_type const& relational_operator();
    unary_miscellaneous_operator_type const& unary_miscellaneous_operator();
    binary_miscellaneous_operator_type const& binary_miscellaneous_operator();
    adding_operator_type const& adding_operator();
    multiplying_operator_type const& multiplying_operator();
    shift_operator_type const& shift_operator();
    sign_operator_type const& sign_operator();

} } } } // namespace eda.vhdl93.parser.api


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_OPERATOR_HPP_ */
