#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <vector>

namespace ibis::vhdl::ast {

//
// AST nodes forward declared
//
// Quick & Dirty created by:
//
// \code.{.sh}
// #!/usr/bin/env bash
//
// egrep '(struct|using)' source/vhdl/include/ibis/vhdl/ast/node/*.hpp \
// | awk -F':' '{print $2}' \
// | sed -e '/^ /d' -e 's/using/struct/g' -e 's/=.*//g' -e 's/ $/;/g' \
// | sort | uniq
// \endcode
//
// with tweaking by hand afterwards.
//
struct abstract_literal;
struct access_type_definition;
struct actual_designator;
// struct actual_parameter_part;
// struct actual_part;
struct actual_part_chunk;
struct aggregate;
struct alias_declaration;
struct alias_designator;
struct allocator;
struct architecture_body;
// struct architecture_declarative_part;
struct architecture_statement_part;
struct array_type_definition;
struct assertion;
struct assertion_statement;
struct association_element;
struct association_list;
struct attribute_declaration;
struct attribute_name;
struct attribute_specification;
struct based_literal;
struct binding_indication;
struct bit_string_literal;
struct block_configuration;
// struct block_declarative_item;
// struct block_declarative_part;
struct block_header;
struct block_specification;
struct block_specification_chunk;
struct block_statement;
struct block_statement_part;
struct case_statement;
struct case_statement_alternative;
struct character_literal;
// struct choice;
// struct choices;
struct component_configuration;
struct component_declaration;
struct component_instantiation_statement;
struct component_specification;
struct composite_type_definition;
struct concurrent_assertion_statement;
struct concurrent_procedure_call_statement;
struct concurrent_signal_assignment_statement;
struct concurrent_statement;
// struct condition;
struct conditional_signal_assignment;
struct conditional_waveforms;
struct condition_clause;
struct configuration_declaration;
// struct configuration_declarative_item;
struct configuration_declarative_part;  // FixMe: using ... = vector<>
// struct configuration_item;
struct configuration_specification;
struct constant_declaration;
struct constrained_array_definition;
struct constraint;
// struct context_clause;
// struct context_item;
struct decimal_literal;
struct delay_mechanism;
struct designator;
struct design_file;  // FixMe: using ... = vector<>
struct design_unit;
struct disconnection_specification;
struct discrete_range;
struct element_association;
struct element_declaration;
struct entity_aspect;
struct entity_aspect_configuration;
struct entity_aspect_entity;
struct entity_class_entry_list;
struct entity_declaration;
// struct entity_declarative_item;
struct entity_declarative_part;  // FixMe: using ... = vector<>
struct entity_designator;
struct entity_designator_list;
struct entity_header;
struct entity_name_list;
struct entity_specification;
// struct entity_statement;
struct entity_statement_part;  // FixMe: using .. vector<>
// struct entity_tag;
struct enumeration_literal;
struct enumeration_type_definition;
struct exit_statement;
struct expression;
struct factor;
struct factor_binary_operation;
struct factor_unary_operation;
struct file_declaration;
// struct file_logical_name;
struct file_open_information;
// struct file_type_definition;
struct formal_designator;
// struct formal_parameter_list;
struct formal_part;
struct function_call;
struct generate_statement;
struct generation_scheme;
struct generic_clause;
struct generic_map_aspect;
// struct group_constituent;
// struct group_constituent_list;
struct group_declaration;
struct group_template_declaration;
struct guarded_signal_specification;
struct identifier;
struct identifier_list;
struct if_statement;
struct index_constraint;
struct indexed_name;
struct index_specification;
struct index_subtype_definition;
struct instantiated_unit;
struct instantiated_unit_component;
struct instantiated_unit_configuration;
struct instantiated_unit_entity;
// struct instantiation_label_list;
struct instantiation_list;
struct interface_constant_declaration;
// struct interface_declaration;
// struct interface_element;
struct interface_file_declaration;
struct interface_list;
struct interface_signal_declaration;
struct interface_variable_declaration;
struct iteration_scheme;
// struct label;
struct library_clause;
// struct library_unit;
struct literal;
// struct logical_name;
struct loop_statement;
struct name;
struct next_statement;
struct null_statement;
struct numeric_literal;
// struct operator_symbol;
struct options;
struct package_body;
// struct package_body_declarative_item;
// struct package_body_declarative_part;
struct package_declaration;
// struct package_declarative_item;
// struct package_declarative_part;
struct parameter_specification;
struct physical_literal;
struct physical_type_definition;
struct port_clause;
struct port_map_aspect;
struct prefix;
struct primary;
struct primary_unit;
// struct primary_unit_declaration;
struct procedure_call;
struct procedure_call_statement;
// struct process_declarative_item;
struct process_declarative_part;  // FixMe: using ... = vector<>
struct process_statement;
// struct process_statement_part;
struct qualified_expression;
struct range;
// struct range_attribute_name;
// struct range_constraint;
struct range_expression;
struct record_type_definition;
struct relation;
struct report_statement;
struct return_statement;
struct scalar_type_definition;
struct secondary_unit;
struct secondary_unit_declaration;
struct selected_name;
struct selected_signal_assignment;
struct selected_waveform;
struct selected_waveforms;
struct sensitivity_clause;
struct sensitivity_list;
struct sequence_of_statements;
// struct sequential_statement;
struct shift_expression;
struct signal_assignment_statement;
struct signal_declaration;
struct signal_list;
struct signal_list_list;
struct signature;
struct simple_expression;
// struct simple_name;
struct slice_name;
struct string_literal;
struct subprogram_body;
// struct subprogram_declaration;
// struct subprogram_declarative_item;
// struct subprogram_declarative_part;
struct subprogram_specification;
struct subprogram_specification_function;
struct subprogram_specification_procedure;
// struct subprogram_statement_part;
struct subtype_declaration;
struct subtype_indication;
struct suffix;
struct target;
struct term;
struct timeout_clause;
struct type_conversion;
struct type_declaration;
struct type_definition;
struct unconstrained_array_definition;
struct use_clause;
struct variable_assignment_statement;
struct variable_declaration;
struct wait_statement;
struct waveform;
struct waveform_element;
// struct waveform_element_form;
struct waveform_element_list;

struct nullary;

enum class keyword_token;

using actual_parameter_part = association_list;
using condition = ast::expression;
using file_logical_name = expression;
using file_type_definition = ast::name;
using formal_parameter_list = interface_list;
using label = ast::identifier;
using logical_name = ast::identifier;
using operator_symbol = ast::string_literal;
using primary_unit_declaration = ast::identifier;
using process_statement_part = ast::sequence_of_statements;
using range_attribute_name = ast::attribute_name;
using range_constraint = ast::range;
using simple_name = ast::identifier;
using subprogram_declaration = ast::subprogram_specification;
using subprogram_statement_part = sequence_of_statements;

using actual_part = variant<actual_designator, actual_part_chunk>;
using choice = variant<nullary, simple_name, discrete_range, simple_expression, keyword_token>;
using entity_tag = variant<nullary, simple_name, character_literal, operator_symbol>;
using group_constituent = variant<ast::nullary, ast::name, ast::character_literal>;
using interface_declaration =
    variant<nullary, interface_constant_declaration, interface_signal_declaration,
            interface_variable_declaration, interface_file_declaration>;
using interface_element = ast::interface_declaration;
using subprogram_declarative_item =
    variant<ast::nullary, ast::subprogram_declaration, forward_ast<ast::subprogram_body>,
            ast::type_declaration, ast::subtype_declaration, ast::constant_declaration,
            ast::variable_declaration, ast::file_declaration, ast::alias_declaration,
            ast::attribute_declaration, ast::attribute_specification, ast::use_clause,
            ast::group_template_declaration, ast::group_declaration>;
using sequential_statement =
    variant<nullary, wait_statement, assertion_statement, report_statement,
            signal_assignment_statement, variable_assignment_statement, procedure_call_statement,
            forward_ast<if_statement>, forward_ast<case_statement>, forward_ast<loop_statement>,
            next_statement, exit_statement, return_statement, null_statement>;
using block_declarative_item =
    variant<ast::nullary, ast::alias_declaration, ast::attribute_declaration,
            ast::attribute_specification, ast::component_declaration,
            ast::configuration_specification, ast::constant_declaration,
            ast::disconnection_specification, ast::file_declaration, ast::group_declaration,
            ast::group_template_declaration, ast::variable_declaration, ast::signal_declaration,
            ast::subprogram_body, ast::subprogram_declaration, ast::subtype_declaration,
            ast::type_declaration, ast::use_clause>;
using process_declarative_item =
    variant<nullary, alias_declaration, attribute_declaration, attribute_specification,
            constant_declaration, file_declaration, group_declaration, group_template_declaration,
            subprogram_body, subprogram_declaration, subtype_declaration, type_declaration,
            use_clause, variable_declaration>;
using configuration_item = variant<ast::nullary, forward_ast<ast::block_configuration>,
                                   forward_ast<ast::component_configuration> >;
using configuration_declarative_item =
    variant<ast::nullary, ast::use_clause, ast::attribute_specification, ast::group_declaration>;
using context_item = variant<ast::nullary, ast::library_clause, ast::use_clause>;
using context_clause = std::vector<ast::context_item>;
using entity_declarative_item =
    variant<nullary, alias_declaration, attribute_declaration, attribute_specification,
            constant_declaration, disconnection_specification, file_declaration, group_declaration,
            group_template_declaration, variable_declaration, signal_declaration, subprogram_body,
            subprogram_declaration, subtype_declaration, type_declaration, use_clause>;
using entity_statement = variant<ast::nullary, ast::concurrent_assertion_statement,
                                 ast::concurrent_procedure_call_statement, ast::process_statement>;
using package_declarative_item =
    variant<ast::nullary, ast::subprogram_declaration, ast::type_declaration,
            ast::subtype_declaration, ast::constant_declaration, ast::signal_declaration,
            ast::variable_declaration,  // shared_variable_declaration
            ast::file_declaration, ast::alias_declaration, ast::component_declaration,
            ast::attribute_declaration, ast::attribute_specification,
            ast::disconnection_specification, ast::use_clause, ast::group_template_declaration,
            ast::group_declaration>;
using package_body_declarative_item =
    variant<ast::nullary, ast::subprogram_declaration, ast::subprogram_body, ast::type_declaration,
            ast::subtype_declaration, ast::constant_declaration,
            ast::variable_declaration,  // shared_variable_declaration
            ast::file_declaration, ast::alias_declaration, ast::use_clause,
            ast::group_template_declaration, ast::group_declaration>;
using library_unit = variant<ast::nullary, ast::primary_unit, ast::secondary_unit>;
using waveform_element_form = variant<ast::expression, ast::keyword_token>;

using choices = std::vector<choice>;
using group_constituent_list = std::vector<ast::group_constituent>;
using instantiation_label_list = std::vector<ast::label>;
using subprogram_declarative_part = std::vector<ast::subprogram_declarative_item>;
using block_declarative_part = std::vector<ast::block_declarative_item>;
using package_declarative_part = std::vector<ast::package_declarative_item>;
using package_body_declarative_part = std::vector<ast::package_body_declarative_item>;

using architecture_declarative_part = ast::block_declarative_part;

}  // namespace ibis::vhdl::ast
