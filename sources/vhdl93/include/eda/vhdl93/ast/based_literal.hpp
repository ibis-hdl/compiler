/*
 * based_literal.hpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_


#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct based_literal {
    std::string                     base;
    std::string                     literal;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_ */
