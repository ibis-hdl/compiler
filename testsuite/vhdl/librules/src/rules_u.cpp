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

BOOST_SPIRIT_INSTANTIATE(unconstrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(use_clause_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda