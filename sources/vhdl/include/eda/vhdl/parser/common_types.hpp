/*
 * common_types.hpp
 *
 *  Created on: 13.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_COMMON_TYPES_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_COMMON_TYPES_HPP_


#include <string>


namespace eda { namespace vhdl { namespace parser {


/**
 * Basic type used by the parser
 *
 * std::string_view isn't a first citizen of Spirit.X3; from time to time
 * problems rises. To avoid they until std::string_view is fully supported
 * boost::range_iterator<IteratorType> exposed by x3::raw[] directive is used.
 * Unfortunately, the IteratorType is required up to the top level rule which
 * would required excessive rewrites of the grammar rules.
 * The simple work-around is to define it 'globally', since it must be of the
 * same type as of the x3::parse function.
 * For the concrete problem behind \see StackOverflow
 * [Spirit.X3 using string_view and member named 'insert' compiler error](
 *  https://stackoverflow.com/questions/50310015/spirit-x3-using-string-view-and-member-named-insert-compiler-error?answertab=active#tab-top)
 */
typedef char                                char_type;

typedef std::basic_string<
    char_type
>::const_iterator                           iterator_type;


}}}  // namespace eda.vhdl.parser



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_COMMON_TYPES_HPP_ */
