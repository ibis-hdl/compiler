#pragma once

#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/position_cache.hpp>

#include <tuple>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {

template <typename IteratorT>
class literal_parser {
public:
    using position_proxy = typename ast::position_cache<IteratorT>::proxy;

public:
    std::tuple<bool, ast::bit_string_literal> bit_string_literal(position_proxy const& cache) const;

    std::tuple<bool, ast::decimal_literal> decimal_literal(position_proxy const& cache) const;

    std::tuple<bool, ast::based_literal> based_literal(position_proxy const& cache) const;

private:
    template <typename ParserType, typename AttrType>
    std::tuple<bool, AttrType> parse(ParserType const& numeric_parser, AttrType& attr,
                                     position_proxy const& cache_proxy) const;
};

}  // namespace testsuite
