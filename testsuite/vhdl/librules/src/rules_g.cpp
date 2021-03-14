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
BOOST_SPIRIT_INSTANTIATE(generate_statement_type, iterator_type, context_type);

BOOST_SPIRIT_INSTANTIATE(generic_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_template_declaration_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda