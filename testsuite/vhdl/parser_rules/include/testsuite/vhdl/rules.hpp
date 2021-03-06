//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/grammar_decl.hpp>

namespace testsuite::vhdl::parser {

namespace parser = ibis::vhdl::parser;

parser::abstract_literal_type abstract_literal();
parser::actual_part_type actual_part();
parser::aggregate_type aggregate();
parser::alias_declaration_type alias_declaration();
parser::allocator_type allocator();
parser::architecture_body_type architecture_body();
parser::assertion_type assertion();
parser::association_list_type association_list();
parser::attribute_name_type attribute_name();
parser::attribute_specification_type attribute_specification();
parser::based_literal_type based_literal();
parser::binding_indication_type binding_indication();
parser::bit_string_literal_type bit_string_literal();
parser::block_configuration_type block_configuration();
parser::block_header_type block_header();
parser::block_statement_type block_statement();
parser::case_statement_type case_statement();
parser::character_literal_type character_literal();
parser::choices_type choices();
parser::component_configuration_type component_configuration();
parser::component_declaration_type component_declaration();
parser::component_instantiation_statement_type component_instantiation_statement();
parser::component_specification_type component_specification();
parser::concurrent_assertion_statement_type concurrent_assertion_statement();
parser::conditional_signal_assignment_type conditional_signal_assignment();
parser::configuration_declaration_type configuration_declaration();
parser::configuration_specification_type configuration_specification();
parser::constant_declaration_type constant_declaration();
parser::constrained_array_definition_type constrained_array_definition();
parser::constraint_type constraint();
parser::context_clause_type context_clause();
parser::decimal_literal_type decimal_literal();
parser::disconnection_specification_type disconnection_specification();
parser::discrete_range_type discrete_range();
parser::element_declaration_type element_declaration();
parser::entity_aspect_type entity_aspect();
parser::entity_declaration_type entity_declaration();
parser::enumeration_type_definition_type enumeration_type_definition();
parser::exit_statement_type exit_statement();
parser::expression_type expression();
parser::factor_type factor();
parser::file_declaration_type file_declaration();
parser::file_open_information_type file_open_information();
parser::formal_part_type formal_part();
parser::function_call_type function_call();
parser::generate_statement_type generate_statement();
parser::generic_clause_type generic_clause();
parser::generic_map_aspect_type generic_map_aspect();
parser::group_declaration_type group_declaration();
parser::group_template_declaration_type group_template_declaration();
parser::identifier_type identifier();
parser::identifier_list_type identifier_list();
parser::if_statement_type if_statement();
parser::index_constraint_type index_constraint();
parser::index_subtype_definition_type index_subtype_definition();
parser::indexed_name_type indexed_name();
parser::integer_type integer();
parser::interface_constant_declaration_type interface_constant_declaration();
parser::interface_file_declaration_type interface_file_declaration();
parser::interface_signal_declaration_type interface_signal_declaration();
parser::interface_variable_declaration_type interface_variable_declaration();
parser::library_clause_type library_clause();
parser::literal_type literal();
parser::loop_statement_type loop_statement();
parser::name_type name();
parser::next_statement_type next_statement();
parser::numeric_literal_type numeric_literal();
parser::package_body_type package_body();
parser::package_declaration_type package_declaration();
parser::parameter_specification_type parameter_specification();
parser::physical_literal_type physical_literal();
parser::physical_type_definition_type physical_type_definition();
parser::port_clause_type port_clause();
parser::port_map_aspect_type port_map_aspect();
parser::primary_type primary();
parser::primary_unit_declaration_type primary_unit_declaration();
parser::procedure_call_type procedure_call();
parser::process_statement_type process_statement();
parser::qualified_expression_type qualified_expression();
parser::range_constraint_type range_constraint();
parser::record_type_definition_type record_type_definition();
parser::relation_type relation();
parser::return_statement_type return_statement();
parser::secondary_unit_declaration_type secondary_unit_declaration();
parser::selected_signal_assignment_type selected_signal_assignment();
parser::sequential_statement_type sequential_statement();
parser::shift_expression_type shift_expression();
parser::signal_assignment_statement_type signal_assignment_statement();
parser::signal_declaration_type signal_declaration();
parser::signal_list_type signal_list();
parser::simple_expression_type simple_expression();
parser::slice_name_type slice_name();
parser::string_literal_type string_literal();
parser::subprogram_body_type subprogram_body();
parser::subprogram_specification_type subprogram_specification();
parser::subtype_declaration_type subtype_declaration();
parser::subtype_indication_type subtype_indication();
parser::term_type term();
parser::type_conversion_type type_conversion();
parser::type_declaration_type type_declaration();
parser::type_definition_type type_definition();
parser::unconstrained_array_definition_type unconstrained_array_definition();
parser::use_clause_type use_clause();
parser::variable_assignment_statement_type variable_assignment_statement();
parser::variable_declaration_type variable_declaration();
parser::wait_statement_type wait_statement();
parser::waveform_type waveform();

}  // namespace testsuite::vhdl::parser
