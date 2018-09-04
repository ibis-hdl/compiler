/*
 * grammar.cpp
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#include <eda/vhdl/parser/grammar.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda {
namespace vhdl {
namespace parser {

BOOST_SPIRIT_INSTANTIATE(design_file_type, iterator_type, context_type);

parser::design_file_type const& grammar() { return eda::vhdl::parser::design_file; }

} // namespace parser
} // namespace vhdl
} // namespace eda
