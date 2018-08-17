/*
 * error_handler.cpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/ast/position_cache_def.hpp>
#include <eda/vhdl/parser/iterator_type.hpp> // for explicit template instantiation

#include <eda/support/boost/locale.hpp>

#include <eda/color/message.hpp>
#include <eda/util/string/position_indicator.hpp>

#include <iostream>

#include <eda/util/cxx_bug_fatal.hpp>


namespace eda { namespace vhdl { namespace parser {


// AST/parse related error handler
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    iterator_type error_pos, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    os << format(translate("in file {1}, line {2}:\n"))
          % file_name()
          % line_number(error_pos)
          ;

    os << color::message::error(translate("Parse ERROR")) << ": "
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry"))
       << "\n"
          ;

    // erroneous source snippet
    iterator_type start = get_line_start(error_pos);
    os << current_line(start);
    os << std::endl;

    // error indicator
    using eda::util::position_indicator;
    os << position_indicator(start, error_pos, tab_sz, '_')
	   << "^_"
	   << std::endl;


    return x3::error_handler_result::fail;
}


template <typename Iterator>
std::string error_handler<Iterator>::file_name() const
{
    if (!filename.empty()) return filename;

    return boost::locale::translate("Unknown File Name", "<unknown>");
}


}}} // namespace eda.vhdl.parser


namespace eda { namespace vhdl { namespace parser {


// Explicit template instantiation
template class error_handler<parser::iterator_type>;


}}} // namespace eda.vhdl.parser

