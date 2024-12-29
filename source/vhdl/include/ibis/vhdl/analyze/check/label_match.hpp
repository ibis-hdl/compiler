//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/optional.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/label.hpp>

#include <ibis/util/pretty_typename.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

#include <type_traits>
#include <tuple>
#include <format>

namespace ibis::vhdl::ast {
struct architecture_body;
struct block_statement;
struct case_statement;
struct configuration_declaration;
struct entity_declaration;
struct generate_statement;
struct if_statement;
struct loop_statement;
struct package_body;
struct package_declaration;
struct process_statement;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::analyze {

///
/// check for matching label pairs
///
class label_match {
public:
    enum class result { OK, MISMATCH, ILLFORMED };

public:
    result operator()(ast::architecture_body const& node) const;
    result operator()(ast::block_statement const& node) const;
    result operator()(ast::case_statement const& node) const;
    result operator()(ast::configuration_declaration const& node) const;
    result operator()(ast::entity_declaration const& node) const;
    result operator()(ast::generate_statement const& node) const;
    result operator()(ast::if_statement const& node) const;
    result operator()(ast::loop_statement const& node) const;
    result operator()(ast::package_body const& node) const;
    result operator()(ast::package_declaration const& node) const;
    result operator()(ast::process_statement const& node) const;

private:
    static result compare(ast::optional<ast::label> const& start_label,
                          ast::optional<ast::label> const& end_label);
    static result compare(ast::identifier const& start_identifier,
                          ast::optional<ast::identifier> const& end_identifier);
};

///
/// Helper functions to extract {start, end}_label of nodes for use with the diagnostic of error
/// handler. VHDL LRM states by convention two types of AST nodes with labels:
/// - node with label pair of label and end_label
/// - node with identifier pair of  identifier and end_identifier
///
/// This helper function `labels_of` allows to handle both kind of nodes in the same manner.
///
/// Concept: @see [coliru]/(https://coliru.stacked-crooked.com/a/997b3e9fa6e3cdcb)
///
namespace detail {

template <typename NodeT>
concept has_identifier = requires(const NodeT& node) {
    { node.identifier } -> std::convertible_to<ast::identifier>;
};

template <typename NodeT>
concept has_optional_end_identifier = requires(const NodeT& node) {
    { node.end_identifier.get() } -> std::convertible_to<ast::identifier>;
};

template <typename NodeT>
concept has_label = requires(const NodeT& node) {
    { node.label } -> std::convertible_to<ast::label>;
};

template <typename NodeT>
concept has_optional_label = requires(const NodeT& node) {
    { node.label.get() } -> std::convertible_to<ast::label>;
};

template <typename NodeT>
concept has_optional_end_label = requires(const NodeT& node) {
    { node.end_label.get() } -> std::convertible_to<ast::label>;
};

}  // namespace detail

///
/// @brief Extract the label and their identifier from given node.
///
/// Here it's assumed that the identifier follow the convention as they are
/// paired as:
/// - label - end_label
/// - identifier - end_identifier (where first identifier is mandatory)
///
/// @tparam NodeT The node type.
/// @param node Node to be proceed.
/// @return std::tuple<ast::identifier const&, ast::identifier const&>
///
template <typename NodeT>
std::tuple<ast::identifier, ast::identifier> inline labels_of(NodeT const& node)
{
    static_assert(std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>,  // --
                  "AST node must be derived from ast::position_tagged to provide diagnostics");

    // It is assumed that the AST nodes are correctly initialized with their labels/identifiers.
    // Otherwise boost::optional's `.get()` throws an exception.
    // Using C++20 concept here, which find concepts by looking at the algorithms that use them.
    try {
        if constexpr (detail::has_optional_label<NodeT> && detail::has_optional_end_label<NodeT>) {
            // e.g. ast::if_statement
            return { node.label.get(), node.end_label.get() };
        }
        else if constexpr (detail::has_label<NodeT> && detail::has_optional_end_label<NodeT>) {
            // e.g. ast::block_statement
            return { node.label, node.end_label.get() };
        }
        else if constexpr (detail::has_identifier<NodeT> &&
                           detail::has_optional_end_identifier<NodeT>) {
            // e.g. ast::architecture_body
            return { node.identifier, node.end_identifier.get() };
        }
        else {
            // obviously this function was called with an AST node which doesn't have any labels
            static_assert(sizeof(NodeT) == 0, "unexpected node with identifier/label pairs");
        }
    }
    catch (boost::bad_optional_access const& e) {
        // An access to optional's .get() has been performed, where the optional doesn't contain
        // a value. This shouldn't happen since Spirit.X3 grammar should prevent this.
        // @todo [Assert] Render Warning only so we can continue with misleading error message.
        std::cerr << std::format("caught '{}' by accessing AST node '{}'\n",  // --
                                 e.what(), util::pretty_typename<NodeT>().str());
    }

    // we shouldn't be here, but isn't critical
    return { {}, {} };
}

}  // namespace ibis::vhdl::analyze
