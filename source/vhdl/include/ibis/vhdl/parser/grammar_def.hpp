//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/grammar.hpp>
#include <ibis/vhdl/parser/grammar_id.hpp>
#include <ibis/vhdl/parser/grammar_type.hpp>

#include <ibis/vhdl/parser/error_handler.hpp>
#include <ibis/vhdl/parser/success_handler.hpp>

#include <ibis/vhdl/ast/ast_adapted.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/spirit/home/x3.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <ibis/vhdl/parser/spirit_x3_util.hpp>

#include <range/v3/view/filter.hpp>

namespace ibis::vhdl::parser::detail {

///
/// distinct parser directive allowing to avoid partial matches while parsing
/// using a skipper.
///
/// @note This is a problem specific helper function (due to VHDL's character set
/// use here), so it isn't placed into `spirit_x3_util.hpp` file.
///
struct distinct_directive {
    ///
    /// Attributeless overload.
    ///
    /// @param parser The core parser to be used.
    /// @return The combined parser base on given argument
    ///
    template <typename Parser>
    constexpr auto operator()(Parser&& parser) const
    {
        // clang-format off
        return x3::lexeme[
                   x3::no_case[ std::forward<Parser>(parser) ]
                >> !(x3::iso8859_1::alnum | '_')
            ];
        // clang-format on
    }

    ///
    /// Overload for literals, like keywords
    ///
    /// @param keyword_str The keyword.
    /// @return The distinct rule.
    ///
    constexpr auto operator()(char const* keyword_str) const
    {
        // clang-format off
        return x3::rule<struct _, x3::unused_type>{ keyword_str } = //this->operator()(keyword_str);
            x3::lexeme[
                    x3::no_case[ x3::lit(keyword_str) ]
                >> !(x3::iso8859_1::alnum | '_')
            ];
        // clang-format on
    }

    ///
    /// Overload to use with attributes
    ///
    /// @param keyword_str The keyword.
    /// @param attr The attribute to be exposed.
    /// @return The combined parser based on given argument.
    ///
    template <typename Attr>
    constexpr auto operator()(char const* keyword_str, Attr&& attr) const

    {
        return this->operator()(keyword_str) >> x3::attr(std::forward<Attr>(attr));
    }
};

const distinct_directive distinct = {};

///
/// Literal parser with attribute.
///
/// Expose an attribute from given literal.
///
/// \note There is no overload without attribute since it would decay to
/// x3::lit() parser self.
///
struct literal_attribute {
    ///
    ///
    /// @param str The string literal.
    /// @param attr The Attribute to be exposed.
    /// @return The combined parser based on given argument
    ///
    template <typename StrT, typename AttrT>
    constexpr auto operator()(StrT&& str, AttrT&& attr) const
    {
        // clang-format off
        return
               x3::lit(std::forward<StrT>(str))
            >> x3::attr(std::forward<AttrT>(attr))
            ;
        // clang-format on
    }
};

const literal_attribute literal = {};

}  // namespace ibis::vhdl::parser::detail

//******************************************************************************
// Keywords
//
namespace ibis::vhdl::parser::keywords {

using detail::distinct;

auto const ACCESS = distinct("access");
auto const AFTER = distinct("after");
auto const ALIAS = distinct("alias");
auto const ALL = distinct("all", ast::keyword_token::ALL);
auto const ARCHITECTURE = distinct("architecture");
auto const ARRAY = distinct("array");
auto const ASSERT = distinct("assert");
auto const ATTRIBUTE = distinct("attribute");
auto const BEGIN = distinct("begin");
auto const BLOCK = distinct("block");
auto const BODY = distinct("body");
auto const BUS = distinct("bus", ast::keyword_token::BUS);
auto const CASE = distinct("case");
auto const COMPONENT = distinct("component");
auto const CONFIGURATION = distinct("configuration");
auto const CONSTANT = distinct("constant", ast::keyword_token::CONSTANT);
auto const DISCONNECT = distinct("disconnect");
auto const DOWNTO = distinct("downto", ast::keyword_token::DOWNTO);
auto const ELSE = distinct("else");
auto const ELSIF = distinct("elsif");
auto const END = distinct("end");
auto const ENTITY = distinct("entity");
auto const EXIT = distinct("exit");
auto const FILE = distinct("file");
auto const FOR = distinct("for");
auto const FUNCTION = distinct("function");
auto const GENERATE = distinct("generate");
auto const GENERIC = distinct("generic");
auto const GROUP = distinct("group");
auto const GUARDED = distinct("guarded", ast::keyword_token::GUARDED);
auto const IF = distinct("if");
auto const IMPURE = distinct("impure", ast::keyword_token::IMPURE);
auto const IN = distinct("in", ast::keyword_token::IN);
auto const INERTIAL = distinct("inertial", ast::keyword_token::INERTIAL);
auto const IS = distinct("is");
auto const LABEL = distinct("label");
auto const LIBRARY = distinct("library");
auto const LITERAL = distinct("literal", ast::keyword_token::LITERAL);
auto const LOOP = distinct("loop");
auto const MAP = distinct("map");
auto const NEW = distinct("new");
auto const NEXT = distinct("next");
auto const NULL_ = distinct("null", ast::keyword_token::NULL_);
auto const OF = distinct("of");
auto const ON = distinct("on");
auto const OPEN = distinct("open", ast::keyword_token::OPEN);
auto const OTHERS = distinct("others", ast::keyword_token::OTHERS);
auto const PACKAGE = distinct("package");
auto const PORT = distinct("port");
auto const POSTPONED = distinct("postponed", ast::keyword_token::POSTPONED);
auto const PROCEDURE = distinct("procedure");
auto const PROCESS = distinct("process");
auto const PURE = distinct("pure", ast::keyword_token::PURE);
auto const RANGE = distinct("range");
auto const RECORD = distinct("record");
auto const REGISTER = distinct("register", ast::keyword_token::REGISTER);
auto const REJECT = distinct("reject");
auto const REPORT = distinct("report");
auto const RETURN = distinct("return");
auto const SELECT = distinct("select");
auto const SEVERITY = distinct("severity");
auto const SIGNAL = distinct("signal", ast::keyword_token::SIGNAL);
auto const SHARED = distinct("shared", ast::keyword_token::SHARED);
auto const SUBTYPE = distinct("subtype");
auto const THEN = distinct("then");
auto const TO = distinct("to", ast::keyword_token::TO);
auto const TRANSPORT = distinct("transport", ast::keyword_token::TRANSPORT);
auto const TYPE = distinct("type");
auto const UNAFFECTED = distinct("unaffected", ast::keyword_token::UNAFFECTED);
auto const UNITS = distinct("units");
auto const UNTIL = distinct("until");
auto const USE = distinct("use");
auto const VARIABLE = distinct("variable", ast::keyword_token::VARIABLE);
auto const WAIT = distinct("wait");
auto const WHEN = distinct("when");
auto const WHILE = distinct("while");
auto const WITH = distinct("with");

//
// Symbols of all keyword to them distinguish from identifier by rule
//
x3::symbols<> const keywords(
    // clang-format off
    {
      "abs",          "access",     "after",      "alias",     "all",       "and",
      "architecture", "array",      "assert",     "attribute", "begin",     "block",
      "body",         "buffer",     "bus",        "case",      "component", "configuration",
      "constant",     "disconnect", "downto",     "else",      "elsif",     "end",
      "entity",       "exit",       "file",       "for",       "function",  "generate",
      "generic",      "group",      "guarded",    "if",        "impure",    "in",
      "inertial",     "inout",      "is",         "label",     "library",   "linkage",
      "literal",      "loop",       "map",        "mod",       "nand",      "new",
      "next",         "nor",        "not",        "null",      "of",        "on",
      "open",         "or",         "others",     "out",       "package",   "port",
      "postponed",    "procedure",  "process",    "pure",      "range",     "record",
      "register",     "reject",     "rem",        "report",    "return",    "rol",
      "ror",          "select",     "severity",   "signal",    "shared",    "sla",
      "sll",          "sra",        "srl",        "subtype",   "then",      "to",
      "transport",    "type",       "unaffected", "units",     "until",     "use",
      "variable",     "wait",       "when",       "while",     "with",      "xnor",
      "xor"
    },
    "keyword"
    // clang-format on
);

auto const keyword = x3::rule<struct _>{ "keyword" } = distinct(keywords);

}  // namespace ibis::vhdl::parser::keywords

//******************************************************************************
// Operators
//
namespace ibis::vhdl::parser::operators {

//
// Operator Rule IDs
//
struct binary_logical_operator_class;
struct unary_logical_operator_class;
struct binary_miscellaneous_operator_class;
struct unary_miscellaneous_operator_class;
struct multiplying_operator_class;
struct shift_operator_class;

//
// Rule Types
//
// clang-format off
using binary_logical_operator_type = x3::rule<binary_logical_operator_class, ast::operator_token>;
using unary_logical_operator_type = x3::rule<unary_logical_operator_class, ast::operator_token>;
using binary_miscellaneous_operator_type = x3::rule<binary_miscellaneous_operator_class, ast::operator_token>;
using unary_miscellaneous_operator_type = x3::rule<unary_miscellaneous_operator_class, ast::operator_token>;
using multiplying_operator_type = x3::rule<multiplying_operator_class, ast::operator_token>;
using shift_operator_type = x3::rule<shift_operator_class, ast::operator_token>;
using relational_operator_type = x3::symbols<ast::operator_token>;
using adding_operator_type = x3::symbols<ast::operator_token>;
// clang-format on

//
// Rule Instances
//
// clang-format off
binary_logical_operator_type const binary_logical_operator{ "logical_operator" };
unary_logical_operator_type const unary_logical_operator{ "logical_operator" };
binary_miscellaneous_operator_type const binary_miscellaneous_operator{ "miscellaneous_operator" };
unary_miscellaneous_operator_type const unary_miscellaneous_operator{ "miscellaneous_operator" };
multiplying_operator_type const multiplying_operator{ "multiplying_operator" };
shift_operator_type const shift_operator{ "shift_operator" };
// clang-format on

//
// Rule Definitions
//
using detail::distinct;
using detail::literal;

/// miscellaneous_operator ::=  ** | abs | not                      [LRM93 §7.2]
auto const EXPONENT = literal("**", ast::operator_token::EXPONENT);

// clang-format off
auto const binary_miscellaneous_operator_def =
    EXPONENT
    ;
// clang-format on

auto const ABS = distinct("abs", ast::operator_token::ABS);
auto const NOT = distinct("not", ast::operator_token::NOT);

// clang-format off
auto const unary_miscellaneous_operator_def =
    ABS | NOT
    ;
// clang-format on

/// logical_operator ::=  and | or | nand | nor | xor | xnor        [LRM93 §7.2]
x3::symbols<ast::operator_token> const binary_logical_operator_symbols(
    // clang-format off
    {
        { "and",  ast::operator_token::AND },
        { "or",   ast::operator_token::OR },
        { "xor",  ast::operator_token::XOR },
        { "xnor", ast::operator_token::XNOR }
    },
    "logical_operator"
    // clang-format on
);

auto const binary_logical_operator_def = distinct(binary_logical_operator_symbols);

auto const NAND = distinct("nand", ast::operator_token::NAND);
auto const NOR = distinct("nor", ast::operator_token::NOR);

// clang-format off
auto const unary_logical_operator_def =
    NAND | NOR
    ;
// clang-format on

/// relational_operator ::=   =  |  /=  |  <  |  <=  |  >  |  >=    [LRM93 §7.2]
x3::symbols<ast::operator_token> const relational_operator(
    // clang-format off
    {
        { "=",  ast::operator_token::EQUAL },
        { "/=", ast::operator_token::NOT_EQUALS },
        { "<",  ast::operator_token::LESS },
        { "<=", ast::operator_token::LESS_EQUALS },
        { ">",  ast::operator_token::GREATER },
        { ">=", ast::operator_token::GREATER_EQUALS }
    },
    "relational_operator"
    // clang-format on
);

/// adding_operator ::=  + | -  | &                                 [LRM93 §7.2]
x3::symbols<ast::operator_token> const adding_operator(
    // clang-format off
    {
        { "+", ast::operator_token::ADD },
        { "-", ast::operator_token::SUB },
        { "&", ast::operator_token::CONCAT }
    },
    "adding_operator"
    // clang-format on
);

/// multiplying_operator ::=  * | / | mod | rem                     [LRM93 §7.2]

auto const MUL = literal("*", ast::operator_token::MUL);
auto const DIV = literal("/", ast::operator_token::DIV);
auto const MOD = distinct("mod", ast::operator_token::MOD);
auto const REM = distinct("rem", ast::operator_token::REM);

// clang-format off
auto const multiplying_operator_def =
    MUL | DIV | MOD | REM
    ;
// clang-format on

/// shift_operator ::=  sll | srl | sla | sra | rol | ror           [LRM93 §7.2]
x3::symbols<ast::operator_token> const shift_operator_symbols(
    // clang-format off
    {
        { "sll", ast::operator_token::SLL },
        { "srl", ast::operator_token::SRL },
        { "sla", ast::operator_token::SLA },
        { "sra", ast::operator_token::SRA },
        { "rol", ast::operator_token::ROL },
        { "ror", ast::operator_token::ROR }
    },
    "shift_operator"
    // clang-format on
);

auto const shift_operator_def = distinct(shift_operator_symbols);

// special boost.spirit.x3 header to get rid off the annoying unused parameter
// warnings from x3
#include <ibis/util/compiler/warnings_off.hpp>

// clang-format off
BOOST_SPIRIT_DEFINE(
    binary_logical_operator,
    unary_logical_operator,
    binary_miscellaneous_operator,
    unary_miscellaneous_operator,
    multiplying_operator,
    shift_operator
)
// clang-format on

#include <ibis/util/compiler/warnings_on.hpp>

}  // namespace ibis::vhdl::parser::operators

//******************************************************************************
// Rule Instances
//
namespace ibis::vhdl::parser {

// clang-format off
abstract_literal_type const abstract_literal { "abstract_literal" };
access_type_definition_type const access_type_definition { "access_type_definition" };
actual_designator_type const actual_designator { "actual_designator" };
actual_parameter_part_type const actual_parameter_part { "actual_parameter_part" };
actual_part_type const actual_part { "actual_part" };
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
//base_type const base { "base" };
based_integer_type const based_integer { "based_integer" };
based_literal_type const based_literal { "based_literal" };
basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };
basic_identifier_type const basic_identifier { "basic_identifier" };
binding_indication_type const binding_indication { "binding_indication" };
bit_string_literal_type const bit_string_literal { "bit_string_literal" };
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
extended_identifier_type const extended_identifier { "extended_identifier" };
factor_type const factor { "factor" };
file_declaration_type const file_declaration { "file_declaration" };
file_logical_name_type const file_logical_name { "file_logical_name" };
file_open_information_type const file_open_information { "file_open_information" };
file_type_definition_type const file_type_definition { "file_type_definition" };
// floating_type_definition_type const floating_type_definition { "floating_type_definition" };
formal_designator_type const formal_designator { "formal_designator" };
formal_parameter_list_type const formal_parameter_list { "formal_parameter_list" };
formal_part_type const formal_part { "formal_part" };
// full_type_declaration_type const full_type_declaration { "full_type_declaration" };
function_call_type const function_call { "function_call" };
generate_statement_type const generate_statement { "generate_statement" };
generation_scheme_type const generation_scheme { "generation_scheme" };
generic_clause_type const generic_clause { "generic_clause" };
// generic_list_type const generic_list { "generic_list" };
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
// incomplete_type_declaration_type const incomplete_type_declaration { "incomplete_type_declaration" };
index_constraint_type const index_constraint { "index_constraint" };
index_specification_type const index_specification { "index_specification" };
index_subtype_definition_type const index_subtype_definition { "index_subtype_definition" };
indexed_name_type const indexed_name { "indexed_name" };
instantiated_unit_type const instantiated_unit { "instantiated_unit" };
instantiation_list_type const instantiation_list { "instantiation_list" };
integer_type const integer { "integer" };
// integer_type_definition_type const integer_type_definition { "integer_type_definition" };
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
loop_statement_type const loop_statement { "loop_statement" };
mode_type const mode { "mode" };
name_type const name { "name" };
next_statement_type const next_statement { "next_statement" };
null_statement_type const null_statement { "null_statement" };
numeric_literal_type const numeric_literal { "numeric_literal" };
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
// port_list_type const port_list { "port_list" };
port_map_aspect_type const port_map_aspect { "port_map_aspect" };
prefix_type const prefix { "prefix" };
primary_type const primary { "primary" };
primary_unit_type const primary_unit { "primary_unit" };
primary_unit_declaration_type const primary_unit_declaration { "primary_unit_declaration" };
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
waveform_element_type const waveform_element { "waveform_element" };
// clang-format on

}  // namespace ibis::vhdl::parser

