/*
 * decimal_literal.hpp
 *
 *  Created on: 12.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <eda/support/boost/spirit_x3/string_view.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct decimal_literal : x3::position_tagged
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


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DECIMAL_LITERAL_HPP_ */
