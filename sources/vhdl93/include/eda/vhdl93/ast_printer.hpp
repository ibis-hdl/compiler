/*
 * ast_printer.hpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_


#include <eda/vhdl93/ast.hpp>

#include <ostream>


namespace eda { namespace vhdl93 { namespace ast {


class ast_printer
{
    std::ostream&   os;
    uint16_t        indent;
    uint16_t const  tab_size { 4 };

    void tab(uint16_t spaces);

public:
    // ...
    ast_printer(std::ostream& out, uint16_t indent = 0)
    : os{ out }, indent { indent }
    { }

    void operator()(abstract_literal const& node) const;
//    void operator()(access_type_definition const& node) const;
//    void operator()(actual_designator const& node) const;
//    void operator()(actual_parameter_part const& node) const;
//    void operator()(actual_part const& node) const;
//    void operator()(adding_operator const& node) const;
//    void operator()(aggregate const& node) const;
//    void operator()(alias_declaration const& node) const;
//    void operator()(alias_designator const& node) const;
//    void operator()(allocator const& node) const;
//    void operator()(architecture_body const& node) const;
//    void operator()(architecture_declarative_part const& node) const;
//    void operator()(architecture_statement_part const& node) const;
//    void operator()(array_type_definition const& node) const;
//    void operator()(assertion const& node) const;
//    void operator()(assertion_statement const& node) const;
//    void operator()(association_element const& node) const;
//    void operator()(association_list const& node) const;
//    void operator()(attribute_declaration const& node) const;
//    void operator()(attribute_designator const& node) const;
//    void operator()(attribute_name const& node) const;
//    void operator()(attribute_specification const& node) const;
//    void operator()(base const& node) const;
//    void operator()(base_specifier const& node) const;
//    void operator()(base_unit_declaration const& node) const;
//    void operator()(based_integer const& node) const;
    void operator()(based_literal const& node) const;
//    void operator()(basic_character const& node) const;
//    void operator()(basic_graphic_character const& node) const;
//    void operator()(basic_identifier const& node) const;
//    void operator()(binding_indication const& node) const;
    void operator()(bit_string_literal const& node) const;
//    void operator()(bit_value const& node) const;
//    void operator()(block_configuration const& node) const;
//    void operator()(block_declarative_item const& node) const;
//    void operator()(block_declarative_part const& node) const;
//    void operator()(block_header const& node) const;
//    void operator()(block_specification const& node) const;
//    void operator()(block_statement const& node) const;
//    void operator()(block_statement_part const& node) const;
//    void operator()(case_statement const& node) const;
//    void operator()(case_statement_alternative const& node) const;
    void operator()(character_literal const& node) const;
//    void operator()(choice const& node) const;
//    void operator()(choices const& node) const;
//    void operator()(component_configuration const& node) const;
//    void operator()(component_declaration const& node) const;
//    void operator()(component_instantiation_statement const& node) const;
//    void operator()(component_specification const& node) const;
//    void operator()(composite_type_definition const& node) const;
//    void operator()(concurrent_assertion_statement const& node) const;
//    void operator()(concurrent_procedure_call_statement const& node) const;
//    void operator()(concurrent_signal_assignment_statement const& node) const;
//    void operator()(concurrent_statement const& node) const;
//    void operator()(condition const& node) const;
//    void operator()(condition_clause const& node) const;
//    void operator()(conditional_signal_assignment const& node) const;
//    void operator()(conditional_waveforms const& node) const;
//    void operator()(configuration_declaration const& node) const;
//    void operator()(configuration_declarative_item const& node) const;
//    void operator()(configuration_declarative_part const& node) const;
//    void operator()(configuration_item const& node) const;
//    void operator()(configuration_specification const& node) const;
//    void operator()(constant_declaration const& node) const;
//    void operator()(constrained_array_definition const& node) const;
//    void operator()(constraint const& node) const;
//    void operator()(context_clause const& node) const;
//    void operator()(context_item const& node) const;
    void operator()(decimal_literal const& node) const;
//    void operator()(declaration const& node) const;
//    void operator()(delay_mechanism const& node) const;
//    void operator()(design_file const& node) const;
//    void operator()(design_unit const& node) const;
//    void operator()(designator const& node) const;
//    void operator()(direction const& node) const;
//    void operator()(disconnection_specification const& node) const;
//    void operator()(discrete_range const& node) const;
//    void operator()(element_association const& node) const;
//    void operator()(element_declaration const& node) const;
//    void operator()(element_subtype_definition const& node) const;
//    void operator()(entity_aspect const& node) const;
//    void operator()(entity_class const& node) const;
//    void operator()(entity_class_entry const& node) const;
//    void operator()(entity_class_entry_list const& node) const;
//    void operator()(entity_declaration const& node) const;
//    void operator()(entity_declarative_item const& node) const;
//    void operator()(entity_declarative_part const& node) const;
//    void operator()(entity_designator const& node) const;
//    void operator()(entity_header const& node) const;
//    void operator()(entity_name_list const& node) const;
//    void operator()(entity_specification const& node) const;
//    void operator()(entity_statement const& node) const;
//    void operator()(entity_statement_part const& node) const;
//    void operator()(entity_tag const& node) const;
    void operator()(enumeration_literal const& node) const;
//    void operator()(enumeration_type_definition const& node) const;
//    void operator()(exit_statement const& node) const;
//    void operator()(exponent const& node) const;
//    void operator()(expression const& node) const;
//    void operator()(extended_digit const& node) const;
//    void operator()(extended_identifier const& node) const;
//    void operator()(factor const& node) const;
//    void operator()(file_declaration const& node) const;
//    void operator()(file_logical_name const& node) const;
//    void operator()(file_open_information const& node) const;
//    void operator()(file_type_definition const& node) const;
//    void operator()(formal_designator const& node) const;
//    void operator()(formal_parameter_list const& node) const;
//    void operator()(formal_part const& node) const;
//    void operator()(full_type_declaration const& node) const;
//    void operator()(function_call const& node) const;
//    void operator()(generate_statement const& node) const;
//    void operator()(generation_scheme const& node) const;
//    void operator()(generic_clause const& node) const;
//    void operator()(generic_list const& node) const;
//    void operator()(generic_map_aspect const& node) const;
//    void operator()(graphic_character const& node) const;
//    void operator()(group_constituent const& node) const;
//    void operator()(group_constituent_list const& node) const;
//    void operator()(group_declaration const& node) const;
//    void operator()(group_template_declaration const& node) const;
//    void operator()(guarded_signal_specification const& node) const;
//    void operator()(identifier const& node) const;
//    void operator()(identifier_list const& node) const;
//    void operator()(if_statement const& node) const;
//    void operator()(incomplete_type_declaration const& node) const;
//    void operator()(index_constraint const& node) const;
//    void operator()(index_specification const& node) const;
//    void operator()(index_subtype_definition const& node) const;
//    void operator()(indexed_name const& node) const;
//    void operator()(instantiated_unit const& node) const;
//    void operator()(instantiation_list const& node) const;
//    void operator()(integer const& node) const;
//    void operator()(integer_type_definition const& node) const;
//    void operator()(interface_constant_declaration const& node) const;
//    void operator()(interface_declaration const& node) const;
//    void operator()(interface_element const& node) const;
//    void operator()(interface_file_declaration const& node) const;
//    void operator()(interface_list const& node) const;
//    void operator()(interface_signal_declaration const& node) const;
//    void operator()(interface_variable_declaration const& node) const;
//    void operator()(iteration_scheme const& node) const;
//    void operator()(label const& node) const;
//    void operator()(letter const& node) const;
//    void operator()(letter_or_digit const& node) const;
//    void operator()(library_clause const& node) const;
//    void operator()(library_unit const& node) const;
//    void operator()(literal const& node) const;
//    void operator()(logical_name const& node) const;
//    void operator()(logical_name_list const& node) const;
//    void operator()(logical_operator const& node) const;
//    void operator()(loop_statement const& node) const;
//    void operator()(miscellaneous_operator const& node) const;
//    void operator()(mode const& node) const;
//    void operator()(multiplying_operator const& node) const;
//    void operator()(name const& node) const;
//    void operator()(next_statement const& node) const;
//    void operator()(null_statement const& node) const;
    void operator()(numeric_literal const& node) const;
//    void operator()(object_declaration const& node) const;
//    void operator()(operator_symbol const& node) const;
//    void operator()(options const& node) const;
//    void operator()(package_body const& node) const;
//    void operator()(package_body_declarative_item const& node) const;
//    void operator()(package_body_declarative_part const& node) const;
//    void operator()(package_declaration const& node) const;
//    void operator()(package_declarative_item const& node) const;
//    void operator()(package_declarative_part const& node) const;
//    void operator()(parameter_specification const& node) const;
    void operator()(physical_literal const& node) const;
//    void operator()(physical_type_definition const& node) const;
//    void operator()(port_clause const& node) const;
//    void operator()(port_list const& node) const;
//    void operator()(port_map_aspect const& node) const;
//    void operator()(prefix const& node) const;
//    void operator()(primary const& node) const;
//    void operator()(primary_unit const& node) const;
//    void operator()(procedure_call const& node) const;
//    void operator()(procedure_call_statement const& node) const;
//    void operator()(process_declarative_item const& node) const;
//    void operator()(process_declarative_part const& node) const;
//    void operator()(process_statement const& node) const;
//    void operator()(process_statement_part const& node) const;
//    void operator()(qualified_expression const& node) const;
//    void operator()(range const& node) const;
//    void operator()(range_constraint const& node) const;
//    void operator()(record_type_definition const& node) const;
//    void operator()(relation const& node) const;
//    void operator()(relational_operator const& node) const;
//    void operator()(report_statement const& node) const;
//    void operator()(return_statement const& node) const;
//    void operator()(scalar_type_definition const& node) const;
//    void operator()(secondary_unit const& node) const;
//    void operator()(secondary_unit_declaration const& node) const;
//    void operator()(selected_name const& node) const;
//    void operator()(selected_signal_assignment const& node) const;
//    void operator()(selected_waveforms const& node) const;
//    void operator()(sensitivity_clause const& node) const;
//    void operator()(sensitivity_list const& node) const;
//    void operator()(sequence_of_statements const& node) const;
//    void operator()(sequential_statement const& node) const;
//    void operator()(shift_expression const& node) const;
//    void operator()(shift_operator const& node) const;
//    void operator()(sign const& node) const;
//    void operator()(signal_assignment_statement const& node) const;
//    void operator()(signal_declaration const& node) const;
//    void operator()(signal_kind const& node) const;
//    void operator()(signal_list const& node) const;
//    void operator()(signature const& node) const;
//    void operator()(simple_expression const& node) const;
//    void operator()(simple_name const& node) const;
//    void operator()(slice_name const& node) const;
    void operator()(string_literal const& node) const;
//    void operator()(subprogram_body const& node) const;
//    void operator()(subprogram_declaration const& node) const;
//    void operator()(subprogram_declarative_item const& node) const;
//    void operator()(subprogram_declarative_part const& node) const;
//    void operator()(subprogram_kind const& node) const;
//    void operator()(subprogram_specification const& node) const;
//    void operator()(subprogram_statement_part const& node) const;
//    void operator()(subtype_declaration const& node) const;
//    void operator()(subtype_indication const& node) const;
//    void operator()(suffix const& node) const;
//    void operator()(target const& node) const;
//    void operator()(term const& node) const;
//    void operator()(timeout_clause const& node) const;
//    void operator()(type_conversion const& node) const;
//    void operator()(type_declaration const& node) const;
//    void operator()(type_definition const& node) const;
//    void operator()(type_mark const& node) const;
//    void operator()(unconstrained_array_definition const& node) const;
//    void operator()(use_clause const& node) const;
//    void operator()(variable_assignment_statement const& node) const;
//    void operator()(variable_declaration const& node) const;
//    void operator()(wait_statement const& node) const;
//    void operator()(waveform const& node) const;

};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRINTER_HPP_ */
