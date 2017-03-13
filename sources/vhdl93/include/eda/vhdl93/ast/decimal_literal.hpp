/*
 * decimal_literal.hpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_


#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct decimal_literal {
    enum class tag { integer, real };
    std::string                     literal;
    tag                             hint;
};


std::ostream& operator<<(std::ostream& os, decimal_literal const& decimal);
std::ostream& operator<<(std::ostream& os, decimal_literal::tag const& tag);
using boost::fusion::operator<<;


} } } // namespace eda.vhdl93.ast


BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::decimal_literal,
    (std::string,                   literal)
    (eda::vhdl93::ast::decimal_literal::tag,     hint)
)



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_ */
