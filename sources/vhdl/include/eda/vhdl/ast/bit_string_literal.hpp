/*
 * bit_string_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <string_view>


namespace eda { namespace vhdl { namespace ast {


// FixMe: change to {Base, Literal}
struct bit_string_literal : position_tagged
{
    enum class tag { bin, oct, hex };

    std::string_view                literal;
    tag                             hint;
};


/**
 * Convert the literal to the type T. The type T can be <int> or <double> due to
 * the provided specializations. On overflow it will throw an exception.
 */
template<typename T>
T get(bit_string_literal const& literal);


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_ */
