/*
 * abstract_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_


//#include <eda/vhdl93/ast/based_literal.hpp>
//#include <eda/vhdl93/ast/decimal_literal.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct decimal_literal;
struct based_literal;


typedef x3::variant<
        decimal_literal
      , based_literal
    > abstract_literal;


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_ */
