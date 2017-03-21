/*
 * ast_printer.cpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast_printer.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>
#include <eda/exception.hpp>

#include <boost/exception/all.hpp>


namespace eda { namespace vhdl93 { namespace ast {


void printer::tab(uint16_t spaces) {

    for (unsigned i = 0; i != spaces; ++i)
        os << ' ';
}


void printer::operator()(abstract_literal const& node) const {
	boost::apply_visitor(*this, node);
}



#if 0
void printer::operator()(access_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(actual_designator const& node) const {

}
#endif


#if 0
void printer::operator()(actual_parameter_part const& node) const {

}
#endif


#if 0
void printer::operator()(actual_part const& node) const {

}
#endif


#if 0
void printer::operator()(adding_operator const& node) const {

}
#endif


#if 0
void printer::operator()(aggregate const& node) const {

}
#endif


#if 0
void printer::operator()(alias_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(alias_designator const& node) const {

}
#endif


#if 0
void printer::operator()(allocator const& node) const {

}
#endif


#if 0
void printer::operator()(architecture_body const& node) const {

}
#endif


#if 0
void printer::operator()(architecture_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(architecture_statement_part const& node) const {

}
#endif


#if 0
void printer::operator()(array_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(assertion const& node) const {

}
#endif


#if 0
void printer::operator()(assertion_statement const& node) const {

}
#endif


#if 0
void printer::operator()(association_element const& node) const {

}
#endif


#if 0
void printer::operator()(association_list const& node) const {

}
#endif


#if 0
void printer::operator()(attribute_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(attribute_designator const& node) const {

}
#endif


#if 0
void printer::operator()(attribute_name const& node) const {

}
#endif


#if 0
void printer::operator()(attribute_specification const& node) const {

}
#endif


#if 0
void printer::operator()(base const& node) const {

}
#endif


#if 0
void printer::operator()(base_specifier const& node) const {

}
#endif


#if 0
void printer::operator()(base_unit_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(based_integer const& node) const {

}
#endif



void printer::operator()(based_literal const& node) const {

}



#if 0
void printer::operator()(basic_character const& node) const {

}
#endif


#if 0
void printer::operator()(basic_graphic_character const& node) const {

}
#endif


#if 0
void printer::operator()(basic_identifier const& node) const {

}
#endif


#if 0
void printer::operator()(binding_indication const& node) const {

}
#endif



void printer::operator()(bit_string_literal const& node) const {
    os << node;
}



#if 0
void printer::operator()(bit_value const& node) const {

}
#endif


#if 0
void printer::operator()(block_configuration const& node) const {

}
#endif


#if 0
void printer::operator()(block_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(block_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(block_header const& node) const {

}
#endif


#if 0
void printer::operator()(block_specification const& node) const {

}
#endif


#if 0
void printer::operator()(block_statement const& node) const {

}
#endif


#if 0
void printer::operator()(block_statement_part const& node) const {

}
#endif


#if 0
void printer::operator()(case_statement const& node) const {

}
#endif


#if 0
void printer::operator()(case_statement_alternative const& node) const {

}
#endif



void printer::operator()(character_literal const& node) const {

}



#if 0
void printer::operator()(choice const& node) const {

}
#endif


#if 0
void printer::operator()(choices const& node) const {

}
#endif


#if 0
void printer::operator()(component_configuration const& node) const {

}
#endif


#if 0
void printer::operator()(component_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(component_instantiation_statement const& node) const {

}
#endif


#if 0
void printer::operator()(component_specification const& node) const {

}
#endif


#if 0
void printer::operator()(composite_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(concurrent_assertion_statement const& node) const {

}
#endif


#if 0
void printer::operator()(concurrent_procedure_call_statement const& node) const {

}
#endif


#if 0
void printer::operator()(concurrent_signal_assignment_statement const& node) const {

}
#endif


#if 0
void printer::operator()(concurrent_statement const& node) const {

}
#endif


#if 0
void printer::operator()(condition const& node) const {

}
#endif


#if 0
void printer::operator()(condition_clause const& node) const {

}
#endif


#if 0
void printer::operator()(conditional_signal_assignment const& node) const {

}
#endif


#if 0
void printer::operator()(conditional_waveforms const& node) const {

}
#endif


#if 0
void printer::operator()(configuration_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(configuration_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(configuration_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(configuration_item const& node) const {

}
#endif


#if 0
void printer::operator()(configuration_specification const& node) const {

}
#endif


#if 0
void printer::operator()(constant_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(constrained_array_definition const& node) const {

}
#endif


#if 0
void printer::operator()(constraint const& node) const {

}
#endif


#if 0
void printer::operator()(context_clause const& node) const {

}
#endif


#if 0
void printer::operator()(context_item const& node) const {

}
#endif



void printer::operator()(decimal_literal const& node) const {
    os << node;
}



#if 0
void printer::operator()(declaration const& node) const {

}
#endif


#if 0
void printer::operator()(delay_mechanism const& node) const {

}
#endif


#if 0
void printer::operator()(design_file const& node) const {

}
#endif


#if 0
void printer::operator()(design_unit const& node) const {

}
#endif


#if 0
void printer::operator()(designator const& node) const {

}
#endif


#if 0
void printer::operator()(direction const& node) const {

}
#endif


#if 0
void printer::operator()(disconnection_specification const& node) const {

}
#endif


#if 0
void printer::operator()(discrete_range const& node) const {

}
#endif


#if 0
void printer::operator()(element_association const& node) const {

}
#endif


#if 0
void printer::operator()(element_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(element_subtype_definition const& node) const {

}
#endif


#if 0
void printer::operator()(entity_aspect const& node) const {

}
#endif


#if 0
void printer::operator()(entity_class const& node) const {

}
#endif


#if 0
void printer::operator()(entity_class_entry const& node) const {

}
#endif


#if 0
void printer::operator()(entity_class_entry_list const& node) const {

}
#endif


#if 0
void printer::operator()(entity_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(entity_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(entity_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(entity_designator const& node) const {

}
#endif


#if 0
void printer::operator()(entity_header const& node) const {

}
#endif


#if 0
void printer::operator()(entity_name_list const& node) const {

}
#endif


#if 0
void printer::operator()(entity_specification const& node) const {

}
#endif


#if 0
void printer::operator()(entity_statement const& node) const {

}
#endif


#if 0
void printer::operator()(entity_statement_part const& node) const {

}
#endif


#if 0
void printer::operator()(entity_tag const& node) const {

}
#endif



void printer::operator()(enumeration_literal const& node) const {

}



#if 0
void printer::operator()(enumeration_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(exit_statement const& node) const {

}
#endif


#if 0
void printer::operator()(exponent const& node) const {

}
#endif


#if 0
void printer::operator()(expression const& node) const {

}
#endif


#if 0
void printer::operator()(extended_digit const& node) const {

}
#endif


#if 0
void printer::operator()(extended_identifier const& node) const {

}
#endif


#if 0
void printer::operator()(factor const& node) const {

}
#endif


#if 0
void printer::operator()(file_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(file_logical_name const& node) const {

}
#endif


#if 0
void printer::operator()(file_open_information const& node) const {

}
#endif


#if 0
void printer::operator()(file_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(formal_designator const& node) const {

}
#endif


#if 0
void printer::operator()(formal_parameter_list const& node) const {

}
#endif


#if 0
void printer::operator()(formal_part const& node) const {

}
#endif


#if 0
void printer::operator()(full_type_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(function_call const& node) const {

}
#endif


#if 0
void printer::operator()(generate_statement const& node) const {

}
#endif


#if 0
void printer::operator()(generation_scheme const& node) const {

}
#endif


#if 0
void printer::operator()(generic_clause const& node) const {

}
#endif


#if 0
void printer::operator()(generic_list const& node) const {

}
#endif


#if 0
void printer::operator()(generic_map_aspect const& node) const {

}
#endif


#if 0
void printer::operator()(graphic_character const& node) const {

}
#endif


#if 0
void printer::operator()(group_constituent const& node) const {

}
#endif


#if 0
void printer::operator()(group_constituent_list const& node) const {

}
#endif


#if 0
void printer::operator()(group_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(group_template_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(guarded_signal_specification const& node) const {

}
#endif


#if 0
void printer::operator()(identifier const& node) const {

}
#endif


#if 0
void printer::operator()(identifier_list const& node) const {

}
#endif


#if 0
void printer::operator()(if_statement const& node) const {

}
#endif


#if 0
void printer::operator()(incomplete_type_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(index_constraint const& node) const {

}
#endif


#if 0
void printer::operator()(index_specification const& node) const {

}
#endif


#if 0
void printer::operator()(index_subtype_definition const& node) const {

}
#endif


#if 0
void printer::operator()(indexed_name const& node) const {

}
#endif


#if 0
void printer::operator()(instantiated_unit const& node) const {

}
#endif


#if 0
void printer::operator()(instantiation_list const& node) const {

}
#endif


#if 0
void printer::operator()(integer const& node) const {

}
#endif


#if 0
void printer::operator()(integer_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(interface_constant_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(interface_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(interface_element const& node) const {

}
#endif


#if 0
void printer::operator()(interface_file_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(interface_list const& node) const {

}
#endif


#if 0
void printer::operator()(interface_signal_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(interface_variable_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(iteration_scheme const& node) const {

}
#endif


#if 0
void printer::operator()(label const& node) const {

}
#endif


#if 0
void printer::operator()(letter const& node) const {

}
#endif


#if 0
void printer::operator()(letter_or_digit const& node) const {

}
#endif


#if 0
void printer::operator()(library_clause const& node) const {

}
#endif


#if 0
void printer::operator()(library_unit const& node) const {

}
#endif


#if 0
void printer::operator()(literal const& node) const {

}
#endif


#if 0
void printer::operator()(logical_name const& node) const {

}
#endif


#if 0
void printer::operator()(logical_name_list const& node) const {

}
#endif


#if 0
void printer::operator()(logical_operator const& node) const {

}
#endif


#if 0
void printer::operator()(loop_statement const& node) const {

}
#endif


#if 0
void printer::operator()(miscellaneous_operator const& node) const {

}
#endif


#if 0
void printer::operator()(mode const& node) const {

}
#endif


#if 0
void printer::operator()(multiplying_operator const& node) const {

}
#endif


#if 0
void printer::operator()(name const& node) const {

}
#endif


#if 0
void printer::operator()(next_statement const& node) const {

}
#endif


#if 0
void printer::operator()(null_statement const& node) const {

}
#endif



void printer::operator()(numeric_literal const& node) const {

}



#if 0
void printer::operator()(object_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(operator_symbol const& node) const {

}
#endif


#if 0
void printer::operator()(options const& node) const {

}
#endif


#if 0
void printer::operator()(package_body const& node) const {

}
#endif


#if 0
void printer::operator()(package_body_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(package_body_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(package_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(package_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(package_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(parameter_specification const& node) const {

}
#endif



void printer::operator()(physical_literal const& node) const {

}



#if 0
void printer::operator()(physical_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(port_clause const& node) const {

}
#endif


#if 0
void printer::operator()(port_list const& node) const {

}
#endif


#if 0
void printer::operator()(port_map_aspect const& node) const {

}
#endif


#if 0
void printer::operator()(prefix const& node) const {

}
#endif


#if 0
void printer::operator()(primary const& node) const {

}
#endif


#if 0
void printer::operator()(primary_unit const& node) const {

}
#endif


#if 0
void printer::operator()(procedure_call const& node) const {

}
#endif


#if 0
void printer::operator()(procedure_call_statement const& node) const {

}
#endif


#if 0
void printer::operator()(process_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(process_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(process_statement const& node) const {

}
#endif


#if 0
void printer::operator()(process_statement_part const& node) const {

}
#endif


#if 0
void printer::operator()(qualified_expression const& node) const {

}
#endif


#if 0
void printer::operator()(range const& node) const {

}
#endif


#if 0
void printer::operator()(range_constraint const& node) const {

}
#endif


#if 0
void printer::operator()(record_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(relation const& node) const {

}
#endif


#if 0
void printer::operator()(relational_operator const& node) const {

}
#endif


#if 0
void printer::operator()(report_statement const& node) const {

}
#endif


#if 0
void printer::operator()(return_statement const& node) const {

}
#endif


#if 0
void printer::operator()(scalar_type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(secondary_unit const& node) const {

}
#endif


#if 0
void printer::operator()(secondary_unit_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(selected_name const& node) const {

}
#endif


#if 0
void printer::operator()(selected_signal_assignment const& node) const {

}
#endif


#if 0
void printer::operator()(selected_waveforms const& node) const {

}
#endif


#if 0
void printer::operator()(sensitivity_clause const& node) const {

}
#endif


#if 0
void printer::operator()(sensitivity_list const& node) const {

}
#endif


#if 0
void printer::operator()(sequence_of_statements const& node) const {

}
#endif


#if 0
void printer::operator()(sequential_statement const& node) const {

}
#endif


#if 0
void printer::operator()(shift_expression const& node) const {

}
#endif


#if 0
void printer::operator()(shift_operator const& node) const {

}
#endif


#if 0
void printer::operator()(sign const& node) const {

}
#endif


#if 0
void printer::operator()(signal_assignment_statement const& node) const {

}
#endif


#if 0
void printer::operator()(signal_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(signal_kind const& node) const {

}
#endif


#if 0
void printer::operator()(signal_list const& node) const {

}
#endif


#if 0
void printer::operator()(signature const& node) const {

}
#endif


#if 0
void printer::operator()(simple_expression const& node) const {

}
#endif


#if 0
void printer::operator()(simple_name const& node) const {

}
#endif


#if 0
void printer::operator()(slice_name const& node) const {

}
#endif



void printer::operator()(string_literal const& node) const {

}



#if 0
void printer::operator()(subprogram_body const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_declarative_item const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_declarative_part const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_kind const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_specification const& node) const {

}
#endif


#if 0
void printer::operator()(subprogram_statement_part const& node) const {

}
#endif


#if 0
void printer::operator()(subtype_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(subtype_indication const& node) const {

}
#endif


#if 0
void printer::operator()(suffix const& node) const {

}
#endif


#if 0
void printer::operator()(target const& node) const {

}
#endif


#if 0
void printer::operator()(term const& node) const {

}
#endif


#if 0
void printer::operator()(timeout_clause const& node) const {

}
#endif


#if 0
void printer::operator()(type_conversion const& node) const {

}
#endif


#if 0
void printer::operator()(type_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(type_definition const& node) const {

}
#endif


#if 0
void printer::operator()(type_mark const& node) const {

}
#endif


#if 0
void printer::operator()(unconstrained_array_definition const& node) const {

}
#endif


#if 0
void printer::operator()(use_clause const& node) const {

}
#endif


#if 0
void printer::operator()(variable_assignment_statement const& node) const {

}
#endif


#if 0
void printer::operator()(variable_declaration const& node) const {

}
#endif


#if 0
void printer::operator()(wait_statement const& node) const {

}
#endif


#if 0
void printer::operator()(waveform const& node) const {

}
#endif


} } } // namespace eda.vhdl93.ast

