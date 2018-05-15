/*
 * based_literal.hpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/parser/common_types.hpp>
#include <boost/range/iterator_range.hpp>


namespace eda { namespace vhdl { namespace ast {


struct based_literal : position_tagged
{
    boost::iterator_range<parser::iterator_type>    base;
    boost::iterator_range<parser::iterator_type>    number;
    boost::iterator_range<parser::iterator_type>    exponent;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_ */
