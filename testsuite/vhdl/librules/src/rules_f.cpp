/*
 * rules.cpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda {
namespace vhdl {
namespace parser {

BOOST_SPIRIT_INSTANTIATE(factor_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_open_information_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(formal_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(function_call_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
