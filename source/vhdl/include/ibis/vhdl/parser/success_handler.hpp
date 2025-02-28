//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/ast_context.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/support/utility/lambda_visitor.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <ibis/namespace_alias.hpp>

#include <boost/utility/enable_if.hpp>
// #include <boost/type_index.hpp>

namespace ibis::vhdl::parser {

///
/// Base class for annotating the AST
///
/// The success_handler tags the AST with the iterator position for error
/// handling. The success_handler also ties the AST to a vector of iterator
/// positions for the purpose of subsequent semantic error handling when the
/// program is being compiled.
///
/// @note The source is based on the original [x3::annotate_on_success](
/// https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/annotate_on_success.hpp)
/// This file can't be used here directly since error handler and AST annotation are two different
/// task and classes here. This implies nested x3::with<>[] directive.
///
struct success_handler {
    template <typename IteratorT, typename ContextT, typename... Types>
    void on_success(IteratorT first, IteratorT last, ast::variant<Types...>& node,
                    ContextT const& x3_ctx) const
    {
        node.apply_visitor(x3::make_lambda_visitor<void>(  // --
            [&](auto& node_)                               // --
            {
                this->on_success(first, last, node_, x3_ctx);  // --
            }));
    }

    template <typename NodeT, typename IteratorT, typename ContextT>
    void on_success(IteratorT first, IteratorT last, x3::forward_ast<NodeT>& node,
                    ContextT const& x3_ctx) const
    {
        this->on_success(first, last, node.get(), x3_ctx);
    }

    template <typename NodeT, typename IteratorT, typename ContextT>
    typename boost::disable_if<x3::traits::is_variant<NodeT>>::type on_success(  // --
        IteratorT first, IteratorT last, NodeT& node, ContextT const& x3_ctx) const
    {
        // Hint: to get the type of the context, just uncomment next line
        // struct {} _ = *static_cast<decltype(context)*>(nullptr);
        x3::get<parser::annotator_tag>(x3_ctx).get().annotate(node, first, last);
    }
};

}  // namespace ibis::vhdl::parser
