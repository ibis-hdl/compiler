/*
 * abstract_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct decimal_literal;
struct based_literal;


struct abstract_literal :
    x3::variant<
        x3::forward_ast<decimal_literal>
      , x3::forward_ast<based_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


std::ostream& operator<<(std::ostream& os, abstract_literal const& node);


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ABSTRACT_LITERAL_HPP_ */
