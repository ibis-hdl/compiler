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

BOOST_SPIRIT_INSTANTIATE(element_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(enumeration_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(exit_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
