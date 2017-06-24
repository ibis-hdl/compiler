/*
 * decimal_literal.hpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <string_view>


namespace eda { namespace vhdl { namespace ast {


struct decimal_literal : position_tagged
{
    enum class tag { integer, real };

    std::string_view                literal;
    tag                             hint;
};


/**
 * Convert the literal to the type T. The type T can be <int> or <double> due to
 * the provided specializations. On overflow it will throw an exception.
 */
template<typename T>
T get(decimal_literal const& literal);


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DECIMAL_LITERAL_HPP_ */
