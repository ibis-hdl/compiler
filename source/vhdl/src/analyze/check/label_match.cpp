//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/analyze/check/label_match.hpp>

#include <ibis/vhdl/ast/node/architecture_body.hpp>
#include <ibis/vhdl/ast/node/block_statement.hpp>
#include <ibis/vhdl/ast/node/case_statement.hpp>
#include <ibis/vhdl/ast/node/configuration_declaration.hpp>
#include <ibis/vhdl/ast/node/entity_declaration.hpp>
#include <ibis/vhdl/ast/node/generate_statement.hpp>
#include <ibis/vhdl/ast/node/if_statement.hpp>
#include <ibis/vhdl/ast/node/loop_statement.hpp>
#include <ibis/vhdl/ast/node/package_body.hpp>
#include <ibis/vhdl/ast/node/package_declaration.hpp>
#include <ibis/vhdl/ast/node/process_statement.hpp>
#include <ibis/vhdl/ast/node/identifier.hpp>
// required due to forward and variant used
#include <ibis/vhdl/ast/node/allocator.hpp>             // IWYU pragma: keep
#include <ibis/vhdl/ast/node/qualified_expression.hpp>  // IWYU pragma: keep

#include <ibis/vhdl/ast/util/optional.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

#include <ibis/util/icompare.hpp>

#include <boost/optional/detail/optional_relops.hpp>

// don't pollute AST's namespace with operators required only here
namespace ibis::vhdl::ast {

inline bool operator==(ast::identifier const& lhs, ast::identifier const& rhs)
{
    return util::icompare(as_string_view(lhs.name), as_string_view(rhs.name));
}

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::analyze {

label_match::result label_match::compare(ast::optional<ast::label> const& start_label,
                                         ast::optional<ast::label> const& end_label)
{
    if (!start_label && end_label) {
        return result::ILLFORMED;
    }

    if (start_label && end_label) {
        if (start_label == end_label) {
            return result::OK;
        }
        return result::MISMATCH;
    }

    return result::OK;
}

label_match::result label_match::compare(ast::identifier const& start_identifier,
                                         ast::optional<ast::identifier> const& end_identifier)
{
    if (end_identifier) {
        if (start_identifier == end_identifier) {
            return result::OK;
        }
        return result::MISMATCH;
    }

    return result::OK;
}

label_match::result label_match::operator()(ast::architecture_body const& node) const
{
    return compare(node.identifier, node.end_identifier);
}

label_match::result label_match::operator()(ast::block_statement const& node) const
{
    return compare(node.label, node.end_label);
}

label_match::result label_match::operator()(ast::case_statement const& node) const
{
    return compare(node.label, node.end_label);
}

label_match::result label_match::operator()(ast::configuration_declaration const& node) const
{
    return compare(node.identifier, node.end_identifier);
}

label_match::result label_match::operator()(ast::generate_statement const& node) const
{
    return compare(node.label, node.end_label);
}

label_match::result label_match::operator()(ast::entity_declaration const& node) const
{
    return compare(node.identifier, node.end_identifier);
}

label_match::result label_match::operator()(ast::if_statement const& node) const
{
    return compare(node.label, node.end_label);
}

label_match::result label_match::operator()(ast::loop_statement const& node) const
{
    return compare(node.label, node.end_label);
}

label_match::result label_match::operator()(ast::package_body const& node) const
{
    return compare(node.identifier, node.end_identifier);
}

label_match::result label_match::operator()(ast::package_declaration const& node) const
{
    return compare(node.identifier, node.end_identifier);
}

label_match::result label_match::operator()(ast::process_statement const& node) const
{
    return compare(node.label, node.end_label);
}

}  // namespace ibis::vhdl::analyze
