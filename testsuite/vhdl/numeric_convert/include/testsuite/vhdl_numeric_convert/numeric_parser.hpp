/*
 * numeric_parser.hpp
 *
 *  Created on: 29.05.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_
#define TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_


#include <eda/vhdl/ast/bit_string_literal.hpp>
#include <eda/vhdl/ast/decimal_literal.hpp>
#include <eda/vhdl/ast/based_literal.hpp>

#include <tuple>

#include <testsuite/namespace_alias.hpp>


namespace testsuite {


std::tuple<bool, ast::bit_string_literal>
parse_bit_string_literal(std::string const &input);

std::tuple<bool, ast::decimal_literal>
parse_decimal_literal(std::string const &input);

std::tuple<bool, ast::based_literal>
parse_based_literal(std::string const &input);



} // namespace testsuite



#endif /* TESTSUITE_VHDL_NUMERIC_CONVERT_INCLUDE_TESTSUITE_VHDL_NUMERIC_CONVERT_NUMERIC_PARSER_HPP_ */
