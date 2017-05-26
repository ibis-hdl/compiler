/*
 * expression_parse.hpp
 *
 *  Created on: 26.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_PARSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_PARSE_HPP_


#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace parser {


    /* quick&dirty API for expression parsing and evaluation */
    bool parse(const std::string& file, ast::expression& exp);


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_PARSE_HPP_ */
