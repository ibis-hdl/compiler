/*
 * bit_string_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_


#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct bit_string_literal {
    enum class tag { bin, oct, hex };
    std::string                     literal;
    tag                             hint;
};


std::ostream& operator<<(std::ostream& os, bit_string_literal const& literal);
std::ostream& operator<<(std::ostream& os, bit_string_literal::tag const& tag);


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_ */