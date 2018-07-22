/*
 * grammar.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_

#include <eda/vhdl/ast.hpp>

#include <eda/support/boost/spirit_x3.hpp>

#include <eda/util/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <eda/util/compiler_warnings_on.hpp>


namespace eda { namespace vhdl { namespace parser {


struct design_file_class;
typedef x3::rule<design_file_class, ast::design_file> design_file_type;
BOOST_SPIRIT_DECLARE(design_file_type);

parser::design_file_type const& grammar();


} } } // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_ */
