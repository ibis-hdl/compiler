/*
 * bit_string_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>


namespace eda { namespace vhdl { namespace ast {


struct bit_string_literal : position_tagged
{
    enum class base_specifier { bin, oct, hex };

    ast::string_span                                literal;
    base_specifier                                  base_type;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BIT_STRING_LITERAL_HPP_ */