//******************************************************************************
// Spirit.X3 BNF Rule Definitions
//
namespace ibis::vhdl::parser {

using namespace parser::keywords;

using operators::adding_operator;
using operators::binary_logical_operator;
using operators::binary_miscellaneous_operator;
using operators::multiplying_operator;
using operators::relational_operator;
using operators::shift_operator;
using operators::unary_logical_operator;
using operators::unary_miscellaneous_operator;

using iso8859_1::char_;
using iso8859_1::lit;
using x3::lexeme;
using x3::omit;
using x3::raw;

using detail::distinct;

//
// Character Sets                                                 [LRM93 §13.1]
//
// clang-format off
auto const upper_case_letter =
    x3::rule<struct upper_case_letter_class, char> { "upper_case_letter" } =
        char_("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ");
auto const lower_case_letter =
    x3::rule<struct lower_case_letter_class, char> { "lower_case_letter" } =
        char_("abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ");
auto const digit =
    x3::rule<struct digit_class, char> { "digit" } =
        char_("0-9");
auto const special_character =
    x3::rule<struct special_character_class, char> { "special_character" } =
        char_("\"#&'()*+,-./:;<=>[]_|");
auto const other_special_character =
    x3::rule<struct other_special_character_class, char> { "other_special_character" } =
        char_("!$%?@\\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷");

auto const space_character =
    x3::rule<struct space_character_class, char> { "space_character" } =
        iso8859_1::space;
auto const format_effector =
    x3::rule<struct format_effector_class> { "format_effector" } =
        char_("\t\n\v\r\f");
auto const end_of_line =
    x3::rule<struct end_of_line_class> { "end_of_line" } =
        x3::eol;
// clang-format on

#if 0
/// basic_character ::=
/// basic_graphic_character | format_effector
auto const basic_character_def =
        basic_graphic_character | format_effector
        ;
#endif

/// basic_graphic_character ::=                                    [LRM93 §13.1]
/// upper_case_letter | digit | special_character| space_character
// clang-format off
auto const basic_graphic_character_def =
      upper_case_letter
    | digit
    | special_character
    | space_character
    ;
// clang-format on

/// extended_digit ::=                                           [LRM93 §13.4.2]
/// digit | letter
// clang-format off
auto const extended_digit =
    x3::rule<struct _, char> { "extended_digit" } =
        char_("0-9a-fA-F");
// clang-format on

/// graphic_character ::=                                          [LRM93 §13.1]
/// basic_graphic_character | lower_case_letter | other_special_character
// clang-format off
auto const graphic_character_def =
      basic_graphic_character
    | lower_case_letter
    | other_special_character
    ;
// clang-format on

/// letter ::=                                                   [LRM93 §13.3.1]
/// upper_case_letter | lower_case_letter
// clang-format off
auto const letter_def =
    upper_case_letter | lower_case_letter
    ;
// clang-format on

/// letter_or_digit ::=                                          [LRM93 §13.3.1]
/// letter | digit
// clang-format off
auto const letter_or_digit_def =
    letter | digit
    ;
// clang-format on

//
// Common aliases used in BNF
//

/// Convenience rule for 'label :'
// clang-format off
auto const label_colon = x3::rule<struct _, ast::identifier>{ "label" } =
       label
    >> lexeme[ ':' >> !char_('=') ]  // exclude ":=" variable assignment
    ;
// clang-format on

///
/// abstract_literal                                               [LRM93 §13.4]
///
/// @code{.bnf}
/// abstract_literal ::=
///     decimal_literal | based_literal
/// @endcode
// clang-format off
auto const abstract_literal_def =
    // --- order matters ---
      based_literal
    | decimal_literal
    ;
// clang-format on

///
/// access_type_definition                                          [LRM93 §3.3]
///
/// @code{.bnf}
/// access_type_definition ::=
///     access subtype_indication
/// @endcode
// clang-format off
auto const access_type_definition_def =
       ACCESS
    >> subtype_indication
    ;
// clang-format on

///
/// actual_designator                                           [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// actual_designator ::=
///       expression
///     | signal_name
///     | variable_name
///     | file_name
///     | open
/// @endcode
///
/// @note Note, expression also matches the BNF rules:
///         - signal_name
///         - variable_name
///         - file_name
// clang-format off
auto const actual_designator_def =
      expression
    | OPEN
    ;
// clang-format on

///
/// actual_parameter_part                                         [LRM93 §7.3.3]
///
/// @code{.bnf}
/// actual_parameter_part ::=
///     parameter_association_list
/// @endcode
///
/// @todo actual_parameter_part is used only for function_call and
/// procedure_call_statement, but there are parse problem with these
/// to be solved!
///
/// @todo Maybe use of aggregate (procedure_call_statement) or selected_name (function_call)?
/// @code{.bnf}
/// function_call ::= function_name [ ( actual_parameter_part ) ]
/// procedure_call_statement ::= procedure_name [ ( actual_parameter_part ) ] ;
/// @endcode
auto const actual_parameter_part_def =
    // clang-format off
    association_list
    ;
// clang-format on

///
/// actual_part                                                 [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// actual_part ::=
///       actual_designator
///     | function_name ( actual_designator )
///     | type_mark ( actual_designator )
/// @endcode
///
/// @note name covers { function_name | type_mark } rules.
/// @note actual_designator is as of expression and hence {signal, ...}_name.
namespace detail {

// clang-format off
auto const actual_part_chunk = x3::rule<struct _, ast::actual_part_chunk>{ "actual_part" } =
    name >> '(' >> actual_designator >> ')'
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const actual_part_def =
    // --- order matters ---                              
      detail::actual_part_chunk
    | actual_designator
    ;
// clang-format on

/// aggregate ::=                                                 [LRM93 §7.3.2]
///     ( element_association { , element_association } )
// clang-format off
auto const aggregate_def =
    '(' >> (element_association % ',') >> ')'
    ;
// clang-format on

/// alias_declaration ::=                                         [LRM93 §4.3.3]
///     alias alias_designator [ : subtype_indication ] is name [ signature ] ;
// clang-format off
auto const alias_declaration_def =
       ALIAS
    >> alias_designator
    >> -( ':' >> subtype_indication )
    >> IS
    >> name
    >> -signature
    >> x3::expect[';']
    ;
// clang-format on

/// alias_designator ::=                                          [LRM93 §4.3.3]
///     identifier | character_literal | operator_symbol
// clang-format off
auto const alias_designator_def =
      identifier
    | character_literal
    | operator_symbol
    ;
// clang-format on

/// allocator ::=                                                 [LRM93 §7.3.6]
///       new subtype_indication
///     | new qualified_expression
// clang-format off
auto const allocator_def =
       NEW
    >> ( subtype_indication
       | qualified_expression
       )
    ;
// clang-format on

/// architecture_body ::=                                           [LRM93 §1.2]
///     architecture identifier of entity_name is
///         architecture_declarative_part
///     begin
///         architecture_statement_part
///     end [ architecture ] [ architecture_simple_name ] ;
// clang-format off
auto const architecture_body_def =
       ARCHITECTURE
    >> identifier
    >> OF
    >> name
    >> IS
    >> architecture_declarative_part
    >> BEGIN
    >> architecture_statement_part
    >> END
    >> -ARCHITECTURE
    >> -simple_name
    >> x3::expect[';']
    ;
// clang-format on

/// architecture_declarative_part ::=                               [LRM93 §1.2]
///     { block_declarative_item }
auto const architecture_declarative_part_def =
    // clang-format off
    *block_declarative_item
    ;
// clang-format on

/// architecture_statement_part ::=                               [LRM93 §1.2.2]
///     { concurrent_statement }
// clang-format off
auto const architecture_statement_part_def =
    *concurrent_statement
    ;
// clang-format on

/// array_type_definition ::=                                       [LRM93 §8.2]
///     unconstrained_array_definition | constrained_array_definition
// clang-format off
auto const array_type_definition_def =
      unconstrained_array_definition
    | constrained_array_definition
    ;
// clang-format on

///
/// assertion                                                       [LRM93 §8.2]
///
/// @code{.bnf}
/// assertion ::=
///     assert condition
///     [ report expression ]
///     [ severity expression ]
/// @endcode
// clang-format off
auto const assertion_def =
        ( ASSERT   >> condition)
    >> -( REPORT   >> expression )
    >> -( SEVERITY >> expression )
    ;
// clang-format on

///
/// assertion_statement                                             [LRM93 §8.2]
///
/// @code{.bnf}
/// assertion_statement ::=
///     [ label : ] assertion ;
/// @endcode
// clang-format off
auto const assertion_statement_def =
       -label_colon
    >> assertion
    >> x3::expect[';']
    ;
// clang-format on

///
/// association_element                                         [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// association_element ::=
///     [ formal_part => ] actual_part
/// @endcode
// clang-format off
auto const association_element_def =
       -x3::as<ast::formal_part>[
           formal_part >> "=>"
       ]
    >> actual_part
    ;
// clang-format on

///
/// association_list                                            [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// association_list ::=
///     association_element { , association_element }
/// @endcode
// clang-format off
auto const association_list_def =
    association_element % ','
    ;
// clang-format on

/// attribute_declaration ::=                                       [LRM93 §4.4]
///     attribute identifier : type_mark ;
// clang-format off
auto const attribute_declaration_def =
       ATTRIBUTE
    >> identifier
    >> ':'
    >> type_mark
    >> x3::expect[';']
    ;
// clang-format on

/// attribute_designator ::=                                        [LRM93 §6.6]
///     attribute_simple_name
// clang-format off
auto const attribute_designator_def =
    simple_name
    ;
// clang-format on

/// attribute_name ::=                                              [LRM93 §6.6]
///     prefix [ signature ] ' attribute_designator [ ( expression ) ]
// clang-format off
auto const attribute_name_def =
       prefix
    >> -signature
    >> '\''
    >> attribute_designator
    >> -(
        '(' >> expression >> ')'
        )
    ;
// clang-format on

/// attribute_specification ::=                                     [LRM93 §5.1]
///     attribute attribute_designator of entity_specification is expression ;
// clang-format off
auto const attribute_specification_def =
       ATTRIBUTE
    >> attribute_designator
    >> OF
    >> entity_specification
    >> IS
    >> expression
    >> x3::expect[';']
    ;
// clang-format on

#if 0  // Note: UNUSED, embedded directly into based_literal rule
/// base ::=                                                     [LRM93 §13.4.2]
///     integer
auto const base_def =
    integer
    ;
#endif

#if 0  // Note: UNUSED, embedded directly into bit_string_literal rule
/// base_specifier ::=                                             [LRM93 §13.7]
/// B | O | X
auto const base_specifier_def =
    'B' | 'O' | 'X'
    ;
#endif

/// based_integer ::=                                            [LRM93 §13.4.2]
///     extended_digit { [ underline ] extended_digit }
// clang-format off
auto const based_integer_def =
    x3::as<ast::string_span>[
        raw [ lexeme[
            extended_digit >> *( -lit('_') >> extended_digit )
        ]]
    ]
    ;
// clang-format on

/// based_literal                                                [LRM93 §13.4.2]
///
/// @code{.bnf}
/// based_literal ::=
///     base # based_integer [ . based_integer ] # [ exponent ]
/// @endcode
///
/// @note IEEE1076-93 Ch. 13.4.2: "The base and the exponent, if any, are in decimal notation." ...
/// Further, "An exponent for a based integer literal must not have a minus sign."
///

/// [Spirit X3, Is this error handling approach useful?](
/// https://stackoverflow.com/questions/57048008/spirit-x3-is-this-error-handling-approach-useful/57067207#57067207)
#if 0
namespace boost::spirit::x3 {
    template <> struct get_info<int_type> {
        typedef std::string result_type;
        std::string operator()(int_type const&) const { return "integral number"; }
    };
    template <> struct get_info<square::peg::main_type> {
        typedef std::string result_type;
        std::string operator()(square::peg::main_type const&) const { return "quoted string, bare string or integer number pair"; }
    };
}
#endif

namespace based_literal_detail {

// see https://github.com/boostorg/spirit/issues/657
// template <typename RuleID>
struct based_literal_error_handler {
    template <typename IteratorT, typename ContextT>
    x3::error_handler_result on_error(IteratorT& first, IteratorT /* last */,
                                      x3::expectation_failure<IteratorT> const& e,
                                      ContextT const& context) const
    {
        auto& diagnostic_handler = x3::get<parser::diagnostic_handler_tag>(context).get();

        std::string const message =
            // FixMe e.which() contains rule name 'based literal base', hence misleading error msg
            "in based literal '" + e.which() +
            "' the base specifier isn't supported; only 2, 8, 10 and 16!";

        // diagnostic_handler.parser_error(e.where(), message);
        diagnostic_handler.parser_error(first, e.where(), message);

        // advance iter after the error occurred to continue parsing, the error is reported before.
        first = e.where();

        return x3::error_handler_result::accept;
    }
};

template <typename T = x3::unused_type>
static inline auto const as = [](auto parser, const char* name = typeid(T).name()) {
    struct tag : based_literal_error_handler {};
    return x3::rule<tag, T>{ name } = parser;
};

/// parse base of based literals                                [LRM93 §13.4.2]
///
/// @code {.bnf}
/// base ::=
///     integer
/// @endcode
///
/// @note IEEE1076-93 Ch. 13.4 specifies:
/// - "The base and the exponent, if any, are in decimal notation."
/// - "base must be at least two and at most 16."
/// @note Only the common bases of 2, 8, 10, 16 are supported.
///
/// Unfortunately, there isn't a straight forward way to handle decimal separators in Spirit.X3.
/// This implementation uses a 2nd pass to parse the base specifier with help of filtered
/// ranges to handle with '_' separators. This is another approach to handle separators like
/// '_' shown by sehe at  [X3 parse rule doesn't compile](
/// https://stackoverflow.com/questions/47008258/x3-parse-rule-doesnt-compile/47013918#47013918)
/// which also uses a 2nd pass using `stoull`.
///
//
// ToDo Revert Spirit.X3 here, make mini-parser for 3-chars-width and convert
// see notes at ast::based_literal header
//
struct based_literal_base_type : x3::parser<based_literal_base_type> {
    using attribute_type = std::uint32_t;

