/*
 * on_success_base.hpp
 *
 *  Created on: 19.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_SUCCESS_BASE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_SUCCESS_BASE_HPP_

#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/support/utility/lambda_visitor.hpp>
#include <eda/compiler/warnings_on.hpp>

#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace parser {


/**
 * Base class for annotating the AST
 *
 * The on_success handler tags the AST with the iterator position for error
 * handling. The on_success handler also ties the AST to a vector of iterator
 * positions for the purpose of subsequent semantic error handling when the
 * program is being compiled.
 *
 * The parser's error_handler utility is responsible to do these since he depends
 * on this informations.
 *
 * \note It may be natural to separate the process of tagging to an own class,
 *       but this results into a further, nested x3::with<>[] directive near by
 *       the error handler self and some parse language aware context data.
 *
 * \note The source is based on the original [x3::annotate_on_success](
 *       https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/annotate_on_success.hpp)
 */
struct on_success_base
{
    template <typename IteratorT, typename ContextT, typename... Types>
    inline
    void on_success(IteratorT const& first, IteratorT const& last,
                    ast::variant<Types...>& node, ContextT const& context) const
    {
        node.apply_visitor(x3::make_lambda_visitor<void>([&](auto& node_) {
                this->on_success(first, last, node_, context);
            })
        );
    }

    template <typename NodeT, typename IteratorT, typename ContextT>
    inline
    void on_success(IteratorT const& first, IteratorT const& last,
                    NodeT& node, ContextT const& context) const
    {
        auto& error_handler = x3::get<parser::error_handler_tag>(context).get();
        error_handler.annotate(node, first, last);
    }
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_ON_SUCCESS_BASE_HPP_ */
