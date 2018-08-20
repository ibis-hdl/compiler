/*
 * error_handler.cpp
 *
 *  Created on: 16.08.2018
 *      Author: olaf
 */

#include <eda/vhdl/analyze/error_handler.hpp>
#include <eda/vhdl/ast/position_cache_def.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <eda/support/boost/locale.hpp>

#include <eda/color/message.hpp>
#include <eda/util/string/position_indicator.hpp>

#include <eda/util/make_iomanip.hpp>

#include <eda/util/cxx_bug_fatal.hpp>


namespace eda { namespace vhdl { namespace analyze {


/**
 * Display the `error_message` with diagnostics, where only the tagged error
 * position `where_tag` is given.
 */
template <typename Iterator>
void error_handler<Iterator>::operator()(
    ast::position_tagged const& where_tag, std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    cxx_assert(where_tag.pos_id != ast::position_tagged::MAX_ID, "Node not tagged");

    auto const iterators_of = [this](ast::position_tagged const& tagged_node) {
        auto range = position_cache.position_of(tagged_node);
        return std::make_tuple(range.begin(), range.end(), true /* valid */);
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
    	return util::make_iomanip([&](std::ostream& os) {
    	    using eda::util::position_indicator;
    	    os << position_indicator(start, first, tab_sz, ' ')
    	       << position_indicator(start, last,  tab_sz, '~');
    	});
    };


    auto [error_first, error_last, valid] = iterators_of(where_tag);

    boost::ignore_unused(valid);

    os << format(translate("in file {1}, line {2}:\n"))
          % file_name()
          % line_number(error_first)
          ;

    os << color::message::error(translate("Syntax ERROR")) << ": "
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry"))
       << "\n"
          ;

    // erroneous source snippet
    iterator_type line_start = get_line_start(error_first);
    os << current_line(line_start);
    os << std::endl;

    // error indicator
    using eda::util::position_indicator;
    os << indicator(line_start, error_first, error_last)
	   << translate(" <<-- here")
	   << std::endl;
}


/**
 * Display the `error_message` with diagnostics, where the tagged error
 * position `where_tag` and the associated `start_label` and `stop label` are
 * given.
 */
template <typename Iterator>
void error_handler<Iterator>::operator()(
		ast::position_tagged const& where_tag,
		ast::position_tagged const& start_label, ast::position_tagged const& end_label,
		std::string const& error_message) const
{
    using boost::locale::format;
    using boost::locale::translate;

    cxx_assert(where_tag.pos_id   != ast::position_tagged::MAX_ID, "Node not tagged");
    cxx_assert(start_label.pos_id != ast::position_tagged::MAX_ID, "Node/StartLabel not tagged");
    cxx_assert(end_label.pos_id   != ast::position_tagged::MAX_ID, "Node/EndLabel not tagged");

    // XXX handle label_match::result::ILLFORMED correct -> crash at this state

    auto const iterators_of = [this](ast::position_tagged const& tagged_node) {
        auto range = position_cache.position_of(tagged_node);
        return std::make_tuple(range.begin(), range.end(), true /* valid */);
    };

    auto const indicator = [&](auto& start, auto& first, auto& last) {
    	return util::make_iomanip([&](std::ostream& os) {
    	    using eda::util::position_indicator;
    	    os << position_indicator(start, first, tab_sz, ' ')
    	       << position_indicator(start, last,  tab_sz, '~');
    	});
    };

    auto const source_snippet = [&](ast::position_tagged const& tagged_node, auto const& annotation) {
    	return util::make_iomanip([&](std::ostream& os) {
			auto [first, last, valid] = iterators_of(tagged_node);
			if (valid) {
				/* FixMe: g++ (GCC) 7.3.0 on Windows triggers:
				 * internal compiler error: in finish_member_declaration, at cp/semantics.c:2984
				 * by use of ... = get_line_start(first), the simple below fixes
				 * this  */
				iterator_type line_start = position_cache.get_line_start(first);
				os << current_line(line_start) << "\n"
				   << indicator(line_start, first, last)
				   << annotation;
			}
    	});
    };


    auto [error_first, error_last, valid] = iterators_of(where_tag);

    boost::ignore_unused(error_last);
    boost::ignore_unused(valid);

    os << format(translate("in file {1}, line {2}:\n"))
          % file_name()
          % line_number(error_first)
          ;

    os << color::message::error(translate("Syntax ERROR")) << ": "
       << (!error_message.empty() ? error_message : translate("Unspecified Error, Sorry"))
       << "\n"
          ;

	os << source_snippet(start_label, translate(" <<-- here")) << "\n"
	   << "...\n"
	   << source_snippet(end_label, translate(" <<-- and here"))
		  ;

    os << std::endl;
}


template <typename Iterator>
std::string error_handler<Iterator>::file_name() const
{
    if (!filename.empty()) return filename;

    return boost::locale::translate("Unknown File Name", "<unknown>");
}



}}} // namespace eda.vhdl.analyze



namespace eda { namespace vhdl { namespace analyze {


// Explicit template instantiation
template class error_handler<parser::iterator_type>;


}}} // namespace eda.vhdl.analyze
