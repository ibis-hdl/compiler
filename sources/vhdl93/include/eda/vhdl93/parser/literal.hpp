/*
 * literal.hpp
 *
 *  Created on: 21.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_HPP_


#include <eda/vhdl93/parser/common.hpp>
#include <eda/vhdl93/ast/string_literal.hpp>

#include <boost/spirit/home/x3/nonterminal/rule.hpp>


/*
 * VHDL common literals
 */
namespace eda { namespace vhdl93 { namespace parser {


/*
 * Rule IDs
 */
struct string_literal_class;


/*
 * Rule Types
 */
typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;


BOOST_SPIRIT_DECLARE(string_literal_type);


} } } // namespace eda.vhdl93.parser


/*
 * VHDL common literals API
 */
namespace eda { namespace vhdl93 { namespace parser_api {

parser::string_literal_type const& string_literal();


} } } // namespace eda.vhdl93.parser_api



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_HPP_ */
