/*
 * check_label_match.cpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */



#include <eda/vhdl/analyze/check/label_match.hpp>

#include <eda/vhdl/ast/node/allocator.hpp>
#include <eda/vhdl/ast/node/qualified_expression.hpp>

#include <eda/vhdl/ast/node/architecture_body.hpp>
#include <eda/vhdl/ast/node/block_statement.hpp>
#include <eda/vhdl/ast/node/case_statement.hpp>
#include <eda/vhdl/ast/node/configuration_declaration.hpp>
#include <eda/vhdl/ast/node/entity_declaration.hpp>
#include <eda/vhdl/ast/node/generate_statement.hpp>
#include <eda/vhdl/ast/node/if_statement.hpp>
#include <eda/vhdl/ast/node/loop_statement.hpp>
#include <eda/vhdl/ast/node/package_body.hpp>
#include <eda/vhdl/ast/node/package_declaration.hpp>
#include <eda/vhdl/ast/node/process_statement.hpp>

#include <eda/util/string/icompare.hpp>

#include <iostream>


// don't pollute AST's namespace with operators required only here
namespace eda { namespace vhdl { namespace ast {


static inline
bool operator==(ast::identifier const& lhs, ast::identifier const& rhs) {

    return util::icompare(as_string_view(lhs.name), as_string_view(rhs.name));
}


} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace analyze {


label_match::result label_match::compare(ast::identifier const& start_label, ast::optional<ast::identifier> const& end_label) const
{
    if (end_label) {

        bool const label_equal{ start_label == end_label };

        if(label_equal) return result::OK;
        return result::MISMATCH;
    }

    return result::OK;
}


label_match::result label_match::compare(ast::optional<ast::identifier> const& start_label, ast::optional<ast::identifier> const& end_label) const
{
	if (end_label   && !start_label) {
		return result::ILLFORMED;
	}

    if (start_label && end_label) {

        bool const label_equal{ start_label == end_label };

        if(label_equal) return result::OK;
        return result::MISMATCH;
    }

    return result::OK;
}


label_match::result label_match::operator()(ast::architecture_body const& node) const {
    return compare(node.identifier, node.end_identifier);
}


label_match::result label_match::operator()(ast::block_statement const& node) const {
	// block_label mandatory
    return compare(node.label, node.end_label);
}


label_match::result label_match::operator()(ast::case_statement const& node) const {
    return compare(node.label, node.end_label);
}


label_match::result label_match::operator()(ast::configuration_declaration const& node) const {
    return compare(node.identifier, node.end_identifier);
}


label_match::result label_match::operator()(ast::generate_statement const& node) const {
    return compare(node.label, node.end_label);
}


label_match::result label_match::operator()(ast::entity_declaration const& node) const {
    return compare(node.identifier, node.end_identifier);
}


label_match::result label_match::operator()(ast::if_statement const& node) const {
    return compare(node.label, node.end_label);
}


label_match::result label_match::operator()(ast::loop_statement const& node) const {
    return compare(node.label, node.end_label);
}


label_match::result label_match::operator()(ast::package_body const& node) const {
	return compare(node.identifier, node.end_identifier);
}


label_match::result label_match::operator()(ast::package_declaration const& node) const {
	return compare(node.identifier, node.end_identifier);
}


label_match::result label_match::operator()(ast::process_statement const& node) const {
	return compare(node.label, node.end_label);
}


} } } // namespace eda.vhdl.ast

