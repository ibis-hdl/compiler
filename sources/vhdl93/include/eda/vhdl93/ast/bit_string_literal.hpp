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


std::ostream& operator<<(std::ostream& os, bit_string_literal::tag const& hint);


/**
 * Convert the literal to the type T. The type T can be <int> or <double> due to
 * the provided specializations. On overflow it will throw an exception.
 */
template<typename T>
T get(bit_string_literal const& literal);


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BIT_STRING_LITERAL_HPP_ */
