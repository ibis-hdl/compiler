/*
 * expression_parse.hpp
 *
 *  Created on: 26.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_EXPRESSION_PARSE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_EXPRESSION_PARSE_HPP_


#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace parser {


    /* quick&dirty API for expression parsing and evaluation */
    bool parse(const std::string& file, ast::expression& exp);


} } } // namespace eda.vhdl.parser



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_EXPRESSION_PARSE_HPP_ */
