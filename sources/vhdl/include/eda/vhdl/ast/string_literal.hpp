/*
 * string_literal.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <boost/range/iterator_range.hpp>
#include <string>


namespace eda { namespace vhdl { namespace ast {


struct string_literal : position_tagged
{
    std::string                     literal;
//    boost::iterator_range<parser::iterator_type>                literal; // FixMe: use string_view
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_ */
