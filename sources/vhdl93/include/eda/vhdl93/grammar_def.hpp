/*
 * grammar_def.h
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_VHDL93_GRAMMAR_DEF_HPP_
#define INCLUDE_EDA_VHDL93_GRAMMAR_DEF_HPP_


#include <eda/vhdl93/grammar.hpp>

#include <boost/spirit/home/x3.hpp>


namespace eda { namespace vhdl93 { namespace parser {

	namespace x3 = boost::spirit::x3;
	namespace ascii = boost::spirit::x3::ascii;

	// Parser Declarations
	abstract_literal_type const abstract_literal { "abstract_literal" };
	access_type_definition_type const access_type_definition { "access_type_definition" };
	actual_designator_type const actual_designator { "actual_designator" };
	actual_parameter_part_type const actual_parameter_part { "actual_parameter_part" };
	actual_part_type const actual_part { "actual_part" };
	adding_operator_type const adding_operator { "adding_operator" };
	aggregate_type const aggregate { "aggregate" };
	alias_declaration_type const alias_declaration { "alias_declaration" };
	alias_designator_type const alias_designator { "alias_designator" };
	allocator_type const allocator { "allocator" };
	architecture_body_type const architecture_body { "architecture_body" };
	architecture_declarative_part_type const architecture_declarative_part { "architecture_declarative_part" };
	architecture_statement_part_type const architecture_statement_part { "architecture_statement_part" };
	array_type_definition_type const array_type_definition { "array_type_definition" };
	assertion_type const assertion { "assertion" };
	assertion_statement_type const assertion_statement { "assertion_statement" };
	association_element_type const association_element { "association_element" };
	association_list_type const association_list { "association_list" };
	attribute_declaration_type const attribute_declaration { "attribute_declaration" };
	attribute_designator_type const attribute_designator { "attribute_designator" };
	attribute_name_type const attribute_name { "attribute_name" };
	attribute_specification_type const attribute_specification { "attribute_specification" };
	base_type const base { "base" };
	base_specifier_type const base_specifier { "base_specifier" };
	base_unit_declaration_type const base_unit_declaration { "base_unit_declaration" };
	based_integer_type const based_integer { "based_integer" };
	based_literal_type const based_literal { "based_literal" };
	basic_character_type const basic_character { "basic_character" };
	basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };
	basic_identifier_type const basic_identifier { "basic_identifier" };
	binding_indication_type const binding_indication { "binding_indication" };
	bit_string_literal_type const bit_string_literal { "bit_string_literal" };
	bit_value_type const bit_value { "bit_value" };
	block_configuration_type const block_configuration { "block_configuration" };
	block_declarative_item_type const block_declarative_item { "block_declarative_item" };
	block_declarative_part_type const block_declarative_part { "block_declarative_part" };
	block_header_type const block_header { "block_header" };
	block_specification_type const block_specification { "block_specification" };
	block_statement_type const block_statement { "block_statement" };
	block_statement_part_type const block_statement_part { "block_statement_part" };
	case_statement_type const case_statement { "case_statement" };
	case_statement_alternative_type const case_statement_alternative { "case_statement_alternative" };
	character_literal_type const character_literal { "character_literal" };
	choice_type const choice { "choice" };
	choices_type const choices { "choices" };
	component_configuration_type const component_configuration { "component_configuration" };
	component_declaration_type const component_declaration { "component_declaration" };
	component_instantiation_statement_type const component_instantiation_statement { "component_instantiation_statement" };
	component_specification_type const component_specification { "component_specification" };
	composite_type_definition_type const composite_type_definition { "composite_type_definition" };
	concurrent_assertion_statement_type const concurrent_assertion_statement { "concurrent_assertion_statement" };
	concurrent_procedure_call_statement_type const concurrent_procedure_call_statement { "concurrent_procedure_call_statement" };
	concurrent_signal_assignment_statement_type const concurrent_signal_assignment_statement { "concurrent_signal_assignment_statement" };
	concurrent_statement_type const concurrent_statement { "concurrent_statement" };
	condition_type const condition { "condition" };
	condition_clause_type const condition_clause { "condition_clause" };
	conditional_signal_assignment_type const conditional_signal_assignment { "conditional_signal_assignment" };
	conditional_waveforms_type const conditional_waveforms { "conditional_waveforms" };
	configuration_declaration_type const configuration_declaration { "configuration_declaration" };
	configuration_declarative_item_type const configuration_declarative_item { "configuration_declarative_item" };
	configuration_declarative_part_type const configuration_declarative_part { "configuration_declarative_part" };
	configuration_item_type const configuration_item { "configuration_item" };
	configuration_specification_type const configuration_specification { "configuration_specification" };
	constant_declaration_type const constant_declaration { "constant_declaration" };
	constrained_array_definition_type const constrained_array_definition { "constrained_array_definition" };
	constraint_type const constraint { "constraint" };
	context_clause_type const context_clause { "context_clause" };
	context_item_type const context_item { "context_item" };
	decimal_literal_type const decimal_literal { "decimal_literal" };
	declaration_type const declaration { "declaration" };
	delay_mechanism_type const delay_mechanism { "delay_mechanism" };
	design_file_type const design_file { "design_file" };
	design_unit_type const design_unit { "design_unit" };
	designator_type const designator { "designator" };
	direction_type const direction { "direction" };
	disconnection_specification_type const disconnection_specification { "disconnection_specification" };
	discrete_range_type const discrete_range { "discrete_range" };
	element_association_type const element_association { "element_association" };
	element_declaration_type const element_declaration { "element_declaration" };
	element_subtype_definition_type const element_subtype_definition { "element_subtype_definition" };
	entity_aspect_type const entity_aspect { "entity_aspect" };
	entity_class_type const entity_class { "entity_class" };
	entity_class_entry_type const entity_class_entry { "entity_class_entry" };
	entity_class_entry_list_type const entity_class_entry_list { "entity_class_entry_list" };
	entity_declaration_type const entity_declaration { "entity_declaration" };
	entity_declarative_item_type const entity_declarative_item { "entity_declarative_item" };
	entity_declarative_part_type const entity_declarative_part { "entity_declarative_part" };
	entity_designator_type const entity_designator { "entity_designator" };
	entity_header_type const entity_header { "entity_header" };
	entity_name_list_type const entity_name_list { "entity_name_list" };
	entity_specification_type const entity_specification { "entity_specification" };
	entity_statement_type const entity_statement { "entity_statement" };
	entity_statement_part_type const entity_statement_part { "entity_statement_part" };
	entity_tag_type const entity_tag { "entity_tag" };
	enumeration_literal_type const enumeration_literal { "enumeration_literal" };
	enumeration_type_definition_type const enumeration_type_definition { "enumeration_type_definition" };
	exit_statement_type const exit_statement { "exit_statement" };
	exponent_type const exponent { "exponent" };
	expression_type const expression { "expression" };
	extended_digit_type const extended_digit { "extended_digit" };
	extended_identifier_type const extended_identifier { "extended_identifier" };
	factor_type const factor { "factor" };
	file_declaration_type const file_declaration { "file_declaration" };
	file_logical_name_type const file_logical_name { "file_logical_name" };
	file_open_information_type const file_open_information { "file_open_information" };
	file_type_definition_type const file_type_definition { "file_type_definition" };
	formal_designator_type const formal_designator { "formal_designator" };
	formal_parameter_list_type const formal_parameter_list { "formal_parameter_list" };
	formal_part_type const formal_part { "formal_part" };
	full_type_declaration_type const full_type_declaration { "full_type_declaration" };
	function_call_type const function_call { "function_call" };
	generate_statement_type const generate_statement { "generate_statement" };
	generation_scheme_type const generation_scheme { "generation_scheme" };
	generic_clause_type const generic_clause { "generic_clause" };
	generic_list_type const generic_list { "generic_list" };
	generic_map_aspect_type const generic_map_aspect { "generic_map_aspect" };
	graphic_character_type const graphic_character { "graphic_character" };
	group_constituent_type const group_constituent { "group_constituent" };
	group_constituent_list_type const group_constituent_list { "group_constituent_list" };
	group_template_declaration_type const group_template_declaration { "group_template_declaration" };
	group_declaration_type const group_declaration { "group_declaration" };
	guarded_signal_specification_type const guarded_signal_specification { "guarded_signal_specification" };
	identifier_type const identifier { "identifier" };
	identifier_list_type const identifier_list { "identifier_list" };
	if_statement_type const if_statement { "if_statement" };
	incomplete_type_declaration_type const incomplete_type_declaration { "incomplete_type_declaration" };
	index_constraint_type const index_constraint { "index_constraint" };
	index_specification_type const index_specification { "index_specification" };
	index_subtype_definition_type const index_subtype_definition { "index_subtype_definition" };
	indexed_name_type const indexed_name { "indexed_name" };
	instantiated_unit_type const instantiated_unit { "instantiated_unit" };
	instantiation_list_type const instantiation_list { "instantiation_list" };
	integer_type const integer { "integer" };
	integer_type_definition_type const integer_type_definition { "integer_type_definition" };
	interface_constant_declaration_type const interface_constant_declaration { "interface_constant_declaration" };
	interface_declaration_type const interface_declaration { "interface_declaration" };
	interface_element_type const interface_element { "interface_element" };
	interface_file_declaration_type const interface_file_declaration { "interface_file_declaration" };
	interface_list_type const interface_list { "interface_list" };
	interface_signal_declaration_type const interface_signal_declaration { "interface_signal_declaration" };
	interface_variable_declaration_type const interface_variable_declaration { "interface_variable_declaration" };
	iteration_scheme_type const iteration_scheme { "iteration_scheme" };
	label_type const label { "label" };
	letter_type const letter { "letter" };
	letter_or_digit_type const letter_or_digit { "letter_or_digit" };
	library_clause_type const library_clause { "library_clause" };
	library_unit_type const library_unit { "library_unit" };
	literal_type const literal { "literal" };
	logical_name_type const logical_name { "logical_name" };
	logical_name_list_type const logical_name_list { "logical_name_list" };
	logical_operator_type const logical_operator { "logical_operator" };
	loop_statement_type const loop_statement { "loop_statement" };
	miscellaneous_operator_type const miscellaneous_operator { "miscellaneous_operator" };
	mode_type const mode { "mode" };
	multiplying_operator_type const multiplying_operator { "multiplying_operator" };
	name_type const name { "name" };
	next_statement_type const next_statement { "next_statement" };
	null_statement_type const null_statement { "null_statement" };
	numeric_literal_type const numeric_literal { "numeric_literal" };
	object_declaration_type const object_declaration { "object_declaration" };
	operator_symbol_type const operator_symbol { "operator_symbol" };
	options_type const options { "options" };
	package_body_type const package_body { "package_body" };
	package_body_declarative_item_type const package_body_declarative_item { "package_body_declarative_item" };
	package_body_declarative_part_type const package_body_declarative_part { "package_body_declarative_part" };
	package_declaration_type const package_declaration { "package_declaration" };
	package_declarative_item_type const package_declarative_item { "package_declarative_item" };
	package_declarative_part_type const package_declarative_part { "package_declarative_part" };
	parameter_specification_type const parameter_specification { "parameter_specification" };
	physical_literal_type const physical_literal { "physical_literal" };
	physical_type_definition_type const physical_type_definition { "physical_type_definition" };
	port_clause_type const port_clause { "port_clause" };
	port_list_type const port_list { "port_list" };
	port_map_aspect_type const port_map_aspect { "port_map_aspect" };
	prefix_type const prefix { "prefix" };
	primary_type const primary { "primary" };
	primary_unit_type const primary_unit { "primary_unit" };
	procedure_call_type const procedure_call { "procedure_call" };
	procedure_call_statement_type const procedure_call_statement { "procedure_call_statement" };
	process_declarative_item_type const process_declarative_item { "process_declarative_item" };
	process_declarative_part_type const process_declarative_part { "process_declarative_part" };
	process_statement_type const process_statement { "process_statement" };
	process_statement_part_type const process_statement_part { "process_statement_part" };
	qualified_expression_type const qualified_expression { "qualified_expression" };
	range_type const range { "range" };
	range_constraint_type const range_constraint { "range_constraint" };
	record_type_definition_type const record_type_definition { "record_type_definition" };
	relation_type const relation { "relation" };
	relational_operator_type const relational_operator { "relational_operator" };
	report_statement_type const report_statement { "report_statement" };
	return_statement_type const return_statement { "return_statement" };
	scalar_type_definition_type const scalar_type_definition { "scalar_type_definition" };
	secondary_unit_type const secondary_unit { "secondary_unit" };
	secondary_unit_declaration_type const secondary_unit_declaration { "secondary_unit_declaration" };
	selected_name_type const selected_name { "selected_name" };
	selected_signal_assignment_type const selected_signal_assignment { "selected_signal_assignment" };
	selected_waveforms_type const selected_waveforms { "selected_waveforms" };
	sensitivity_clause_type const sensitivity_clause { "sensitivity_clause" };
	sensitivity_list_type const sensitivity_list { "sensitivity_list" };
	sequence_of_statements_type const sequence_of_statements { "sequence_of_statements" };
	sequential_statement_type const sequential_statement { "sequential_statement" };
	shift_expression_type const shift_expression { "shift_expression" };
	shift_operator_type const shift_operator { "shift_operator" };
	sign_type const sign { "sign" };
	signal_assignment_statement_type const signal_assignment_statement { "signal_assignment_statement" };
	signal_declaration_type const signal_declaration { "signal_declaration" };
	signal_kind_type const signal_kind { "signal_kind" };
	signal_list_type const signal_list { "signal_list" };
	signature_type const signature { "signature" };
	simple_expression_type const simple_expression { "simple_expression" };
	simple_name_type const simple_name { "simple_name" };
	slice_name_type const slice_name { "slice_name" };
	string_literal_type const string_literal { "string_literal" };
	subprogram_body_type const subprogram_body { "subprogram_body" };
	subprogram_declaration_type const subprogram_declaration { "subprogram_declaration" };
	subprogram_declarative_item_type const subprogram_declarative_item { "subprogram_declarative_item" };
	subprogram_declarative_part_type const subprogram_declarative_part { "subprogram_declarative_part" };
	subprogram_kind_type const subprogram_kind { "subprogram_kind" };
	subprogram_specification_type const subprogram_specification { "subprogram_specification" };
	subprogram_statement_part_type const subprogram_statement_part { "subprogram_statement_part" };
	subtype_declaration_type const subtype_declaration { "subtype_declaration" };
	subtype_indication_type const subtype_indication { "subtype_indication" };
	suffix_type const suffix { "suffix" };
	target_type const target { "target" };
	term_type const term { "term" };
	timeout_clause_type const timeout_clause { "timeout_clause" };
	type_conversion_type const type_conversion { "type_conversion" };
	type_declaration_type const type_declaration { "type_declaration" };
	type_definition_type const type_definition { "type_definition" };
	type_mark_type const type_mark { "type_mark" };
	unconstrained_array_definition_type const unconstrained_array_definition { "unconstrained_array_definition" };
	use_clause_type const use_clause { "use_clause" };
	variable_assignment_statement_type const variable_assignment_statement { "variable_assignment_statement" };
	variable_declaration_type const variable_declaration { "variable_declaration" };
	wait_statement_type const wait_statement { "wait_statement" };
	waveform_type const waveform { "waveform" };

	// Grammar reserved keywords
	auto kw = [](auto xx) {
	    return x3::lexeme [ x3::no_case[ xx ] >> !(ascii::alnum | '_') ];
	};

	auto const abs_ = kw("abs");
	auto const access_ = kw("access");
	auto const after_ = kw("after");
	auto const alias_ = kw("alias");
	auto const all_ = kw("all");
	auto const and_ = kw("and");
	auto const architecture_ = kw("architecture");
	auto const array_ = kw("array");
	auto const assert_ = kw("assert");
	auto const attribute_ = kw("attribute");
	auto const begin_ = kw("begin");
	auto const block_ = kw("block");
	auto const body_ = kw("body");
	auto const buffer_ = kw("buffer");
	auto const bus_ = kw("bus");
	auto const case_ = kw("case");
	auto const component_ = kw("component");
	auto const configuration_ = kw("configuration");
	auto const constant_ = kw("constant");
	auto const disconnect_ = kw("disconnect");
	auto const downto_ = kw("downto");
	auto const else_ = kw("else");
	auto const elsif_ = kw("elsif");
	auto const end_ = kw("end");
	auto const entity_ = kw("entity");
	auto const exit_ = kw("exit");
	auto const file_ = kw("file");
	auto const for_ = kw("for");
	auto const function_ = kw("function");
	auto const generate_ = kw("generate");
	auto const generic_ = kw("generic");
	auto const group_ = kw("group");
	auto const guarded_ = kw("guarded");
	auto const if_ = kw("if");
	auto const impure_ = kw("impure");
	auto const in_ = kw("in");
	auto const inertial_ = kw("inertial");
	auto const inout_ = kw("inout");
	auto const is_ = kw("is");
	auto const label_ = kw("label");
	auto const library_ = kw("library");
	auto const linkage_ = kw("linkage");
	auto const literal_ = kw("literal");
	auto const loop_ = kw("loop");
	auto const map_ = kw("map");
	auto const mod_ = kw("mod");
	auto const nand_ = kw("nand");
	auto const new_ = kw("new");
	auto const next_ = kw("next");
	auto const nor_ = kw("nor");
	auto const not_ = kw("not");
	auto const null_ = kw("null");
	auto const of_ = kw("of");
	auto const on_ = kw("on");
	auto const open_ = kw("open");
	auto const or_ = kw("or");
	auto const others_ = kw("others");
	auto const out_ = kw("out");
	auto const package_ = kw("package");
	auto const port_ = kw("port");
	auto const postponed_ = kw("postponed");
	auto const procedure_ = kw("procedure");
	auto const process_ = kw("process");
	auto const pure_ = kw("pure");
	auto const range_ = kw("range");
	auto const record_ = kw("record");
	auto const register_ = kw("register");
	auto const reject_ = kw("reject");
	auto const rem_ = kw("rem");
	auto const report_ = kw("report");
	auto const return_ = kw("return");
	auto const rol_ = kw("rol");
	auto const ror_ = kw("ror");
	auto const select_ = kw("select");
	auto const severity_ = kw("severity");
	auto const signal_ = kw("signal");
	auto const shared_ = kw("shared");
	auto const sla_ = kw("sla");
	auto const sll_ = kw("sll");
	auto const sra_ = kw("sra");
	auto const srl_ = kw("srl");
	auto const subtype_ = kw("subtype");
	auto const then_ = kw("then");
	auto const to_ = kw("to");
	auto const transport_ = kw("transport");
	auto const type_ = kw("type");
	auto const unaffected_ = kw("unaffected");
	auto const units_ = kw("units");
	auto const until_ = kw("until");
	auto const use_ = kw("use");
	auto const variable_ = kw("variable");
	auto const wait_ = kw("wait");
	auto const when_ = kw("when");
	auto const while_ = kw("while");
	auto const with_ = kw("with");
	auto const xnor_ = kw("xnor");
	auto const xor_ = kw("xor");


	using x3::char_;
	using x3::graph;


#if 0
// abstract_literal ::=
// decimal_literal | based_literal
auto const abstract_literal_def =
    decimal_literal | based_literal
    ;
#endif

#if 0
// access_type_definition ::=
// access subtype_indication
auto const access_type_definition_def =
    access subtype_indication
    ;
#endif

#if 0
// actual_designator ::=
//     expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open
auto const actual_designator_def =
        expression
    | signal_name
    | variable_name
    | file_name
    | open

    ;
#endif

#if 0
// actual_parameter_part ::=
// parameter_association_list
auto const actual_parameter_part_def =
    parameter_association_list
    ;
#endif

#if 0
// actual_part ::=
//     actual_designator
//     | function_name ( actual_designator )
//     | type_mark ( actual_designator )
auto const actual_part_def =
        actual_designator
    | function_name ( actual_designator )
    | type_mark ( actual_designator )

    ;
#endif

#if 0
// adding_operator ::=
// + | -  | &
auto const adding_operator_def =
    + | -  | &
    ;
#endif

#if 0
// aggregate ::=
//     ( element_association { , element_association } )
auto const aggregate_def =
        ( element_association { char_(',') element_association } )

    ;
#endif

#if 0
// alias_declaration ::=
//     alias alias_designator [ : subtype_indication ] is name [ signature ]
auto const alias_declaration_def =
        alias alias_designator [ char_(':') subtype_indication ] is name [ signature ]

    ;
#endif

#if 0
// alias_designator ::=
// identifier | character_literal | operator_symbol
auto const alias_designator_def =
    identifier | character_literal | operator_symbol
    ;
#endif

#if 0
// allocator ::=
//     new subtype_indication
//     | new qualified_expression
auto const allocator_def =
        new subtype_indication
    | new qualified_expression

    ;
#endif

#if 0
// architecture_body ::=
//     architecture identifier of entity_name is
//     architecture_declarative_part
//     begin
//     architecture_statement_part
//     end [ architecture ] [ architecture_simple_name ]
auto const architecture_body_def =
        architecture identifier of entity_name is
    architecture_declarative_part
    begin
    architecture_statement_part
    end [ architecture ] [ architecture_simple_name ]

    ;
#endif

#if 0
// architecture_declarative_part ::=
//     { block_declarative_item }
auto const architecture_declarative_part_def =
        { block_declarative_item }

    ;
#endif

#if 0
// architecture_statement_part ::=
//     { concurrent_statement }
auto const architecture_statement_part_def =
        { concurrent_statement }

    ;
#endif

#if 0
// array_type_definition ::=
//     unconstrained_array_definition    |   constrained_array_definition
auto const array_type_definition_def =
        unconstrained_array_definition    |   constrained_array_definition

    ;
#endif

#if 0
// assertion ::=
//     assert condition
//     [ report expression ]
//     [ severity expression ]
auto const assertion_def =
        assert condition
    [ report expression ]
    [ severity expression ]

    ;
#endif

#if 0
// assertion_statement ::=
// [ label : ] assertion
auto const assertion_statement_def =
    [ label char_(':') ] assertion
    ;
#endif

#if 0
// association_element ::=
//     [ formal_part => ] actual_part
auto const association_element_def =
        [ formal_part => ] actual_part

    ;
#endif

#if 0
// association_list ::=
//     association_element { , association_element }
auto const association_list_def =
        association_element { char_(',') association_element }

    ;
#endif

#if 0
// attribute_declaration ::=
//     attribute identifier : type_mark
auto const attribute_declaration_def =
        attribute identifier char_(':') type_mark

    ;
#endif

#if 0
// attribute_designator ::=
// attribute_simple_name
auto const attribute_designator_def =
    attribute_simple_name
    ;
#endif

#if 0
// attribute_name ::=
//     prefix [ signature ] ' attribute_designator [ ( expression ) ]
auto const attribute_name_def =
        prefix [ signature ] char_('\'') attribute_designator [ ( expression ) ]

    ;
#endif

#if 0
// attribute_specification ::=
//     attribute attribute_designator of entity_specification is expression
auto const attribute_specification_def =
        attribute attribute_designator of entity_specification is expression

    ;
#endif

#if 0
// base ::=
// integer
auto const base_def =
    integer
    ;
#endif

#if 0
// base_specifier ::=
// B | O | X
auto const base_specifier_def =
    B | O | X
    ;
#endif

#if 0
// base_unit_declaration ::=
// identifier
auto const base_unit_declaration_def =
    identifier
    ;
#endif

#if 0
// based_integer ::=
//     extended_digit { [ underline ] extended_digit }
auto const based_integer_def =
        extended_digit { [ underline ] extended_digit }

    ;
#endif

#if 0
// based_literal ::=
//     base # based_integer [ . based_integer ] # [ exponent ]
auto const based_literal_def =
        base char_('#') based_integer [ char_('.') based_integer ] char_('#') [ exponent ]

    ;
#endif

#if 0
// basic_character ::=
//     basic_graphic_character | format_effector
auto const basic_character_def =
        basic_graphic_character | format_effector

    ;
#endif

#if 0
// basic_graphic_character ::=
//     upper_case_letter | digit | special_character| space_character
auto const basic_graphic_character_def =
        upper_case_letter | digit | special_character| space_character

    ;
#endif

#if 0
// basic_identifier ::=
//     letter { [ underline ] letter_or_digit }
auto const basic_identifier_def =
        letter { [ underline ] letter_or_digit }

    ;
#endif

#if 0
// binding_indication ::=
//     [ use entity_aspect ]
//     [ generic_map_aspect ]
//     [ port_map_aspect ]
auto const binding_indication_def =
        [ use entity_aspect ]
    [ generic_map_aspect ]
    [ port_map_aspect ]

    ;
#endif

#if 0
// bit_string_literal ::=
// base_specifier " bit_value "
auto const bit_string_literal_def =
    base_specifier char_('"') bit_value char_('"')
    ;
#endif

#if 0
// bit_value ::=
// extended_digit { [ underline ] extended_digit }
auto const bit_value_def =
    extended_digit { [ underline ] extended_digit }
    ;
#endif

#if 0
// block_configuration ::=
//     for block_specification
//     { use_clause }
//     { configuration_item }
//     end for
auto const block_configuration_def =
        for block_specification
    { use_clause }
    { configuration_item }
    end for

    ;
#endif

#if 0
// block_declarative_item ::=
//     subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | component_declaration
//     | attribute_declaration
//     | attribute_specification
//     | configuration_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const block_declarative_item_def =
        subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | component_declaration
    | attribute_declaration
    | attribute_specification
    | configuration_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// block_declarative_part ::=
//     { block_declarative_item }
auto const block_declarative_part_def =
        { block_declarative_item }

    ;
#endif

#if 0
// block_header ::=
//     [ generic_clause
//     [ generic_map_aspect ; ] ]
//     [ port_clause
//     [ port_map_aspect ; ] ]
auto const block_header_def =
        [ generic_clause
    [ generic_map_aspect char_(';') ] ]
    [ port_clause
    [ port_map_aspect char_(';') ] ]

    ;
#endif

#if 0
// block_specification ::=
//     architecture_name
//     | block_statement_label
//     | generate_statement_label [ ( index_specification ) ]
auto const block_specification_def =
        architecture_name
    | block_statement_label
    | generate_statement_label [ ( index_specification ) ]

    ;
#endif

#if 0
// block_statement ::=
//     block_label :
//     block [ ( guard_expression ) ] [ is ]
//     block_header
//     block_declarative_part
//     begin
//     block_statement_part
//     end block [ block_label ]
auto const block_statement_def =
        block_label :
    block [ ( guard_expression ) ] [ is ]
    block_header
    block_declarative_part
    begin
    block_statement_part
    end block [ block_label ]

    ;
#endif

#if 0
// block_statement_part ::=
//     { concurrent_statement }
auto const block_statement_part_def =
        { concurrent_statement }

    ;
#endif

#if 0
// case_statement ::=
//     [ case_label : ]
//     case expression is
//     case_statement_alternative
//     { case_statement_alternative }
//     end case [ case_label ]
auto const case_statement_def =
        [ case_label char_(':') ]
    case expression is
    case_statement_alternative
    { case_statement_alternative }
    end case [ case_label ]

    ;
#endif

#if 0
// case_statement_alternative ::=
//     when choices =>
//     sequence_of_statements
auto const case_statement_alternative_def =
        when choices =>
    sequence_of_statements

    ;
#endif

#if 0
// character_literal ::=
// ' graphic_character '
auto const character_literal_def =
    ' graphic_character '
    ;
#endif

#if 0
// choice ::=
//     simple_expression
//     | discrete_range
//     | element_simple_name
//     | others
auto const choice_def =
        simple_expression
    | discrete_range
    | element_simple_name
    | others

    ;
#endif

#if 0
// choices ::=
// choice { | choice }
auto const choices_def =
    choice { | choice }
    ;
#endif

#if 0
// component_configuration ::=
//     for component_specification
//     [ binding_indication ; ]
//     [ block_configuration ]
//     end for
auto const component_configuration_def =
        for component_specification
    [ binding_indication char_(';') ]
    [ block_configuration ]
    end for

    ;
#endif

#if 0
// component_declaration ::=
//     component identifier [ is ]
//     [ local_generic_clause ]
//     [ local_port_clause ]
//     end component [ component_simple_name ]
auto const component_declaration_def =
        component identifier [ is ]
    [ local_generic_clause ]
    [ local_port_clause ]
    end component [ component_simple_name ]

    ;
#endif

#if 0
// component_instantiation_statement ::=
//     instantiation_label :
//     instantiated_unit
//     [ generic_map_aspect ]
//     [ port_map_aspect ]
auto const component_instantiation_statement_def =
        instantiation_label :
    instantiated_unit
    [ generic_map_aspect ]
    [ port_map_aspect ]

    ;
#endif

#if 0
// component_specification ::=
//     instantiation_list : component_name
auto const component_specification_def =
        instantiation_list char_(':') component_name

    ;
#endif

#if 0
// composite_type_definition ::=
//     array_type_definition
//     | record_type_definition
auto const composite_type_definition_def =
        array_type_definition
    | record_type_definition

    ;
#endif

#if 0
// concurrent_assertion_statement ::=
//     [ label : ] [ postponed ] assertion
auto const concurrent_assertion_statement_def =
        [ label char_(':') ] [ postponed ] assertion

    ;
#endif

#if 0
// concurrent_procedure_call_statement ::=
//     [ label : ] [ postponed ] procedure_call
auto const concurrent_procedure_call_statement_def =
        [ label char_(':') ] [ postponed ] procedure_call

    ;
#endif

#if 0
// concurrent_signal_assignment_statement ::=
//     [ label : ] [ postponed ] conditional_signal_assignment
//     | [ label : ] [ postponed ] selected_signal_assignment
auto const concurrent_signal_assignment_statement_def =
        [ label char_(':') ] [ postponed ] conditional_signal_assignment
    | [ label char_(':') ] [ postponed ] selected_signal_assignment

    ;
#endif

#if 0
// concurrent_statement ::=
//     block_statement
//     | process_statement
//     | concurrent_procedure_call_statement
//     | concurrent_assertion_statement
//     | concurrent_signal_assignment_statement
//     | component_instantiation_statement
//     | generate_statement
auto const concurrent_statement_def =
        block_statement
    | process_statement
    | concurrent_procedure_call_statement
    | concurrent_assertion_statement
    | concurrent_signal_assignment_statement
    | component_instantiation_statement
    | generate_statement

    ;
#endif

#if 0
// condition ::=
// boolean_expression
auto const condition_def =
    boolean_expression
    ;
#endif

#if 0
// condition_clause ::=
// until condition
auto const condition_clause_def =
    until condition
    ;
#endif

#if 0
// conditional_signal_assignment ::=
//     target    <= options conditional_waveforms
auto const conditional_signal_assignment_def =
        target    lit("<=") options conditional_waveforms

    ;
#endif

#if 0
// conditional_waveforms ::=
//     { waveform when condition else }
//     waveform [ when condition ]
auto const conditional_waveforms_def =
        { waveform when condition else }
    waveform [ when condition ]

    ;
#endif

#if 0
// configuration_declaration ::=
//     configuration identifier of entity_name is
//     configuration_declarative_part
//     block_configuration
//     end [ configuration ] [ configuration_simple_name ]
auto const configuration_declaration_def =
        configuration identifier of entity_name is
    configuration_declarative_part
    block_configuration
    end [ configuration ] [ configuration_simple_name ]

    ;
#endif

#if 0
// configuration_declarative_item ::=
//     use_clause
//     | attribute_specification
//     | group_declaration
auto const configuration_declarative_item_def =
        use_clause
    | attribute_specification
    | group_declaration

    ;
#endif

#if 0
// configuration_declarative_part ::=
//     { configuration_declarative_item }
auto const configuration_declarative_part_def =
        { configuration_declarative_item }

    ;
#endif

#if 0
// configuration_item ::=
//     block_configuration
//     | component_configuration
auto const configuration_item_def =
        block_configuration
    | component_configuration

    ;
#endif

#if 0
// configuration_specification ::=
//     for component_specification binding_indication
auto const configuration_specification_def =
        for component_specification binding_indication

    ;
#endif

#if 0
// constant_declaration ::=
//     constant identifier_list : subtype_indication [ := expression ]
auto const constant_declaration_def =
        constant identifier_list char_(':') subtype_indication [ := expression ]

    ;
#endif

#if 0
// constrained_array_definition ::=
//     array index_constraint of element_subtype_indication
auto const constrained_array_definition_def =
        array index_constraint of element_subtype_indication

    ;
#endif

#if 0
// constraint ::=
//     range_constraint
//     | index_constraint
auto const constraint_def =
        range_constraint
    | index_constraint

    ;
#endif

#if 0
// context_clause ::=
// { context_item }
auto const context_clause_def =
    { context_item }
    ;
#endif

#if 0
// context_item ::=
//     library_clause
//     | use_clause
auto const context_item_def =
        library_clause
    | use_clause

    ;
#endif

#if 0
// decimal_literal ::=
// integer [ . integer ] [ exponent ]
auto const decimal_literal_def =
    integer [ char_('.') integer ] [ exponent ]
    ;
#endif

#if 0
// declaration ::=
//     type_declaration
//     | subtype_declaration
//     | object_declaration
//     | interface_declaration
//     | alias_declaration
//     | attribute_declaration
//     | component_declaration
//     | group_template_declaration
//     | group_declaration
//     | entity_declaration
//     | configuration_declaration
//     | subprogram_declaration
//     | package_declaration
auto const declaration_def =
        type_declaration
    | subtype_declaration
    | object_declaration
    | interface_declaration
    | alias_declaration
    | attribute_declaration
    | component_declaration
    | group_template_declaration
    | group_declaration
    | entity_declaration
    | configuration_declaration
    | subprogram_declaration
    | package_declaration

    ;
#endif

#if 0
// delay_mechanism ::=
//     transport
//     | [ reject time_expression ] inertial
auto const delay_mechanism_def =
        transport
    | [ reject time_expression ] inertial

    ;
#endif

#if 0
// design_file ::=
// design_unit { design_unit }
auto const design_file_def =
    design_unit { design_unit }
    ;
#endif

#if 0
// design_unit ::=
// context_clause library_unit
auto const design_unit_def =
    context_clause library_unit
    ;
#endif

#if 0
// designator ::=
// identifier  |  operator_symbol
auto const designator_def =
    identifier  |  operator_symbol
    ;
#endif

#if 0
// direction ::=
// to | downto
auto const direction_def =
    to | downto
    ;
#endif

#if 0
// disconnection_specification ::=
//     disconnect guarded_signal_specification after time_expression
auto const disconnection_specification_def =
        disconnect guarded_signal_specification after time_expression

    ;
#endif

#if 0
// discrete_range ::=
// discrete_subtype_indication | range
auto const discrete_range_def =
    discrete_subtype_indication | range
    ;
#endif

#if 0
// element_association ::=
//     [ choices => ] expression
auto const element_association_def =
        [ choices => ] expression

    ;
#endif

#if 0
// element_declaration ::=
//     identifier_list : element_subtype_definition
auto const element_declaration_def =
        identifier_list char_(':') element_subtype_definition

    ;
#endif

#if 0
// element_subtype_definition ::=
// subtype_indication
auto const element_subtype_definition_def =
    subtype_indication
    ;
#endif

#if 0
// entity_aspect ::=
//     entity entity_name [ ( architecture_identifier) ]
//     | configuration configuration_name
//     | open
auto const entity_aspect_def =
        entity entity_name [ ( architecture_identifier) ]
    | configuration configuration_name
    | open

    ;
#endif

#if 0
// entity_class ::=
//     entity         | architecture  | configuration
//     | procedure  | function         | package
//     | type         | subtype         | constant
//     | signal     | variable         | component
//     | label         | literal         | units
//     | group         | file
auto const entity_class_def =
        entity         | architecture  | configuration
    | procedure  | function         | package
    | type         | subtype         | constant
    | signal     | variable         | component
    | label         | literal         | units
    | group         | file

    ;
#endif

#if 0
// entity_class_entry ::=
// entity_class [ <> ]
auto const entity_class_entry_def =
    entity_class [ <> ]
    ;
#endif

#if 0
// entity_class_entry_list ::=
//     entity_class_entry { , entity_class_entry }
auto const entity_class_entry_list_def =
        entity_class_entry { char_(',') entity_class_entry }

    ;
#endif

#if 0
// entity_declaration ::=
//     entity identifier is
//     entity_header
//     entity_declarative_part
//     [ begin
//     entity_statement_part ]
//     end [ entity ] [ entity_simple_name ]
auto const entity_declaration_def =
        entity identifier is
    entity_header
    entity_declarative_part
    [ begin
    entity_statement_part ]
    end [ entity ] [ entity_simple_name ]

    ;
#endif

#if 0
// entity_declarative_item ::=
//     subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const entity_declarative_item_def =
        subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// entity_declarative_part ::=
//     { entity_declarative_item }
auto const entity_declarative_part_def =
        { entity_declarative_item }

    ;
#endif

#if 0
// entity_designator ::=
// entity_tag [ signature ]
auto const entity_designator_def =
    entity_tag [ signature ]
    ;
#endif

#if 0
// entity_header ::=
//     [ formal_generic_clause ]
//     [ formal_port_clause ]
auto const entity_header_def =
        [ formal_generic_clause ]
    [ formal_port_clause ]

    ;
#endif

#if 0
// entity_name_list ::=
//     entity_designator { , entity_designator }
//     | others
//     | all
auto const entity_name_list_def =
        entity_designator { char_(',') entity_designator }
    | others
    | all

    ;
#endif

#if 0
// entity_specification ::=
//     entity_name_list : entity_class
auto const entity_specification_def =
        entity_name_list char_(':') entity_class

    ;
#endif

#if 0
// entity_statement ::=
//     concurrent_assertion_statement
//     | passive_concurrent_procedure_call_statement
//     | passive_process_statement
auto const entity_statement_def =
        concurrent_assertion_statement
    | passive_concurrent_procedure_call_statement
    | passive_process_statement

    ;
#endif

#if 0
// entity_statement_part ::=
//     { entity_statement }
auto const entity_statement_part_def =
        { entity_statement }

    ;
#endif

#if 0
// entity_tag ::=
// simple_name | character_literal | operator_symbol
auto const entity_tag_def =
    simple_name | character_literal | operator_symbol
    ;
#endif

#if 0
// enumeration_literal ::=
// identifier | character_literal
auto const enumeration_literal_def =
    identifier | character_literal
    ;
#endif

#if 0
// enumeration_type_definition ::=
//     ( enumeration_literal { , enumeration_literal } )
auto const enumeration_type_definition_def =
        ( enumeration_literal { char_(',') enumeration_literal } )

    ;
#endif

#if 0
// exit_statement ::=
//     [ label : ] exit [ loop_label ] [ when condition ]
auto const exit_statement_def =
        [ label char_(':') ] exit [ loop_label ] [ when condition ]

    ;
#endif

#if 0
// exponent ::=
// E [ + ] integer | E - integer
auto const exponent_def =
    E [ + ] integer | E - integer
    ;
#endif

#if 0
// expression ::=
//     relation { and relation }
//     | relation { or relation }
//     | relation { xor relation }
//     | relation [ nand relation ]
//     | relation [ nor relation ]
//     | relation { xnor relation }
auto const expression_def =
        relation { and relation }
    | relation { or relation }
    | relation { xor relation }
    | relation [ nand relation ]
    | relation [ nor relation ]
    | relation { xnor relation }

    ;
#endif

#if 0
// extended_digit ::=
// digit | letter
auto const extended_digit_def =
    digit | letter
    ;
#endif

#if 0
// extended_identifier ::=
//     \ graphic_character { graphic_character }
auto const extended_identifier_def =
        \\ graphic_character { graphic_character }

    ;
#endif

#if 0
// factor ::=
//     primary [ ** primary ]
//     | abs primary
//     | not primary
auto const factor_def =
        primary [ ** primary ]
    | abs primary
    | not primary

    ;
#endif

#if 0
// file_declaration ::=
//     file identifier_list : subtype_indication file_open_information ]
auto const file_declaration_def =
        file identifier_list char_(':') subtype_indication file_open_information ]

    ;
#endif

#if 0
// file_logical_name ::=
// string_expression
auto const file_logical_name_def =
    string_expression
    ;
#endif

#if 0
// file_open_information ::=
//     [ open file_open_kind_expression ] is file_logical_name
auto const file_open_information_def =
        [ open file_open_kind_expression ] is file_logical_name

    ;
#endif

#if 0
// file_type_definition ::=
//     file  of type_mark
//     floating_type_definition  :=  range_constraint
auto const file_type_definition_def =
        file  of type_mark
    floating_type_definition  :=  range_constraint

    ;
#endif

#if 0
// formal_designator ::=
//     generic_name
//     | port_name
//     | parameter_name
auto const formal_designator_def =
        generic_name
    | port_name
    | parameter_name

    ;
#endif

#if 0
// formal_parameter_list ::=
// parameter_interface_list
auto const formal_parameter_list_def =
    parameter_interface_list
    ;
#endif

#if 0
// formal_part ::=
//     formal_designator
//     | function_name ( formal_designator )
//     | type_mark ( formal_designator )
auto const formal_part_def =
        formal_designator
    | function_name ( formal_designator )
    | type_mark ( formal_designator )

    ;
#endif

#if 0
// full_type_declaration ::=
//     type identifier is type_definition
auto const full_type_declaration_def =
        type identifier is type_definition

    ;
#endif

#if 0
// function_call ::=
//     function_name [ ( actual_parameter_part ) ]
auto const function_call_def =
        function_name [ ( actual_parameter_part ) ]

    ;
#endif

#if 0
// generate_statement ::=
//     generate_label :
//     generation_scheme generate
//     [ { block_declarative_item }
//     begin ]
//     { concurrent_statement }
//     end generate [ generate_label ]
auto const generate_statement_def =
        generate_label :
    generation_scheme generate
    [ { block_declarative_item }
    begin ]
    { concurrent_statement }
    end generate [ generate_label ]

    ;
#endif

#if 0
// generation_scheme ::=
//     for generate_parameter_specification
//     | if condition
auto const generation_scheme_def =
        for generate_parameter_specification
    | if condition

    ;
#endif

#if 0
// generic_clause ::=
//     generic ( generic_list )
auto const generic_clause_def =
        generic ( generic_list )

    ;
#endif

#if 0
// generic_list ::=
// generic_interface_list
auto const generic_list_def =
    generic_interface_list
    ;
#endif

#if 0
// generic_map_aspect ::=
//     generic map ( generic_association_list )
auto const generic_map_aspect_def =
        generic map ( generic_association_list )

    ;
#endif

#if 0
// graphic_character ::=
//     basic_graphic_character     | lower_case_letter | other_special_character
auto const graphic_character_def =
        basic_graphic_character     | lower_case_letter | other_special_character

    ;
#endif

#if 0
// group_constituent ::=
// name | character_literal
auto const group_constituent_def =
    name | character_literal
    ;
#endif

#if 0
// group_constituent_list ::=
// group_constituent { , group_constituent }
auto const group_constituent_list_def =
    group_constituent { char_(',') group_constituent }
    ;
#endif

#if 0
// group_template_declaration ::=
//     group identifier is ( entity_class_entry_list )
auto const group_template_declaration_def =
        group identifier is ( entity_class_entry_list )

    ;
#endif

#if 0
// group_declaration ::=
//     group identifier : group_template_name ( group_constituent_list )
auto const group_declaration_def =
        group identifier char_(':') group_template_name ( group_constituent_list )

    ;
#endif

#if 0
// guarded_signal_specification ::=
//     guarded_signal_list : type_mark
auto const guarded_signal_specification_def =
        guarded_signal_list char_(':') type_mark

    ;
#endif

#if 0
// identifier ::=
//     basic_identifier | extended_identifier
auto const identifier_def =
        basic_identifier | extended_identifier

    ;
#endif

#if 0
// identifier_list ::=
// identifier { , identifier }
auto const identifier_list_def =
    identifier { char_(',') identifier }
    ;
#endif

#if 0
// if_statement ::=
//     [ if_label : ]
//     if condition then
//     sequence_of_statements
//     { elsif condition then
//     sequence_of_statements }
//     [ else
//     sequence_of_statements ]
//     end if [ if_label ]
auto const if_statement_def =
        [ if_label char_(':') ]
    if condition then
    sequence_of_statements
    { elsif condition then
    sequence_of_statements }
    [ else
    sequence_of_statements ]
    end if [ if_label ]

    ;
#endif

#if 0
// incomplete_type_declaration ::=
// type identifier
auto const incomplete_type_declaration_def =
    type identifier
    ;
#endif

#if 0
// index_constraint ::=
// ( discrete_range { , discrete_range } )
auto const index_constraint_def =
    ( discrete_range { char_(',') discrete_range } )
    ;
#endif

#if 0
// index_specification ::=
//     discrete_range
//     | static_expression
auto const index_specification_def =
        discrete_range
    | static_expression

    ;
#endif

#if 0
// index_subtype_definition ::=
// type_mark range <>
auto const index_subtype_definition_def =
    type_mark range <>
    ;
#endif

#if 0
// indexed_name ::=
// prefix ( expression { , expression } )
auto const indexed_name_def =
    prefix ( expression { char_(',') expression } )
    ;
#endif

#if 0
// instantiated_unit ::=
//     [ component ] component_name
//     | entity entity_name [ ( architecture_identifier ) ]
//     | configuration configuration_name
auto const instantiated_unit_def =
        [ component ] component_name
    | entity entity_name [ ( architecture_identifier ) ]
    | configuration configuration_name

    ;
#endif

#if 0
// instantiation_list ::=
//     instantiation_label { , instantiation_label }
//     | others
//     | all
auto const instantiation_list_def =
        instantiation_label { char_(',') instantiation_label }
    | others
    | all

    ;
#endif

#if 0
// integer ::=
// digit { [ underline ] digit }
auto const integer_def =
    digit { [ underline ] digit }
    ;
#endif

#if 0
// integer_type_definition ::=
// range_constraint
auto const integer_type_definition_def =
    range_constraint
    ;
#endif

#if 0
// interface_constant_declaration ::=
//     [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]
auto const interface_constant_declaration_def =
        [ constant ] identifier_list char_(':') [ in ] subtype_indication [ := static_expression ]

    ;
#endif

#if 0
// interface_declaration ::=
//     interface_constant_declaration
//     | interface_signal_declaration
//     | interface_variable_declaration
//     | interface_file_declaration
auto const interface_declaration_def =
        interface_constant_declaration
    | interface_signal_declaration
    | interface_variable_declaration
    | interface_file_declaration

    ;
#endif

#if 0
// interface_element ::=
// interface_declaration
auto const interface_element_def =
    interface_declaration
    ;
#endif

#if 0
// interface_file_declaration ::=
//     file identifier_list : subtype_indication
auto const interface_file_declaration_def =
        file identifier_list char_(':') subtype_indication

    ;
#endif

#if 0
// interface_list ::=
//     interface_element { ; interface_element }
auto const interface_list_def =
        interface_element { char_(';') interface_element }

    ;
#endif

#if 0
// interface_signal_declaration ::=
//     [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]
auto const interface_signal_declaration_def =
        [signal] identifier_list char_(':') [ mode ] subtype_indication [ bus ] [ := static_expression ]

    ;
#endif

#if 0
// interface_variable_declaration ::=
//     [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]
auto const interface_variable_declaration_def =
        [variable] identifier_list char_(':') [ mode ] subtype_indication [ := static_expression ]

    ;
#endif

#if 0
// iteration_scheme ::=
//     while condition
//     | for loop_parameter_specification
auto const iteration_scheme_def =
        while condition
    | for loop_parameter_specification

    ;
#endif

#if 0
// label ::=
// identifier
auto const label_def =
    identifier
    ;
#endif

#if 0
// letter ::=
// upper_case_letter | lower_case_letter
auto const letter_def =
    upper_case_letter | lower_case_letter
    ;
#endif

#if 0
// letter_or_digit ::=
// letter | digit
auto const letter_or_digit_def =
    letter | digit
    ;
#endif

#if 0
// library_clause ::=
// library logical_name_list
auto const library_clause_def =
    library logical_name_list
    ;
#endif

#if 0
// library_unit ::=
//     primary_unit
//     | secondary_unit
auto const library_unit_def =
        primary_unit
    | secondary_unit

    ;
#endif

#if 0
// literal ::=
//     numeric_literal
//     | enumeration_literal
//     | string_literal
//     | bit_string_literal
//     | null
auto const literal_def =
        numeric_literal
    | enumeration_literal
    | string_literal
    | bit_string_literal
    | null

    ;
#endif

#if 0
// logical_name ::=
// identifier
auto const logical_name_def =
    identifier
    ;
#endif

#if 0
// logical_name_list ::=
// logical_name { , logical_name }
auto const logical_name_list_def =
    logical_name { char_(',') logical_name }
    ;
#endif

#if 0
// logical_operator ::=
// and | or | nand | nor | xor | xnor
auto const logical_operator_def =
    and | or | nand | nor | xor | xnor
    ;
#endif

#if 0
// loop_statement ::=
//     [ loop_label : ]
//     [ iteration_scheme ] loop
//     sequence_of_statements
//     end loop [ loop_label ]
auto const loop_statement_def =
        [ loop_label char_(':') ]
    [ iteration_scheme ] loop
    sequence_of_statements
    end loop [ loop_label ]

    ;
#endif

#if 0
// miscellaneous_operator ::=
// ** | abs | not
auto const miscellaneous_operator_def =
    ** | abs | not
    ;
#endif

#if 0
// mode ::=
// in | out | inout | buffer | linkage
auto const mode_def =
    in | out | inout | buffer | linkage
    ;
#endif

#if 0
// multiplying_operator ::=
// * | / | mod | rem
auto const multiplying_operator_def =
    * | / | mod | rem
    ;
#endif

#if 0
// name ::=
//     simple_name
//     | operator_symbol
//     | selected_name
//     | indexed_name
//     | slice_name
//     | attribute_name
auto const name_def =
        simple_name
    | operator_symbol
    | selected_name
    | indexed_name
    | slice_name
    | attribute_name

    ;
#endif

#if 0
// next_statement ::=
//     [ label : ] next [ loop_label ] [ when condition ]
auto const next_statement_def =
        [ label char_(':') ] next [ loop_label ] [ when condition ]

    ;
#endif

#if 0
// null_statement ::=
// [ label : ] null
auto const null_statement_def =
    [ label char_(':') ] null
    ;
#endif

#if 0
// numeric_literal ::=
//     abstract_literal
//     | physical_literal
auto const numeric_literal_def =
        abstract_literal
    | physical_literal

    ;
#endif

#if 0
// object_declaration ::=
//     constant_declaration
//     | signal_declaration
//     | variable_declaration
//     | file_declaration
auto const object_declaration_def =
        constant_declaration
    | signal_declaration
    | variable_declaration
    | file_declaration

    ;
#endif

#if 0
// operator_symbol ::=
// string_literal
auto const operator_symbol_def =
    string_literal
    ;
#endif

#if 0
// options ::=
// [ guarded ] [ delay_mechanism ]
auto const options_def =
    [ guarded ] [ delay_mechanism ]
    ;
#endif

#if 0
// package_body ::=
//     package body package_simple_name is
//     package_body_declarative_part
//     end [ package body ] [ package_simple_name ]
auto const package_body_def =
        package body package_simple_name is
    package_body_declarative_part
    end [ package body ] [ package_simple_name ]

    ;
#endif

#if 0
// package_body_declarative_item ::=
//     subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const package_body_declarative_item_def =
        subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// package_body_declarative_part ::=
//     { package_body_declarative_item }
auto const package_body_declarative_part_def =
        { package_body_declarative_item }

    ;
#endif

#if 0
// package_declaration ::=
//     package identifier is
//     package_declarative_part
//     end [ package ] [ package_simple_name ]
auto const package_declaration_def =
        package identifier is
    package_declarative_part
    end [ package ] [ package_simple_name ]

    ;
#endif

#if 0
// package_declarative_item ::=
//     subprogram_declaration
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | component_declaration
//     | attribute_declaration
//     | attribute_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const package_declarative_item_def =
        subprogram_declaration
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | component_declaration
    | attribute_declaration
    | attribute_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// package_declarative_part ::=
//     { package_declarative_item }
auto const package_declarative_part_def =
        { package_declarative_item }

    ;
#endif

#if 0
// parameter_specification ::=
//     identifier in discrete_range
auto const parameter_specification_def =
        identifier in discrete_range

    ;
#endif

#if 0
// physical_literal ::=
// [ abstract_literal ] unit_name
auto const physical_literal_def =
    [ abstract_literal ] unit_name
    ;
#endif

#if 0
// physical_type_definition ::=
//     range_constraint
//     units
//     base_unit_declaration
//     { secondary_unit_declaration }
//     end units [ physical_type_simple_name ]
auto const physical_type_definition_def =
        range_constraint
    units
    base_unit_declaration
    { secondary_unit_declaration }
    end units [ physical_type_simple_name ]

    ;
#endif

#if 0
// port_clause ::=
//     port ( port_list )
auto const port_clause_def =
        port ( port_list )

    ;
#endif

#if 0
// port_list ::=
// port_interface_list
auto const port_list_def =
    port_interface_list
    ;
#endif

#if 0
// port_map_aspect ::=
//     port map ( port_association_list )
auto const port_map_aspect_def =
        port map ( port_association_list )

    ;
#endif

#if 0
// prefix ::=
//     name
//     | function_call
auto const prefix_def =
        name
    | function_call

    ;
#endif

#if 0
// primary ::=
//     name
//     | literal
//     | aggregate
//     | function_call
//     | qualified_expression
//     | type_conversion
//     | allocator
//     | ( expression )
auto const primary_def =
        name
    | literal
    | aggregate
    | function_call
    | qualified_expression
    | type_conversion
    | allocator
    | ( expression )

    ;
#endif

#if 0
// primary_unit ::=
//     entity_declaration
//     | configuration_declaration
//     | package_declaration
auto const primary_unit_def =
        entity_declaration
    | configuration_declaration
    | package_declaration

    ;
#endif

#if 0
// procedure_call ::=
// procedure_name [ ( actual_parameter_part ) ]
auto const procedure_call_def =
    procedure_name [ ( actual_parameter_part ) ]
    ;
#endif

#if 0
// procedure_call_statement ::=
//     [ label : ] procedure_call
auto const procedure_call_statement_def =
        [ label char_(':') ] procedure_call

    ;
#endif

#if 0
// process_declarative_item ::=
//     subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const process_declarative_item_def =
        subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// process_declarative_part ::=
//     { process_declarative_item }
auto const process_declarative_part_def =
        { process_declarative_item }

    ;
#endif

#if 0
// process_statement ::=
//     [ process_label : ]
//     [ postponed ] process [ ( sensitivity_list ) ] [ is ]
//     process_declarative_part
//     begin
//     process_statement_part
//     end [ postponed ] process [ process_label ]
auto const process_statement_def =
        [ process_label char_(':') ]
    [ postponed ] process [ ( sensitivity_list ) ] [ is ]
    process_declarative_part
    begin
    process_statement_part
    end [ postponed ] process [ process_label ]

    ;
#endif

#if 0
// process_statement_part ::=
//     { sequential_statement }
auto const process_statement_part_def =
        { sequential_statement }

    ;
#endif

#if 0
// qualified_expression ::=
//     type_mark ' ( expression )
//     | type_mark ' aggregate
auto const qualified_expression_def =
        type_mark char_('\'') ( expression )
    | type_mark char_('\'') aggregate

    ;
#endif

#if 0
// range ::=
//     range_attribute_name
//     | simple_expression direction simple_expression
auto const range_def =
        range_attribute_name
    | simple_expression direction simple_expression

    ;
#endif

#if 0
// range_constraint ::=
// range range
auto const range_constraint_def =
    range range
    ;
#endif

#if 0
// record_type_definition ::=
//     record
//     element_declaration
//     { element_declaration }
//     end record [ record_type_simple_name ]
auto const record_type_definition_def =
        record
    element_declaration
    { element_declaration }
    end record [ record_type_simple_name ]

    ;
#endif

#if 0
// relation ::=
//     shift_expression [ relational_operator shift_expression ]
auto const relation_def =
        shift_expression [ relational_operator shift_expression ]

    ;
#endif

#if 0
// relational_operator ::=
// =  |    /=  |  <  |  <=     |  >  |  >=
auto const relational_operator_def =
    =  |    /=  |  <  |  lit("<=")     |  >  |  >=
    ;
#endif

#if 0
// report_statement ::=
//     [ label : ]
//     report expression
//     [ severity expression ]
auto const report_statement_def =
        [ label char_(':') ]
    report expression
    [ severity expression ]

    ;
#endif

#if 0
// return_statement ::=
//     [ label : ] return [ expression ]
auto const return_statement_def =
        [ label char_(':') ] return [ expression ]

    ;
#endif

#if 0
// scalar_type_definition ::=
//     enumeration_type_definition   | integer_type_definition
//     | floating_type_definition      | physical_type_definition
auto const scalar_type_definition_def =
        enumeration_type_definition   | integer_type_definition
    | floating_type_definition      | physical_type_definition

    ;
#endif

#if 0
// secondary_unit ::=
//     architecture_body
//     | package_body
auto const secondary_unit_def =
        architecture_body
    | package_body

    ;
#endif

#if 0
// secondary_unit_declaration ::=
// identifier = physical_literal
auto const secondary_unit_declaration_def =
    identifier = physical_literal
    ;
#endif

#if 0
// selected_name ::=
// prefix . suffix
auto const selected_name_def =
    prefix char_('.') suffix
    ;
#endif

#if 0
// selected_signal_assignment ::=
//     with expression select
//     target    <= options selected_waveforms
auto const selected_signal_assignment_def =
        with expression select
    target    lit("<=") options selected_waveforms

    ;
#endif

#if 0
// selected_waveforms ::=
//     { waveform when choices , }
//     waveform when choices
auto const selected_waveforms_def =
        { waveform when choices char_(',') }
    waveform when choices

    ;
#endif

#if 0
// sensitivity_clause ::=
// on sensitivity_list
auto const sensitivity_clause_def =
    on sensitivity_list
    ;
#endif

#if 0
// sensitivity_list ::=
// signal_name { , signal_name }
auto const sensitivity_list_def =
    signal_name { char_(',') signal_name }
    ;
#endif

#if 0
// sequence_of_statements ::=
//     { sequential_statement }
auto const sequence_of_statements_def =
        { sequential_statement }

    ;
#endif

#if 0
// sequential_statement ::=
//     wait_statement
//     | assertion_statement
//     | report_statement
//     | signal_assignment_statement
//     | variable_assignment_statement
//     | procedure_call_statement
//     | if_statement
//     | case_statement
//     | loop_statement
//     | next_statement
//     | exit_statement
//     | return_statement
//     | null_statement
auto const sequential_statement_def =
        wait_statement
    | assertion_statement
    | report_statement
    | signal_assignment_statement
    | variable_assignment_statement
    | procedure_call_statement
    | if_statement
    | case_statement
    | loop_statement
    | next_statement
    | exit_statement
    | return_statement
    | null_statement

    ;
#endif

#if 0
// shift_expression ::=
//     simple_expression [ shift_operator simple_expression ]
auto const shift_expression_def =
        simple_expression [ shift_operator simple_expression ]

    ;
#endif

#if 0
// shift_operator ::=
// sll | srl | sla | sra | rol | ror
auto const shift_operator_def =
    sll | srl | sla | sra | rol | ror
    ;
#endif

#if 0
// sign ::=
// + | -
auto const sign_def =
    + | -
    ;
#endif

#if 0
// signal_assignment_statement ::=
//     [ label : ] target <= [ delay_mechanism ] waveform
auto const signal_assignment_statement_def =
        [ label char_(':') ] target lit("<=") [ delay_mechanism ] waveform

    ;
#endif

#if 0
// signal_declaration ::=
//     signal identifier_list : subtype_indication [ signal_kind ] [ := expression ]
auto const signal_declaration_def =
        signal identifier_list char_(':') subtype_indication [ signal_kind ] [ := expression ]

    ;
#endif

#if 0
// signal_kind ::=
// register  |  bus
auto const signal_kind_def =
    register  |  bus
    ;
#endif

#if 0
// signal_list ::=
//     signal_name { , signal_name }
//     | others
//     | all
auto const signal_list_def =
        signal_name { char_(',') signal_name }
    | others
    | all

    ;
#endif

#if 0
// signature ::=
// [ [ type_mark { , type_mark } ] [ return type_mark ] ]
auto const signature_def =
    [ [ type_mark { char_(',') type_mark } ] [ return type_mark ] ]
    ;
#endif

#if 0
// simple_expression ::=
//     [ sign ] term { adding_operator term }
auto const simple_expression_def =
        [ sign ] term { adding_operator term }

    ;
#endif

#if 0
// simple_name ::=
// identifier
auto const simple_name_def =
    identifier
    ;
#endif

#if 0
// slice_name ::=
// prefix ( discrete_range )
auto const slice_name_def =
    prefix ( discrete_range )
    ;
#endif

#if 1
// string_literal ::=
// " { graphic_character } "
auto const string_literal_def =
	'"' > *graph > '"'
    ;
#endif

#if 0
// subprogram_body ::=
//     subprogram_specification is
//     subprogram_declarative_part
//     begin
//     subprogram_statement_part
//     end [ subprogram_kind ] [ designator ]
auto const subprogram_body_def =
        subprogram_specification is
    subprogram_declarative_part
    begin
    subprogram_statement_part
    end [ subprogram_kind ] [ designator ]

    ;
#endif

#if 0
// subprogram_declaration ::=
//     subprogram_specification
auto const subprogram_declaration_def =
        subprogram_specification

    ;
#endif

#if 0
// subprogram_declarative_item ::=
//     subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const subprogram_declarative_item_def =
        subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | use_clause
    | group_template_declaration
    | group_declaration

    ;
#endif

#if 0
// subprogram_declarative_part ::=
//     { subprogram_declarative_item }
auto const subprogram_declarative_part_def =
        { subprogram_declarative_item }

    ;
#endif

#if 0
// subprogram_kind ::=
// procedure | function
auto const subprogram_kind_def =
    procedure | function
    ;
#endif

#if 0
// subprogram_specification ::=
//     procedure designator [ ( formal_parameter_list ) ]
//     | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
//     return type_mark
auto const subprogram_specification_def =
        procedure designator [ ( formal_parameter_list ) ]
    | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
    return type_mark

    ;
#endif

#if 0
// subprogram_statement_part ::=
//     { sequential_statement }
auto const subprogram_statement_part_def =
        { sequential_statement }

    ;
#endif

#if 0
// subtype_declaration ::=
//     subtype identifier is subtype_indication
auto const subtype_declaration_def =
        subtype identifier is subtype_indication

    ;
#endif

#if 0
// subtype_indication ::=
//     [ resolution_function_name ] type_mark [ constraint ]
auto const subtype_indication_def =
        [ resolution_function_name ] type_mark [ constraint ]

    ;
#endif

#if 0
// suffix ::=
//     simple_name
//     | character_literal
//     | operator_symbol
//     | all
auto const suffix_def =
        simple_name
    | character_literal
    | operator_symbol
    | all

    ;
#endif

#if 0
// target ::=
//     name
//     | aggregate
auto const target_def =
        name
    | aggregate

    ;
#endif

#if 0
// term ::=
//     factor { multiplying_operator factor }
auto const term_def =
        factor { multiplying_operator factor }

    ;
#endif

#if 0
// timeout_clause ::=
// for time_expression
auto const timeout_clause_def =
    for time_expression
    ;
#endif

#if 0
// type_conversion ::=
// type_mark ( expression )
auto const type_conversion_def =
    type_mark ( expression )
    ;
#endif

#if 0
// type_declaration ::=
//     full_type_declaration
//     | incomplete_type_declaration
auto const type_declaration_def =
        full_type_declaration
    | incomplete_type_declaration

    ;
#endif

#if 0
// type_definition ::=
//     scalar_type_definition
//     | composite_type_definition
//     | access_type_definition
//     | file_type_definition
auto const type_definition_def =
        scalar_type_definition
    | composite_type_definition
    | access_type_definition
    | file_type_definition

    ;
#endif

#if 0
// type_mark ::=
//     type_name
//     | subtype_name
auto const type_mark_def =
        type_name
    | subtype_name

    ;
#endif

#if 0
// unconstrained_array_definition ::=
//     array ( index_subtype_definition { , index_subtype_definition } )
//     of element_subtype_indication
auto const unconstrained_array_definition_def =
        array ( index_subtype_definition { char_(',') index_subtype_definition } )
    of element_subtype_indication

    ;
#endif

#if 0
// use_clause ::=
//     use selected_name { , selected_name }
auto const use_clause_def =
        use selected_name { char_(',') selected_name }

    ;
#endif

#if 0
// variable_assignment_statement ::=
//     [ label : ] target  := expression
auto const variable_assignment_statement_def =
        [ label char_(':') ] target  := expression

    ;
#endif

#if 0
// variable_declaration ::=
//     [ shared ] variable identifier_list : subtype_indication [ := expression ]
auto const variable_declaration_def =
        [ shared ] variable identifier_list char_(':') subtype_indication [ := expression ]

    ;
#endif

#if 0
// wait_statement ::=
//     [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ]
auto const wait_statement_def =
        [ label char_(':') ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ]

    ;
#endif

#if 0
// waveform ::=
//     waveform_element { , waveform_element }
//     | unaffected
auto const waveform_def =
        waveform_element { char_(',') waveform_element }
    | unaffected

    ;
#else
    auto const waveform_def = *x3::char_;
#endif

    // Utilities
    auto const skipper =
    	  x3::space
		| "--" >> *(char_ - x3::eol)// required??? >> x3::eol
		;


    BOOST_SPIRIT_DEFINE(
        //    abstract_literal,
        //    access_type_definition,
        //    actual_designator,
        //    actual_parameter_part,
        //    actual_part,
        //    adding_operator,
        //    aggregate,
        //    alias_declaration,
        //    alias_designator,
        //    allocator,
        //    architecture_body,
        //    architecture_declarative_part,
        //    architecture_statement_part,
        //    array_type_definition,
        //    assertion,
        //    assertion_statement,
        //    association_element,
        //    association_list,
        //    attribute_declaration,
        //    attribute_designator,
        //    attribute_name,
        //    attribute_specification,
        //    base,
        //    base_specifier,
        //    base_unit_declaration,
        //    based_integer,
        //    based_literal,
        //    basic_character,
        //    basic_graphic_character,
        //    basic_identifier,
        //    binding_indication,
        //    bit_string_literal,
        //    bit_value,
        //    block_configuration,
        //    block_declarative_item,
        //    block_declarative_part,
        //    block_header,
        //    block_specification,
        //    block_statement,
        //    block_statement_part,
        //    case_statement,
        //    case_statement_alternative,
        //    character_literal,
        //    choice,
        //    choices,
        //    component_configuration,
        //    component_declaration,
        //    component_instantiation_statement,
        //    component_specification,
        //    composite_type_definition,
        //    concurrent_assertion_statement,
        //    concurrent_procedure_call_statement,
        //    concurrent_signal_assignment_statement,
        //    concurrent_statement,
        //    condition,
        //    condition_clause,
        //    conditional_signal_assignment,
        //    conditional_waveforms,
        //    configuration_declaration,
        //    configuration_declarative_item,
        //    configuration_declarative_part,
        //    configuration_item,
        //    configuration_specification,
        //    constant_declaration,
        //    constrained_array_definition,
        //    constraint,
        //    context_clause,
        //    context_item,
        //    decimal_literal,
        //    declaration,
        //    delay_mechanism,
        //    design_file,
        //    design_unit,
        //    designator,
        //    direction,
        //    disconnection_specification,
        //    discrete_range,
        //    element_association,
        //    element_declaration,
        //    element_subtype_definition,
        //    entity_aspect,
        //    entity_class,
        //    entity_class_entry,
        //    entity_class_entry_list,
        //    entity_declaration,
        //    entity_declarative_item,
        //    entity_declarative_part,
        //    entity_designator,
        //    entity_header,
        //    entity_name_list,
        //    entity_specification,
        //    entity_statement,
        //    entity_statement_part,
        //    entity_tag,
        //    enumeration_literal,
        //    enumeration_type_definition,
        //    exit_statement,
        //    exponent,
        //    expression,
        //    extended_digit,
        //    extended_identifier,
        //    factor,
        //    file_declaration,
        //    file_logical_name,
        //    file_open_information,
        //    file_type_definition,
        //    formal_designator,
        //    formal_parameter_list,
        //    formal_part,
        //    full_type_declaration,
        //    function_call,
        //    generate_statement,
        //    generation_scheme,
        //    generic_clause,
        //    generic_list,
        //    generic_map_aspect,
        //    graphic_character,
        //    group_constituent,
        //    group_constituent_list,
        //    group_template_declaration,
        //    group_declaration,
        //    guarded_signal_specification,
        //    identifier,
        //    identifier_list,
        //    if_statement,
        //    incomplete_type_declaration,
        //    index_constraint,
        //    index_specification,
        //    index_subtype_definition,
        //    indexed_name,
        //    instantiated_unit,
        //    instantiation_list,
        //    integer,
        //    integer_type_definition,
        //    interface_constant_declaration,
        //    interface_declaration,
        //    interface_element,
        //    interface_file_declaration,
        //    interface_list,
        //    interface_signal_declaration,
        //    interface_variable_declaration,
        //    iteration_scheme,
        //    label,
        //    letter,
        //    letter_or_digit,
        //    library_clause,
        //    library_unit,
        //    literal,
        //    logical_name,
        //    logical_name_list,
        //    logical_operator,
        //    loop_statement,
        //    miscellaneous_operator,
        //    mode,
        //    multiplying_operator,
        //    name,
        //    next_statement,
        //    null_statement,
        //    numeric_literal,
        //    object_declaration,
        //    operator_symbol,
        //    options,
        //    package_body,
        //    package_body_declarative_item,
        //    package_body_declarative_part,
        //    package_declaration,
        //    package_declarative_item,
        //    package_declarative_part,
        //    parameter_specification,
        //    physical_literal,
        //    physical_type_definition,
        //    port_clause,
        //    port_list,
        //    port_map_aspect,
        //    prefix,
        //    primary,
        //    primary_unit,
        //    procedure_call,
        //    procedure_call_statement,
        //    process_declarative_item,
        //    process_declarative_part,
        //    process_statement,
        //    process_statement_part,
        //    qualified_expression,
        //    range,
        //    range_constraint,
        //    record_type_definition,
        //    relation,
        //    relational_operator,
        //    report_statement,
        //    return_statement,
        //    scalar_type_definition,
        //    secondary_unit,
        //    secondary_unit_declaration,
        //    selected_name,
        //    selected_signal_assignment,
        //    selected_waveforms,
        //    sensitivity_clause,
        //    sensitivity_list,
        //    sequence_of_statements,
        //    sequential_statement,
        //    shift_expression,
        //    shift_operator,
        //    sign,
        //    signal_assignment_statement,
        //    signal_declaration,
        //    signal_kind,
        //    signal_list,
        //    signature,
        //    simple_expression,
        //    simple_name,
        //    slice_name,
    		string_literal,
        //    subprogram_body,
        //    subprogram_declaration,
        //    subprogram_declarative_item,
        //    subprogram_declarative_part,
        //    subprogram_kind,
        //    subprogram_specification,
        //    subprogram_statement_part,
        //    subtype_declaration,
        //    subtype_indication,
        //    suffix,
        //    target,
        //    term,
        //    timeout_clause,
        //    type_conversion,
        //    type_declaration,
        //    type_definition,
        //    type_mark,
        //    unconstrained_array_definition,
        //    use_clause,
        //    variable_assignment_statement,
        //    variable_declaration,
        //    wait_statement,
    		waveform
        );

} } } // namespace eda.vhdl93.parser


#endif /* INCLUDE_EDA_VHDL93_GRAMMAR_DEF_HPP_ */
