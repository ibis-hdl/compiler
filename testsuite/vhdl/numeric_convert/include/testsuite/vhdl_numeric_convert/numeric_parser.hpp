/*
 * numeric_parser.hpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_
#define TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_


#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast/position_cache.hpp>

#include <tuple>

#include <testsuite/namespace_alias.hpp>


namespace testsuite {


template<typename IteratorT>
class literal_parser
{
public:
    using position_proxy = typename ast::position_cache<IteratorT>::proxy;

public:
    std::tuple<bool, ast::bit_string_literal>
    bit_string_literal(position_proxy const& cache) const;

    std::tuple<bool, ast::decimal_literal>
    decimal_literal(position_proxy const& cache) const;

    std::tuple<bool, ast::based_literal>
    based_literal(position_proxy const& cache) const;

private:
    template<typename ParserType, typename AttrType>
    std::tuple<bool, AttrType> parse(ParserType const& numeric_parser, AttrType& attr,
                                     position_proxy const& cache_proxy) const;
};

} // namespace testsuite


#endif /* TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_ */
