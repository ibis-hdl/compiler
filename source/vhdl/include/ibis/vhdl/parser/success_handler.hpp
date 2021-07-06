#pragma once

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/support/utility/lambda_visitor.hpp>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::parser {

///
/// Base class for annotating the AST
///
/// The on_success handler tags the AST with the iterator position for error
/// handling. The on_success handler also ties the AST to a vector of iterator
/// positions for the purpose of subsequent semantic error handling when the
/// program is being compiled.
///
/// The parser's diagnostic_handler utility is responsible to do these since he depends
/// on this informations.
///
/// @note It may be natural to separate the process of tagging to an own class,
/// but this results into a further, nested x3::with<>[] directive near by
/// the error handler self and some parse language aware context data.
/// Also, have a look at [Boost spirit x3 tokenizer with annotation does not work](
/// https://stackoverflow.com/questions/65614720/boost-spirit-x3-tokenizer-with-annotation-does-not-work)
///
/// @note The source is based on the original [x3::annotate_on_success](
/// https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/x3/support/utility/annotate_on_success.hpp)
///
struct success_handler {
    template <typename IteratorT, typename ContextT, typename... Types>
    inline void on_success(IteratorT const& first, IteratorT const& last,
                           ast::variant<Types...>& node, ContextT const& context) const
    {
        node.apply_visitor(x3::make_lambda_visitor<void>(
            [&](auto& node_) { this->on_success(first, last, node_, context); }));
    }

    template <typename NodeT, typename IteratorT, typename ContextT>
    inline void on_success(IteratorT const& first, IteratorT const& last, NodeT& node,
                           ContextT const& context) const
    {
        // to get the type of the context, just uncomment next line
        //struct {} _ = *static_cast<decltype(context)*>(nullptr);

        auto& position_cache_proxy = x3::get<parser::position_cache_tag>(context).get();
        position_cache_proxy.annotate(node, first, last);
    }
};

}  // namespace ibis::vhdl::parser
