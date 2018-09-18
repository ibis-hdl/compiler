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

BOOST_SPIRIT_INSTANTIATE(identifier_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(identifier_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(if_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_subtype_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(indexed_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(integer_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_variable_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(library_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(loop_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(next_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(numeric_literal_type, iterator_type, context_type);
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
BOOST_SPIRIT_INSTANTIATE(qualified_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(range_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(record_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(relation_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(return_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(secondary_unit_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(selected_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(sequential_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(shift_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(simple_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(slice_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(string_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_indication_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(term_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_conversion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(unconstrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(use_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(variable_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(variable_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(wait_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(waveform_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
