/*
 * syntax.hpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_


#include <eda/vhdl/ast.hpp>

#include <boost/type_index.hpp>
#include <iostream>


namespace eda { namespace vhdl { namespace analyze {


class syntax : public boost::static_visitor<bool>
{
    std::ostream&                                   os;

public:
    syntax(std::ostream& os_)
    : os{ os_ }
    { }

    bool operator()(abstract_literal const& node);
    bool operator()(access_type_definition const& node);
    bool operator()(actual_designator const& node);
    bool operator()(actual_part const& node);
    bool operator()(aggregate const& node);
    bool operator()(alias_declaration const& node);
    bool operator()(alias_designator const& node);
    bool operator()(allocator const& node);
    bool operator()(architecture_body const& node);
    bool operator()(architecture_statement_part const& node);
    bool operator()(array_type_definition const& node);
    bool operator()(assertion const& node);
    bool operator()(assertion_statement const& node);
    bool operator()(association_element const& node);
    bool operator()(association_list const& node);
    bool operator()(attribute_declaration const& node);
    bool operator()(attribute_name const& node);
    bool operator()(attribute_specification const& node);
    bool operator()(based_literal const& node);
    bool operator()(binding_indication const& node);
    bool operator()(bit_string_literal const& node);
    bool operator()(block_configuration const& node);
    bool operator()(block_declarative_item const& node);
    bool operator()(block_declarative_part const& node);
    bool operator()(block_header const& node);
    bool operator()(block_specification const& node);
    bool operator()(block_statement const& node);
    bool operator()(block_statement_part const& node);
    bool operator()(case_statement const& node);
    bool operator()(case_statement_alternative const& node);
    bool operator()(character_literal const& node);
    bool operator()(choice const& node);
    bool operator()(choices const& node);
    bool operator()(component_configuration const& node);
    bool operator()(component_declaration const& node);
    bool operator()(component_instantiation_statement const& node);
    bool operator()(component_specification const& node);
    bool operator()(composite_type_definition const& node);
    bool operator()(concurrent_assertion_statement const& node);
    bool operator()(concurrent_procedure_call_statement const& node);
    bool operator()(concurrent_signal_assignment_statement const& node);
    bool operator()(concurrent_statement const& node);
    bool operator()(condition_clause const& node);
    bool operator()(conditional_signal_assignment const& node);
    bool operator()(conditional_waveforms const& node);
    bool operator()(configuration_declaration const& node);
    bool operator()(configuration_declarative_item const& node);
    bool operator()(configuration_declarative_part const& node);
    bool operator()(configuration_item const& node);
    bool operator()(configuration_specification const& node);
    bool operator()(constant_declaration const& node);
    bool operator()(constrained_array_definition const& node);
    bool operator()(constraint const& node);
    bool operator()(context_clause const& node);
    bool operator()(context_item const& node);
    bool operator()(decimal_literal const& node);
    bool operator()(delay_mechanism const& node);
    bool operator()(design_file const& node);
    bool operator()(design_unit const& node);
    bool operator()(designator const& node);
    bool operator()(disconnection_specification const& node);
    bool operator()(discrete_range const& node);
    bool operator()(element_association const& node);
    bool operator()(element_declaration const& node);
    bool operator()(entity_aspect const& node);
    bool operator()(entity_class_entry_list const& node);
    bool operator()(entity_declaration const& node);
    bool operator()(entity_declarative_item const& node);
    bool operator()(entity_declarative_part const& node);
    bool operator()(entity_designator const& node);
    bool operator()(entity_header const& node);
    bool operator()(entity_name_list const& node);
    bool operator()(entity_specification const& node);
    bool operator()(entity_statement const& node);
    bool operator()(entity_statement_part const& node);
    bool operator()(entity_tag const& node);
    bool operator()(enumeration_literal const& node);
    bool operator()(enumeration_type_definition const& node);
    bool operator()(exit_statement const& node);
    bool operator()(expression const& node);
    bool operator()(factor_binary_operation const& node);
    bool operator()(factor_unary_operation const& node);
    bool operator()(factor const& node);
    bool operator()(file_declaration const& node);
    bool operator()(file_open_information const& node);
    bool operator()(formal_part const& node);
    bool operator()(function_call const& node);
    bool operator()(generate_statement const& node);
    bool operator()(generation_scheme const& node);
    bool operator()(generic_clause const& node);
    bool operator()(generic_map_aspect const& node);
    bool operator()(group_constituent const& node);
    bool operator()(group_constituent_list const& node);
    bool operator()(group_declaration const& node);
    bool operator()(group_template_declaration const& node);
    bool operator()(guarded_signal_specification const& node);
    bool operator()(identifier const& node);
    bool operator()(identifier_list const& node);
    bool operator()(if_statement const& node);
    bool operator()(index_constraint const& node);
    bool operator()(index_specification const& node);
    bool operator()(index_subtype_definition const& node);
    bool operator()(indexed_name const& node);
    bool operator()(instantiated_unit const& node);
    bool operator()(instantiation_list const& node);
    bool operator()(interface_constant_declaration const& node);
    bool operator()(interface_declaration const& node);
    bool operator()(interface_file_declaration const& node);
    bool operator()(interface_list const& node);
    bool operator()(interface_signal_declaration const& node);
    bool operator()(interface_variable_declaration const& node);
    bool operator()(iteration_scheme const& node);
    bool operator()(library_clause const& node);
    bool operator()(library_unit const& node);
    bool operator()(literal const& node);
    bool operator()(loop_statement const& node);
    bool operator()(name const& node);
    bool operator()(next_statement const& node);
    bool operator()(null_statement const& node);
    bool operator()(numeric_literal const& node);
    bool operator()(options const& node);
    bool operator()(package_body const& node);
    bool operator()(package_body_declarative_item const& node);
    bool operator()(package_body_declarative_part const& node);
    bool operator()(package_declaration const& node);
    bool operator()(package_declarative_item const& node);
    bool operator()(package_declarative_part const& node);
    bool operator()(parameter_specification const& node);
    bool operator()(physical_literal const& node);
    bool operator()(physical_type_definition const& node);
    bool operator()(port_clause const& node);
    bool operator()(port_map_aspect const& node);
    bool operator()(prefix const& node);
    bool operator()(primary const& node);
    bool operator()(primary_unit const& node);
    bool operator()(procedure_call const& node);
    bool operator()(procedure_call_statement const& node);
    bool operator()(process_declarative_item const& node);
    bool operator()(process_declarative_part const& node);
    bool operator()(process_statement const& node);
    bool operator()(qualified_expression const& node);
    bool operator()(range const& node);
    bool operator()(record_type_definition const& node);
    bool operator()(relation const& node);
    bool operator()(report_statement const& node);
    bool operator()(return_statement const& node);
    bool operator()(scalar_type_definition const& node);
    bool operator()(secondary_unit const& node);
    bool operator()(secondary_unit_declaration const& node);
    bool operator()(selected_name const& node);
    bool operator()(selected_signal_assignment const& node);
    bool operator()(selected_waveforms const& node);
    bool operator()(sensitivity_clause const& node);
    bool operator()(sensitivity_list const& node);
    bool operator()(sequence_of_statements const& node);
    bool operator()(sequential_statement const& node);
    bool operator()(shift_expression const& node);
    bool operator()(signal_assignment_statement const& node);
    bool operator()(signal_declaration const& node);
    bool operator()(signal_list_list const& node); // signal_list helper (not in BNF)
    bool operator()(signal_list const& node);
    bool operator()(signature const& node);
    bool operator()(simple_expression const& node);
    bool operator()(slice_name const& node);
    bool operator()(string_literal const& node);
    bool operator()(subprogram_body const& node);
    bool operator()(subprogram_declarative_item const& node);
    bool operator()(subprogram_declarative_part const& node);
    bool operator()(subprogram_specification const& node);
    bool operator()(subtype_declaration const& node);
    bool operator()(subtype_indication const& node);
    bool operator()(suffix const& node);
    bool operator()(target const& node);
    bool operator()(term const& node);
    bool operator()(timeout_clause const& node);
    bool operator()(type_conversion const& node);
    bool operator()(type_declaration const& node);
    bool operator()(type_definition const& node);
    bool operator()(unconstrained_array_definition const& node);
    bool operator()(use_clause const& node);
    bool operator()(variable_assignment_statement const& node);
    bool operator()(variable_declaration const& node);
    bool operator()(wait_statement const& node);
    bool operator()(waveform const& node);
    bool operator()(waveform_element const& node);

    // keywords and miscellaneous
    bool operator()(boost::iterator_range<parser::iterator_type> const& node);
    bool operator()(keyword_token token);

    bool operator()(nullary const& node);
};


} } } // namespace eda.vhdl.analyze


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_ANALYZE_SYNTAX_HPP_ */
