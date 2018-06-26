/*
 * string_span.hpp
 *
 *  Created on: 26.06.2018
 *      Author: olpetzol
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HPP_

#include <boost/range/iterator_range.hpp>
#include <eda/vhdl/parser/common_types.hpp>


namespace eda { namespace vhdl { namespace ast {


/*
 * Hot Fix
 *
 * This is required to work with 'string_view', later version of Spirit.X3
 * as 1.64. Note the hard coded iterator type!!, \see
 * [Spirit.X3 using string_view and member named 'insert' compiler error](
 *  https://stackoverflow.com/questions/50310015/spirit-x3-using-string-view-and-member-named-insert-compiler-error?answertab=active#tab-top) */
using string_span = boost::iterator_range<parser::iterator_type>;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HPP_ */
