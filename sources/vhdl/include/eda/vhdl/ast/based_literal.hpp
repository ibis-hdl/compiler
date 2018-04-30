/*
 * based_literal.hpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <string_view>


namespace eda { namespace vhdl { namespace ast {


struct based_literal : position_tagged
{
    std::string_view                base;
    std::string_view                number;
    std::string_view                exponent;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_ */
