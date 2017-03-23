/*
 * numeric_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct abstract_literal;
struct physical_literal;


struct numeric_literal :
    x3::variant<
        x3::forward_ast<abstract_literal>
      , x3::forward_ast<physical_literal>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


std::ostream& operator<<(std::ostream& os, numeric_literal const& node);


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NUMERIC_LITERAL_HPP_ */
