/*
 * check_label_match.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_

#include <eda/vhdl/ast/util/optional.hpp>

#include <type_traits>
#include <tuple>

namespace eda::vhdl::ast {
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
}  // namespace eda::vhdl::ast

namespace eda {
namespace vhdl {
namespace analyze {

/**
 * check for matching label pairs
 */
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

/**
 * Helper functions to extract {start, end}_label of nodes for use with the error
 * handler. Basically there are by convention 2 types of AST nodes with labels
 * here:
 *
 * - the 'classic' label pair with label and end_label
 * - blocks with identifier and end_identifier (aka end label)
 *
 * From C++ it's required to detect that a node type has the member label
 * or identifier. The library fundamentals TS v2 provide this; here is a
 * copy&paste from
 * [std::experimental::is_detected](https://en.cppreference.com/w/cpp/experimental/is_detected) used
 * since C++17 (as today) hasn't it.
 *
 * With this, labels_of helper function has the same API for the two labeled
 * nodes.
 */
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

template <typename NodeT>
std::tuple<ast::identifier const&, ast::identifier const&> static inline labels_of(
    NodeT const& node)
{
    using tuple_type = std::tuple<ast::identifier const&, ast::identifier const&>;

    /* here it's assumed that the identifier follow the convention as they are
     * paired as:
     * - label - end_label (the classical VHDL labels) or
     * - identifier - end_identifier (where identifier is mandatory) */
    if constexpr (label_util::is_detected<label_util::has_label, NodeT>::value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(node.label)>,
                                     ast::optional<ast::identifier>>) {
            return tuple_type{ *node.label, *node.end_label };
        }
        else {
            // mandatory start label
            return tuple_type{ node.label, *node.end_label };
        }
    }
    else if constexpr (label_util::is_detected<label_util::has_identifier, NodeT>::value) {
        // always mandatory identifier
        return tuple_type{ node.identifier, *node.end_identifier };
    }
    else { /* expect compiler error */
    }
}

}  // namespace analyze
}  // namespace vhdl
}  // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_CHECK_LABEL_MATCH_HPP_ */
