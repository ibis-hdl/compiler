/*
 * grammar.hpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_

#include <eda/vhdl/ast.hpp>

#include <eda/support/boost/spirit_x3.hpp>

// clang-format off
#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <eda/compiler/warnings_on.hpp>
// clang-format on

namespace eda {
namespace vhdl {
namespace parser {

struct design_file_class;

using design_file_type = x3::rule<design_file_class, ast::design_file>;

#if !defined(DOXYGEN)
BOOST_SPIRIT_DECLARE(design_file_type);
#endif

parser::design_file_type const& grammar();

} // namespace parser
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_HPP_ */