    template <typename IteratorT, typename ContextT, typename RContextT, typename AttributeT>
    bool parse(IteratorT& first, IteratorT const& last, [[maybe_unused]] ContextT const& ctx,
               [[maybe_unused]] RContextT const& rctx, AttributeT& base_attribute) const
    {
        skip_over(first, last, ctx);  // pre-skip using surrounding skipper

        using string_range_type = ast::string_span;
        string_range_type base_literal;

        // clang-format off
        auto const integer_literal = x3::rule<struct _, string_range_type>{ "based literal's base" } =
            raw[ lexeme [
                digit >> *( -lit("_") >> digit )
            ]]
            ;
        // clang-format on

        bool const literal_ok = x3::parse(first, last, integer_literal, base_literal);

        if (!literal_ok) {
            return false;
        }

        using namespace ranges;
        auto pruned_literal = base_literal | views::filter([](char chr) { return chr != '_'; });

        auto parse_iter = std::begin(pruned_literal);
        auto const parse_last = std::end(pruned_literal);

        bool const parse_ok =
            x3::parse(parse_iter, parse_last, x3::uint_ >> x3::eoi, base_attribute);

        if (!parse_ok || !supported_base(base_attribute)) {
            return false;
        }
        return true;
    }

    bool supported_base(attribute_type base) const
    {
        // clang-format off
        switch (base) {
            // NOLINTNEXTLINE(bugprone-branch-clone)
            case 2:  [[fallthrough]];
            case 8:  [[fallthrough]];
            case 10: [[fallthrough]];
            case 16: return true;
            default: return false;
        }
        // clang-format on
    }
};

based_literal_base_type const base_r;
auto const base = x3::expect[as<unsigned>(base_r, "based literal base")];

#if 0  // FixMe: Move out of this namespace, requires based_literal_detail::base_type before!
// @see https://wandbox.org/permlink/Up1mD3FTVbE02tJG
namespace boost::spirit::x3 {
    template <> struct x3::get_info<based_literal_detail::base_type> {
        using result_type = std::string;
        result_type operator()(based_literal_detail::base_type const&) const {
             return "based literal's base specifier"; 
        }
    };
}
#endif

// clang-format off
auto const integer_exponent = x3::rule<struct _exp, ast::string_span>{ "based_literal" } =
    x3::as<ast::string_span>[
        x3::omit[
            char_("Ee") >> -char_('+')  // integer with '+' exponent is allowed, but not '-'!
        ] >> integer
    ]
    ;
// clang-format on

// clang-format off
auto const integer = x3::rule<struct _int, ast::based_literal::number_chunk>{ "based_literal" } =
       lexeme[
           //                      empty fractional part
           based_integer >> x3::attr(ast::string_span{}) >> '#' >> -integer_exponent
       ] 
    >> x3::attr(ast::based_literal::numeric_type_specifier::integer)
    ;
// clang-format on

// clang-format off
auto const real = x3::rule<struct _real, ast::based_literal::number_chunk>{ "based_literal" } =
       lexeme[
           based_integer >> lit('.') >> based_integer >> '#' >> -exponent
       ]
    >> x3::attr(ast::based_literal::numeric_type_specifier::real);
// clang-format on

}  // namespace based_literal_detail

// clang-format off
auto const based_literal_def =
    lexeme[
        based_literal_detail::base >> '#' >> (based_literal_detail::real | based_literal_detail::integer)
    ]
    ;
// clang-format on

/// basic_identifier ::=                                           [LRM93 §13.3]
///     letter { [ underline ] letter_or_digit }
namespace basic_identifier_detail {

// clang-format off
auto const feasible = x3::rule<struct _, ast::string_span>{ "basic_identifier" } =
    raw[
        lexeme[
               letter >> !char_('"')  // reject bit_string_literal
            >> *(letter_or_digit | char_("_"))
        ]
    ];
// clang-format on
}  // namespace basic_identifier_detail

auto const basic_identifier_def = basic_identifier_detail::feasible - keyword;

/// binding_indication ::=                                        [LRM93 §5.2.1]
///     [ use entity_aspect ]
///     [ generic_map_aspect ]
///     [ port_map_aspect ]
// clang-format off
auto const binding_indication_def =
       -(USE >> entity_aspect)
    >> -generic_map_aspect 
    >> -port_map_aspect;
// clang-format on

/// bit_string_literal ::=                                         [LRM93 §13.7]
///     base_specifier " bit_value "
namespace detail {

auto const bit_string_literal = [](auto&& base, auto&& char_range, auto&& attr) {
    using CharT = decltype(char_range);
    using AttrT = decltype(attr);

    // clang-format off
    auto const char_set = [](auto&& char_range_) {
        return x3::rule<struct _, ast::string_span>{ "char_set" } = x3::as_parser(
            raw[
                   char_(std::forward<CharT>(char_range_))
                >> *(-lit("_") >> char_(std::forward<CharT>(char_range_)))
            ]
        );
    };
    // clang-format on

    // clang-format off
    return x3::rule<struct _, ast::bit_string_literal>{ "bit_string_literal" } = x3::as_parser(
           lexeme[
                  x3::omit[char_(std::forward<decltype(base)>(base))]
               >> lit('"') 
               >> char_set(std::forward<CharT>(char_range)) 
               >> lit('"')
           ]
        >> x3::attr(std::forward<AttrT>(attr)));
    // clang-format on
};

}  // namespace detail

// clang-format off
auto const bit_string_literal_def =
    detail::bit_string_literal("Bb", "01", ast::bit_string_literal::numeric_base_specifier::base2) |
    detail::bit_string_literal("Xx", "0-9a-fA-F", ast::bit_string_literal::numeric_base_specifier::base16) |
    detail::bit_string_literal("Oo", "0-7", ast::bit_string_literal::numeric_base_specifier::base8);
// clang-format on

#if 0  // Note: UNUSED, embedded directly into bit_string_literal
/// bit_value ::=
///     extended_digit { [ underline ] extended_digit }
auto const bit_value_def =
    extended_digit { -( underline ) extended_digit }
    ;
#endif

/// block_configuration ::                                        [LRM93 §1.3.1]
///     for block_specification
///         { use_clause }
///         { configuration_item }
///     end for ;
// clang-format off
auto const block_configuration_def =
       FOR
    >> block_specification 
    >> *use_clause 
    >> *configuration_item 
    >> END >> FOR 
    >> x3::expect[';']
    ;
// clang-format on

/// block_declarative_item ::=                                    [LRM93 §1.2.1]
///       subprogram_declaration
///     | subprogram_body
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | signal_declaration
///     | shared_variable_declaration
///     | file_declaration
///     | alias_declaration
///     | component_declaration
///     | attribute_declaration
///     | attribute_specification
///     | configuration_specification
///     | disconnection_specification
///     | use_clause
///     | group_template_declaration
///     | group_declaration
// clang-format off
auto const block_declarative_item_def =
    subprogram_declaration 
    | subprogram_body 
    | type_declaration 
    | subtype_declaration 
    | constant_declaration 
    | signal_declaration 
    | variable_declaration  // shared_variable_declaration
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
// clang-format on

/// block_declarative_part ::=                                      [LRM93 §9.1]
///     { block_declarative_item }
// clang-format off
auto const block_declarative_part_def =
    *block_declarative_item
    ;
// clang-format on

/// block_header ::=                                                [LRM93 §9.1]
///     [ generic_clause
///     [ generic_map_aspect ; ] ]
///     [ port_clause
///     [ port_map_aspect ; ] ]
namespace detail {

// clang-format off
auto const block_header_generic = x3::rule<struct _, ast::block_header::generic_part_chunk>{ "block_header.generic"} = 
       generic_clause 
    >> -(generic_map_aspect >> x3::expect[';'])
    ;
// clang-format on

// clang-format off
auto const block_header_port = x3::rule<struct _, ast::block_header::port_part_chunk>{ "block_header.port" } = 
       port_clause
    >> -(port_map_aspect >> x3::expect[';'])
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const block_header_def =
        -detail::block_header_generic
     >> -detail::block_header_port
     ;
// clang-format on

/// block_specification ::=                                       [LRM93 §1.3.1]
///       architecture_name
///     | block_statement_label
///     | generate_statement_label [ ( index_specification ) ]
// clang-format off
auto const block_specification_def =
    // --- order matters ---                                      
       label >> -('(' >> index_specification >> ')')
    |  name
    ;
// clang-format on

/// block_statement ::=                                             [LRM93 §9.1]
///     block_label :
///         block [ ( guard_expression ) ] [ is ]
///             block_header
///             block_declarative_part
///         begin
///             block_statement_part
///         end block [ block_label ] ;
// clang-format off
auto const block_statement_def =
       label_colon
    >> BLOCK 
    >> -('(' >> expression >> ')') >> -IS
    >> block_header 
    >> block_declarative_part
    >> BEGIN
    >> block_statement_part 
    >> END >> BLOCK >> -label
    >> x3::expect[';']
    ;
// clang-format on

/// block_statement_part ::=                                        [LRM93 §9.1]
///     { concurrent_statement }
// clang-format off
auto const block_statement_part_def =
    *concurrent_statement;
// clang-format on

/// case_statement ::=                                              [LRM93 §8.8]
///     [ case_label : ]
///         case expression is
///             case_statement_alternative
///             { case_statement_alternative }
///         end case [ case_label ] ;
// clang-format off
auto const case_statement_def =
        -label_colon 
     >> CASE >> expression >> IS 
     >> +case_statement_alternative 
     >> END >> CASE >> -label 
     >> x3::expect[';']
     ;
// clang-format on

/// case_statement_alternative ::=                                  [LRM93 §8.8]
///     when choices =>
///         sequence_of_statements
// clang-format off
auto const case_statement_alternative_def =
       WHEN >> choices >> "=>" 
    >> sequence_of_statements
    ;
// clang-format on

/// character_literal ::=                                          [LRM93 §13.5]
///     ' graphic_character '
// clang-format off
auto const character_literal_def =
    x3::lexeme[
       "\'" >> ((graphic_character - '\'') | char_("\'")) >> "\'"
    ]
    ;
// clang-format on

/// choice ::=                                                    [LRM93 §7.3.2]
///       simple_expression
///     | discrete_range
///     | element_simple_name
///     | others
// clang-format off
auto const choice_def =
    // Note, (element)_simple_name get never been parsed, since:
    // simple_expression -> term -> factor -> primary -> name -> simple_name
      simple_expression 
    | discrete_range 
    | OTHERS
    ;
// clang-format on

/// choices ::=                                                   [LRM93 §7.3.2]
///     choice { | choice }
// clang-format off
auto const choices_def =
    choice % '|';
// clang-format on

/// component_configuration ::=                                   [LRM93 §1.3.2]
///     for component_specification
///         [ binding_indication ; ]
///         [ block_configuration ]
///     end for ;
// clang-format off
auto const component_configuration_def =
        FOR >> component_specification
     >> -(binding_indication >> x3::expect[';']) 
     >> -block_configuration
     >> END >> FOR
     >> x3::expect[';']
     ;
// clang-format on

/// component_declaration ::=                                       [LRM93 §4.5]
///     component identifier [ is ]
///         [ local_generic_clause ]
///         [ local_port_clause ]
///     end component [ component_simple_name ] ;
// clang-format off
auto const component_declaration_def =
       COMPONENT >> identifier >> -IS
    >> -generic_clause
    >> -port_clause
    >> END >> COMPONENT >> -simple_name
    >> x3::expect[';']
    ;
// clang-format on

/// component_instantiation_statement ::=                           [LRM93 §9.6]
///     instantiation_label :
///         instantiated_unit
///             [ generic_map_aspect ]
///             [ port_map_aspect ] ;
// clang-format off
auto const component_instantiation_statement_def =
       label_colon
    >> instantiated_unit
    >> -generic_map_aspect
    >> -port_map_aspect
    >> x3::expect[';']
    ;
// clang-format on

/// component_specification ::=                                     [LRM93 §5.2]
///     instantiation_list : component_name
// clang-format off
auto const component_specification_def =
     instantiation_list >> ':' >> name
     ;
// clang-format on

/// composite_type_definition ::=                                   [LRM93 §3.2]
///       array_type_definition
///     | record_type_definition
// clang-format off
auto const composite_type_definition_def =
       array_type_definition
    | record_type_definition
    ;
// clang-format on

/// concurrent_assertion_statement ::=                              [LRM93 §9.4]
/// [ label : ] [ postponed ] assertion ;
// clang-format off
auto const concurrent_assertion_statement_def =
    -label_colon >> -POSTPONED >> assertion >> x3::expect[';']
    ;
// clang-format on

/// concurrent_procedure_call_statement ::=                         [LRM93 §9.3]
/// [ label : ] [ postponed ] procedure_call ;
// clang-format off
auto const concurrent_procedure_call_statement_def =
    -label_colon >> -POSTPONED >> procedure_call >> x3::expect[';']
    ;
// clang-format on

/// concurrent_signal_assignment_statement ::=                      [LRM93 §9.5]
///       [ label : ] [ postponed ] conditional_signal_assignment
///     | [ label : ] [ postponed ] selected_signal_assignment
// clang-format off
auto const concurrent_signal_assignment_statement_def =
       -label_colon >> -POSTPONED 
    >> (conditional_signal_assignment | selected_signal_assignment)
    ;
// clang-format on

/// concurrent_statement ::=                                          [LRM93 §9]
///       block_statement
///     | process_statement
///     | concurrent_procedure_call_statement
///     | concurrent_assertion_statement
///     | concurrent_signal_assignment_statement
///     | component_instantiation_statement
///     | generate_statement
// clang-format off
auto const concurrent_statement_def =
    // Note, order matters but is fragile; the problem seems to rise from rule
    // label >> ':', which is same/similar to component_instantiation_statement
       component_instantiation_statement
    | concurrent_signal_assignment_statement 
    | concurrent_procedure_call_statement 
    | concurrent_assertion_statement 
    | block_statement 
    | generate_statement 
    | process_statement
    ;
// clang-format on

/// condition ::=                                                   [LRM93 §8.1]
///     boolean_expression
// clang-format off
auto const condition_def =
    expression
    ;
// clang-format on

/// condition_clause ::=                                            [LRM93 §8.1]
///     until condition
// clang-format off
auto const condition_clause_def =
     UNTIL >> condition
     ;
// clang-format on

/// conditional_signal_assignment ::=                             [LRM93 §9.5.1]
///     target    <= options conditional_waveforms ;
// clang-format off
auto const conditional_signal_assignment_def =
       target >> "<=" >> options >> conditional_waveforms >> x3::expect[';']
    ;
// clang-format on

/// conditional_waveforms ::=                                     [LRM93 §9.5.1]
///     { waveform when condition else }
///       waveform [ when condition ]
// clang-format off
auto const conditional_waveforms_def =
       *(waveform >> WHEN >> condition >> ELSE)
    >> waveform >> -(WHEN >> condition)
    ;
// clang-format on

/// configuration_declaration ::=                                   [LRM93 §1.3]
///     configuration identifier of entity_name is
///         configuration_declarative_part
///         block_configuration
///     end [ configuration ] [ configuration_simple_name ] ;
// clang-format off
auto const configuration_declaration_def =
       CONFIGURATION >> identifier >> OF >> name >> IS
    >> configuration_declarative_part
    >> block_configuration
    >> END >> -CONFIGURATION >> -simple_name
    >> x3::expect[';']
    ;
// clang-format on

/// configuration_declarative_item ::=                              [LRM93 §1.3]
///       use_clause
///     | attribute_specification
///     | group_declaration
// clang-format off
auto const configuration_declarative_item_def =
      use_clause
    | attribute_specification
    | group_declaration
    ;
// clang-format on

/// configuration_declarative_part ::=                              [LRM93 §1.3]
///     { configuration_declarative_item }
// clang-format off
auto const configuration_declarative_part_def =
     *configuration_declarative_item
     ;
// clang-format on

/// configuration_item ::=                                        [LRM93 §1.3.1]
///       block_configuration
///     | component_configuration
// clang-format off
auto const configuration_item_def =
      block_configuration
    | component_configuration
    ;
// clang-format on

/// configuration_specification ::=                                 [LRM93 §5.2]
///     for component_specification binding_indication ;
// clang-format off
auto const configuration_specification_def =
    FOR >> component_specification >> binding_indication >> x3::expect[';']
    ;
// clang-format on

/// constant_declaration ::=                                    [LRM93 §4.3.1.1]
///     constant identifier_list : subtype_indication [ := expression ] ;
// clang-format off
auto const constant_declaration_def =
       omit[CONSTANT]
    >> identifier_list >> ':' >> subtype_indication >> -(":=" >> expression) >> x3::expect[';']
    ;
// clang-format on

/// constrained_array_definition ::=                              [LRM93 §3.2.1]
///     array index_constraint of element_subtype_indication
// clang-format off
auto const constrained_array_definition_def =
    ARRAY >> index_constraint >> OF >> subtype_indication
    ;
// clang-format on

/// constraint ::=                                                  [LRM93 §4.2]
///       range_constraint
///     | index_constraint
// clang-format off
auto const constraint_def =
       range_constraint
     | index_constraint
     ;
// clang-format on

/// context_clause ::=                                             [LRM93 §11.3]
///     { context_item }
// clang-format off
auto const context_clause_def =
    *context_item
    ;
// clang-format on

/// context_item ::=                                               [LRM93 §11.3]
///       library_clause
///     | use_clause
// clang-format off
auto const context_item_def =
      library_clause
    | use_clause
    ;
// clang-format on

/// decimal_literal ::=                                          [LRM93 §13.4.1]
///     integer [ . integer ] [ exponent ]
namespace decimal_literal_detail {

// clang-format off
auto const real_type = x3::rule<struct _, ast::decimal_literal>{ "decimal_literal<real>" } =
    x3::as<ast::string_span>[
        raw[
            lexeme[
                integer >> char_('.') >> integer >> -exponent
            ]
        ]
    ] >> x3::attr(ast::decimal_literal::numeric_type_specifier::real)
    ;
// clang-format on

// clang-format off
auto const integer_exponent = x3::rule<struct _, ast::string_span>{ "exponent" } =
    // Note, following IEEE1076-93 Ch. 13.4, the exponent on integer type must
    // not have a minus sign. This means implicit (even from NBF) that a positive
    // (optional) sign is allowed.
    raw[lexeme[char_("Ee") >> -char_("+") >> integer]]
    ;
// clang-format on

// clang-format off
auto const integer_type = x3::rule<struct _, ast::decimal_literal>{ "decimal_literal<int>" } =
    x3::as<ast::string_span>[
        raw[
            lexeme[
                integer >> -integer_exponent
            ]
        ]
    ] >> x3::attr(ast::decimal_literal::numeric_type_specifier::integer)
    ;
// clang-format on

}  // namespace decimal_literal_detail

// clang-format off
auto const decimal_literal_def =
      decimal_literal_detail::real_type
    | decimal_literal_detail::integer_type
    ;
// clang-format on

#if 0  // UNUSED in the BNF
/// declaration ::=                                                   [LRM93 §4]
///       type_declaration
///     | subtype_declaration
///     | object_declaration
///     | interface_declaration
///     | alias_declaration
///     | attribute_declaration
///     | component_declaration
///     | group_template_declaration
///     | group_declaration
///     | entity_declaration
///     | configuration_declaration
///     | subprogram_declaration
///     | package_declaration
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

/// delay_mechanism ::=                                             [LRM93 §8.4]
///       transport
///     | [ reject time_expression ] inertial
// clang-format off
auto const delay_mechanism_def =
    TRANSPORT | (-(REJECT >> expression) >> INERTIAL)
    ;
// clang-format on

/// design_file ::=                                                [LRM93 §11.1]
///     design_unit { design_unit }
// clang-format off
auto const design_file_def =
    *design_unit
    ;
// clang-format on

/// design_unit ::=                                                [LRM93 §11.1]
///     context_clause library_unit
// clang-format off
auto const design_unit_def =
    context_clause >> library_unit
    ;
// clang-format on

/// designator ::=                                                  [LRM93 §2.1]
///     identifier  |  operator_symbol
// clang-format off
auto const designator_def =
      identifier
    | operator_symbol
    ;
// clang-format on

/// direction ::=                                                   [LRM93 §3.1]
///     to | downto
// clang-format off
auto const direction_def =
    TO | DOWNTO
    ;
// clang-format on

/// disconnection_specification ::=                                 [LRM93 §5.3]
///     disconnect guarded_signal_specification after time_expression ;
// clang-format off
auto const disconnection_specification_def =
    DISCONNECT >> guarded_signal_specification >> AFTER >> expression >> x3::expect[';']
    ;
// clang-format on

/// discrete_range ::=                                            [LRM93 §3.2.1]
///     discrete_subtype_indication | range
// clang-format off
auto const discrete_range_def =
    // --- order matters ---                                 
      range
    | subtype_indication
    ;
// clang-format on

///
/// element_association                                           [LRM93 §7.3.2]
///
/// @code{.bnf}
/// element_association ::=
///     [ choices => ] expression
/// @endcode
///
/// Note that parsing element_association is a bit tricky, due to backtracking side
/// effect. The problem did rise up first time on parsing attribute_specification's
/// expression:
///
/// @code{.bnf}
/// attribute_specification ::=
///        attribute attribute_designator OF entity_specification IS expression ;
/// @endcode
///
/// with descent aggregate's element_association:
///
/// @code{.bnf}
/// aggregate           ::= ( element_association { , element_association } )
/// element_association ::= [ choices => ] expression
/// @endcode
///
/// If the choices rule fails due to missing "=>" the element_association node
/// still contains the previous parsed data, hence holding the leaf data twice
/// using two parse paths. as[] directive solve this.
// clang-format off
auto const element_association_def =
       -x3::as<ast::choices>[choices >> "=>"]  // no expected[]
    >> expression
    ;
// clang-format on

/// element_declaration ::=                                       [LRM93 §3.2.2]
///     identifier_list : element_subtype_definition ;
// clang-format off
auto const element_declaration_def =
    identifier_list >> ':' >> element_subtype_definition >> x3::expect[';']
    ;
// clang-format on

/// element_subtype_definition ::=                                [LRM93 §3.2.2]
///     subtype_indication
// clang-format off
auto const element_subtype_definition_def =
    subtype_indication
    ;
// clang-format on

/// entity_aspect ::=                                           [LRM93 §5.2.1.1]
///       entity entity_name [ ( architecture_identifier) ]
///     | configuration configuration_name
///     | open
namespace entity_aspect_detail {

// clang-format off
auto const entity = x3::rule<struct _, ast::entity_aspect_entity>{ "entity_aspect.entity" } =
    ENTITY >> name >> -('(' >> identifier >> ')')
    ;
// clang-format on

// clang-format off
auto const configuration = x3::rule<struct _, ast::entity_aspect_configuration>{ "entity_aspect.configuration" } =
    CONFIGURATION >> name;
// clang-format on

}  // namespace entity_aspect_detail

// clang-format off
auto const entity_aspect_def =
      entity_aspect_detail::entity
    | entity_aspect_detail::configuration
    | OPEN
    ;
// clang-format on

/// entity_class ::=                                                [LRM93 §5.1]
///       entity        | architecture  | configuration
///     | procedure     | function      | package
///     | type          | subtype       | constant
///     | signal        | variable      | component
///     | label         | literal       | units
///     | group         | file
namespace detail {

// clang-format off
x3::symbols<ast::keyword_token> const entity_class_symbols(
    {
        { "entity"        , ast::keyword_token::ENTITY },
        { "architecture"  , ast::keyword_token::ARCHITECTURE },
        { "configuration" , ast::keyword_token::CONFIGURATION },
        { "procedure"     , ast::keyword_token::PROCEDURE },
        { "function"      , ast::keyword_token::FUNCTION },
        { "package"       , ast::keyword_token::PACKAGE },
        { "type"          , ast::keyword_token::TYPE },
        { "subtype"       , ast::keyword_token::SUBTYPE },
        { "constant"      , ast::keyword_token::CONSTANT },
        { "signal"        , ast::keyword_token::SIGNAL },
        { "variable"      , ast::keyword_token::VARIABLE },
        { "component"     , ast::keyword_token::COMPONENT },
        { "label"         , ast::keyword_token::LABEL },
        { "literal"       , ast::keyword_token::LITERAL },
        { "units"         , ast::keyword_token::UNITS },
        { "group"         , ast::keyword_token::GROUP },
        { "file"          , ast::keyword_token::FILE }
    },
    "entity_class");
// clang-format on

}  // namespace detail

// clang-format off
auto const entity_class_def =
    distinct(detail::entity_class_symbols)
    ;
// clang-format on

/// entity_class_entry ::=                                          [LRM93 §4.6]
///     entity_class [ <> ]
// clang-format off
auto const entity_class_entry_def =
    entity_class >> -lit("<>")
    ;
// clang-format on

/// entity_class_entry_list ::=                                     [LRM93 §4.6]
///     entity_class_entry { , entity_class_entry }
// clang-format off
auto const entity_class_entry_list_def =
    entity_class_entry % ','
    ;
// clang-format on

///
/// entity_declaration                                              [LRM93 §1.1]
///
/// \code{.bnf}
/// entity_declaration ::=
///     entity identifier is
///         entity_header
///         entity_declarative_part
///   [ begin
///         entity_statement_part ]
///     end [ entity ] [ entity_simple_name ] ;
/// \endcode
// clang-format off
auto const entity_declaration_def =
       ENTITY >> identifier >> IS
    >> entity_header
    >> entity_declarative_part
    >> -(BEGIN >> entity_statement_part) >> END >> -ENTITY >> -simple_name
    >> x3::expect[';']
    ;
// clang-format on

///
/// entity_declarative_item                                       [LRM93 §1.1.2]
///
/// @code{.bnf}
/// entity_declarative_item ::=
///       subprogram_declaration
///     | subprogram_body
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | signal_declaration
///     | shared_variable_declaration
///     | file_declaration
///     | alias_declaration
///     | attribute_declaration
///     | attribute_specification
///     | disconnection_specification
///     | use_clause
///     | group_template_declaration
///     | group_declaration
/// @endcode
// clang-format off
auto const entity_declarative_item_def =
      subprogram_declaration 
    | subprogram_body 
    | type_declaration 
    | subtype_declaration 
    | constant_declaration 
    | signal_declaration 
    | variable_declaration  // shared_variable_declaration
    | file_declaration 
    | alias_declaration 
    | attribute_declaration 
    | attribute_specification 
    | disconnection_specification 
    | use_clause 
    | group_template_declaration 
    | group_declaration
    ;
// clang-format on

///
/// entity_declarative_part                                       [LRM93 §1.1.2]
///
/// \code{.bnf}
/// entity_declarative_part ::=
///     { entity_declarative_item }
/// \endcode
// clang-format off
auto const entity_declarative_part_def =
    *entity_declarative_item
    ;
// clang-format on

/// entity_designator ::=                                           [LRM93 §5.1]
///     entity_tag [ signature ]
// clang-format off
auto const entity_designator_def =
    entity_tag >> -signature;
// clang-format on

/// entity_header ::=                                             [LRM93 §1.1.1]
///     [ formal_generic_clause ]
///     [ formal_port_clause ]
// clang-format off
auto const entity_header_def =
    -generic_clause >> -port_clause
    ;
// clang-format on

/// entity_name_list ::=                                            [LRM93 §5.1]
///       entity_designator { , entity_designator }
///     | others
///     | all
// clang-format off
auto const entity_name_list_def =
      (entity_designator % ',')
    | OTHERS
    | ALL
     ;
// clang-format on

/// entity_specification ::=                                        [LRM93 §5.1]
///     entity_name_list : entity_class
// clang-format off
auto const entity_specification_def =
    entity_name_list >> ':' >> entity_class
    ;
// clang-format on

///
/// entity_statement                                              [LRM93 §1.1.3]
///
/// \code{.bnf}
/// entity_statement ::=
///       concurrent_assertion_statement
///     | passive_concurrent_procedure_call_statement
///     | passive_process_statement
/// \endcode
// clang-format off
auto const entity_statement_def =
      concurrent_assertion_statement
    | concurrent_procedure_call_statement
    | process_statement;
// clang-format on

///
/// entity_statement_part                                         [LRM93 §1.1.3]
///
/// \code{.bnf}
/// entity_statement_part ::=
///     { entity_statement }
/// \endcode
// clang-format off
auto const entity_statement_part_def =
    *entity_statement
    ;
// clang-format on

/// entity_tag ::=                                                  [LRM93 §5.1]
/// simple_name | character_literal | operator_symbol
// clang-format off
auto const entity_tag_def =
      simple_name
    | character_literal
    | operator_symbol
    ;
// clang-format on

/// enumeration_literal ::=                                       [LRM93 §3.1.1]
///     identifier | character_literal
// clang-format off
auto const enumeration_literal_def =
      identifier
    | character_literal
    ;
// clang-format on

/// enumeration_type_definition ::=                               [LRM93 §3.1.1]
///     ( enumeration_literal { , enumeration_literal } )
// clang-format off
auto const enumeration_type_definition_def =
    '(' >> (enumeration_literal % ',') >> ')'
    ;
// clang-format on

/// exit_statement ::=                                             [LRM93 §8.11]
///     [ label : ] exit [ loop_label ] [ when condition ] ;
// clang-format off
auto const exit_statement_def =
     -label_colon >> EXIT >> -label >> -(WHEN >> condition) >> x3::expect[';']
    ;
// clang-format on

/// exponent ::=                                                 [LRM93 §13.4.1]
///     E [ + ] integer | E - integer
// clang-format off
auto const exponent_def =
    // Note, that exponent rule parses real exponent, for integer types no sign
    // is allowed, hence embedded into the concrete rule
    // x3::as<ast::string_span>[
    x3::omit[char_("Ee")] >> x3::raw[-char_("-+") >> integer]
    //]
    ;
// clang-format on

/// expression ::=                                                  [LRM93 §7.1]
///       relation { and relation }
///     | relation { or relation }
///     | relation { xor relation }
///     | relation [ nand relation ]
///     | relation [ nor relation ]
///     | relation { xnor relation }
namespace expression_detail {

// clang-format off
auto const chunks_1 = x3::rule<struct _, std::vector<ast::expression::chunk>>{ "expression" } =
    *(binary_logical_operator >> relation)
    ;
// clang-format on

// clang-format off
auto const chunk_2 = x3::rule<struct _, std::vector<ast::expression::chunk>>{ "expression" } =
    x3::repeat(1)[  // enforce artificial vector to unify ast node
        unary_logical_operator >> relation
    ]
    ;
// clang-format on

}  // namespace expression_detail

// clang-format off
auto const expression_def =
       relation
    >> ( expression_detail::chunk_2   // NAND, NOR
       | expression_detail::chunks_1  // AND, ...
       )
    ;
// clang-format on

/// extended_identifier ::=                                      [LRM93 §13.3.2]
///     \ graphic_character { graphic_character } \                             .
namespace extended_identifier_detail {

// clang-format off
auto const charset = x3::rule<struct _, ast::string_span>{ "extended_identifier" } =
    +(graphic_character - char_('\\'))
    ;
// clang-format on

// clang-format off
auto const atom = x3::rule<struct _, ast::string_span>{ "extended_identifier" } =
    raw[
        lexeme[
            char_('\\') >> charset >> char_('\\')
        ]
    ]
    ;
// clang-format on

}  // namespace extended_identifier_detail

// clang-format off
auto const extended_identifier_def =
    x3::as<ast::string_span>[
        raw[
            lexeme[
                   extended_identifier_detail::atom 
                >> *(extended_identifier_detail::atom % (char_('\\') >> char_('\\')))
            ]
        ]
    ]
    ;
// clang-format on

/// factor ::=                                                      [LRM93 §7.1]
///       primary [ ** primary ]
///     | abs primary
///     | not primary
namespace factor_detail {

// clang-format off
auto const binary_expr = x3::rule<struct _, ast::factor_binary_operation>{ "factor" } =
       primary
    >> binary_miscellaneous_operator  // ** (exponent)
    >> primary
    ;
// clang-format on

// clang-format off
auto const unary_expr = x3::rule<struct _, ast::factor_unary_operation>{ "factor" } =
       unary_miscellaneous_operator  // ABS | NOT
    >> primary
    ;
// clang-format on

}  // namespace factor_detail

// clang-format off
auto const factor_def =
    // --- order matters ---                         
      factor_detail::binary_expr
    | factor_detail::unary_expr
    | primary;
// clang-format on

/// file_declaration ::=                                        [LRM93 §4.3.1.4]
///     file identifier_list : subtype_indication [ file_open_information ] ;
// clang-format off
auto const file_declaration_def =
       FILE >> identifier_list >> ':'
    >> subtype_indication >> -file_open_information >> x3::expect[';']
    ;
// clang-format on

/// file_logical_name ::=                                       [LRM93 §4.3.1.4]
///     string_expression
// clang-format off
auto const file_logical_name_def =
    expression
    ;
// clang-format on

/// file_open_information ::=                                   [LRM93 §4.3.1.4]
///     [ open file_open_kind_expression ] is file_logical_name
// clang-format off
auto const file_open_information_def =
    -(omit[OPEN] >> expression) >> IS >> file_logical_name
    ;
// clang-format on

/// file_type_definition ::=                                        [LRM93 §3.4]
///     file  of type_mark
// clang-format off
auto const file_type_definition_def =
    FILE >> OF >> type_mark
    ;
// clang-format on

#if 0  // UNUSED; embedded into scalar_type_definition
/// floating_type_definition ::=                                  [LRM93 §3.1.4]
///     range_constraint
auto const floating_type_definition_def =
    range_constraint
    ;
#endif

///
/// formal_designator ::=                                       [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// formal_designator ::=                                       [LRM93 §4.3.2.2]
///       generic_name
///     | port_name
///     | parameter_name
/// @endcode
// clang-format off
auto const formal_designator_def =
    name
    ;
// clang-format on

/// formal_parameter_list ::=                                     [LRM93 §2.1.1]
///     parameter_interface_list
// clang-format off
auto const formal_parameter_list_def =
    interface_list
    ;
// clang-format on

///
/// formal_part                                                 [LRM93 §4.3.2.2]
///
/// @code{.bnf}
/// formal_part ::=
///       formal_designator
///     | function_name ( formal_designator )
///     | type_mark ( formal_designator )
/// @endcode
///
/// @note formal_designator is a context tied name ({generic, port, parameter}_name)
/// where `function_name` and `type_mark` are also names. Hence parse a list of names, for
/// convenience into `std::vector`, even if the number of elements parsed can not reach more
/// than 2 due to explicit grammar rule.
// clang-format off
auto const formal_part_def =
    x3::as<std::vector<ast::name>>[
        name >> -( '(' >> formal_designator >> ')' )
    ]
    ;
// clang-format on

#if 0  // UNUSED; embedded into type_declaration
/// full_type_declaration ::=                                       [LRM93 §4.1]
///     type identifier is type_definition ;
auto const full_type_declaration_def = ( // operator precedence
       TYPE
    >> identifier
    >> IS
    >> type_definition
    )
    >  ';'
    ;
#endif

/// function_call ::=                                             [LRM93 §7.3.3]
///     function_name [ ( actual_parameter_part ) ]
// clang-format off
auto const function_call_def =
    name >> -( '(' >> actual_parameter_part >> ')' )
    ;
// clang-format on

/// generate_statement ::=                                          [LRM93 §9.7]
///     generate_label :
///         generation_scheme generate
///             [ { block_declarative_item }
///         begin ]
///             { concurrent_statement }
///         end generate [ generate_label ] ;
///
/// FixMe: testing this rule failed - never seen
/// concurrent_statement/component_instantiation_statement
// clang-format off
auto const generate_statement_def =
       label_colon >> generation_scheme >> GENERATE
    >> -(*block_declarative_item >> BEGIN)
    >> *concurrent_statement
    >> END >> GENERATE >> -label
    >> x3::expect[';']
    ;
// clang-format on

///
/// generation_scheme                                               [LRM93 §9.7]
///
/// \code{.bnf}
/// generation_scheme ::=
///       for generate_parameter_specification
///     | if condition
/// \endcode
// clang-format off
auto const generation_scheme_def =
      (FOR >> parameter_specification)
    | (IF >> condition)
    ;
// clang-format on

///
/// generic_clause                                                [LRM93 §1.1.1]
///
/// \code{.bnf}
/// generic_clause ::=
///     generic ( generic_list ) ;
/// \endcode
// clang-format off
auto const generic_clause_def =
    GENERIC >> '(' >> interface_list >> ')' >> x3::expect[';']
    ;
// clang-format on

#if 0  // DISABLED; embedded into generic_clause
/// generic_list ::=                                            [LRM93 §1.1.1.1]
///     generic_interface_list
auto const generic_list_def =
    interface_list
    ;
#endif

/// generic_map_aspect ::=                                      [LRM93 §5.2.1.2]
///     generic map ( generic_association_list )
// clang-format off
auto const generic_map_aspect_def =
    GENERIC >> MAP >> '(' >> association_list >> ')'
    ;
// clang-format on

/// group_constituent ::                                            [LRM93 §4.7]
///     name | character_literal
// clang-format off
auto const group_constituent_def =
      name
    | character_literal
    ;
// clang-format on

/// group_constituent_list ::=                                      [LRM93 §4.7]
///     group_constituent { , group_constituent }
// clang-format off
auto const group_constituent_list_def =
    group_constituent % ','
    ;
// clang-format on

/// group_template_declaration ::=                                  [LRM93 §4.6]
///     group identifier is ( entity_class_entry_list ) ;
// clang-format off
auto const group_template_declaration_def =
    GROUP >> identifier >> IS >> '(' >> entity_class_entry_list >> ')' >> x3::expect[';']
    ;
// clang-format on

/// group_declaration ::=                                           [LRM93 §4.7]
///     group identifier : group_template_name ( group_constituent_list ) ;
// clang-format off
auto const group_declaration_def =
    GROUP >> identifier >> ':' >> name >> '(' >> group_constituent_list >> ')' >> x3::expect[';']
    ;
// clang-format on

/// guarded_signal_specification ::=                                [LRM93 §5.3]
///     guarded_signal_list : type_mark
// clang-format off
auto const guarded_signal_specification_def =
    signal_list >> ':' >> type_mark
    ;
// clang-format on

/// identifier ::=                                                 [LRM93 §13.3]
///     basic_identifier | extended_identifier
// clang-format off
auto const identifier_def =
      basic_identifier
    | extended_identifier
    ;
// clang-format on

/// identifier_list ::=                                           [LRM93 §3.2.2]
///     identifier { , identifier }
// clang-format off
auto const identifier_list_def =
    identifier % ','
    ;
// clang-format on

/// if_statement ::=                                                [LRM93 §8.7]
///     [ if_label : ]
///         if condition then
///             sequence_of_statements
///       { elsif condition then
///             sequence_of_statements }
///       [ else
///             sequence_of_statements ]
///         end if [ if_label ] ;
// clang-format off
auto const if_statement_def =
       -label_colon >> IF >> condition >> THEN
    >> sequence_of_statements
    >> *(ELSIF >> condition >> THEN >> sequence_of_statements)
    >> -(ELSE >> sequence_of_statements)
    >> END >> IF >> -label
    >> x3::expect[';']
    ;
// clang-format on

#if 0  // UNUSED; embedded into type_declaration
/// incomplete_type_declaration ::=                               [LRM93 §3.3.1]
///     type identifier ;
auto const incomplete_type_declaration_def = ( // operator precedence
       TYPE
    >> identifier
    )
    >  ';'
    ;
#endif

/// index_constraint ::=                                          [LRM93 §3.2.1]
///     ( discrete_range { , discrete_range } )
// clang-format off
auto const index_constraint_def =
    '(' >> (discrete_range % ',') >> ')'
    ;
// clang-format on

/// index_specification ::=                                       [LRM93 §1.3.1]
///       discrete_range
///     | static_expression
// clang-format off
auto const index_specification_def =
      discrete_range
    | expression
    ;
// clang-format on

/// index_subtype_definition ::=                                  [LRM93 §3.2.1]
///     type_mark range <>
// clang-format off
auto const index_subtype_definition_def =
    type_mark >> RANGE >> "<>"
    ;
// clang-format on

/// indexed_name ::=                                                [LRM93 §6.4]
///     prefix ( expression { , expression } )
// clang-format off
auto const indexed_name_def =
    prefix >> '(' >> (expression % ',') >> ')'
    ;
// clang-format on

/// instantiated_unit ::=                                           [LRM93 §9.6]
///       [ component ] component_name
///     | entity entity_name [ ( architecture_identifier ) ]
///     | configuration configuration_name
// clang-format off
auto const instantiated_unit_def =
      x3::as<ast::instantiated_unit_component>[-COMPONENT >> name]
    | x3::as<ast::instantiated_unit_entity>[ENTITY >> name >> -('(' >> identifier >> ')')]
    | x3::as<ast::instantiated_unit_configuration>[CONFIGURATION >> name]
    ;
// clang-format on

/// instantiation_list ::=                                          [LRM93 §5.2]
///       instantiation_label { , instantiation_label }
///     | others
///     | all
// clang-format off
auto const instantiation_list_def =
    (label % ',') | OTHERS | ALL
    ;
// clang-format on

/// integer ::=                                                        § 13.4.1]
///     digit { [ underline ] digit }
// clang-format off
auto const integer_def =
    x3::as<ast::string_span>[
        raw[
            lexeme[
                digit >> *(-lit("_") >> digit)
            ]
        ]
    ]
    ;
// clang-format on

#if 0  // DISABLED, embedded into scalar_type_definition
/// integer_type_definition ::=                                   [LRM93 §3.1.2]
///     range_constraint
auto const integer_type_definition_def =
    range_constraint
    ;
#endif

/// interface_constant_declaration ::=                            [LRM93 §4.3.2]
///     [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]
// clang-format off
auto const interface_constant_declaration_def =
     -CONSTANT >> identifier_list >> ':' >> -IN >> subtype_indication >> -(":=" >> expression)
    ;
// clang-format on

/// interface_declaration ::=                                     [LRM93 §4.3.2]
///       interface_constant_declaration
///     | interface_signal_declaration
///     | interface_variable_declaration
///     | interface_file_declaration
// clang-format off
auto const interface_declaration_def =
      interface_constant_declaration
    | interface_signal_declaration
    | interface_variable_declaration
    | interface_file_declaration
    ;
// clang-format on

/// interface_element ::=                                       [LRM93 §4.3.2.1]
///      interface_declaration
// clang-format off
auto const interface_element_def =
    interface_declaration
    ;
// clang-format on

/// interface_file_declaration ::=                                [LRM93 §4.3.2]
///     file identifier_list : subtype_indication
// clang-format off
auto const interface_file_declaration_def =
    FILE >> identifier_list >> ':' >> subtype_indication
    ;
// clang-format on

/// interface_list ::=                                          [LRM93 §4.3.2.1]
///     interface_element { ; interface_element }
///
/// FixMe: using ```interface_element % x3::expect[';']``` won't work here since the
/// last interface_element isn't terminated with trailing ';'
// clang-format off
auto const interface_list_def =
    interface_element % ';'
    ;
// clang-format on

/// interface_signal_declaration ::=                              [LRM93 §4.3.2]
///     [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]
// clang-format off
auto const interface_signal_declaration_def =
       -SIGNAL >> identifier_list >> ':'
    >> -mode >> subtype_indication >> -BUS >> -(":=" >> expression)
    ;
// clang-format on

/// interface_variable_declaration ::=                            [LRM93 §4.3.2]
///     [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]
// clang-format off
auto const interface_variable_declaration_def =
       -VARIABLE >> identifier_list >> ':'
    >> -mode >> subtype_indication >> -(":=" >> expression)
    ;
// clang-format on

/// iteration_scheme ::=                                            [LRM93 §8.9]
///       while condition
///     | for loop_parameter_specification
// clang-format off
auto const iteration_scheme_def =
    (WHILE >> condition) | (FOR >> parameter_specification)
    ;
// clang-format on

/// label ::=                                                       [LRM93 §9.7]
///     identifier
// clang-format off
auto const label_def =
    identifier
    ;
// clang-format on

/// library_clause ::=                                             [LRM93 §11.2]
///     library logical_name_list ;
// clang-format off
auto const library_clause_def =
    LIBRARY >> logical_name_list >> x3::expect[';']
    ;
// clang-format on

/// library_unit ::=                                               [LRM93 §11.1]
///       primary_unit
///     | secondary_unit
// clang-format off
auto const library_unit_def =
      primary_unit
    | secondary_unit
    ;
// clang-format on

/// literal ::=                                                   [LRM93 §7.3.1]
///       numeric_literal
///     | enumeration_literal
///     | string_literal
///     | bit_string_literal
///     | null
// clang-format off
auto const literal_def =
    // --- order matters ---                          
      enumeration_literal
    | string_literal
    | bit_string_literal
    | numeric_literal
    | NULL_
    ;
// clang-format on

/// logical_name ::=                                               [LRM93 §11.2]
///     identifier
// clang-format off
auto const logical_name_def =
    identifier
    ;
// clang-format on

/// logical_name_list ::=                                          [LRM93 §11.2]
///     logical_name { , logical_name }
// clang-format off
auto const logical_name_list_def =
    logical_name % ','
    ;
// clang-format on

/// loop_statement ::=                                              [LRM93 §8.9]
///     [ loop_label : ]
///         [ iteration_scheme ] loop
///             sequence_of_statements
///         end loop [ loop_label ] ;
// clang-format off
auto const loop_statement_def =
       -label_colon
    >> -iteration_scheme >> LOOP
    >> sequence_of_statements
    >> END >> LOOP >> -label
    >> x3::expect[';']
    ;
// clang-format on

/// mode ::=                                                      [LRM93 §4.3.2]
///     in | out | inout | buffer | linkage
namespace detail {

// clang-format off
x3::symbols<ast::keyword_token> const mode_symbols(
    {
        { "in"     , ast::keyword_token::IN },
        { "out"    , ast::keyword_token::OUT },
        { "inout"  , ast::keyword_token::INOUT },
        { "buffer" , ast::keyword_token::BUFFER },
        { "linkage", ast::keyword_token::LINKAGE }
    },
    "mode"
);
// clang-format on

}  // namespace detail

// clang-format off
auto const mode_def =
    distinct(detail::mode_symbols)
    ;
// clang-format on

/// name ::=                                                        [LRM93 §6.1]
///       simple_name
///     | operator_symbol
///     | selected_name
///     | indexed_name
///     | slice_name
///     | attribute_name
// clang-format off
auto const name_def =
    // Note, using LRM BNF rule for selected_name results into left recursion, see
    // selected_name for details.
      simple_name
    | operator_symbol
    //    | selected_name
    //    | indexed_name // FixMe
    //    | slice_name
    //    | attribute_name
    ;
// clang-format on

/// next_statement ::=                                             [LRM93 §8.10]
///     [ label : ] next [ loop_label ] [ when condition ] ;
// clang-format off
auto const next_statement_def =
    -label_colon >> NEXT >> -label >> -(WHEN >> condition) >> x3::expect[';']
    ;
// clang-format on

/// null_statement ::=                                             [LRM93 §8.13]
///      [ label : ] null ;
// clang-format off
auto const null_statement_def =
    -label_colon >> omit[NULL_] >> x3::expect[';']
    ;
// clang-format on

/// numeric_literal ::=                                           [LRM93 §7.3.1]
///       abstract_literal
///     | physical_literal
// clang-format off
auto const numeric_literal_def =
    // --- order matters ---                                  
      physical_literal
    | abstract_literal
    ;
// clang-format on

#if 0  // UNUSED, no referrer in BNF (even unused declaration)
/// object_declaration ::=                                        [LRM93 §4.3.1]
///       constant_declaration
///     | signal_declaration
///     | variable_declaration
///     | file_declaration
auto const object_declaration_def =
      constant_declaration
    | signal_declaration
    | variable_declaration
    | file_declaration
    ;
#endif

/// operator_symbol ::=                                             [LRM93 §2.1]
///     string_literal
// clang-format off
auto const operator_symbol_def =
    string_literal
    ;
// clang-format on

/// options ::=                                                     [LRM93 §9.5]
///     [ guarded ] [ delay_mechanism ]
// clang-format off
auto const options_def =
    -GUARDED >> -delay_mechanism
    ;
// clang-format on

/// package_body ::=                                                [LRM93 §2.6]
///     package body package_simple_name is
///         package_body_declarative_part
///     end [ package body ] [ package_simple_name ] ;
// clang-format off
auto const package_body_def =
       PACKAGE >> BODY >> simple_name >> IS
    >> package_body_declarative_part
    >> END >> -(PACKAGE >> BODY) >> -simple_name
    >> x3::expect[';']
    ;
// clang-format on

/// package_body_declarative_item ::=                               [LRM93 §2.6]
///       subprogram_declaration
///     | subprogram_body
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | shared_variable_declaration
///     | file_declaration
///     | alias_declaration
///     | use_clause
///     | group_template_declaration
///     | group_declaration
// clang-format off
auto const package_body_declarative_item_def =
      subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | variable_declaration  // shared_variable_declaration
    | file_declaration
    | alias_declaration
    | use_clause
    | group_template_declaration
    | group_declaration
    ;
// clang-format on

/// package_body_declarative_part ::=                               [LRM93 §2.6]
///     { package_body_declarative_item }
// clang-format off
auto const package_body_declarative_part_def =
    *package_body_declarative_item
    ;
// clang-format on

/// package_declaration ::=                                         [LRM93 §2.5]
///     package identifier is
///         package_declarative_part
///     end [ package ] [ package_simple_name ] ;
// clang-format off
auto const package_declaration_def =
       PACKAGE >> identifier >> IS
    >> package_declarative_part
    >> END >> -PACKAGE >> -simple_name  // package_simple_name, aka identifier
    >> x3::expect[';']
    ;
// clang-format on

/// package_declarative_item ::=                                    [LRM93 §2.5]
///       subprogram_declaration
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | signal_declaration
///     | shared_variable_declaration
///     | file_declaration
///     | alias_declaration
///     | component_declaration
///     | attribute_declaration
///     | attribute_specification
///     | disconnection_specification
///     | use_clause
///     | group_template_declaration
///     | group_declaration
// clang-format off
auto const package_declarative_item_def =
      subprogram_declaration
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | variable_declaration  // shared_variable_declaration
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
// clang-format on

/// package_declarative_part ::=                                    [LRM93 §2.5]
///     { package_declarative_item }
// clang-format off
auto const package_declarative_part_def =
    *package_declarative_item
    ;
// clang-format on

/// parameter_specification ::=                                     [LRM93 §8.9]
///     identifier in discrete_range
// clang-format off
auto const parameter_specification_def =
    identifier >> omit[IN] >> discrete_range;
// clang-format on

/// physical_literal ::=                                          [LRM93 §3.1.3]
///     [ abstract_literal ] unit_name
namespace physical_literal_detail {

// Note, the LRM doesn't specify the allowed characters, hence it's assumed
// that it follows the natural conventions.
// clang-format off
auto const unit_name =
    x3::as<ast::string_span>[
        raw[
            lexeme[
                +(lower_case_letter | upper_case_letter)
            ]
        ]
    ]
    ;
// clang-format on

}  // namespace physical_literal_detail

// clang-format off
auto const physical_literal_def =
    -abstract_literal >> (physical_literal_detail::unit_name - keyword)
    ;
// clang-format on

/// physical_type_definition ::=                                  [LRM93 §3.1.3]
///     range_constraint
///         units
///             primary_unit_declaration
///             { secondary_unit_declaration }
///         end units [ physical_type_simple_name ]
// clang-format off
auto const physical_type_definition_def =
       range_constraint
    >> UNITS
    >> primary_unit_declaration
    >> *secondary_unit_declaration
    >> END >> UNITS >> -simple_name
    ;
// clang-format on

///
/// port_clause                                                   [LRM93 §1.1.1]
///
/// \code{.bnf}
/// port_clause ::=
///     port ( port_list ) ;
/// \endcode
// clang-format off
auto const port_clause_def =
    PORT >> '(' >> interface_list >> ')' >> x3::expect[';']
    ;
// clang-format on

#if 0  // DISABLED; embedded into port_clause
/// port_list ::=                                               [LRM93 §1.1.1.2]
///     port_interface_list
auto const port_list_def =
    interface_list
    ;
#endif

/// port_map_aspect ::=                                         [LRM93 §5.2.1.2]
///     port map ( port_association_list )
// clang-format off
auto const port_map_aspect_def =
    PORT >> MAP >> '(' >> association_list >> ')'
    ;
// clang-format on

/// prefix ::=                                                      [LRM93 §6.1]
///       name
///     | function_call
// clang-format off
auto const prefix_def =
      name
    | function_call
    ;
// clang-format on

/// primary ::=                                                     [LRM93 §7.1]
///       name
///     | literal
///     | aggregate
///     | function_call
///     | qualified_expression
///     | type_conversion
///     | allocator
///     | ( expression )
// clang-format off
auto const primary_def =
    // Order matters; if aggregate is prior expression as of the BNF, a
    // backtracking problem occurred at:
    // aggregate -> element_association -> choices
    // --- order matters ---    
      !char_('"') >> name  // ignore string_literals which follow below
    | literal
    | function_call
    | qualified_expression
//  | type_conversion
    | allocator
    | ( '(' >> expression >> ')' )
    | aggregate
    ;
// clang-format on

/// primary_unit ::=                                               [LRM93 §11.1]
///       entity_declaration
///     | configuration_declaration
///     | package_declaration
// clang-format off
auto const primary_unit_def =
      entity_declaration
    | configuration_declaration
    | package_declaration
    ;
// clang-format on

/// primary_unit_declaration ::=
///     identifier ;
// clang-format off
auto const primary_unit_declaration_def =
    identifier >> x3::expect[';']
    ;
// clang-format on

/// procedure_call ::=                                              [LRM93 §8.6]
///     procedure_name [ ( actual_parameter_part ) ]
// clang-format off
auto const procedure_call_def =
    name >> -( '(' >> actual_parameter_part >> ')' )
    ;
// clang-format on

/// procedure_call_statement ::=                                    [LRM93 §8.6]
///     [ label : ] procedure_call ;
// clang-format off
auto const procedure_call_statement_def =
    -label_colon >> procedure_call >> x3::expect[';']
    ;
// clang-format on

/// process_declarative_item ::=                                    [LRM93 §9.2]
///       subprogram_declaration
///     | subprogram_body
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | variable_declaration
///     | file_declaration
///     | alias_declaration
///     | attribute_declaration
///     | attribute_specification
///     | use_clause
///     | group_template_declaration
///     | group_declaration
// clang-format off
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
// clang-format on

/// process_declarative_part ::=                                    [LRM93 §9.2]
///     { process_declarative_item }
// clang-format off
auto const process_declarative_part_def =
    *process_declarative_item
    ;
// clang-format on

/// process_statement ::=                                           [LRM93 §9.2]
///     [ process_label : ]
///         [ postponed ] process [ ( sensitivity_list ) ] [ is ]
///             process_declarative_part
///         begin
///             process_statement_part
///         end [ postponed ] process [ process_label ] ;
// clang-format off
auto const process_statement_def =
       -label_colon
    >> -POSTPONED >> PROCESS >> -('(' >> sensitivity_list >> ')') >> -IS
    >> process_declarative_part
    >> BEGIN
    >> process_statement_part
    >> END >> -POSTPONED >> PROCESS >> -label
    >> x3::expect[';']
    ;
// clang-format on

/// process_statement_part ::=                                      [LRM93 §9.2]
///     { sequential_statement }
// clang-format off
auto const process_statement_part_def =
    sequence_of_statements
    ;
// clang-format on

/// qualified_expression ::=                                      [LRM93 §7.3.4]
///       type_mark ' ( expression )
///     | type_mark ' aggregate
// clang-format off
auto const qualified_expression_def =
    // Note: This BNF rule is ambiguous, since
    // aggregate           ::= ( element_association { , element_association } )
    // element_association ::= [ choices => ] expression
    // again. AST node takes care on this.
    type_mark >> "\'" >> ( ( "(" >> expression >> ")" ) | aggregate )
    ;
// clang-format on

///
/// range [LRM93 §3.1]
///
/// \note The order is changed to get the longest match, since simple_expression
///       can also be a name as of range_attribute_name
///
/// \code{.bnf}
/// range ::=
///       range_attribute_name
///     | simple_expression direction simple_expression
/// \endcode
namespace detail {

// clang-format off
auto const range_expression = x3::rule<struct _, ast::range_expression>{ "range_expression" } =
    simple_expression >> direction >> simple_expression
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const range_def =
    // --- order matters ---                        
      detail::range_expression
    | attribute_name
    ;
// clang-format on

///
/// range_constraint                                                [LRM93 §3.1]
///
/// \code{.bnf}
/// range_constraint ::=
///     range range
/// \endcode
// clang-format off
auto const range_constraint_def =
    RANGE >> range
    ;
// clang-format on

/// record_type_definition ::=                                    [LRM93 §3.2.2]
///     record
///         element_declaration
///         { element_declaration }
///     end record [ record_type_simple_name ]
// clang-format off
auto const record_type_definition_def =
       RECORD
    >> +element_declaration
    >> END >> RECORD >> -simple_name
    ;
// clang-format on

/// relation ::=                                                    [LRM93 §7.1]
///     shift_expression [ relational_operator shift_expression ]
namespace relation_detail {

// clang-format off
auto const chunk = x3::rule<struct _, ast::relation::chunk>{ "relation" } =
    relational_operator >> shift_expression;
// clang-format on

}  // namespace relation_detail

// clang-format off
auto const relation_def =
    shift_expression >> -relation_detail::chunk
    ;
// clang-format on

/// report_statement ::=                                            [LRM93 §8.3]
///     [ label : ]
///     report expression
///     [ severity expression ] ;
// clang-format off
auto const report_statement_def =
    -label_colon >> (REPORT >> expression) >> -(SEVERITY >> expression) >> x3::expect[';']
    ;
// clang-format on

/// return_statement ::=                                           [LRM93 §8.12]
///     [ label : ] return [ expression ] ;
// clang-format off
auto const return_statement_def =
    -label_colon >> RETURN >> -expression >> x3::expect[';']
    ;
// clang-format on

/// scalar_type_definition ::=                                      [LRM93 §3.1]
///       enumeration_type_definition   | integer_type_definition
///     | floating_type_definition      | physical_type_definition
// clang-format off
auto const scalar_type_definition_def =
    // --- order matters ---                                         
      physical_type_definition
    | enumeration_type_definition
    | range_constraint  // {integer,floating}_type_definition
    ;
// clang-format on

/// secondary_unit ::=                                             [LRM93 §11.1]
///       architecture_body
///     | package_body
// clang-format off
auto const secondary_unit_def =
      architecture_body
    | package_body
    ;
// clang-format on

/// secondary_unit_declaration ::=                                [LRM93 §3.1.3]
///     identifier = physical_literal ;
// clang-format off
auto const secondary_unit_declaration_def =
    identifier >> "=" >> physical_literal >> x3::expect[';']
    ;
// clang-format on

/// selected_name                                                   [LRM93 §6.3]
///
/// @code{.bnf}
/// selected_name ::=
///     prefix . suffix
/// @endcode
///
/// LRM93 [§6.3] defined a concept of an expanded name: A selected name (in
/// the syntactic sense) that denotes one or all of the primary units in a
/// library or any named entity within a primary unit.
/// [...]
/// The prefix of an expanded name may not be a function call.
///
/// The BNF rule results into recursive calling of prefix (which is a name).
///
/// @code{.bnf}
/// selected_name ::= prefix . suffix
/// prefix        ::= name | function_call
/// name          ::= ... | selected_name | ...
/// suffix        ::= simple_name | character_literal | operator_symbol | ALL
/// @endcode
///
/// The solution is to mimic the prefix without the name self (limit the name
/// rules). This allows the name to be selected_name too. No rewrote of the name
/// rule so far.

namespace detail {

struct name_class_;
struct prefix_class_;

using name_type = x3::rule<struct name_class_, ast::name>;
using prefix_list_type = x3::rule<struct prefix_class_, std::vector<ast::prefix>>;

name_type const name{ "name" };
prefix_list_type const prefix{ "prefix" };

// clang-format off
auto const name_def =
      simple_name
    | operator_symbol
//  | indexed_name
//  | slice_name
//  | attribute_name
    ;
// clang-format on

// function_call doesn't make sense here
// clang-format off
auto const prefix_def =
    x3::repeat(1, 2)[name % '.']
    ;
// clang-format on

BOOST_SPIRIT_DEFINE(name)
BOOST_SPIRIT_DEFINE(prefix)

}  // namespace detail

// clang-format off
auto const selected_name_def =
    x3::lexeme[prefix >> '.' >> suffix]
    ;
// clang-format on

/// selected_signal_assignment ::=                                [LRM93 §9.5.2]
///     with expression select
///         target    <= options selected_waveforms ;
// clang-format off
auto const selected_signal_assignment_def =
       WITH >> expression >> SELECT
    >> target >> "<=" >> options >> selected_waveforms >> x3::expect[';']
    ;
// clang-format on

/// selected_waveforms ::=                                        [LRM93 §9.5.2]
///     { waveform when choices , }
///     waveform when choices
// clang-format off
auto const selected_waveforms_def =
    (waveform >> WHEN >> choices) % ','
    ;
// clang-format on

/// sensitivity_clause ::=                                          [LRM93 §8.1]
///     on sensitivity_list
// clang-format off
auto const sensitivity_clause_def =
    ON >> sensitivity_list
    ;
// clang-format on

/// sensitivity_list ::=                                            [LRM93 §8.1]
///     signal_name { , signal_name }
// clang-format off
auto const sensitivity_list_def =
    name % ',';
// clang-format on

/// sequence_of_statements ::=                                        [LRM93 §8]
///     { sequential_statement }
// clang-format off
auto const sequence_of_statements_def =
    *sequential_statement
    ;
// clang-format on

/// sequential_statement ::=                                          [LRM93 §8]
///       wait_statement
///     | assertion_statement
///     | report_statement
///     | signal_assignment_statement
///     | variable_assignment_statement
///     | procedure_call_statement
///     | if_statement
///     | case_statement
///     | loop_statement
///     | next_statement
///     | exit_statement
///     | return_statement
///     | null_statement
// clang-format off
auto const sequential_statement_def =
      wait_statement
    | assertion_statement
    | report_statement
    | signal_assignment_statement
    | variable_assignment_statement
//    | procedure_call_statement
    | if_statement
    | case_statement
    | loop_statement
    | next_statement
    | exit_statement
    | return_statement
    | null_statement
    ;
// clang-format on

/// shift_expression ::=                                            [LRM93 §7.1]
///     simple_expression [ shift_operator simple_expression ]
namespace shift_expression_detail {

// clang-format off
auto const chunk = x3::rule<struct _, ast::shift_expression::chunk>{ "shift_expression" } =
    shift_operator >> simple_expression
    ;
// clang-format on

}  // namespace shift_expression_detail

// clang-format off
auto const shift_expression_def =
    simple_expression >> -shift_expression_detail::chunk
    ;
// clang-format on

/// sign ::=                                                        [LRM93 §7.2]
///     + | -
// clang-format off
auto const sign_def =
       ("-" >> x3::attr(ast::operator_token::SIGN_NEG))
     | ("+" >> x3::attr(ast::operator_token::SIGN_POS))
     ;
// clang-format on

/// signal_assignment_statement ::=                                 [LRM93 §8.4]
///     [ label : ] target <= [ delay_mechanism ] waveform ;
// clang-format off
auto const signal_assignment_statement_def =
    // clang-format off
    -label_colon >> target >> "<=" >> -delay_mechanism >> waveform >> x3::expect[';']
    ;
// clang-format on

/// signal_declaration ::=                                      [LRM93 §4.3.1.2]
///     signal identifier_list : subtype_indication [ signal_kind ] [ := expression ] ;
// clang-format off
auto const signal_declaration_def =
       omit[SIGNAL] >> identifier_list >> ':'
    >> subtype_indication >> -signal_kind >> -(":=" >> expression) >> x3::expect[';']
    ;
// clang-format on

/// signal_kind ::=                                             [LRM93 §4.3.1.2]
///     register  |  bus
// clang-format off
auto const signal_kind_def =
      REGISTER
    | BUS
    ;
// clang-format on

/// signal_list ::=                                                 [LRM93 §5.3]
///       signal_name { , signal_name }
///     | others
///     | all
// clang-format off
auto const signal_list_def =
      (name % ',')
    | OTHERS
    | ALL
    ;
// clang-format on

/// signature ::=                                                 [LRM93 §2.3.2]
///     [ [ type_mark { , type_mark } ] [ return type_mark ] ]
// clang-format off
auto const signature_def =
    '[' >> -(type_mark % ',') >> -(RETURN >> type_mark) >> ']'
    ;
// clang-format on

/// simple_expression ::=
///     [ sign ] term { adding_operator term }
// clang-format off
auto const simple_expression_def =
    -sign >> term >> *(adding_operator >> term)
    ;
// clang-format on

/// simple_name ::=                                                 [LRM93 §6.2]
///     identifier
// clang-format off
auto const simple_name_def =
    identifier
    ;
// clang-format on

/// slice_name ::=                                                  [LRM93 §6.5]
///     prefix ( discrete_range )
// clang-format off
auto const slice_name_def =
    prefix >> '(' >> discrete_range >> ')'
    ;
// clang-format on

/// string_literal ::=                                             [LRM93 §13.6]
///     " { graphic_character } "
namespace string_literal_detail {

// clang-format off
auto const string_literal_1 = x3::rule<struct _, ast::string_span>{ "string_literal" } =
    x3::raw[
        *((graphic_character - '"') | (char_('"') >> '"'))
    ]
    ;
// clang-format on

// clang-format off
auto const string_literal_2 = x3::rule<struct _, ast::string_span>{ "string_literal" } =
    x3::raw[
        *((graphic_character - '%') | (char_('%') >> '%'))
    ]
    ;
// clang-format on

}  // namespace string_literal_detail

// clang-format off
auto const string_literal_def =
    lexeme[
          '"' >> x3::raw[string_literal_detail::string_literal_1] >> '"'
        | '%' >> x3::raw[string_literal_detail::string_literal_2] >> '%'
    ]
    ;
// clang-format on

/// subprogram_body ::=                                             [LRM93 §2.2]
///     subprogram_specification is
///         subprogram_declarative_part
///     begin
///         subprogram_statement_part
///     end [ subprogram_kind ] [ designator ] ;
// clang-format off
auto const subprogram_body_def =
       subprogram_specification >> IS
    >> subprogram_declarative_part
    >> BEGIN
    >> subprogram_statement_part
    >> END >> -subprogram_kind >> -designator >> x3::expect[';']
    ;
// clang-format on

/// subprogram_declaration ::=                                      [LRM93 §2.1]
///     subprogram_specification ;
// clang-format off
auto const subprogram_declaration_def =
     subprogram_specification >> x3::expect[';']
    ;
// clang-format on

/// subprogram_declarative_item ::=                                 [LRM93 §2.2]
///       subprogram_declaration
///     | subprogram_body
///     | type_declaration
///     | subtype_declaration
///     | constant_declaration
///     | variable_declaration
///     | file_declaration
///     | alias_declaration
///     | attribute_declaration
///     | attribute_specification
///     | use_clause
///     | group_template_declaration
///     | group_declaration
// clang-format off
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
// clang-format on

/// subprogram_declarative_part ::=                                 [LRM93 §2.2]
///     { subprogram_declarative_item }
// clang-format off
auto const subprogram_declarative_part_def =
    *subprogram_declarative_item
    ;
// clang-format on

/// subprogram_kind ::=                                             [LRM93 §2.2]
///     procedure | function
// clang-format off
auto const subprogram_kind_def =
      distinct("procedure", ast::keyword_token::PROCEDURE)
    | distinct("function", ast::keyword_token::FUNCTION)
    ;
// clang-format on

/// subprogram_specification ::=                                    [LRM93 §2.1]
///       procedure designator [ ( formal_parameter_list ) ]
///     | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
///       return type_mark
namespace subprogram_specification_detail {

// clang-format off
    // clang-format off
auto const procedure = x3::rule<struct _, ast::subprogram_specification_procedure>{"subprogram_specification.procedure"} =
    PROCEDURE >> designator >> -('(' >> formal_parameter_list >> ')')
    ;
// clang-format on

// clang-format off
auto const function = x3::rule<struct _, ast::subprogram_specification_function>{ "subprogram_specification.function" } =
        -(IMPURE | PURE) >> FUNCTION >> designator >> -('(' >> formal_parameter_list >> ')')
     >> RETURN >> type_mark
    ;
// clang-format on

}  // namespace subprogram_specification_detail

// clang-format off
auto const subprogram_specification_def =
      subprogram_specification_detail::procedure
    | subprogram_specification_detail::function
    ;
// clang-format on

/// subprogram_statement_part ::=                                   [LRM93 §2.2]
///     { sequential_statement }
// clang-format off
auto const subprogram_statement_part_def =
    sequence_of_statements
    ;
// clang-format on

/// subtype_declaration ::=
///     subtype identifier is subtype_indication ;
// clang-format off
auto const subtype_declaration_def =
    SUBTYPE >> identifier >> IS >> subtype_indication >> x3::expect[';']
    ;
// clang-format on

/// subtype_indication                                              [LRM93 §4.2]
///
/// @code{.bnf}
/// subtype_indication ::=
///     [ resolution_function_name ] type_mark [ constraint ]
/// @endcode
///
/// Parse a list of unspecified names, since:
///
/// @code{.bnf}
///      resolution_function_name ::= name
///      type_mark                ::= type_name | subtype_name
/// @endcode
///
/// is ambiguous, even with optional. Nevertheless, syntactically
/// resolution_function_name and type_mark are names, semantically matters on
/// context as of VHDL.
/// Further more, 2nd name can be a keyword (which can't be a name), hence
/// the alternative parse branch.
// clang-format off
auto const subtype_indication_def =
      (x3::repeat(1, 2)[
             name           // range as keyword can follow; name forbids keywords!
        ] >> -constraint)
    | (x3::repeat(1)[
             name           // mandatory type_mark ...
        ] >> -constraint    // followed by keyword RANGE ...
      )
    ;
// clang-format on

/// suffix ::=                                                      [LRM93 §6.3]
///       simple_name
///     | character_literal
///     | operator_symbol
///     | all
// clang-format off
auto const suffix_def =
      simple_name
    | character_literal
    | operator_symbol
    | ALL
    ;
// clang-format on

/// target ::=                                                      [LRM93 §8.4]
///       name
///     | aggregate
// clang-format off
auto const target_def =
      name
    | aggregate
    ;
// clang-format on

/// term                                                            [LRM93 §7.1]
///
/// @code{.bnf}
/// term ::=
///     factor { multiplying_operator factor }
/// @endcode
///
/// Note there is no expectation point: Consider the case of '-5 mod -3', where
/// mod is a multiplying operator with an higher operator precedence as the
/// sign operator. This is no valid VHDL and would in case of use of an
/// expectation point result into expectation_failure. See
/// 'test_case/expression_failure/expression_failure_003', or even the
/// [Sigasi: Be careful with VHDL operator precedence](
/// http://insights.sigasi.com/tech/be-careful-vhdl-operator-precedence.html)
// clang-format off
auto const term_def =
    factor >> *(multiplying_operator >> factor)
    ;
// clang-format on

/// timeout_clause ::=                                              [LRM93 §8.1]
///     for time_expression
// clang-format off
auto const timeout_clause_def =
    FOR >> expression
    ;
// clang-format on

/// type_conversion ::=                                           [LRM93 §7.3.5]
///     type_mark ( expression )
// clang-format off
auto const type_conversion_def =
    type_mark >> '(' >> expression >> ')'
    ;
// clang-format on

/// type_declaration                                                [LRM93 §4.1]
///
/// @code{.bnf}
/// type_declaration ::=
///       full_type_declaration
///     | incomplete_type_declaration
/// @endcode
///
/// Note, this node covers both alternatives from type_declaration BNF:
/// @code{.bnf}
/// full_type_declaration       ::= TYPE identifier IS type_definition ;
/// incomplete_type_declaration ::= TYPE identifier ;
/// @endcode
// clang-format off
auto const type_declaration_def =
    TYPE >> identifier >> -(IS >> type_definition) >> x3::expect[';']
    ;
// clang-format on

/// type_definition ::=                                             [LRM93 §4.1]
///       scalar_type_definition
///     | composite_type_definition
///     | access_type_definition
///     | file_type_definition
// clang-format off
auto const type_definition_def =
      scalar_type_definition
    | composite_type_definition
    | access_type_definition
    | file_type_definition
    ;
// clang-format on

/// type_mark
///
/// @code{.bnf}
/// type_mark ::=
///       type_name
///     | subtype_name
/// @endcode
///
/// There is no way to distinguish between type_name and subtype_name at
/// parser level. Further read
/// [Question about type_mark bnf](
/// https://groups.google.com/forum/#!topic/comp.lang.vhdl/exUhoMrFavU)
// clang-format off
auto const type_mark_def =
    name
    ;
// clang-format on

/// unconstrained_array_definition ::=                            [LRM93 §3.2.1]
///     array ( index_subtype_definition { , index_subtype_definition } )
///         of element_subtype_indication
// clang-format off
auto const unconstrained_array_definition_def =
    ARRAY >> '(' >> (index_subtype_definition % ',') >> ')' >> OF >> subtype_indication
    ;
// clang-format on

/// use_clause                                                     [LRM93 §10.4]
///
/// @code{.bnf}
/// use_clause ::=
///     use selected_name { , selected_name } ;
/// @endcode
///
/// LRM93 [§6.3] defined a concept of an expanded name: A selected name (in
/// the syntactic sense) that denotes one or all of the primary units in a
/// library or any named entity within a primary unit.
/// [...]
/// The prefix of an expanded name may not be a function call.
///
/// For the use clause hence a specialized version is required. See Notes
/// at the AST node ast::use_clause.
namespace use_clause_detail {

// clang-format off
auto const lib_prefix = x3::rule<struct _, std::vector<ast::name>>{ "prefix" } =
    x3::lexeme[name >> '.' >> name]
    ;
// clang-format on

// clang-format off
auto const pkg_prefix = x3::rule<struct _, std::vector<ast::name>>{ "prefix" } =
    x3::repeat(1)[  // enforce artificial vector to unify ast node
        name
    ]
    ;
// clang-format on

// clang-format off
auto const lib_selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected_name" } =
    // clang-format on
    // clang-format off
    x3::lexeme[lib_prefix >> '.' >> suffix]
    ;
// clang-format on

// clang-format off
auto const pkg_selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected_name" } =
    // clang-format on
    // clang-format off
    x3::lexeme[pkg_prefix >> '.' >> suffix]
    ;
// clang-format on

// clang-format off
auto const selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected_name" } =
    lib_selected_name | pkg_selected_name;
// clang-format on

}  // namespace use_clause_detail

// clang-format off
auto const use_clause_def =
    USE >> (use_clause_detail::selected_name % ',') >> x3::expect[';']
    ;
// clang-format on

/// variable_assignment_statement ::=                               [LRM93 §8.5]
///     [ label : ] target  := expression ;
// clang-format off
auto const variable_assignment_statement_def =
    -label_colon >> target >> ":=" >> expression >> x3::expect[';']
    ;
// clang-format on

/// variable_declaration ::=                                    [LRM93 §4.3.1.3]
///     [ shared ] variable identifier_list : subtype_indication [ := expression ] ;
// clang-format off
auto const variable_declaration_def =
        -SHARED >> omit[VARIABLE] >> identifier_list >> ':'
     >> subtype_indication >> -(":=" >> expression) >> x3::expect[';']
    ;
// clang-format on

/// wait_statement ::=                                              [LRM93 §8.1]
///     [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ] ;
// clang-format off
auto const wait_statement_def =
     -label_colon >> WAIT >> -sensitivity_clause >> -condition_clause >> -timeout_clause >> x3::expect[';']
    ;
// clang-format on

/// waveform ::=                                                    [LRM93 §8.4]
///       waveform_element { , waveform_element }
///     | unaffected
// clang-format off
auto const waveform_def =
      (waveform_element % ',')
    | UNAFFECTED
    ;
// clang-format on

///
/// waveform_element                                              [LRM93 §8.4.1]
/// [LRM93 §8.4.1](https://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_8.HTM#8.4)
///
/// \code{.bnf}
/// waveform_element ::=
///       value_expression [ after time_expression ]
///     | null [ after time_expression ]
/// \endcode
// clang-format off
auto const waveform_element_def =
    (expression | NULL_) >> -(AFTER >> expression)
    ;
// clang-format on

}  // namespace ibis::vhdl::parser

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)

//******************************************************************************
// Spirit.X3 BNF Rule Definitions
//
namespace ibis::vhdl::parser {

#include <ibis/util/compiler/warnings_off.hpp>

// clang-format off
BOOST_SPIRIT_DEFINE(  // -- A --
      abstract_literal
    , access_type_definition
    , actual_designator
    , actual_parameter_part
    , actual_part
    , aggregate
    , alias_declaration
    , alias_designator
    , allocator
    , architecture_body
    , architecture_declarative_part
    , architecture_statement_part
    , array_type_definition
    , assertion
    , assertion_statement
    , association_element
    , association_list
    , attribute_declaration
    , attribute_designator
    , attribute_name
    , attribute_specification
)
BOOST_SPIRIT_DEFINE(  // -- B --
    // base
      based_integer
    , based_literal
    //, basic_character
    , basic_graphic_character
    , basic_identifier
    , binding_indication
    , bit_string_literal
    , block_configuration
    , block_declarative_item
    , block_declarative_part
    , block_header
    , block_specification
    , block_statement
    , block_statement_part
)
BOOST_SPIRIT_DEFINE(  // -- C --
      case_statement
    , case_statement_alternative
    , character_literal
    , choice
    , choices
    , component_configuration
    , component_declaration
    , component_instantiation_statement
    , component_specification
    , composite_type_definition
    , concurrent_assertion_statement
    , concurrent_procedure_call_statement
    , concurrent_signal_assignment_statement
    , concurrent_statement
    , condition
    , condition_clause
    , conditional_signal_assignment
    , conditional_waveforms
    , configuration_declaration
    , configuration_declarative_item
    , configuration_declarative_part
    , configuration_item
    , configuration_specification
    , constant_declaration
    , constrained_array_definition
    , constraint
    , context_clause
    , context_item
)
BOOST_SPIRIT_DEFINE(  // -- D --
      decimal_literal
    , delay_mechanism
    , design_file
    , design_unit
    , designator
    , direction
    , disconnection_specification
    , discrete_range
)
BOOST_SPIRIT_DEFINE(  // -- E --
      element_association
    , element_declaration
    , element_subtype_definition
    , entity_aspect
    , entity_class
    , entity_class_entry
    , entity_class_entry_list
    , entity_declaration
    , entity_declarative_item
    , entity_declarative_part
    , entity_designator
    , entity_header
    , entity_name_list
    , entity_specification
    , entity_statement
    , entity_statement_part
    , entity_tag
    , enumeration_literal
    , enumeration_type_definition
    , exit_statement
    , exponent
    , expression
    , extended_identifier
)
BOOST_SPIRIT_DEFINE(  // -- F --
      factor
    , file_declaration
    , file_logical_name
    , file_open_information
    , file_type_definition
    //EMBEDDED, floating_type_definition
    , formal_designator
    , formal_parameter_list
    , formal_part
    //EMBEDDED, full_type_declaration
    , function_call
)
BOOST_SPIRIT_DEFINE(  // -- G --
      generate_statement
    , generation_scheme
    , generic_clause
    , generic_map_aspect
    , graphic_character
    , group_constituent
    , group_constituent_list
    , group_template_declaration
    , group_declaration
    , guarded_signal_specification
)
BOOST_SPIRIT_DEFINE(  // -- I --
      identifier
    , identifier_list
    , if_statement
    //EMBEDDED, incomplete_type_declaration
    , index_constraint
    , index_specification
    , index_subtype_definition
    , indexed_name
    , instantiated_unit
    , instantiation_list
    , integer
    // EMBEDDED, integer_type_definition
    , interface_constant_declaration
    , interface_declaration
    , interface_element
    , interface_file_declaration
    , interface_list
    , interface_signal_declaration
    , interface_variable_declaration
    , iteration_scheme
)
BOOST_SPIRIT_DEFINE(  // -- L --
      label
    , letter
    , letter_or_digit
    , library_clause
    , library_unit
    , literal
    , logical_name
    , logical_name_list
    , loop_statement
)
BOOST_SPIRIT_DEFINE(  // -- M --
      mode
)
BOOST_SPIRIT_DEFINE(  // -- N --
      name
    , next_statement
    , null_statement
    , numeric_literal
)
BOOST_SPIRIT_DEFINE(  // -- O --
      operator_symbol
    , options
)
BOOST_SPIRIT_DEFINE(  // -- P --
      package_body
    , package_body_declarative_item
    , package_body_declarative_part
    , package_declaration
    , package_declarative_item
    , package_declarative_part
    , parameter_specification
    , physical_literal
    , physical_type_definition
    , port_clause
    , port_map_aspect
    , prefix
    , primary
    , primary_unit
    , primary_unit_declaration
    , procedure_call
    , procedure_call_statement
    , process_declarative_item
    , process_declarative_part
    , process_statement
    , process_statement_part
)
BOOST_SPIRIT_DEFINE(  // -- Q --
      qualified_expression
)
BOOST_SPIRIT_DEFINE(  // -- R --
      range
    , range_constraint
    , record_type_definition
    , relation
    , report_statement
    , return_statement
)
BOOST_SPIRIT_DEFINE(  // -- S --
      scalar_type_definition
    , secondary_unit
    , secondary_unit_declaration
    , selected_name
    , selected_signal_assignment
    , selected_waveforms
    , sensitivity_clause
    , sensitivity_list
    , sequence_of_statements
    , sequential_statement
    , shift_expression
    , sign
    , signal_assignment_statement
    , signal_declaration
    , signal_kind
    , signal_list
    , signature
    , simple_expression
    , simple_name
    , slice_name
    , string_literal
    , subprogram_body
    , subprogram_declaration
    , subprogram_declarative_item
    , subprogram_declarative_part
    , subprogram_kind
    , subprogram_specification
    , subprogram_statement_part
    , subtype_declaration
    , subtype_indication
    , suffix
)
BOOST_SPIRIT_DEFINE(  // -- T --
      target
    , term
    , timeout_clause
    , type_conversion
    , type_declaration
    , type_definition
    , type_mark
)
BOOST_SPIRIT_DEFINE(  // -- U --
      unconstrained_array_definition
    , use_clause
)
BOOST_SPIRIT_DEFINE(  // -- V --
      variable_assignment_statement
    , variable_declaration
)
BOOST_SPIRIT_DEFINE(  // -- W --
      wait_statement
    , waveform
    , waveform_element
)
// clang-format on

#include <ibis/util/compiler/warnings_on.hpp>

#endif  // !defined(DOXYGEN_DOCUMENTATION_BUILD)
}

//******************************************************************************
// Annotation and Error handling
//
// Here the "classic" approach from spirit x3's examples/documentation is used:
// Derive the tag class from success "handler" to tag the node self and from
// error "handler" to cope with parser/expectation exceptions using on_error()
// member function.
// Possible is also to cope with specific error handling as shown by
// - Code Vamping's Blog [Spirit X3 Error Handling: V3 - Tag and release](
//    https://www.codevamping.com/2018/12/spirit-x3-error-handling/)
// - or even [Custom error on rule level? #657](
//   https://github.com/boostorg/spirit/issues/657)
//
namespace ibis::vhdl::parser {

// clang-format off
struct abstract_literal_class : success_handler {};
struct access_type_definition_class : success_handler {};
struct actual_designator_class : success_handler {};
struct actual_parameter_part_class : success_handler {};
struct actual_part_class : success_handler {};
struct aggregate_class : success_handler {};
struct alias_declaration_class : success_handler {};
struct alias_designator_class : success_handler {};
struct allocator_class : success_handler {};
struct architecture_body_class : success_handler {};
struct architecture_declarative_part_class : success_handler {};
struct architecture_statement_part_class : success_handler {};
struct array_type_definition_class : success_handler {};
struct assertion_class : success_handler {};
struct assertion_statement_class : success_handler {};
struct association_element_class : success_handler {};
struct association_list_class : success_handler {};
struct attribute_declaration_class : success_handler {};
struct attribute_designator_class : success_handler {};
struct attribute_name_class : success_handler {};
struct attribute_specification_class : success_handler {};
struct base_class : success_handler {};
struct based_integer_class : success_handler {};
struct based_literal_class : success_handler, based_literal_detail::based_literal_error_handler {};
// struct basic_graphic_character_class : success_handler {};    // char isn't tagable
struct basic_identifier_class : success_handler {};
struct binding_indication_class : success_handler {};
struct bit_string_literal_class : success_handler {};
struct block_configuration_class : success_handler {};
struct block_declarative_item_class : success_handler {};
struct block_declarative_part_class : success_handler {};
struct block_header_class : success_handler {};
struct block_specification_class : success_handler {};
struct block_statement_class : success_handler {};
struct block_statement_part_class : success_handler {};
struct case_statement_class : success_handler {};
struct case_statement_alternative_class : success_handler {};
struct character_literal_class : success_handler {};
struct choice_class : success_handler {};
struct choices_class : success_handler {};
struct component_configuration_class : success_handler {};
struct component_declaration_class : success_handler {};
struct component_instantiation_statement_class : success_handler {};
struct component_specification_class : success_handler {};
struct composite_type_definition_class : success_handler {};
struct concurrent_assertion_statement_class : success_handler {};
struct concurrent_procedure_call_statement_class : success_handler {};
struct concurrent_signal_assignment_statement_class : success_handler {};
struct concurrent_statement_class : success_handler {};
struct condition_class : success_handler {};
struct condition_clause_class : success_handler {};
struct conditional_signal_assignment_class : success_handler {};
struct conditional_waveforms_class : success_handler {};
struct configuration_declaration_class : success_handler {};
struct configuration_declarative_item_class : success_handler {};
struct configuration_declarative_part_class : success_handler {};
struct configuration_item_class : success_handler {};
struct configuration_specification_class : success_handler {};
struct constant_declaration_class : success_handler {};
struct constrained_array_definition_class : success_handler {};
struct constraint_class : success_handler {};
struct context_clause_class : success_handler {};
struct context_item_class : success_handler {};
struct decimal_literal_class : success_handler {};
struct delay_mechanism_class : success_handler {};
struct design_file_class : success_handler, error_handler {}; // our start rule
struct design_unit_class : success_handler {};
struct designator_class : success_handler {};
struct direction_class : success_handler {};
struct disconnection_specification_class : success_handler {};
struct discrete_range_class : success_handler {};
struct element_association_class : success_handler {};
struct element_declaration_class : success_handler {};
struct element_subtype_definition_class : success_handler {};
struct entity_aspect_class : success_handler {};
struct entity_class_class : success_handler {};
struct entity_class_entry_class : success_handler {};
struct entity_class_entry_list_class : success_handler {};
struct entity_declaration_class : success_handler {};
struct entity_declarative_item_class : success_handler {};
struct entity_declarative_part_class : success_handler {};
struct entity_designator_class : success_handler {};
struct entity_header_class : success_handler {};
struct entity_name_list_class : success_handler {};
struct entity_specification_class : success_handler {};
struct entity_statement_class : success_handler {};
struct entity_statement_part_class : success_handler {};
struct entity_tag_class : success_handler {};
struct enumeration_literal_class : success_handler {};
struct enumeration_type_definition_class : success_handler {};
struct exit_statement_class : success_handler {};
struct exponent_class : success_handler {};
struct expression_class : success_handler {};
struct extended_identifier_class : success_handler {};
struct factor_class : success_handler {};
struct file_declaration_class : success_handler {};
struct file_logical_name_class : success_handler {};
struct file_open_information_class : success_handler {};
struct file_type_definition_class : success_handler {};
struct formal_designator_class : success_handler {};
struct formal_parameter_list_class : success_handler {};
struct formal_part_class : success_handler {};
struct function_call_class : success_handler {};
struct generate_statement_class : success_handler {};
struct generation_scheme_class : success_handler {};
struct generic_clause_class : success_handler {};
struct generic_list_class : success_handler {};
struct generic_map_aspect_class : success_handler {};
// struct graphic_character_class : success_handler {};     // char isn't tagable
struct group_constituent_class : success_handler {};
struct group_constituent_list_class : success_handler {};
struct group_template_declaration_class : success_handler {};
struct group_declaration_class : success_handler {};
struct guarded_signal_specification_class : success_handler {};
struct identifier_class : success_handler {};
struct identifier_list_class : success_handler {};
struct if_statement_class : success_handler {};
struct index_constraint_class : success_handler {};
struct index_specification_class : success_handler {};
struct index_subtype_definition_class : success_handler {};
struct indexed_name_class : success_handler {};
struct instantiated_unit_class : success_handler {};
struct instantiation_list_class : success_handler {};
struct integer_class : success_handler {};
struct interface_constant_declaration_class : success_handler {};
struct interface_declaration_class : success_handler {};
struct interface_element_class : success_handler {};
struct interface_file_declaration_class : success_handler {};
struct interface_list_class : success_handler {};
struct interface_signal_declaration_class : success_handler {};
struct interface_variable_declaration_class : success_handler {};
struct iteration_scheme_class : success_handler {};
struct label_class : success_handler {};
struct letter_class : success_handler {};
struct letter_or_digit_class : success_handler {};
struct library_clause_class : success_handler {};
struct library_unit_class : success_handler {};
struct literal_class : success_handler {};
struct logical_name_class : success_handler {};
struct logical_name_list_class : success_handler {};
struct loop_statement_class : success_handler {};
struct mode_class : success_handler {};
struct name_class : success_handler {};
struct next_statement_class : success_handler {};
struct null_statement_class : success_handler {};
struct numeric_literal_class : success_handler {};
struct operator_symbol_class : success_handler {};
struct options_class : success_handler {};
struct package_body_class : success_handler {};
struct package_body_declarative_item_class : success_handler {};
struct package_body_declarative_part_class : success_handler {};
struct package_declaration_class : success_handler {};
struct package_declarative_item_class : success_handler {};
struct package_declarative_part_class : success_handler {};
struct parameter_specification_class : success_handler {};
struct physical_literal_class : success_handler {};
struct physical_type_definition_class : success_handler {};
struct port_clause_class : success_handler {};
struct port_list_class : success_handler {};
struct port_map_aspect_class : success_handler {};
struct prefix_class : success_handler {};
struct primary_class : success_handler {};
struct primary_unit_class : success_handler {};
struct primary_unit_declaration_class : success_handler {};
struct procedure_call_class : success_handler {};
struct procedure_call_statement_class : success_handler {};
struct process_declarative_item_class : success_handler {};
struct process_declarative_part_class : success_handler {};
struct process_statement_class : success_handler {};
struct process_statement_part_class : success_handler {};
struct qualified_expression_class : success_handler {};
struct range_class : success_handler {};
struct range_constraint_class : success_handler {};
struct record_type_definition_class : success_handler {};
struct relation_class : success_handler {};
struct report_statement_class : success_handler {};
struct return_statement_class : success_handler {};
struct scalar_type_definition_class : success_handler {};
struct secondary_unit_class : success_handler {};
struct secondary_unit_declaration_class : success_handler {};
struct selected_name_class : success_handler {};
struct selected_signal_assignment_class : success_handler {};
struct selected_waveforms_class : success_handler {};
struct sensitivity_clause_class : success_handler {};
struct sensitivity_list_class : success_handler {};
struct sequence_of_statements_class : success_handler {};
struct sequential_statement_class : success_handler {};
struct shift_expression_class : success_handler {};
struct sign_class : success_handler {};
struct signal_assignment_statement_class : success_handler {};
struct signal_declaration_class : success_handler {};
struct signal_kind_class : success_handler {};
struct signal_list_class : success_handler {};
struct signature_class : success_handler {};
struct simple_expression_class : success_handler {};
struct simple_name_class : success_handler {};
struct slice_name_class : success_handler {};
struct string_literal_class : success_handler {};
struct subprogram_body_class : success_handler {};
struct subprogram_declaration_class : success_handler {};
struct subprogram_declarative_item_class : success_handler {};
struct subprogram_declarative_part_class : success_handler {};
struct subprogram_kind_class : success_handler {};
struct subprogram_specification_class : success_handler {};
struct subprogram_statement_part_class : success_handler {};
struct subtype_declaration_class : success_handler {};
struct subtype_indication_class : success_handler {};
struct suffix_class : success_handler {};
struct target_class : success_handler {};
struct term_class : success_handler {};
struct timeout_clause_class : success_handler {};
struct type_conversion_class : success_handler {};
struct type_declaration_class : success_handler {};
struct type_definition_class : success_handler {};
struct type_mark_class : success_handler {};
struct unconstrained_array_definition_class : success_handler {};
struct use_clause_class : success_handler {};
struct variable_assignment_statement_class : success_handler {};
struct variable_declaration_class : success_handler {};
struct wait_statement_class : success_handler {};
struct waveform_class : success_handler {};
struct waveform_element_class : success_handler {};
// clang-format on

}  // namespace ibis::vhdl::parser
