//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/optional.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>

// G++-11  requires full defined types
#include <ibis/vhdl/ast/node/identifier.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <type_traits>
#include <tuple>

namespace ibis::vhdl::ast {
struct architecture_body;
struct block_statement;
struct case_statement;
struct configuration_declaration;
struct entity_declaration;
struct generate_statement;
struct identifier;
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
    static result compare(ast::identifier const& start_label,
                          ast::optional<ast::identifier> const& end_label);
    static result compare(ast::optional<ast::identifier> const& start_label,
                          ast::optional<ast::identifier> const& end_label);
};

///
/// Helper functions to extract {start, end}_label of nodes for use with the error
/// handler. Basically there are by convention 2 types of AST nodes with labels
/// here:
///
/// - the 'classic' label pair with label and end_label
/// - blocks with identifier and end_identifier (aka end label)
///
/// With this, labels_of helper function has the same API for the two labeled
/// nodes.
///
/// @todo [C++20] From C++ it's required to detect that a node type has the member `label`
/// or `identifier`. The library fundamentals TS v2 provide this; here is a
/// copy&paste from [std::experimental::is_detected](
/// https://en.cppreference.com/w/cpp/experimental/is_detected)
/// used since C++17 (as today) hasn't it.
///
namespace label_util {

namespace detail {

template <class Default, class AlwaysVoid, template <class...> class Op, class... Args>
struct detector {
    using value_t = std::false_type;
    using type = Default;
};

template <class Default, template <class...> class Op, class... Args>
struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
    // Note that std::void_t is a C++17 feature
    using value_t = std::true_type;
    using type = Op<Args...>;
};

}  // namespace detail

struct nonesuch {
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
};

template <template <class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template <template <class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

template <class Default, template <class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

}  // namespace label_util

namespace label_util {

template <class T>
using has_label = decltype(std::declval<T&>().label);

template <class T>
using has_identifier = decltype(std::declval<T&>().identifier);

}  // namespace label_util

///
/// @brief Extract the label and their identifier from given node.
///
/// Here it's assumed that the identifier follow the convention as they are
/// paired as:
/// - label - end_label (the classical VHDL labels) or
/// - identifier - end_identifier (where identifier is mandatory)
///
/// @tparam NodeT The node type.
/// @param node Node to be proceed.
/// @return std::tuple<ast::identifier const&, ast::identifier const&>
///
template <typename NodeT>
std::tuple<ast::identifier, ast::identifier> inline labels_of(NodeT const& node)
{
    static_assert(std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>, // --
        "AST node must be derived from ast::position_tagged to provide diagnostics");

    if constexpr (label_util::is_detected<label_util::has_label, NodeT>::value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(node.label)>,
                                     ast::optional<ast::identifier>>) {
            // optional start and end label; e.g. ast::if_statement
            return { *node.label, *node.end_label };
        }
        else {
            // mandatory start label, optional end label; e.g. ast::block_statement
            return { node.label, *node.end_label };
        }
    }
    else if constexpr (label_util::is_detected<label_util::has_identifier, NodeT>::value) {
        // mandatory identifier, optional identifier; e.g. ast::architecture_body
        return { node.identifier, *node.end_identifier };
    }
    else {
        // obviously this function was called with an AST node which doesn't have any labels
        cxx_unreachable_bug_triggered();
    }
}

}  // namespace ibis::vhdl::analyze
