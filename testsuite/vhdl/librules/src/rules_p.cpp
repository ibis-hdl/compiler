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

BOOST_SPIRIT_INSTANTIATE(package_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(package_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(parameter_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(physical_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(physical_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(port_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(port_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(primary_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(primary_unit_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(procedure_call_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(process_statement_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
