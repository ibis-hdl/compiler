#pragma once

#include <eda/vhdl/ast.hpp>

#include <eda/support/boost/spirit_x3.hpp>

// clang-format off
#include <eda/compiler/warnings_off.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#include <eda/compiler/warnings_on.hpp>
// clang-format on

namespace eda::vhdl::parser {

struct design_file_class;

using design_file_type = boost::spirit::x3::rule<design_file_class, ast::design_file>;

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_DECLARE(design_file_type)
#endif

parser::design_file_type const& grammar();

}  // namespace eda::vhdl::parser
