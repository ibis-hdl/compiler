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


bool syntax_worker::success() const {
	return context.error_count == 0;
}


template<typename NodeT>
bool syntax_worker::label_matches(NodeT const& node, std::string_view const& node_name) const
{
	label_match check_label{};

    using boost::locale::format;
    using boost::locale::translate;

    switch(check_label(node)) {
		case label_match::result::OK:
			return true;

		case label_match::result::MISMATCH: {
			auto [start_label, end_label] = labels_of(node);
			error_handler(node, start_label, end_label,
				(format(translate(
					"Label mismatch in {1}"
					))
					% node_name // XXX lookup for pretty name (like on_error_base::ruleid_map)
				).str()
			);
			++context.error_count;
			return false;
		}

		case label_match::result::ILLFORMED: {
			auto [start_label, end_label] = labels_of(node);
			error_handler(node, start_label, end_label,
				(format(translate(
					"Label ill-formed in {1}"
					))
					% node_name // XXX lookup for pretty name (like on_error_base::ruleid_map)
				).str()
			);
			++context.error_count;
			return false;
		}

		default:
			cxx_unreachable_bug_triggered();
	}
	cxx_unreachable_bug_triggered();
}


void syntax_worker::operator()(ast::architecture_body const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::block_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::case_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::configuration_declaration const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::entity_declaration const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::generate_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::if_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::loop_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::package_body const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::package_declaration const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}

void syntax_worker::operator()(ast::process_statement const& node, std::string_view const& node_name) const {
	label_matches(node, node_name);
}


} } } // namespace eda.vhdl.analyze

