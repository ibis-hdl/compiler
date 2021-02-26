/*
 * on_error_base.cpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#include <eda/vhdl/parser/on_error_base.hpp>

#include <eda/support/boost/locale.hpp> // IWYU pragma: keep

#include <iostream>
#include <unordered_map>

namespace eda {
namespace vhdl {
namespace parser {

using namespace std::string_view_literals;

std::string_view on_error_base::lookup(std::string_view which) const
{
    using rule_map_type = std::unordered_map<std::string_view, std::string_view>;

    // Spirit.X3 rule ID/name map. The rule names may be different from node 
    // names, so we can't use ast::pretty_node_name here.
    static const rule_map_type ruleid_map{
        { "abstract_literal"sv, "Abstract Literal"sv },
        { "access_type_definition"sv, "Access Type Definition"sv },
        { "actual_designator"sv, "Actual Designator"sv },
        { "actual_parameter_part"sv, "Actual Parameter Part"sv },
        { "actual_part"sv, "Actual Part"sv },
        { "adding_operator"sv, "Adding Operator"sv },
        { "aggregate"sv, "Aggregate"sv },
        { "alias_declaration"sv, "Alias Declaration"sv },
        { "alias_designator"sv, "Alias Designator"sv },
        { "allocator"sv, "Allocator"sv },
        { "architecture_body"sv, "Architecture Body"sv },
        { "architecture_declarative_part"sv, "Architecture Declarative Part"sv },
        { "architecture_statement_part"sv, "Architecture Statement Part"sv },
        { "array_type_definition"sv, "Array Type Definition"sv },
        { "assertion"sv, "Assertion"sv },
        { "assertion_statement"sv, "Assertion Statement"sv },
        { "association_element"sv, "Association Element"sv },
        { "association_list"sv, "Association List"sv },
        { "attribute_declaration"sv, "Attribute Declaration"sv },
        { "attribute_designator"sv, "Attribute Designator"sv },
        { "attribute_name"sv, "Attribute Name"sv },
        { "attribute_specification"sv, "Attribute Specification"sv },
        { "base"sv, "Base"sv },
        { "base_specifier"sv, "Base Specifier"sv },
        { "base_unit_declaration"sv, "Base Unit Declaration"sv },
        { "based_integer"sv, "Based Integer"sv },
        { "based_literal"sv, "Based Literal"sv },
        { "basic_character"sv, "Basic Character"sv },
        { "basic_graphic_character"sv, "Basic Graphic Character"sv },
        { "basic_identifier"sv, "Basic Identifier"sv },
        { "binding_indication"sv, "Binding Indication"sv },
        { "bit_string_literal"sv, "Bit String Literal"sv },
        { "bit_value"sv, "Bit Value"sv },
        { "block_configuration"sv, "Block Configuration"sv },
        { "block_declarative_item"sv, "Block Declarative Item"sv },
        { "block_declarative_part"sv, "Block Declarative Part"sv },
        { "block_header"sv, "Block Header"sv },
        { "block_specification"sv, "Block Specification"sv },
        { "block_statement"sv, "Block Statement"sv },
        { "block_statement_part"sv, "Block Statement Part"sv },
        { "case_statement"sv, "Case Statement"sv },
        { "case_statement_alternative"sv, "Case Statement Alternative"sv },
        { "character_literal"sv, "Character Literal"sv },
        { "choice"sv, "Choice"sv },
        { "choices"sv, "Choices"sv },
        { "component_configuration"sv, "Component Configuration"sv },
        { "component_declaration"sv, "Component Declaration"sv },
        { "component_instantiation_statement"sv, "Component Instantiation Statement"sv },
        { "component_specification"sv, "Component Specification"sv },
        { "composite_type_definition"sv, "Composite Type Definition"sv },
        { "concurrent_assertion_statement"sv, "Concurrent Assertion Statement"sv },
        { "concurrent_procedure_call_statement"sv, "Concurrent Procedure Call Statement"sv },
        { "concurrent_signal_assignment_statement"sv, "Concurrent Signal Assignment Statement"sv },
        { "concurrent_statement"sv, "Concurrent Statement"sv },
        { "condition"sv, "Condition"sv },
        { "condition_clause"sv, "Condition Clause"sv },
        { "conditional_signal_assignment"sv, "Conditional Signal Assignment"sv },
        { "conditional_waveforms"sv, "Conditional Waveforms"sv },
        { "configuration_declaration"sv, "Configuration Declaration"sv },
        { "configuration_declarative_item"sv, "Configuration Declarative Item"sv },
        { "configuration_declarative_part"sv, "Configuration Declarative Part"sv },
        { "configuration_item"sv, "Configuration Item"sv },
        { "configuration_specification"sv, "Configuration Specification"sv },
        { "constant_declaration"sv, "Constant Declaration"sv },
        { "constrained_array_definition"sv, "Constrained Array Definition"sv },
        { "constraint"sv, "Constraint"sv },
        { "context_clause"sv, "Context Clause"sv },
        { "context_item"sv, "Context Item"sv },
        { "decimal_literal"sv, "Decimal Literal"sv },
        { "declaration"sv, "Declaration"sv },
        { "delay_mechanism"sv, "Delay Mechanism"sv },
        { "design_file"sv, "Design File"sv },
        { "design_unit"sv, "Design Unit"sv },
        { "designator"sv, "Designator"sv },
        { "direction"sv, "Direction"sv },
        { "disconnection_specification"sv, "Disconnection Specification"sv },
        { "discrete_range"sv, "Discrete Range"sv },
        { "element_association"sv, "Element Association"sv },
        { "element_declaration"sv, "Element Declaration"sv },
        { "element_subtype_definition"sv, "Element Subtype Definition"sv },
        { "entity_aspect"sv, "Entity Aspect"sv },
        { "entity_class"sv, "Entity Class"sv },
        { "entity_class_entry"sv, "Entity Class Entry"sv },
        { "entity_class_entry_list"sv, "Entity Class Entry List"sv },
        { "entity_declaration"sv, "Entity Declaration"sv },
        { "entity_declarative_item"sv, "Entity Declarative Item"sv },
        { "entity_declarative_part"sv, "Entity Declarative Part"sv },
        { "entity_designator"sv, "Entity Designator"sv },
        { "entity_header"sv, "Entity Header"sv },
        { "entity_name_list"sv, "Entity Name List"sv },
        { "entity_specification"sv, "Entity Specification"sv },
        { "entity_statement"sv, "Entity Statement"sv },
        { "entity_statement_part"sv, "Entity Statement Part"sv },
        { "entity_tag"sv, "Entity Tag"sv },
        { "enumeration_literal"sv, "Enumeration Literal"sv },
        { "enumeration_type_definition"sv, "Enumeration Type Definition"sv },
        { "exit_statement"sv, "Exit Statement"sv },
        { "exponent"sv, "Exponent"sv },
        { "expression"sv, "Expression"sv },
        { "extended_digit"sv, "Extended Digit"sv },
        { "extended_identifier"sv, "Extended Identifier"sv },
        { "factor"sv, "Factor"sv },
        { "file_declaration"sv, "File Declaration"sv },
        { "file_logical_name"sv, "File Logical Name"sv },
        { "file_open_information"sv, "File Open Information"sv },
        { "file_type_definition"sv, "File Type Definition"sv },
        { "formal_designator"sv, "Formal Designator"sv },
        { "formal_parameter_list"sv, "Formal Parameter List"sv },
        { "formal_part"sv, "Formal Part"sv },
        { "full_type_declaration"sv, "Full Type Declaration"sv },
        { "function_call"sv, "Function Call"sv },
        { "generate_statement"sv, "Generate Statement"sv },
        { "generation_scheme"sv, "Generation Scheme"sv },
        { "generic_clause"sv, "Generic Clause"sv },
        { "generic_list"sv, "Generic List"sv },
        { "generic_map_aspect"sv, "Generic Map Aspect"sv },
        { "graphic_character"sv, "Graphic Character"sv },
        { "group_constituent"sv, "Group Constituent"sv },
        { "group_constituent_list"sv, "Group Constituent List"sv },
        { "group_template_declaration"sv, "Group Template Declaration"sv },
        { "group_declaration"sv, "Group Declaration"sv },
        { "guarded_signal_specification"sv, "Guarded Signal Specification"sv },
        { "identifier"sv, "Identifier"sv },
        { "identifier_list"sv, "Identifier List"sv },
        { "if_statement"sv, "If Statement"sv },
        { "incomplete_type_declaration"sv, "Incomplete Type Declaration"sv },
        { "index_constraint"sv, "Index Constraint"sv },
        { "index_specification"sv, "Index Specification"sv },
        { "index_subtype_definition"sv, "Index Subtype Definition"sv },
        { "indexed_name"sv, "Indexed Name"sv },
        { "instantiated_unit"sv, "Instantiated Unit"sv },
        { "instantiation_list"sv, "Instantiation List"sv },
        { "integer"sv, "Integer"sv },
        { "integer_type_definition"sv, "Integer Type Definition"sv },
        { "interface_constant_declaration"sv, "Interface Constant Declaration"sv },
        { "interface_declaration"sv, "Interface Declaration"sv },
        { "interface_element"sv, "Interface Element"sv },
        { "interface_file_declaration"sv, "Interface File Declaration"sv },
        { "interface_list"sv, "Interface List"sv },
        { "interface_signal_declaration"sv, "Interface Signal Declaration"sv },
        { "interface_variable_declaration"sv, "Interface Variable Declaration"sv },
        { "iteration_scheme"sv, "Iteration Scheme"sv },
        { "label"sv, "Label"sv },
        { "letter"sv, "Letter"sv },
        { "letter_or_digit"sv, "Letter Or Digit"sv },
        { "library_clause"sv, "Library Clause"sv },
        { "library_unit"sv, "Library Unit"sv },
        { "literal"sv, "Literal"sv },
        { "logical_name"sv, "Logical Name"sv },
        { "logical_name_list"sv, "Logical Name List"sv },
        { "logical_operator"sv, "Logical Operator"sv },
        { "loop_statement"sv, "Loop Statement"sv },
        { "miscellaneous_operator"sv, "Miscellaneous Operator"sv },
        { "mode"sv, "Mode"sv },
        { "multiplying_operator"sv, "Multiplying Operator"sv },
        { "name"sv, "Name"sv },
        { "next_statement"sv, "Next Statement"sv },
        { "null_statement"sv, "Null Statement"sv },
        { "numeric_literal"sv, "Numeric Literal"sv },
        { "object_declaration"sv, "Object Declaration"sv },
        { "operator_symbol"sv, "Operator Symbol"sv },
        { "options"sv, "Options"sv },
        { "package_body"sv, "Package Body"sv },
        { "package_body_declarative_item"sv, "Package Body Declarative Item"sv },
        { "package_body_declarative_part"sv, "Package Body Declarative Part"sv },
        { "package_declaration"sv, "Package Declaration"sv },
        { "package_declarative_item"sv, "Package Declarative Item"sv },
        { "package_declarative_part"sv, "Package Declarative Part"sv },
        { "parameter_specification"sv, "Parameter Specification"sv },
        { "physical_literal"sv, "Physical Literal"sv },
        { "physical_type_definition"sv, "Physical Type Definition"sv },
        { "port_clause"sv, "Port Clause"sv },
        { "port_list"sv, "Port List"sv },
        { "port_map_aspect"sv, "Port Map Aspect"sv },
        { "prefix"sv, "Prefix"sv },
        { "primary"sv, "Primary"sv },
        { "primary_unit"sv, "Primary Unit"sv },
        { "procedure_call"sv, "Procedure Call"sv },
        { "procedure_call_statement"sv, "Procedure Call Statement"sv },
        { "process_declarative_item"sv, "Process Declarative Item"sv },
        { "process_declarative_part"sv, "Process Declarative Part"sv },
        { "process_statement"sv, "Process Statement"sv },
        { "process_statement_part"sv, "Process Statement Part"sv },
        { "qualified_expression"sv, "Qualified Expression"sv },
        { "range"sv, "Range"sv },
        { "range_constraint"sv, "Range Constraint"sv },
        { "record_type_definition"sv, "Record Type Definition"sv },
        { "relation"sv, "Relation"sv },
        { "relational_operator"sv, "Relational Operator"sv },
        { "report_statement"sv, "Report Statement"sv },
        { "return_statement"sv, "Return Statement"sv },
        { "scalar_type_definition"sv, "Scalar Type Definition"sv },
        { "secondary_unit"sv, "Secondary Unit"sv },
        { "secondary_unit_declaration"sv, "Secondary Unit Declaration"sv },
        { "selected_name"sv, "Selected Name"sv },
        { "selected_signal_assignment"sv, "Selected Signal Assignment"sv },
        { "selected_waveforms"sv, "Selected Waveforms"sv },
        { "sensitivity_clause"sv, "Sensitivity Clause"sv },
        { "sensitivity_list"sv, "Sensitivity List"sv },
        { "sequence_of_statements"sv, "Sequence Of Statements"sv },
        { "sequential_statement"sv, "Sequential Statement"sv },
        { "shift_expression"sv, "Shift Expression"sv },
        { "shift_operator"sv, "Shift Operator"sv },
        { "sign"sv, "Sign"sv },
        { "signal_assignment_statement"sv, "Signal Assignment Statement"sv },
        { "signal_declaration"sv, "Signal Declaration"sv },
        { "signal_kind"sv, "Signal Kind"sv },
        { "signal_list"sv, "Signal List"sv },
        { "signature"sv, "Signature"sv },
        { "simple_expression"sv, "Simple Expression"sv },
        { "simple_name"sv, "Simple Name"sv },
        { "slice_name"sv, "Slice Name"sv },
        { "string_literal"sv, "String Literal"sv },
        { "subprogram_body"sv, "Subprogram Body"sv },
        { "subprogram_declaration"sv, "Subprogram Declaration"sv },
        { "subprogram_declarative_item"sv, "Subprogram Declarative Item"sv },
        { "subprogram_declarative_part"sv, "Subprogram Declarative Part"sv },
        { "subprogram_kind"sv, "Subprogram Kind"sv },
        { "subprogram_specification"sv, "Subprogram Specification"sv },
        { "subprogram_statement_part"sv, "Subprogram Statement Part"sv },
        { "subtype_declaration"sv, "Subtype Declaration"sv },
        { "subtype_indication"sv, "Subtype Indication"sv },
        { "suffix"sv, "Suffix"sv },
        { "target"sv, "Target"sv },
        { "term"sv, "Term"sv },
        { "timeout_clause"sv, "Timeout Clause"sv },
        { "type_conversion"sv, "Type Conversion"sv },
        { "type_declaration"sv, "Type Declaration"sv },
        { "type_definition"sv, "Type Definition"sv },
        { "type_mark"sv, "Type Mark"sv },
        { "unconstrained_array_definition"sv, "Unconstrained Array Definition"sv },
        { "use_clause"sv, "Use Clause"sv },
        { "variable_assignment_statement"sv, "Variable Assignment Statement"sv },
        { "variable_declaration"sv, "Variable Declaration"sv },
        { "wait_statement"sv, "Wait Statement"sv },
        { "waveform"sv, "Waveform"sv },
        { "waveform_element"sv, "Waveform Element"sv },

        /* other */
        { "signal_name"sv, "Signal Name"sv },

        { "boolean_expression"sv, "Boolean Expression"sv },
        { "time_expression"sv, "Time Expression"sv },
        { "value_expression"sv, "Value Expression"sv },

        /* Typographical */
        { "';'"sv, "Semicolon ';'"sv },
        { "':'"sv, "Colon ':'"sv },
        { "','"sv, "Comma ':'"sv },
        { "'{'"sv, "Opening '{' Curly Brace"sv },
        { "'}'"sv, "Closing '}' Curly Brace"sv },
        { "'['"sv, "Opening '[' Square Bracket"sv },
        { "']'"sv, "Closing ']' Square Bracket"sv },
        { "'('"sv, "Opening '(' Brace/Parentheses"sv },
        { "'('"sv, "Closing ')' Brace/Parentheses"sv },
    };

    auto const iter = ruleid_map.find(which);

    if (iter != ruleid_map.end()) {
        return iter->second;
    }

    // FixMe: lookup failed, give a warning to developer
    return which;
}

std::string on_error_base::make_error_description(std::string_view which) const
{
    using boost::locale::format;
    using boost::locale::translate;

    return (format(translate("Error, expecting {1} here:")) % lookup(which)).str();
}

} // namespace parser
} // namespace vhdl
} // namespace eda
