/*
 * syntax.cpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#include <eda/vhdl/analyze/syntax.hpp>

#include <eda/vhdl/analyze/check/label_match.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace analyze {


template<typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view const& node_name) const
{
	label_match check_label{};

	if (!check_label(node)) {
    	//os << "label error\n";
    	error_handler(node, check_label.make_error_description(node_name));
    	++context.error_count;

    	return false;
    }

	return true;
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


