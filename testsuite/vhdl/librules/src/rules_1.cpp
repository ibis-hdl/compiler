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

BOOST_SPIRIT_INSTANTIATE(abstract_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(actual_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(aggregate_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(alias_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(allocator_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(architecture_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(assertion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(association_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(based_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(binding_indication_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(bit_string_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_configuration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_header_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(case_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(character_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(choices_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_configuration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_instantiation_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(concurrent_assertion_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(conditional_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(context_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(decimal_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(disconnection_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(discrete_range_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(element_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(enumeration_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(exit_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(factor_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_open_information_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(formal_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(function_call_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generate_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_template_declaration_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda
