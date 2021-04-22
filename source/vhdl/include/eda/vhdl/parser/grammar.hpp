#pragma once

#include <eda/vhdl/ast.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>

namespace eda::vhdl::parser {

struct design_file_class;
using design_file_type = boost::spirit::x3::rule<design_file_class, ast::design_file>;

}  // namespace eda::vhdl::parser

namespace eda::vhdl::parser {

parser::design_file_type grammar();

}  // namespace eda::vhdl::parser
