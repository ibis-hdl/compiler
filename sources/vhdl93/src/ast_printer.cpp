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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"


namespace eda { namespace vhdl93 { namespace ast {


void printer::tab(uint16_t spaces)
{
    for (unsigned i=0; i != spaces; ++i)
        os << ' ';
}

void printer::operator()(abstract_literal const &node) const
{
    os << "(v:abstract_literal=";
    boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(access_type_definition const &node) const
{
    os << "(access_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(actual_designator const &node) const
{
    os << "(XXXX actual_designator="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(actual_parameter_part const &node) const
{
    os << "(actual_parameter_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(actual_part const &node) const
{
    os << "(XXXX actual_part="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(aggregate const &node) const
{
    os << "(aggregate=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(alias_declaration const &node) const
{
    os << "(alias_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(alias_designator const &node) const
{
    os << "(XXXX alias_designator="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(allocator const &node) const
{
    os << "(XXXX allocator="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(architecture_body const &node) const
{
    os << "(architecture_body=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(architecture_declarative_part const &node) const
{
    os << "(architecture_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(architecture_statement_part const &node) const
{
    os << "(architecture_statement_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(array_type_definition const &node) const
{
    os << "(XXXX array_type_definition="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(assertion const &node) const
{
    os << "(assertion=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(assertion_statement const &node) const
{
    os << "(assertion_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(association_element const &node) const
{
    os << "(association_element=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(association_list const &node) const
{
    os << "(association_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(attribute_declaration const &node) const
{
    os << "(attribute_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(attribute_designator const &node) const
{
    os << "(attribute_designator=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(attribute_name const &node) const
{
    os << "(attribute_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(attribute_specification const &node) const
{
    os << "(attribute_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(base const &node) const
{
    os << "(base=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(base_unit_declaration const &node) const
{
    os << "(base_unit_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(based_integer const &node) const
{
    os << "(based_integer=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(based_literal const &node) const
{
    os << "(based_literal=";
    os << "{b=" << node.base << ", n=" << node.literal << "}";
    os << ")";
}


void printer::operator()(basic_character const &node) const
{
    os << "(XXXX basic_character="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(basic_graphic_character const &node) const
{
    os << "(XXXX basic_graphic_character="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(basic_identifier const &node) const
{
    os << "(basic_identifier=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(binding_indication const &node) const
{
    os << "(binding_indication=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(bit_string_literal const &node) const
{

	using tag = bit_string_literal::tag;

    os << "(bit_string_literal={";
    os << "l=" << node.literal << ", tag=";

    switch(node.hint) {
        case tag::bin: os << "bin"; break;
        case tag::oct: os << "oct"; break;
        case tag::hex: os << "hex"; break;
        default:       os << "INVALID";
    }

    os << "})";
}


void printer::operator()(block_configuration const &node) const
{
    os << "(block_configuration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(block_declarative_item const &node) const
{
    os << "(XXXX block_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(block_declarative_part const &node) const
{
    os << "(block_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(block_header const &node) const
{
    os << "(block_header=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(block_specification const &node) const
{
    os << "(XXXX block_specification="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(block_statement const &node) const
{
    os << "(block_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(block_statement_part const &node) const
{
    os << "(block_statement_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(case_statement const &node) const
{
    os << "(case_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(case_statement_alternative const &node) const
{
    os << "(case_statement_alternative=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(character_literal const &node) const
{
    os << "(character_literal=";
    os << node.literal;
    os << ")";
}


void printer::operator()(choice const &node) const
{
    os << "(XXXX choice="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(choices const &node) const
{
    os << "(XXXX choices="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(component_configuration const &node) const
{
    os << "(component_configuration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(component_declaration const &node) const
{
    os << "(component_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(component_instantiation_statement const &node) const
{
    os << "(component_instantiation_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(component_specification const &node) const
{
    os << "(component_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(composite_type_definition const &node) const
{
    os << "(XXXX composite_type_definition="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(concurrent_assertion_statement const &node) const
{
    os << "(concurrent_assertion_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(concurrent_procedure_call_statement const &node) const
{
    os << "(concurrent_procedure_call_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(concurrent_signal_assignment_statement const &node) const
{
    os << "(XXXX concurrent_signal_assignment_statement="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(concurrent_statement const &node) const
{
    os << "(XXXX concurrent_statement="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(condition const &node) const
{
    os << "(condition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(condition_clause const &node) const
{
    os << "(condition_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(conditional_signal_assignment const &node) const
{
    os << "(conditional_signal_assignment=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(conditional_waveforms const &node) const
{
    os << "(conditional_waveforms=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(configuration_declaration const &node) const
{
    os << "(configuration_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(configuration_declarative_item const &node) const
{
    os << "(XXXX configuration_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(configuration_declarative_part const &node) const
{
    os << "(configuration_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(configuration_item const &node) const
{
    os << "(XXXX configuration_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(configuration_specification const &node) const
{
    os << "(configuration_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(constant_declaration const &node) const
{
    os << "(constant_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(constrained_array_definition const &node) const
{
    os << "(constrained_array_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(constraint const &node) const
{
    os << "(XXXX constraint="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(context_clause const &node) const
{
    os << "(context_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(context_item const &node) const
{
    os << "(XXXX context_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(decimal_literal const &node) const
{

	using tag = decimal_literal::tag;

    os << "(decimal_literal={";
    os << "l=" << node.literal << ", tag=";

    switch(node.hint) {
        case tag::integer: os << "int";    break;
        case tag::real:    os << "double"; break;
        default:           os << "INVALID";
    }

    os << "})";
}


void printer::operator()(declaration const &node) const
{
    os << "(XXXX declaration="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(delay_mechanism const &node) const
{
    os << "(XXXX delay_mechanism="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(design_file const &node) const
{
    os << "(design_file=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(design_unit const &node) const
{
    os << "(design_unit=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(designator const &node) const
{
    os << "(XXXX designator="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(direction const &node) const
{
    os << "(XXXX direction="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(disconnection_specification const &node) const
{
    os << "(disconnection_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(discrete_range const &node) const
{
    os << "(XXXX discrete_range="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(element_association const &node) const
{
    os << "(element_association=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(element_declaration const &node) const
{
    os << "(element_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(element_subtype_definition const &node) const
{
    os << "(element_subtype_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_aspect const &node) const
{
    os << "(XXXX entity_aspect="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(entity_class const &node) const
{
    os << "(XXXX entity_class="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(entity_class_entry const &node) const
{
    os << "(entity_class_entry=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_class_entry_list const &node) const
{
    os << "(entity_class_entry_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_declaration const &node) const
{
    os << "(entity_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_declarative_item const &node) const
{
    os << "(XXXX entity_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(entity_declarative_part const &node) const
{
    os << "(entity_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_designator const &node) const
{
    os << "(entity_designator=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_header const &node) const
{
    os << "(entity_header=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_name_list const &node) const
{
    os << "(XXXX entity_name_list="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(entity_specification const &node) const
{
    os << "(entity_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_statement const &node) const
{
    os << "(XXXX entity_statement="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(entity_statement_part const &node) const
{
    os << "(entity_statement_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(entity_tag const &node) const
{
    os << "(XXXX entity_tag="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(enumeration_literal const &node) const
{
    os << "(v:enumeration_literal=";
    boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(enumeration_type_definition const &node) const
{
    os << "(enumeration_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(exit_statement const &node) const
{
    os << "(exit_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(exponent const &node) const
{
    os << "(XXXX exponent="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(expression const &node) const
{
    os << "(XXXX expression="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(extended_identifier const &node) const
{
    os << "(extended_identifier=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(factor const &node) const
{
    os << "(XXXX factor="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(file_declaration const &node) const
{
    os << "(file_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(file_logical_name const &node) const
{
    os << "(file_logical_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(file_open_information const &node) const
{
    os << "(file_open_information=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(file_type_definition const &node) const
{
    os << "(file_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(formal_designator const &node) const
{
    os << "(XXXX formal_designator="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(formal_parameter_list const &node) const
{
    os << "(formal_parameter_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(formal_part const &node) const
{
    os << "(XXXX formal_part="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(full_type_declaration const &node) const
{
    os << "(full_type_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(function_call const &node) const
{
    os << "(function_call=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(generate_statement const &node) const
{
    os << "(generate_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(generation_scheme const &node) const
{
    os << "(XXXX generation_scheme="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(generic_clause const &node) const
{
    os << "(generic_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(generic_list const &node) const
{
    os << "(generic_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(generic_map_aspect const &node) const
{
    os << "(generic_map_aspect=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(graphic_character const &node) const
{
    os << "(XXXX graphic_character="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(group_constituent const &node) const
{
    os << "(XXXX group_constituent="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(group_constituent_list const &node) const
{
    os << "(group_constituent_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(group_declaration const &node) const
{
    os << "(group_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(group_template_declaration const &node) const
{
    os << "(group_template_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(guarded_signal_specification const &node) const
{
    os << "(guarded_signal_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(identifier const &node) const
{
    os << "(XXXX identifier="; // FixMe: Review and Implement
    os << node; // FixMe: operator<<
    os << ")";
}


void printer::operator()(identifier_list const &node) const
{
    os << "(identifier_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(if_statement const &node) const
{
    os << "(if_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(incomplete_type_declaration const &node) const
{
    os << "(incomplete_type_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(index_constraint const &node) const
{
    os << "(index_constraint=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(index_specification const &node) const
{
    os << "(XXXX index_specification="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(index_subtype_definition const &node) const
{
    os << "(index_subtype_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(indexed_name const &node) const
{
    os << "(indexed_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(instantiated_unit const &node) const
{
    os << "(XXXX instantiated_unit="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(instantiation_list const &node) const
{
    os << "(XXXX instantiation_list="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(integer const &node) const
{
    os << "(integer=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(integer_type_definition const &node) const
{
    os << "(integer_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_constant_declaration const &node) const
{
    os << "(interface_constant_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_declaration const &node) const
{
    os << "(XXXX interface_declaration="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(interface_element const &node) const
{
    os << "(interface_element=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_file_declaration const &node) const
{
    os << "(interface_file_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_list const &node) const
{
    os << "(interface_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_signal_declaration const &node) const
{
    os << "(interface_signal_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(interface_variable_declaration const &node) const
{
    os << "(interface_variable_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(iteration_scheme const &node) const
{
    os << "(XXXX iteration_scheme="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(label const &node) const
{
    os << "(label=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(letter_or_digit const &node) const
{
    os << "(XXXX letter_or_digit="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(library_clause const &node) const
{
    os << "(library_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(library_unit const &node) const
{
    os << "(XXXX library_unit="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(literal const &node) const
{
    os << "(v:literal=";
    boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(logical_name const &node) const
{
    os << "(logical_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(logical_name_list const &node) const
{
    os << "(logical_name_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(loop_statement const &node) const
{
    os << "(loop_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(mode const &node) const
{
    os << "(XXXX mode="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(name const &node) const
{
    os << "(XXXX name="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(next_statement const &node) const
{
    os << "(next_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(null_statement const &node) const
{
    os << "(null_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(numeric_literal const &node) const
{
    os << "(v:numeric_literal=";
    boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(object_declaration const &node) const
{
    os << "(XXXX object_declaration="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(operator_symbol const &node) const
{
    os << "(operator_symbol=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(options const &node) const
{
    os << "(options=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(package_body const &node) const
{
    os << "(package_body=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(package_body_declarative_item const &node) const
{
    os << "(XXXX package_body_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(package_body_declarative_part const &node) const
{
    os << "(package_body_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(package_declaration const &node) const
{
    os << "(package_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(package_declarative_item const &node) const
{
    os << "(XXXX package_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(package_declarative_part const &node) const
{
    os << "(package_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(parameter_specification const &node) const
{
    os << "(parameter_specification=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(physical_literal const &node) const
{
    os << "(physical_literal={l=";
    (*this)(node.literal);
    os << ", u=" << node.unit_name;
    os << "})";
}


void printer::operator()(physical_type_definition const &node) const
{
    os << "(physical_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(port_clause const &node) const
{
    os << "(port_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(port_list const &node) const
{
    os << "(port_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(port_map_aspect const &node) const
{
    os << "(port_map_aspect=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(prefix const &node) const
{
    os << "(XXXX prefix="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(primary const &node) const
{
    os << "(XXXX primary="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(primary_unit const &node) const
{
    os << "(XXXX primary_unit="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(procedure_call const &node) const
{
    os << "(procedure_call=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(procedure_call_statement const &node) const
{
    os << "(procedure_call_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(process_declarative_item const &node) const
{
    os << "(XXXX process_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(process_declarative_part const &node) const
{
    os << "(process_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(process_statement const &node) const
{
    os << "(process_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(process_statement_part const &node) const
{
    os << "(process_statement_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(qualified_expression const &node) const
{
    os << "(XXXX qualified_expression="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(range const &node) const
{
    os << "(XXXX range="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(range_constraint const &node) const
{
    os << "(range_constraint=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(record_type_definition const &node) const
{
    os << "(record_type_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(relation const &node) const
{
    os << "(relation=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(report_statement const &node) const
{
    os << "(report_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(return_statement const &node) const
{
    os << "(return_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(scalar_type_definition const &node) const
{
    os << "(XXXX scalar_type_definition="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(secondary_unit const &node) const
{
    os << "(XXXX secondary_unit="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(secondary_unit_declaration const &node) const
{
    os << "(secondary_unit_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(selected_name const &node) const
{
    os << "(selected_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(selected_signal_assignment const &node) const
{
    os << "(selected_signal_assignment=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(selected_waveforms const &node) const
{
    os << "(selected_waveforms=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(sensitivity_clause const &node) const
{
    os << "(sensitivity_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(sensitivity_list const &node) const
{
    os << "(sensitivity_list=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(sequence_of_statements const &node) const
{
    os << "(sequence_of_statements=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(sequential_statement const &node) const
{
    os << "(XXXX sequential_statement="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(shift_expression const &node) const
{
    os << "(shift_expression=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(sign const &node) const
{
    os << "(XXXX sign="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(signal_assignment_statement const &node) const
{
    os << "(signal_assignment_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(signal_declaration const &node) const
{
    os << "(signal_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(signal_kind const &node) const
{
    os << "(XXXX signal_kind="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(signal_list const &node) const
{
    os << "(XXXX signal_list="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(signature const &node) const
{
    os << "(signature=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(simple_expression const &node) const
{
    os << "(simple_expression=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(simple_name const &node) const
{
    os << "(simple_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(slice_name const &node) const
{
    os << "(slice_name=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(string_literal const &node) const
{
    os << "(string_literal=";
    os << node; // FixMe: operator<<
    os << ")";
}


void printer::operator()(subprogram_body const &node) const
{
    os << "(subprogram_body=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(subprogram_declaration const &node) const
{
    os << "(subprogram_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(subprogram_declarative_item const &node) const
{
    os << "(XXXX subprogram_declarative_item="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(subprogram_declarative_part const &node) const
{
    os << "(subprogram_declarative_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(subprogram_kind const &node) const
{
    os << "(XXXX subprogram_kind="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(subprogram_specification const &node) const
{
    os << "(XXXX subprogram_specification="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(subprogram_statement_part const &node) const
{
    os << "(subprogram_statement_part=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(subtype_declaration const &node) const
{
    os << "(subtype_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(subtype_indication const &node) const
{
    os << "(subtype_indication=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(suffix const &node) const
{
    os << "(XXXX suffix="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(target const &node) const
{
    os << "(XXXX target="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(term const &node) const
{
    os << "(term=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(timeout_clause const &node) const
{
    os << "(timeout_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(type_conversion const &node) const
{
    os << "(type_conversion=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(type_declaration const &node) const
{
    os << "(XXXX type_declaration="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(type_definition const &node) const
{
    os << "(XXXX type_definition="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(type_mark const &node) const
{
    os << "(XXXX type_mark="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}


void printer::operator()(unconstrained_array_definition const &node) const
{
    os << "(unconstrained_array_definition=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(use_clause const &node) const
{
    os << "(use_clause=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(variable_assignment_statement const &node) const
{
    os << "(variable_assignment_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(variable_declaration const &node) const
{
    os << "(variable_declaration=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(wait_statement const &node) const
{
    os << "(wait_statement=";
    os << "XXXX"; //os << node; // FixMe: Review and Implement
    os << ")";
}


void printer::operator()(waveform const &node) const
{
    os << "(XXXX waveform="; // FixMe: Review and Implement
    // boost::apply_visitor(*this, node);
    os << ")";
}

} } } // namespace eda.vhdl93.ast


#pragma GCC diagnostic pop
