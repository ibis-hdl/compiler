#pragma once

#include <ibis/vhdl/ast_fwd.hpp>
#include <ibis/vhdl/parser/error_handler.hpp>

#include <tuple>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {

template <typename IteratorT>
class literal_parser {
public:
    using error_handler_type = parser::error_handler<IteratorT>;
    using position_proxy = typename parser::position_cache<IteratorT>::proxy;

public:
    std::tuple<bool, ast::bit_string_literal> bit_string_literal(  // --
        position_proxy& position_cache_proxy, error_handler_type& error_handler) const;

    std::tuple<bool, ast::decimal_literal> decimal_literal(  // --
        position_proxy& position_cache_proxy, error_handler_type& error_handler) const;

    std::tuple<bool, ast::based_literal> based_literal(  // --
        position_proxy& position_cache_proxy, error_handler_type& error_handler) const;

private:
    template <typename ParserType, typename AttrType>
    std::tuple<bool, AttrType> parse(                      // --
        ParserType const& numeric_parser, AttrType& attr,  // --
        position_proxy& position_cache_proxy, error_handler_type& error_handler) const;
};

}  // namespace testsuite

namespace testsuite {

/// Explicit template instantiation declaration
extern template class literal_parser<parser::iterator_type>;

}  // namespace testsuite
