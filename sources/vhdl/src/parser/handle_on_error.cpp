/*
 * error_handler.cpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#include <eda/vhdl/parser/handle_on_error.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace parser {


handle_on_error::handle_on_error()
: m_ruleid_map {
    /* Spirit.X3's error handling embraces the rule with apostrophes, at last for
     * semicolon.  */
    { "'abstract_literal'", "Abstract Literal" },
    { "'access_type_definition'", "Access Type Definition" },
    { "'actual_designator'", "Actual Designator" },
    { "'actual_parameter_part'", "Actual Parameter Part" },
    { "'actual_part'", "Actual Part" },
    { "'adding_operator'", "Adding Operator" },
    { "'aggregate'", "Aggregate" },
    { "'alias_declaration'", "Alias Declaration" },
    { "'alias_designator'", "Alias Designator" },
    { "'allocator'", "Allocator" },
    { "'architecture_body'", "Architecture Body" },
    { "'architecture_declarative_part'", "Architecture Declarative Part" },
    { "'architecture_statement_part'", "Architecture Statement Part" },
    { "'array_type_definition'", "Array Type Definition" },
    { "'assertion'", "Assertion" },
    { "'assertion_statement'", "Assertion Statement" },
    { "'association_element'", "Association Element" },
    { "'association_list'", "Association List" },
    { "'attribute_declaration'", "Attribute Declaration" },
    { "'attribute_designator'", "Attribute Designator" },
    { "'attribute_name'", "Attribute Name" },
    { "'attribute_specification'", "Attribute Specification" },
    { "'base'", "Base" },
    { "'base_specifier'", "Base Specifier" },
    { "'base_unit_declaration'", "Base Unit Declaration" },
    { "'based_integer'", "Based Integer" },
    { "'based_literal'", "Based Literal" },
    { "'basic_character'", "Basic Character" },
    { "'basic_graphic_character'", "Basic Graphic Character" },
    { "'basic_identifier'", "Basic Identifier" },
    { "'binding_indication'", "Binding Indication" },
    { "'bit_string_literal'", "Bit String Literal" },
    { "'bit_value'", "Bit Value" },
    { "'block_configuration'", "Block Configuration" },
    { "'block_declarative_item'", "Block Declarative Item" },
    { "'block_declarative_part'", "Block Declarative Part" },
    { "'block_header'", "Block Header" },
    { "'block_specification'", "Block Specification" },
    { "'block_statement'", "Block Statement" },
    { "'block_statement_part'", "Block Statement Part" },
    { "'case_statement'", "Case Statement" },
    { "'case_statement_alternative'", "Case Statement Alternative" },
    { "'character_literal'", "Character Literal" },
    { "'choice'", "Choice" },
    { "'choices'", "Choices" },
    { "'component_configuration'", "Component Configuration" },
    { "'component_declaration'", "Component Declaration" },
    { "'component_instantiation_statement'", "Component Instantiation Statement" },
    { "'component_specification'", "Component Specification" },
    { "'composite_type_definition'", "Composite Type Definition" },
    { "'concurrent_assertion_statement'", "Concurrent Assertion Statement" },
    { "'concurrent_procedure_call_statement'", "Concurrent Procedure Call Statement" },
    { "'concurrent_signal_assignment_statement'", "Concurrent Signal Assignment Statement" },
    { "'concurrent_statement'", "Concurrent Statement" },
    { "'condition'", "Condition" },
    { "'condition_clause'", "Condition Clause" },
    { "'conditional_signal_assignment'", "Conditional Signal Assignment" },
    { "'conditional_waveforms'", "Conditional Waveforms" },
    { "'configuration_declaration'", "Configuration Declaration" },
    { "'configuration_declarative_item'", "Configuration Declarative Item" },
    { "'configuration_declarative_part'", "Configuration Declarative Part" },
    { "'configuration_item'", "Configuration Item" },
    { "'configuration_specification'", "Configuration Specification" },
    { "'constant_declaration'", "Constant Declaration" },
    { "'constrained_array_definition'", "Constrained Array Definition" },
    { "'constraint'", "Constraint" },
    { "'context_clause'", "Context Clause" },
    { "'context_item'", "Context Item" },
    { "'decimal_literal'", "Decimal Literal" },
    { "'declaration'", "Declaration" },
    { "'delay_mechanism'", "Delay Mechanism" },
    { "'design_file'", "Design File" },
    { "'design_unit'", "Design Unit" },
    { "'designator'", "Designator" },
    { "'direction'", "Direction" },
    { "'disconnection_specification'", "Disconnection Specification" },
    { "'discrete_range'", "Discrete Range" },
    { "'element_association'", "Element Association" },
    { "'element_declaration'", "Element Declaration" },
    { "'element_subtype_definition'", "Element Subtype Definition" },
    { "'entity_aspect'", "Entity Aspect" },
    { "'entity_class'", "Entity Class" },
    { "'entity_class_entry'", "Entity Class Entry" },
    { "'entity_class_entry_list'", "Entity Class Entry List" },
    { "'entity_declaration'", "Entity Declaration" },
    { "'entity_declarative_item'", "Entity Declarative Item" },
    { "'entity_declarative_part'", "Entity Declarative Part" },
    { "'entity_designator'", "Entity Designator" },
    { "'entity_header'", "Entity Header" },
    { "'entity_name_list'", "Entity Name List" },
    { "'entity_specification'", "Entity Specification" },
    { "'entity_statement'", "Entity Statement" },
    { "'entity_statement_part'", "Entity Statement Part" },
    { "'entity_tag'", "Entity Tag" },
    { "'enumeration_literal'", "Enumeration Literal" },
    { "'enumeration_type_definition'", "Enumeration Type Definition" },
    { "'exit_statement'", "Exit Statement" },
    { "'exponent'", "Exponent" },
    { "'expression'", "Expression" },
    { "'extended_digit'", "Extended Digit" },
    { "'extended_identifier'", "Extended Identifier" },
    { "'factor'", "Factor" },
    { "'file_declaration'", "File Declaration" },
    { "'file_logical_name'", "File Logical Name" },
    { "'file_open_information'", "File Open Information" },
    { "'file_type_definition'", "File Type Definition" },
    { "'formal_designator'", "Formal Designator" },
    { "'formal_parameter_list'", "Formal Parameter List" },
    { "'formal_part'", "Formal Part" },
    { "'full_type_declaration'", "Full Type Declaration" },
    { "'function_call'", "Function Call" },
    { "'generate_statement'", "Generate Statement" },
    { "'generation_scheme'", "Generation Scheme" },
    { "'generic_clause'", "Generic Clause" },
    { "'generic_list'", "Generic List" },
    { "'generic_map_aspect'", "Generic Map Aspect" },
    { "'graphic_character'", "Graphic Character" },
    { "'group_constituent'", "Group Constituent" },
    { "'group_constituent_list'", "Group Constituent List" },
    { "'group_template_declaration'", "Group Template Declaration" },
    { "'group_declaration'", "Group Declaration" },
    { "'guarded_signal_specification'", "Guarded Signal Specification" },
    { "'identifier'", "Identifier" },
    { "'identifier_list'", "Identifier List" },
    { "'if_statement'", "If Statement" },
    { "'incomplete_type_declaration'", "Incomplete Type Declaration" },
    { "'index_constraint'", "Index Constraint" },
    { "'index_specification'", "Index Specification" },
    { "'index_subtype_definition'", "Index Subtype Definition" },
    { "'indexed_name'", "Indexed Name" },
    { "'instantiated_unit'", "Instantiated Unit" },
    { "'instantiation_list'", "Instantiation List" },
    { "'integer'", "Integer" },
    { "'integer_type_definition'", "Integer Type Definition" },
    { "'interface_constant_declaration'", "Interface Constant Declaration" },
    { "'interface_declaration'", "Interface Declaration" },
    { "'interface_element'", "Interface Element" },
    { "'interface_file_declaration'", "Interface File Declaration" },
    { "'interface_list'", "Interface List" },
    { "'interface_signal_declaration'", "Interface Signal Declaration" },
    { "'interface_variable_declaration'", "Interface Variable Declaration" },
    { "'iteration_scheme'", "Iteration Scheme" },
    { "'label'", "Label" },
    { "'letter'", "Letter" },
    { "'letter_or_digit'", "Letter Or Digit" },
    { "'library_clause'", "Library Clause" },
    { "'library_unit'", "Library Unit" },
    { "'literal'", "Literal" },
    { "'logical_name'", "Logical Name" },
    { "'logical_name_list'", "Logical Name List" },
    { "'logical_operator'", "Logical Operator" },
    { "'loop_statement'", "Loop Statement" },
    { "'miscellaneous_operator'", "Miscellaneous Operator" },
    { "'mode'", "Mode" },
    { "'multiplying_operator'", "Multiplying Operator" },
    { "'name'", "Name" },
    { "'next_statement'", "Next Statement" },
    { "'null_statement'", "Null Statement" },
    { "'numeric_literal'", "Numeric Literal" },
    { "'object_declaration'", "Object Declaration" },
    { "'operator_symbol'", "Operator Symbol" },
    { "'options'", "Options" },
    { "'package_body'", "Package Body" },
    { "'package_body_declarative_item'", "Package Body Declarative Item" },
    { "'package_body_declarative_part'", "Package Body Declarative Part" },
    { "'package_declaration'", "Package Declaration" },
    { "'package_declarative_item'", "Package Declarative Item" },
    { "'package_declarative_part'", "Package Declarative Part" },
    { "'parameter_specification'", "Parameter Specification" },
    { "'physical_literal'", "Physical Literal" },
    { "'physical_type_definition'", "Physical Type Definition" },
    { "'port_clause'", "Port Clause" },
    { "'port_list'", "Port List" },
    { "'port_map_aspect'", "Port Map Aspect" },
    { "'prefix'", "Prefix" },
    { "'primary'", "Primary" },
    { "'primary_unit'", "Primary Unit" },
    { "'procedure_call'", "Procedure Call" },
    { "'procedure_call_statement'", "Procedure Call Statement" },
    { "'process_declarative_item'", "Process Declarative Item" },
    { "'process_declarative_part'", "Process Declarative Part" },
    { "'process_statement'", "Process Statement" },
    { "'process_statement_part'", "Process Statement Part" },
    { "'qualified_expression'", "Qualified Expression" },
    { "'range'", "Range" },
    { "'range_constraint'", "Range Constraint" },
    { "'record_type_definition'", "Record Type Definition" },
    { "'relation'", "Relation" },
    { "'relational_operator'", "Relational Operator" },
    { "'report_statement'", "Report Statement" },
    { "'return_statement'", "Return Statement" },
    { "'scalar_type_definition'", "Scalar Type Definition" },
    { "'secondary_unit'", "Secondary Unit" },
    { "'secondary_unit_declaration'", "Secondary Unit Declaration" },
    { "'selected_name'", "Selected Name" },
    { "'selected_signal_assignment'", "Selected Signal Assignment" },
    { "'selected_waveforms'", "Selected Waveforms" },
    { "'sensitivity_clause'", "Sensitivity Clause" },
    { "'sensitivity_list'", "Sensitivity List" },
    { "'sequence_of_statements'", "Sequence Of Statements" },
    { "'sequential_statement'", "Sequential Statement" },
    { "'shift_expression'", "Shift Expression" },
    { "'shift_operator'", "Shift Operator" },
    { "'sign'", "Sign" },
    { "'signal_assignment_statement'", "Signal Assignment Statement" },
    { "'signal_declaration'", "Signal Declaration" },
    { "'signal_kind'", "Signal Kind" },
    { "'signal_list'", "Signal List" },
    { "'signature'", "Signature" },
    { "'simple_expression'", "Simple Expression" },
    { "'simple_name'", "Simple Name" },
    { "'slice_name'", "Slice Name" },
    { "'string_literal'", "String Literal" },
    { "'subprogram_body'", "Subprogram Body" },
    { "'subprogram_declaration'", "Subprogram Declaration" },
    { "'subprogram_declarative_item'", "Subprogram Declarative Item" },
    { "'subprogram_declarative_part'", "Subprogram Declarative Part" },
    { "'subprogram_kind'", "Subprogram Kind" },
    { "'subprogram_specification'", "Subprogram Specification" },
    { "'subprogram_statement_part'", "Subprogram Statement Part" },
    { "'subtype_declaration'", "Subtype Declaration" },
    { "'subtype_indication'", "Subtype Indication" },
    { "'suffix'", "Suffix" },
    { "'target'", "Target" },
    { "'term'", "Term" },
    { "'timeout_clause'", "Timeout Clause" },
    { "'type_conversion'", "Type Conversion" },
    { "'type_declaration'", "Type Declaration" },
    { "'type_definition'", "Type Definition" },
    { "'type_mark'", "Type Mark" },
    { "'unconstrained_array_definition'", "Unconstrained Array Definition" },
    { "'use_clause'", "Use Clause" },
    { "'variable_assignment_statement'", "Variable Assignment Statement" },
    { "'variable_declaration'", "Variable Declaration" },
    { "'wait_statement'", "Wait Statement" },
    { "'waveform'", "Waveform" },
    { "'waveform_element'", "Waveform Element" },

    /* other */
    { "'signal_name'", "Signal Name" },

    { "'boolean_expression'", "Boolean Expression" },
    { "'time_expression'", "Time Expression" },
    { "'value_expression'", "Value Expression" },

    /* Typographical */
    { "';'", "Semicolon ';'" },
    { "':'", "Colon ':'" },
    { "'{", "Opening '{' Curly Brace" },
    { "'}", "Closing '}' Curly Brace" },
    { "'[", "Opening '[' Square Bracket" },
    { "']", "Closing ']' Square Bracket" },
    { "'(", "Opening '(' Brace/Parentheses" },
    { "'(", "Closing ')' Brace/Parentheses" },
}
{ }


std::string handle_on_error::assemble_message(std::string which)
{
    auto const iter = m_ruleid_map.find(which);

    if (iter != m_ruleid_map.end()) {
        which = iter->second;
    }
    else {
        std::cerr << "Internal WARNING: failed to lookup '" << which
                  << "' at parser's expectation symbol table\n";

    }

    std::string const message{
        "Syntax Error, expecting " + which + " here:"
    };

    return message;
}


}}} // namespace eda.vhdl.parser
