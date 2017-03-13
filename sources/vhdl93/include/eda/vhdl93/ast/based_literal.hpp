/*
 * based_literal.hpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_


#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct based_literal {
    std::string                     base;
    std::string                     literal;
};


std::ostream& operator<<(std::ostream& os, based_literal const& based);

using boost::fusion::operator<<;


} } } // namespace eda.vhdl93.ast


BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::based_literal,
    (std::string,                   base)
    (std::string,                   literal)
)



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_ */
