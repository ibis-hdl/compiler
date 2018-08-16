/*
 * syntax.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/analyze/syntax.hpp>

#include <eda/vhdl/analyze/check/label_match.hpp>

#include <eda/support/boost/locale.hpp>

#include <eda/util/cxx_bug_fatal.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace analyze {


template<typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view const& node_name) const
{
	label_match check_label{};

    using boost::locale::format;
    using boost::locale::translate;

    switch(check_label(node)) {
		case label_match::result::OK:
			return true;

		case label_match::result::MISMATCH:
			error_handler(node,
				(format(translate(
					"Label mismatch in {1}"
					))
					% node_name // XXX lookup for pretty name (on_error_base::ruleid_map)
				).str()
			);
			++context.error_count;
			return false;

		case label_match::result::ILLFORMED:
			error_handler(node,
				(format(translate(
					"Label ill-formed in {1}"
					))
					% node_name // XXX lookup for pretty name (on_error_base::ruleid_map)
				).str()
			);
			++context.error_count;
			return false;
		default:
			cxx_unreachable_bug_triggered();
	}
	cxx_unreachable_bug_triggered();
}


void syntax_worker::operator()(ast::block_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::case_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::generate_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}


void syntax_worker::operator()(ast::if_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::loop_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::process_statement const& node, std::string_view const& node_name) const {

	//os << node_name << "\n";

	label_matches(node, node_name);
}


} } } // namespace eda.vhdl.analyze



#if 0
namespace eda { namespace vhdl { namespace analyze {

namespace tag {
struct enabled { };
struct disabled { };
}
using verbose = tag::enabled;


/**
 * Debug Indent printer
 */
template<typename T>
struct syntax::indent_logging<T, typename std::enable_if_t<std::is_same_v<T, tag::disabled>>>
{
    indent_logging(syntax const&, const char* const)
    {  }
};

template<typename T>
struct syntax::indent_logging<T, typename std::enable_if_t<std::is_same_v<T, tag::enabled>>>
{
    util::indent_ostream&                           os;
    const char* const                               node_name;

    indent_logging(syntax const& s, const char* const node_name_)
    : os{ s.os }
    , node_name{ node_name_ }
    {
        os << util::increase_indent
           << "<" << node_name << ">\n";
    }

    ~indent_logging()
    {
        os << "</" << node_name << ">\n"
           << util::decrease_indent;
    }
};

} } } // namespace eda.vhdl.analyze

#endif


