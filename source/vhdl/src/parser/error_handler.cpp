#include <ibis/vhdl/parser/error_handler.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

#include <ibis/vhdl/parser/position_cache.hpp>

#include <ibis/util/string/position_indicator.hpp>

#include <ibis/color/message.hpp>
#include <ibis/color/facet.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <algorithm>
#include <iostream>

namespace ibis::vhdl::parser {

// AST/parse related error handler
template <typename Iterator>
typename error_handler<Iterator>::result_type error_handler<Iterator>::operator()(
    iterator_type error_pos, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    os << format(translate("in file {1}, line {2}:"))  // --
              % position_proxy.file_name()             // {1}
              % position_proxy.line_number(error_pos)  // {2}
       << '\n';

    os << color::message::error(translate("Parse ERROR")) << ": "
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry")) << '\n';

    // erroneous source snippet
    iterator_type start = position_proxy.get_line_start(error_pos);
    os << position_proxy.current_line(start);
    os << '\n';

    // error indicator
    using ibis::util::position_indicator;
    os << position_indicator(start, error_pos, tab_sz, '_') << "^_" << '\n';

    return x3::error_handler_result::fail;
}

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

// Explicit template instantiation
template class error_handler<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
