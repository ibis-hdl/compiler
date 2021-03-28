/*
 * decimal_literal.hpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>


namespace eda { namespace vhdl { namespace ast {


struct decimal_literal : position_tagged
{
    enum class kind_specifier { integer, real };

    ast::string_span                                literal;
    kind_specifier                                  kind_type;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_ */
