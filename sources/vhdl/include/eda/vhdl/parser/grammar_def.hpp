/*
 * grammar_def.h
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_DEF_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_DEF_HPP_

#include <eda/vhdl/parser/grammar.hpp>
#include <eda/vhdl/parser/grammar_id.hpp>
#include <eda/vhdl/parser/grammar_type.hpp>

#include <eda/vhdl/parser/on_error_base.hpp>
#include <eda/vhdl/parser/on_success_base.hpp>

#include <eda/vhdl/ast/ast_adapted.hpp>

#include <eda/support/boost/spirit_x3.hpp>
#include <eda/support/boost/spirit_x3_util.hpp>

namespace eda {
namespace vhdl {
namespace parser {
namespace detail {

/* distinct parser directive, but too specific (due to VHDL's character set
 * use here) to move it into spirit_x3_util header. */
struct distinct_directive {
    template <typename Parser> constexpr auto operator()(Parser&& parser) const
    {
        // clang-format off
        return x3::lexeme[
                   x3::no_case[ std::forward<Parser>(parser) ]
                >> !(x3::iso8859_1::alnum | '_')
            ];
        // clang-format on
    }

    template <typename Parser, typename Attr>
    constexpr auto operator()(Parser&& parser, Attr&& attr) const
    {
        // clang-format off
        return
               operator()(std::forward<Parser>(parser))
            >> x3::attr(std::forward<Attr>(attr))
            ;
        // clang-format off
    }
};

const distinct_directive distinct = { };


/* simplify literalize a symbol and return x3::lit() parser rule with given
 * attribute. Note, there is no overload without an attribute since it would
 * decay to X3's lit() parser self.  */
struct literal_attribute
{
    template<typename StrT, typename Attr>
    constexpr auto operator()(StrT&& str, Attr&& attr) const {
        // clang-format off
        return
               x3::lit(std::forward<StrT>(str))
            >> x3::attr(std::forward<Attr>(attr))
            ;
        // clang-format on
    }
};

const literal_attribute literal = {};

} // namespace detail
} // namespace parser
} // namespace vhdl
} // namespace eda

/*******************************************************************************
 * Keywords
 */
namespace eda {
namespace vhdl {
namespace parser {
namespace keywords {

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

/*
 * Symbols of all keyword to them distinguish from identifier by rule
 */
x3::symbols<> const keywords(
    // clang-format off
    {
        "abs", "access", "after", "alias", "all", "and", "architecture",
        "array", "assert", "attribute", "begin", "block", "body", "buffer",
        "bus", "case", "component", "configuration", "constant", "disconnect",
        "downto", "else", "elsif", "end", "entity", "exit", "file", "for",
        "function", "generate", "generic", "group", "guarded", "if", "impure",
        "in", "inertial", "inout", "is", "label",  "library", "linkage",
        "literal", "loop", "map", "mod", "nand", "new", "next", "nor", "not",
        "null", "of", "on",  "open", "or", "others", "out", "package", "port",
        "postponed", "procedure", "process", "pure", "range", "record",
        "register", "reject", "rem", "report", "return", "rol", "ror",
        "select", "severity", "signal", "shared", "sla", "sll", "sra", "srl",
        "subtype", "then", "to", "transport", "type", "unaffected", "units",
        "until", "use", "variable", "wait", "when", "while", "with", "xnor",
        "xor"
    },
    "keyword"
    // clang-format on
);

auto const keyword = x3::rule<struct _>{ "keyword" } = distinct(keywords);

} // namespace keywords
} // namespace parser
} // namespace vhdl
} // namespace eda

/*******************************************************************************
 * Operators
 */
namespace eda {
namespace vhdl {
namespace parser {
namespace operators {

/*
 * Operator Rule IDs
 */
struct binary_logical_operator_class;
struct unary_logical_operator_class;
struct binary_miscellaneous_operator_class;
struct unary_miscellaneous_operator_class;
struct multiplying_operator_class;
struct shift_operator_class;

/*
 * Rule Types
 */
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

/*
 * Rule Instances
 */
// clang-format off
binary_logical_operator_type const binary_logical_operator{ "logical_operator" };
unary_logical_operator_type const unary_logical_operator{ "logical_operator" };
binary_miscellaneous_operator_type const binary_miscellaneous_operator{ "miscellaneous_operator" };
unary_miscellaneous_operator_type const unary_miscellaneous_operator{ "miscellaneous_operator" };
multiplying_operator_type const multiplying_operator{ "multiplying_operator" };
shift_operator_type const shift_operator{ "shift_operator" };
// clang-format on

/*
 * Rule Definitions
 */
using detail::distinct;
using detail::literal;

// miscellaneous_operator ::=  ** | abs | not                       [LRM93 §7.2]
auto const EXPONENT = literal("**", ast::operator_token::EXPONENT);

auto const binary_miscellaneous_operator_def =
    // clang-format off
    EXPONENT
    ;
// clang-format on

auto const ABS = distinct("abs", ast::operator_token::ABS);
auto const NOT = distinct("not", ast::operator_token::NOT);

auto const unary_miscellaneous_operator_def =
    // clang-format off
    ABS | NOT
    ;
// clang-format on

// logical_operator ::=  and | or | nand | nor | xor | xnor         [LRM93 §7.2]
x3::symbols<ast::operator_token> const binary_logical_operator_symbols(
    // clang-format off
    {
        {"and",  ast::operator_token::AND},
        {"or",   ast::operator_token::OR},
        {"xor",  ast::operator_token::XOR},
        {"xnor", ast::operator_token::XNOR}
    },
    "logical_operator"
    // clang-format on
);

auto const binary_logical_operator_def = distinct(binary_logical_operator_symbols);

auto const NAND = distinct("nand", ast::operator_token::NAND);
auto const NOR = distinct("nor", ast::operator_token::NOR);

auto const unary_logical_operator_def =
    // clang-format off
    NAND | NOR
    ;
// clang-format on

// relational_operator ::=   =  |  /=  |  <  |  <=  |  >  |  >=     [LRM93 §7.2]
x3::symbols<ast::operator_token> const relational_operator(
    // clang-format off
    {
        {"=",  ast::operator_token::EQUAL},
        {"/=", ast::operator_token::NOT_EQUALS},
        {"<",  ast::operator_token::LESS},
        {"<=", ast::operator_token::LESS_EQUALS},
        {">",  ast::operator_token::GREATER},
        {">=", ast::operator_token::GREATER_EQUALS}
    },
    "relational_operator"
    // clang-format on
);

// adding_operator ::=  + | -  | &                                  [LRM93 §7.2]
x3::symbols<ast::operator_token> const adding_operator(
    // clang-format off
    {
        {"+", ast::operator_token::ADD},
        {"-", ast::operator_token::SUB},
        {"&", ast::operator_token::CONCAT}
    },
    "adding_operator"
    // clang-format on
);

// multiplying_operator ::=  * | / | mod | rem                      [LRM93 §7.2]

auto const MUL = literal("*", ast::operator_token::MUL);
auto const DIV = literal("/", ast::operator_token::DIV);
auto const MOD = distinct("mod", ast::operator_token::MOD);
auto const REM = distinct("rem", ast::operator_token::REM);

auto const multiplying_operator_def =
    // clang-format off
    MUL | DIV | MOD | REM
    ;
// clang-format on

// shift_operator ::=  sll | srl | sla | sra | rol | ror            [LRM93 §7.2]
x3::symbols<ast::operator_token> const shift_operator_symbols(
    // clang-format off
    {
        {"sll", ast::operator_token::SLL},
        {"srl", ast::operator_token::SRL},
        {"sla", ast::operator_token::SLA},
        {"sra", ast::operator_token::SRA},
        {"rol", ast::operator_token::ROL},
        {"ror", ast::operator_token::ROR}
    },
    "shift_operator"
    // clang-format on
);

auto const shift_operator_def = distinct(shift_operator_symbols);

/* special boost.spirit.x3 header to get rid off the annoying unused parameter
 * warnings from x3 */
#include <eda/compiler/warnings_off.hpp>

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

#include <eda/compiler/warnings_on.hpp>

} // namespace operators
} // namespace parser
} // namespace vhdl
} // namespace eda

/*******************************************************************************
 * Rule Instances
 */
namespace eda {
namespace vhdl {
namespace parser {

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
base_type const base { "base" };
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
//floating_type_definition_type const floating_type_definition { "floating_type_definition" };
formal_designator_type const formal_designator { "formal_designator" };
formal_parameter_list_type const formal_parameter_list { "formal_parameter_list" };
formal_part_type const formal_part { "formal_part" };
//full_type_declaration_type const full_type_declaration { "full_type_declaration" };
function_call_type const function_call { "function_call" };
generate_statement_type const generate_statement { "generate_statement" };
generation_scheme_type const generation_scheme { "generation_scheme" };
generic_clause_type const generic_clause { "generic_clause" };
//generic_list_type const generic_list { "generic_list" };
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
//incomplete_type_declaration_type const incomplete_type_declaration { "incomplete_type_declaration" };
index_constraint_type const index_constraint { "index_constraint" };
index_specification_type const index_specification { "index_specification" };
index_subtype_definition_type const index_subtype_definition { "index_subtype_definition" };
indexed_name_type const indexed_name { "indexed_name" };
instantiated_unit_type const instantiated_unit { "instantiated_unit" };
instantiation_list_type const instantiation_list { "instantiation_list" };
integer_type const integer { "integer" };
//integer_type_definition_type const integer_type_definition { "integer_type_definition" };
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
//port_list_type const port_list { "port_list" };
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

} // namespace parser
} // namespace vhdl
} // namespace eda


/*******************************************************************************
 * Spirit.X3 BNF Rules
 */
namespace eda {
namespace vhdl {
namespace parser {

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

// clang-format off

/*
 * Character Sets                                                  [LRM93 §13.1]
 */
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


#if 0
// basic_character ::=
// basic_graphic_character | format_effector
auto const basic_character_def =
        basic_graphic_character | format_effector
        ;
#endif


// basic_graphic_character ::=                                     [LRM93 §13.1]
// upper_case_letter | digit | special_character| space_character
auto const basic_graphic_character_def =
        upper_case_letter
      | digit
      | special_character
      | space_character
      ;


// extended_digit ::=                                            [LRM93 §13.4.2]
// digit | letter
auto const extended_digit =
    x3::rule<struct _, char> { "extended_digit" } =
        char_("0-9a-fA-F");


// graphic_character ::=                                           [LRM93 §13.1]
// basic_graphic_character | lower_case_letter | other_special_character
auto const graphic_character_def =
      basic_graphic_character
    | lower_case_letter
    | other_special_character
    ;


// letter ::=                                                    [LRM93 §13.3.1]
// upper_case_letter | lower_case_letter
auto const letter_def =
    upper_case_letter | lower_case_letter
    ;



// letter_or_digit ::=                                           [LRM93 §13.3.1]
// letter | digit
auto const letter_or_digit_def =
    letter | digit
    ;




/*
 * Common aliases used in BNF
 */

// Convenience rule for 'label :'
auto const label_colon = x3::rule<struct _, ast::identifier> { "label" } =
       label
    >> lexeme[ ':' >> !char_('=')]  // exclude ":=" variable assignment
    ;


/*
 * Parser Rule Definition
 * ======================
 *
 * WARNING
 * -------
 * Here are some 'anonymous' helper rules (to break down the complexity and
 * to enforce the attributes required) used in the specific rule's detail
 * namespace. The X3 tags the rules, e.g.:
 *
 *  \code{.cpp}
 *  auto const rule = x3::rule<struct _, ...> { "..." } = ...
 *  \endcode
 *
 * It would be naturally to use the parent rules's tag type which belongs the
 * detail helper. But, unfortunately the memory consumption increases dramatically
 * (8+8)GB RAM/SWAP isn't enough). Following StackOverflow
 * [X3: Linker Error (unresolved external symbol “parse_rule”) on nonterminal parser](
 *  https://stackoverflow.com/questions/50277979/x3-linker-error-unresolved-external-symbol-parse-rule-on-nonterminal-parser?answertab=active#tab-top)
 * Sehe's notes, re-using the tag type is recipe for disaster. The rule tags are
 * what dispatches the implementation function in the case of
 * separated compilation units.
 *
 * Some notes about numeric literals
 * ----------------------------------
 * The correct tagged kind_type of {based, decimal}_literal is elementary on
 * elaboration time, since after converting to numeric the informations about
 * the integer/real string are lost, see concrete why it's important e.g.
 * [vhdl error: integer literal cannot have negative exponent](
 * https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent)
 *
 * Strong rules here on parser level simplifies simplifies numeric conversion
 * since more sloppy rules can be used for conversion from literals to concrete
 * intrinsic types.
 */


// abstract_literal ::=                                            [LRM93 §13.4]
//     decimal_literal | based_literal
auto const abstract_literal_def = /* order matters */
      based_literal
    | decimal_literal
    ;



// access_type_definition ::=                                       [LRM93 §3.3]
//     access subtype_indication
auto const access_type_definition_def =
       ACCESS
    >> subtype_indication
    ;



// actual_designator ::=                                        [LRM93 §4.3.2.2]
//       expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open
auto const actual_designator_def =
      // Note, expression also matches {signal,variable,file}_name BNF rules
      expression
    | OPEN
    ;



// actual_parameter_part ::=                                      [LRM93 §7.3.3]
//     parameter_association_list
auto const actual_parameter_part_def =
    association_list
    ;



// actual_part ::=                                              [LRM93 §4.3.2.2]
//       actual_designator
//     | function_name ( actual_designator )
//     | type_mark ( actual_designator )
namespace actual_part_detail {

auto const chunk = x3::rule<struct _, ast::actual_part_chunk>{ "actual_part" } =
       name //  function_name | type_mark
    >> '(' >> actual_designator >> ')'
    ;
} // end detail

auto const actual_part_def = /* order matters */
    /* Note, actual_designator is as of expression and {signal, ...}_name ! */
      actual_part_detail::chunk
    | actual_designator
    ;



// aggregate ::=                                                  [LRM93 §7.3.2]
//     ( element_association { , element_association } )
auto const aggregate_def =
    '(' >> (element_association % ',') >> ')'
    ;



// alias_declaration ::=                                          [LRM93 §4.3.3]
//     alias alias_designator [ : subtype_indication ] is name [ signature ] ;
auto const alias_declaration_def = ( // operator precedence
       ALIAS
    >> alias_designator
    >> -( ':' >> subtype_indication )
    >> IS
    >> name
    >> -signature
    )
    >  ';'
    ;



// alias_designator ::=                                           [LRM93 §4.3.3]
//     identifier | character_literal | operator_symbol
auto const alias_designator_def =
      identifier
    | character_literal
    | operator_symbol
    ;



// allocator ::=                                                  [LRM93 §7.3.6]
//       new subtype_indication
//     | new qualified_expression
auto const allocator_def =
       NEW
    >> ( subtype_indication
       | qualified_expression
       )
    ;



// architecture_body ::=                                            [LRM93 §1.2]
//     architecture identifier of entity_name is
//         architecture_declarative_part
//     begin
//         architecture_statement_part
//     end [ architecture ] [ architecture_simple_name ] ;
auto const architecture_body_def = ( // operator precedence
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
    )
    >  ';'
    ;



// architecture_declarative_part ::=                                [LRM93 §1.2]
//     { block_declarative_item }
auto const architecture_declarative_part_def =
    *block_declarative_item
    ;



// architecture_statement_part ::=                                [LRM93 §1.2.2]
//     { concurrent_statement }
auto const architecture_statement_part_def =
    *concurrent_statement
    ;



// array_type_definition ::=                                        [LRM93 §8.2]
//     unconstrained_array_definition | constrained_array_definition
auto const array_type_definition_def =
      unconstrained_array_definition
    | constrained_array_definition
    ;



// assertion ::=                                                    [LRM93 §8.2]
//     assert condition
//     [ report expression ]
//     [ severity expression ]
auto const assertion_def =
        ( ASSERT   >> condition)
    >> -( REPORT   >> expression )
    >> -( SEVERITY >> expression )
    ;



// assertion_statement ::=                                          [LRM93 §8.2]
//     [ label : ] assertion ;
auto const assertion_statement_def = ( // operator precedence
       -label_colon
    >> assertion
    )
    >  ';'
    ;



// association_element ::=                                      [LRM93 §4.3.2.2]
//     [ formal_part => ] actual_part
auto const association_element_def =
       -x3::as<ast::formal_part>[
           formal_part >> "=>"
       ]
    >> actual_part
    ;



// association_list ::=                                         [LRM93 §4.3.2.2]
//     association_element { , association_element }
auto const association_list_def =
    association_element % ','
    ;



// attribute_declaration ::=                                        [LRM93 §4.4]
//     attribute identifier : type_mark ;
auto const attribute_declaration_def = ( // operator precedence
       ATTRIBUTE
    >> identifier
    >> ':'
    >> type_mark
    )
    >  ';'
    ;



// attribute_designator ::=                                         [LRM93 §6.6]
//     attribute_simple_name
auto const attribute_designator_def =
    simple_name
    ;



// attribute_name ::=                                               [LRM93 §6.6]
//     prefix [ signature ] ' attribute_designator [ ( expression ) ]
auto const attribute_name_def =
       prefix
    >> -signature
    >> '\''
    >> attribute_designator
    >> -(
        '(' >> expression >> ')'
        )
    ;



// attribute_specification ::=                                      [LRM93 §5.1]
//     attribute attribute_designator of entity_specification is expression ;
auto const attribute_specification_def = ( // operator precedence
       ATTRIBUTE
    >> attribute_designator
    >> OF
    >> entity_specification
    >> IS
    >> expression
    )
    >  ';'
    ;


// base ::=                                                      [LRM93 §13.4.2]
//     integer
auto const base_def =
    integer // FixMe: Limit base integer size to 2 digits (range [2...16/32])
    ;


#if 0 /* Note: UNUSED, embedded directly into bit_string_literal rule */
// base_specifier ::=                                              [LRM93 §13.7]
// B | O | X
auto const base_specifier_def =
    'B' | 'O' | 'X'
    ;
#endif

// based_integer ::=                                             [LRM93 §13.4.2]
//     extended_digit { [ underline ] extended_digit }
auto const based_integer_def =
    x3::as<ast::string_span>[
        raw [ lexeme[
            extended_digit >> *( -lit('_') >> extended_digit )
        ]]
    ]
    ;



// based_literal ::=                                             [LRM93 §13.4.2]
//     base # based_integer [ . based_integer ] # [ exponent ]
namespace based_literal_detail {

auto const integer_type = x3::rule<struct _, ast::based_literal::number_chunk>{ "based_literal<int>" } =
    /* Note, IEEE1076-93 Ch. 13.4, specifies for decimal_literal the forbidden
     * negative sign for the exponent of integer types. No restrictions are there
     * defined for based_literal, assume real type exponent. */
    lexeme[
           based_integer >> x3::attr(ast::string_span{/* empty fractional part */})
        >> '#'
        >> -exponent
    ]
    >> x3::attr(ast::based_literal::kind_specifier::integer)
    ;

auto const real_type = x3::rule<struct _, ast::based_literal::number_chunk>{ "based_literal<real>" } =
    lexeme[
          based_integer >> lit('.') >> based_integer
        >> '#'
        >> -exponent
    ]
    >> x3::attr(ast::based_literal::kind_specifier::real)
    ;


} // end detail

auto const based_literal_def =
    lexeme [
           base
        >> '#'
        >> ( based_literal_detail::real_type | based_literal_detail::integer_type )
    ]
    ;


// basic_identifier ::=                                            [LRM93 §13.3]
//     letter { [ underline ] letter_or_digit }
namespace basic_identifier_detail {

auto const feasible = x3::rule<struct _, ast::string_span> { "basic_identifier" } =
    raw[ lexeme [
           letter
        >> !char_('"') // reject bit_string_literal
        >> *( letter_or_digit | char_("_") )
    ]]
    ;
} // end detail

auto const basic_identifier_def =
    basic_identifier_detail::feasible - keyword
    ;



// binding_indication ::=                                         [LRM93 §5.2.1]
//     [ use entity_aspect ]
//     [ generic_map_aspect ]
//     [ port_map_aspect ]
auto const binding_indication_def =
       -( USE >> entity_aspect )
    >> -generic_map_aspect
    >> -port_map_aspect
    ;



// bit_string_literal ::=                                          [LRM93 §13.7]
//     base_specifier " bit_value "
namespace detail {

auto const bit_string_literal = [](auto&& base, auto&& char_range, auto&& attr)
{
    using CharT = decltype(char_range);
    using AttrT = decltype(attr);

    auto const char_set = [](auto&& char_range_) {
        return x3::rule<struct _, ast::string_span>{ "char_set" } = x3::as_parser(
             raw[
                    char_(std::forward<CharT>(char_range_))
                 >> *( -lit("_") >> char_(std::forward<CharT>(char_range_) ))
             ]
        );
    };

    return x3::rule<struct _, ast::bit_string_literal>{ "bit_string_literal" } = x3::as_parser(
        lexeme[
               x3::omit[char_(std::forward<decltype(base)>(base))]
            >> lit('"')
            >> char_set(std::forward<CharT>(char_range))
            >> lit('"')
        ]
        >> x3::attr(std::forward<AttrT>(attr))
    );
};

} // end detail

auto const bit_string_literal_def =
      detail::bit_string_literal("Bb", "01",        ast::bit_string_literal::base_specifier::bin)
    | detail::bit_string_literal("Xx", "0-9a-fA-F", ast::bit_string_literal::base_specifier::hex)
    | detail::bit_string_literal("Oo", "0-7",       ast::bit_string_literal::base_specifier::oct)
    ;



#if 0 /* Note: UNUSED, embedded directly into bit_string_literal */
// bit_value ::=
//     extended_digit { [ underline ] extended_digit }
auto const bit_value_def =
    extended_digit { -( underline ) extended_digit }
    ;
#endif


// block_configuration ::                                         [LRM93 §1.3.1]
//     for block_specification
//         { use_clause }
//         { configuration_item }
//     end for ;
auto const block_configuration_def = ( // operator precedence
       FOR
    >> block_specification
    >> *use_clause
    >> *configuration_item
    >> END >> FOR
    )
    >  ';'
    ;



// block_declarative_item ::=                                     [LRM93 §1.2.1]
//       subprogram_declaration
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



// block_declarative_part ::=                                       [LRM93 §9.1]
//     { block_declarative_item }
auto const block_declarative_part_def =
    *block_declarative_item
    ;



// block_header ::=                                                 [LRM93 §9.1]
//     [ generic_clause
//     [ generic_map_aspect ; ] ]
//     [ port_clause
//     [ port_map_aspect ; ] ]
namespace detail {

auto const block_header_generic = x3::rule<struct _, ast::block_header::generic_part_chunk> { "block_header.generic" } =
       generic_clause
    >> -( generic_map_aspect > ';' )
    ;

auto const block_header_port = x3::rule<struct _, ast::block_header::port_part_chunk> { "block_header.port" } =
       port_clause
    >> -( port_map_aspect > ';' )
    ;
} // end detail

auto const block_header_def =
       -detail::block_header_generic
    >> -detail::block_header_port
    ;



// block_specification ::=                                        [LRM93 §1.3.1]
//       architecture_name
//     | block_statement_label
//     | generate_statement_label [ ( index_specification ) ]
auto const block_specification_def = /* order matters */
      label >> -( '(' >> index_specification >> ')' )
    | name
    ;



// block_statement ::=                                              [LRM93 §9.1]
//     block_label :
//         block [ ( guard_expression ) ] [ is ]
//             block_header
//             block_declarative_part
//         begin
//             block_statement_part
//         end block [ block_label ] ;
auto const block_statement_def = ( // operator precedence
       label_colon
    >> BLOCK
    >> -( '(' >> expression >> ')' )
    >> -IS
    >> block_header
    >> block_declarative_part
    >> BEGIN
    >> block_statement_part
    >> END >> BLOCK
    >> -label
    )
    >  ';'
    ;



// block_statement_part ::=                                         [LRM93 §9.1]
//     { concurrent_statement }
auto const block_statement_part_def =
    *concurrent_statement
    ;



// case_statement ::=                                               [LRM93 §8.8]
//     [ case_label : ]
//         case expression is
//             case_statement_alternative
//             { case_statement_alternative }
//         end case [ case_label ] ;
auto const case_statement_def = ( // operator precedence
       -label_colon
    >> CASE
    >> expression
    >> IS
    >> +case_statement_alternative
    >> END >> CASE
    >> -label
    )
    >  ';'
    ;



// case_statement_alternative ::=                                   [LRM93 §8.8]
//     when choices =>
//         sequence_of_statements
auto const case_statement_alternative_def =
       WHEN
    >> choices
    >> "=>"
    >> sequence_of_statements
    ;



// character_literal ::=                                           [LRM93 §13.5]
//     ' graphic_character '
auto const character_literal_def =
    x3::lexeme [
           "\'"
        >> ( ( graphic_character - '\'' )
           | char_("\'")
           )
        >> "\'"
    ]
    ;



// choice ::=                                                     [LRM93 §7.3.2]
//       simple_expression
//     | discrete_range
//     | element_simple_name
//     | others
auto const choice_def =
/* Note, (element)_simple_name get never been parsed, since:
 * simple_expression -> term -> factor -> primary -> name -> simple_name */
      simple_expression
    | discrete_range
    | OTHERS
    ;



// choices ::=                                                    [LRM93 §7.3.2]
//     choice { | choice }
auto const choices_def =
    choice % '|'
    ;



// component_configuration ::=                                    [LRM93 §1.3.2]
//     for component_specification
//         [ binding_indication ; ]
//         [ block_configuration ]
//     end for ;
auto const component_configuration_def = ( // operator precedence
       FOR
    >> component_specification
    >> -( binding_indication > ';' )
    >> -block_configuration
    >> END >> FOR
    )
    >  ';'
    ;



// component_declaration ::=                                        [LRM93 §4.5]
//     component identifier [ is ]
//         [ local_generic_clause ]
//         [ local_port_clause ]
//     end component [ component_simple_name ] ;
auto const component_declaration_def = ( // operator precedence
       COMPONENT
    >> identifier
    >> -IS
    >> -generic_clause
    >> -port_clause
    >> END >> COMPONENT
    >> -simple_name
    )
    >  ';'
    ;



// component_instantiation_statement ::=                            [LRM93 §9.6]
//     instantiation_label :
//         instantiated_unit
//             [ generic_map_aspect ]
//             [ port_map_aspect ] ;
auto const component_instantiation_statement_def = ( // operator precedence
       label_colon
    >> instantiated_unit
    >> -generic_map_aspect
    >> -port_map_aspect
    )
    >  ';'
    ;



// component_specification ::=                                      [LRM93 §5.2]
//     instantiation_list : component_name
auto const component_specification_def =
       instantiation_list
    >> ':'
    >> name
    ;



// composite_type_definition ::=                                    [LRM93 §3.2]
//       array_type_definition
//     | record_type_definition
auto const composite_type_definition_def =
      array_type_definition
    | record_type_definition
    ;



// concurrent_assertion_statement ::=                               [LRM93 §9.4]
// [ label : ] [ postponed ] assertion ;
auto const concurrent_assertion_statement_def = ( // operator precedence
       -label_colon
    >> -POSTPONED
    >> assertion
    )
    >  ';'
    ;



// concurrent_procedure_call_statement ::=                          [LRM93 §9.3]
// [ label : ] [ postponed ] procedure_call ;
auto const concurrent_procedure_call_statement_def = ( // operator precedence
       -label_colon
    >> -POSTPONED
    >> procedure_call
    )
    >  ';'
    ;



// concurrent_signal_assignment_statement ::=                       [LRM93 §9.5]
//       [ label : ] [ postponed ] conditional_signal_assignment
//     | [ label : ] [ postponed ] selected_signal_assignment
auto const concurrent_signal_assignment_statement_def =
       -label_colon
    >> -POSTPONED
    >> (  conditional_signal_assignment
       | selected_signal_assignment
       )
    ;



// concurrent_statement ::=                                           [LRM93 §9]
//       block_statement
//     | process_statement
//     | concurrent_procedure_call_statement
//     | concurrent_assertion_statement
//     | concurrent_signal_assignment_statement
//     | component_instantiation_statement
//     | generate_statement
auto const concurrent_statement_def =
    /* Note, order matters but is fragile; the problem seems to rise from rule
     * label >> ':', which is same/similar to component_instantiation_statement */
      component_instantiation_statement
    | concurrent_signal_assignment_statement
    | concurrent_procedure_call_statement
    | concurrent_assertion_statement
    | block_statement
    | generate_statement
    | process_statement
    ;



// condition ::=                                                    [LRM93 §8.1]
//     boolean_expression
auto const condition_def =
    expression
    ;



// condition_clause ::=                                             [LRM93 §8.1]
//     until condition
auto const condition_clause_def =
    UNTIL >> condition
    ;



// conditional_signal_assignment ::=                              [LRM93 §9.5.1]
//     target    <= options conditional_waveforms ;
auto const conditional_signal_assignment_def = ( // operator precedence
       target
    >> "<="
    >> options
    >> conditional_waveforms
    )
    >  ';'
    ;



// conditional_waveforms ::=                                      [LRM93 §9.5.1]
//     { waveform when condition else }
//       waveform [ when condition ]
auto const conditional_waveforms_def =
       *( waveform >> WHEN >> condition >> ELSE )
    >> waveform
    >> -( WHEN >> condition )
    ;



// configuration_declaration ::=                                    [LRM93 §1.3]
//     configuration identifier of entity_name is
//         configuration_declarative_part
//         block_configuration
//     end [ configuration ] [ configuration_simple_name ] ;
auto const configuration_declaration_def = ( // operator precedence
       CONFIGURATION
    >> identifier
    >> OF
    >> name
    >> IS
    >> configuration_declarative_part
    >> block_configuration
    >> END >> -CONFIGURATION
    >> -simple_name
    )
    >  ';'
    ;



// configuration_declarative_item ::=                               [LRM93 §1.3]
//       use_clause
//     | attribute_specification
//     | group_declaration
auto const configuration_declarative_item_def =
      use_clause
    | attribute_specification
    | group_declaration
    ;



// configuration_declarative_part ::=                               [LRM93 §1.3]
//     { configuration_declarative_item }
auto const configuration_declarative_part_def =
    *configuration_declarative_item
    ;



// configuration_item ::=                                         [LRM93 §1.3.1]
//       block_configuration
//     | component_configuration
auto const configuration_item_def =
      block_configuration
    | component_configuration
    ;



// configuration_specification ::=                                  [LRM93 §5.2]
//     for component_specification binding_indication ;
auto const configuration_specification_def = ( // operator precedence
       FOR
    >> component_specification
    >> binding_indication
    )
    >  ';'
    ;


// constant_declaration ::=                                     [LRM93 §4.3.1.1]
//     constant identifier_list : subtype_indication [ := expression ] ;
auto const constant_declaration_def = ( // operator precedence
       omit[ CONSTANT ]
    >> identifier_list
    >> ':'
    >> subtype_indication
    >> -( ":=" >>  expression )
    )
    >  ';'
;



// constrained_array_definition ::=                               [LRM93 §3.2.1]
//     array index_constraint of element_subtype_indication
auto const constrained_array_definition_def =
       ARRAY
    >> index_constraint
    >> OF
    >> subtype_indication
    ;



// constraint ::=                                                   [LRM93 §4.2]
//       range_constraint
//     | index_constraint
auto const constraint_def =
      range_constraint
    | index_constraint
    ;



// context_clause ::=                                              [LRM93 §11.3]
//     { context_item }
auto const context_clause_def =
    *context_item
    ;



// context_item ::=                                                [LRM93 §11.3]
//       library_clause
//     | use_clause
auto const context_item_def =
      library_clause
    | use_clause
    ;



// decimal_literal ::=                                           [LRM93 §13.4.1]
//     integer [ . integer ] [ exponent ]
namespace decimal_literal_detail {

auto const real_type = x3::rule<struct _, ast::decimal_literal> { "decimal_literal<real>" } =
       x3::as<ast::string_span>[
           raw[ lexeme[
               integer >> char_('.') >> integer >> -exponent
           ]]
       ]
    >> x3::attr(ast::decimal_literal::kind_specifier::real)
    ;

auto const integer_exponent = x3::rule<struct _, ast::string_span> { "exponent" } =
   /* Note, following IEEE1076-93 Ch. 13.4, the exponent on integer type must
    * not have a minus sign. This means implicit (even from NBF) that a positive
    * (optional) sign is allowed. */
    raw[ lexeme[
        char_("Ee") >> -char_("+") >> integer
    ]]
    ;

auto const integer_type = x3::rule<struct _, ast::decimal_literal> { "decimal_literal<int>" } =
       x3::as<ast::string_span>[
           raw[ lexeme[
               // Note, exponent on integer is always without sign!
               integer >> -integer_exponent
           ]]
       ]
    >> x3::attr(ast::decimal_literal::kind_specifier::integer)
    ;
} // end detail

auto const decimal_literal_def =
      decimal_literal_detail::real_type
    | decimal_literal_detail::integer_type
    ;


#if 0 // UNUSED in the BNF
// declaration ::=                                                    [LRM93 §4]
//       type_declaration
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


// delay_mechanism ::=                                              [LRM93 §8.4]
//       transport
//     | [ reject time_expression ] inertial
auto const delay_mechanism_def =
       TRANSPORT
    | (   -( REJECT >> expression )
       >> INERTIAL
      )
    ;



// design_file ::=                                                 [LRM93 §11.1]
//     design_unit { design_unit }
auto const design_file_def =
    *design_unit
    ;



// design_unit ::=                                                 [LRM93 §11.1]
//     context_clause library_unit
auto const design_unit_def =
       context_clause
    >> library_unit
    ;



// designator ::=                                                   [LRM93 §2.1]
//     identifier  |  operator_symbol
auto const designator_def =
      identifier
    | operator_symbol
    ;



// direction ::=                                                    [LRM93 §3.1]
//     to | downto
auto const direction_def =
    TO | DOWNTO
    ;



// disconnection_specification ::=                                  [LRM93 §5.3]
//     disconnect guarded_signal_specification after time_expression ;
auto const disconnection_specification_def = ( // operator precedence
       DISCONNECT
    >> guarded_signal_specification
    >> AFTER
    >> expression
    )
    >  ';'
    ;



// discrete_range ::=                                             [LRM93 §3.2.1]
//     discrete_subtype_indication | range
auto const discrete_range_def = /* order matters */
      range
    | subtype_indication
    ;



// element_association ::=                                        [LRM93 §7.3.2]
//     [ choices => ] expression
auto const element_association_def =
    /* Note, parsing element_association is a bit tricky, due to backtracking side
     * effect. The problem did rise up first time on parsing attribute_specification's
     * expression:
     *
     * attribute_specification ::=
     *        attribute attribute_designator OF entity_specification IS expression ;
     *
     * with descent aggregate's element_association:
     *
     * aggregate           ::= ( element_association { , element_association } )
     * element_association ::= [ choices => ] expression
     *
     * If the choices rule fails due to missing "=>" the element_association node
     * still contains the previous parsed data, hence holding the leaf data twice
     * using two parse paths. as[] directive solve this. */
       -x3::as<ast::choices>[choices >> "=>"]
    >> expression
    ;



// element_declaration ::=                                        [LRM93 §3.2.2]
//     identifier_list : element_subtype_definition ;
auto const element_declaration_def = ( // operator precedence
       identifier_list
    >> ':'
    >> element_subtype_definition
    )
    >  ';'
    ;



// element_subtype_definition ::=                                 [LRM93 §3.2.2]
//     subtype_indication
auto const element_subtype_definition_def =
    subtype_indication
    ;



// entity_aspect ::=                                            [LRM93 §5.2.1.1]
//       entity entity_name [ ( architecture_identifier) ]
//     | configuration configuration_name
//     | open
namespace entity_aspect_detail {

auto const entity = x3::rule<struct _, ast::entity_aspect_entity> { "entity_aspect.entity" } =
       ENTITY
    >> name
    >> -(      '('
            >> identifier
            >> ')'
        )
    ;

auto const configuration = x3::rule<struct _, ast::entity_aspect_configuration> { "entity_aspect.configuration" } =
       CONFIGURATION
    >> name
    ;
} // end detail

auto const entity_aspect_def =
      entity_aspect_detail::entity
    | entity_aspect_detail::configuration
    | OPEN
    ;



// entity_class ::=                                                 [LRM93 §5.1]
//       entity        | architecture  | configuration
//     | procedure     | function      | package
//     | type          | subtype       | constant
//     | signal        | variable      | component
//     | label         | literal       | units
//     | group         | file
namespace detail {

x3::symbols<ast::keyword_token> const entity_class_symbols(
    {
        {"entity"        , ast::keyword_token::ENTITY},
        {"architecture"  , ast::keyword_token::ARCHITECTURE},
        {"configuration" , ast::keyword_token::CONFIGURATION},
        {"procedure"     , ast::keyword_token::PROCEDURE},
        {"function"      , ast::keyword_token::FUNCTION},
        {"package"       , ast::keyword_token::PACKAGE},
        {"type"          , ast::keyword_token::TYPE},
        {"subtype"       , ast::keyword_token::SUBTYPE},
        {"constant"      , ast::keyword_token::CONSTANT},
        {"signal"        , ast::keyword_token::SIGNAL},
        {"variable"      , ast::keyword_token::VARIABLE},
        {"component"     , ast::keyword_token::COMPONENT},
        {"label"         , ast::keyword_token::LABEL},
        {"literal"       , ast::keyword_token::LITERAL},
        {"units"         , ast::keyword_token::UNITS},
        {"group"         , ast::keyword_token::GROUP},
        {"file"          , ast::keyword_token::FILE}
    },
    "entity_class"
);

} // namespace detail

auto const entity_class_def =
     distinct(detail::entity_class_symbols)
     ;



// entity_class_entry ::=                                           [LRM93 §4.6]
//     entity_class [ <> ]
auto const entity_class_entry_def =
       entity_class
    >> -lit("<>")
    ;



// entity_class_entry_list ::=                                      [LRM93 §4.6]
//     entity_class_entry { , entity_class_entry }
auto const entity_class_entry_list_def =
    entity_class_entry % ','
    ;



// entity_declaration ::=                                           [LRM93 §1.1]
//     entity identifier is
//         entity_header
//         entity_declarative_part
//   [ begin
//         entity_statement_part ]
//     end [ entity ] [ entity_simple_name ] ;
auto const entity_declaration_def = ( // operator precedence
       ENTITY
    >> identifier
    >> IS
    >> entity_header
    >> entity_declarative_part
    >> -(      BEGIN
            >> entity_statement_part
        )
    >> END
    >> -ENTITY
    >> -simple_name
    )
    >  ';'
    ;



// entity_declarative_item ::=                                    [LRM93 §1.1.2]
//       subprogram_declaration
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



// entity_declarative_part ::=                                    [LRM93 §1.1.2]
//     { entity_declarative_item }
auto const entity_declarative_part_def =
    *entity_declarative_item
    ;



// entity_designator ::=                                            [LRM93 §5.1]
//     entity_tag [ signature ]
auto const entity_designator_def =
       entity_tag
    >> -signature
    ;



// entity_header ::=                                              [LRM93 §1.1.1]
//     [ formal_generic_clause ]
//     [ formal_port_clause ]
auto const entity_header_def =
       -generic_clause
    >> -port_clause
    ;



// entity_name_list ::=                                             [LRM93 §5.1]
//       entity_designator { , entity_designator }
//     | others
//     | all
auto const entity_name_list_def =
      (entity_designator % ',')
    | OTHERS
    | ALL
    ;



// entity_specification ::=                                         [LRM93 §5.1]
//     entity_name_list : entity_class
auto const entity_specification_def =
      entity_name_list
    >> ':'
    >> entity_class
    ;



// entity_statement ::=                                           [LRM93 §1.1.3]
//       concurrent_assertion_statement
//     | passive_concurrent_procedure_call_statement
//     | passive_process_statement
auto const entity_statement_def =
      concurrent_assertion_statement
    | concurrent_procedure_call_statement
    | process_statement
    ;



// entity_statement_part ::=                                      [LRM93 §1.1.3]
//     { entity_statement }
auto const entity_statement_part_def =
    *entity_statement
    ;



// entity_tag ::=                                                   [LRM93 §5.1]
// simple_name | character_literal | operator_symbol
auto const entity_tag_def =
      simple_name
    | character_literal
    | operator_symbol
    ;



// enumeration_literal ::=                                        [LRM93 §3.1.1]
//     identifier | character_literal
auto const enumeration_literal_def =
      identifier
    | character_literal
    ;



// enumeration_type_definition ::=                                [LRM93 §3.1.1]
//     ( enumeration_literal { , enumeration_literal } )
auto const enumeration_type_definition_def =
    '(' >> (enumeration_literal % ',') >> ')'
    ;



// exit_statement ::=                                              [LRM93 §8.11]
//     [ label : ] exit [ loop_label ] [ when condition ] ;
auto const exit_statement_def = ( // operator precedence
       -label_colon
    >> EXIT
    >> -label
    >> -( WHEN >> condition )
    )
    >  ';'
    ;



// exponent ::=                                                  [LRM93 §13.4.1]
//     E [ + ] integer | E - integer
auto const exponent_def =
    /* Note, that exponent rule parses real exponent, for integer types no sign
     * is allowed, hence embedded into the concrete rule */
    x3::as<ast::string_span>[
        raw[ lexeme [
             char_("Ee") >> -char_("-+") >> integer
        ]]
    ]
    ;



// expression ::=                                                   [LRM93 §7.1]
//       relation { and relation }
//     | relation { or relation }
//     | relation { xor relation }
//     | relation [ nand relation ]
//     | relation [ nor relation ]
//     | relation { xnor relation }
namespace expression_detail {

auto const chunks_1 = x3::rule<struct _, std::vector<ast::expression::chunk>> { "expression" } =
    *(binary_logical_operator >> relation)
    ;

auto const chunk_2 = x3::rule<struct _, std::vector<ast::expression::chunk>> { "expression" } =
    x3::repeat(1)[ // enforce artificial vector to unify ast node
        unary_logical_operator >> relation
    ];
} // end detail

auto const expression_def =
       relation
    >> ( expression_detail::chunk_2    // NAND, NOR
       | expression_detail::chunks_1   // AND, ...
       )
    ;



// extended_identifier ::=                                       [LRM93 §13.3.2]
//     \ graphic_character { graphic_character } \                             .
namespace extended_identifier_detail {

auto const charset = x3::rule<struct _, ast::string_span> { "extended_identifier" } =
     +( graphic_character - char_('\\') )
     ;

auto const atom = x3::rule<struct _, ast::string_span> { "extended_identifier" } =
    raw[ lexeme [
           char_('\\')
        >> charset
        >> char_('\\')
    ]]
    ;
} // end detail

auto const extended_identifier_def =
    x3::as<ast::string_span>[
        raw[ lexeme [
               extended_identifier_detail::atom
            >> *(extended_identifier_detail::atom % (char_('\\') >> char_('\\')))
        ]]
    ]
    ;



// factor ::=                                                       [LRM93 §7.1]
//       primary [ ** primary ]
//     | abs primary
//     | not primary
namespace factor_detail {

auto const binary_expr = x3::rule<struct _, ast::factor_binary_operation> { "factor" } =
       primary
    >> binary_miscellaneous_operator // ** (exponent)
    >> primary
    ;

auto const unary_expr = x3::rule<struct _, ast::factor_unary_operation> { "factor" } =
    unary_miscellaneous_operator >> primary // ABS | NOT
    ;
} // end detail

auto const factor_def =    /* order matters */
      factor_detail::binary_expr
    | factor_detail::unary_expr
    | primary
    ;



// file_declaration ::=                                         [LRM93 §4.3.1.4]
//     file identifier_list : subtype_indication [ file_open_information ] ;
auto const file_declaration_def = ( // operator precedence
       FILE
    >> identifier_list
    >> ':'
    >> subtype_indication
    >> -file_open_information
    )
    >  ';'
    ;



// file_logical_name ::=                                        [LRM93 §4.3.1.4]
//     string_expression
auto const file_logical_name_def =
    expression
    ;



// file_open_information ::=                                    [LRM93 §4.3.1.4]
//     [ open file_open_kind_expression ] is file_logical_name
auto const file_open_information_def =
    -(    omit[ OPEN ]
       >> expression
     )
    >> IS
    >> file_logical_name
    ;



// file_type_definition ::=                                         [LRM93 §3.4]
//     file  of type_mark
auto const file_type_definition_def =
       FILE
    >> OF
    >> type_mark
    ;


#if 0 // UNUSED; embedded into scalar_type_definition
// floating_type_definition ::=                                   [LRM93 §3.1.4]
//     range_constraint
auto const floating_type_definition_def =
    range_constraint
    ;
#endif


// formal_designator ::=                                        [LRM93 §4.3.2.2]
//       generic_name
//     | port_name
//     | parameter_name
auto const formal_designator_def =
    name    // aka {generic, port, parameter}_name
    ;



// formal_parameter_list ::=                                      [LRM93 §2.1.1]
//     parameter_interface_list
auto const formal_parameter_list_def =
    interface_list
    ;



// formal_part ::=                                              [LRM93 §4.3.2.2]
//       formal_designator
//     | function_name ( formal_designator )
//     | type_mark ( formal_designator )
auto const formal_part_def =
    x3::as<std::vector<ast::name>>[
        /* formal_designator is a context tied name ({generic, port, parameter}_name)
         * where function_name and type_mark are also a name. Hence parse a list
         * of names.  */
           name
        >> -(
                '(' >> formal_designator >> ')'
            )
    ]
    ;


#if 0 // UNUSED; embedded into type_declaration
// full_type_declaration ::=                                        [LRM93 §4.1]
//     type identifier is type_definition ;
auto const full_type_declaration_def = ( // operator precedence
       TYPE
    >> identifier
    >> IS
    >> type_definition
    )
    >  ';'
    ;
#endif


// function_call ::=                                              [LRM93 §7.3.3]
//     function_name [ ( actual_parameter_part ) ]
auto const function_call_def =
       name
    >> -(
            '(' >> actual_parameter_part >> ')'
        )
    ;



// generate_statement ::=                                           [LRM93 §9.7]
//     generate_label :
//         generation_scheme generate
//             [ { block_declarative_item }
//         begin ]
//             { concurrent_statement }
//         end generate [ generate_label ] ;
auto const generate_statement_def = ( // operator precedence
       label_colon
    >> generation_scheme
    >> GENERATE
    >> -(*block_declarative_item
          >> BEGIN
       ) // FIXME: rule failed - never get concurrent_statement/component_instantiation_statement
    >> *concurrent_statement
    >> END >> GENERATE
    >> -label
    )
    >  ';'
    ;



// generation_scheme ::=                                            [LRM93 §9.7]
//       for generate_parameter_specification
//     | if condition
auto const generation_scheme_def =
      (FOR >> parameter_specification)
    | (IF  >> condition)
    ;



// generic_clause ::=                                             [LRM93 §1.1.1]
//     generic ( generic_list ) ;
auto const generic_clause_def = ( // operator precedence
       GENERIC
    >> '('
    >> interface_list
    >> ')'
    )
    >  ';'
    ;


#if 0 // DISABLED; embedded into generic_clause
// generic_list ::=                                             [LRM93 §1.1.1.1]
//     generic_interface_list
auto const generic_list_def =
    interface_list
    ;
#endif


// generic_map_aspect ::=                                       [LRM93 §5.2.1.2]
//     generic map ( generic_association_list )
auto const generic_map_aspect_def =
       GENERIC
    >> MAP
    >> '('
    >> association_list
    >> ')'
    ;




// group_constituent ::                                             [LRM93 §4.7]
//     name | character_literal
auto const group_constituent_def =
    name | character_literal
    ;



// group_constituent_list ::=                                       [LRM93 §4.7]
//     group_constituent { , group_constituent }
auto const group_constituent_list_def =
    group_constituent % ','
    ;



// group_template_declaration ::=                                   [LRM93 §4.6]
//     group identifier is ( entity_class_entry_list ) ;
auto const group_template_declaration_def = ( // operator precedence
       GROUP
    >> identifier
    >> IS
    >> '('
    >> entity_class_entry_list
    >> ')'
    )
    >  ';'
    ;



// group_declaration ::=                                            [LRM93 §4.7]
//     group identifier : group_template_name ( group_constituent_list ) ;
auto const group_declaration_def = ( // operator precedence
       GROUP
    >> identifier
    >> ':'
    >> name
    >> '('
    >> group_constituent_list
    >> ')'
    )
    >  ';'
    ;



// guarded_signal_specification ::=                                 [LRM93 §5.3]
//     guarded_signal_list : type_mark
auto const guarded_signal_specification_def =
       signal_list
    >> ':'
    >> type_mark
    ;



// identifier ::=                                                  [LRM93 §13.3]
//     basic_identifier | extended_identifier
auto const identifier_def =
      basic_identifier
    | extended_identifier
    ;



// identifier_list ::=                                            [LRM93 §3.2.2]
//     identifier { , identifier }
auto const identifier_list_def =
    identifier % ','
    ;



// if_statement ::=                                                 [LRM93 §8.7]
//     [ if_label : ]
//         if condition then
//             sequence_of_statements
//       { elsif condition then
//             sequence_of_statements }
//       [ else
//             sequence_of_statements ]
//         end if [ if_label ] ;
auto const if_statement_def = ( // operator precedence
       -label_colon
    >> IF >> condition >> THEN
    >> sequence_of_statements
    >> *( ELSIF >> condition >> THEN >> sequence_of_statements )
    >> -( ELSE >> sequence_of_statements )
    >> END >> IF
    >> -label
    )
    >  ';'
;


#if 0 // UNUSED; embedded into type_declaration
// incomplete_type_declaration ::=                                [LRM93 §3.3.1]
//     type identifier ;
auto const incomplete_type_declaration_def = ( // operator precedence
       TYPE
    >> identifier
    )
    >  ';'
    ;
#endif


// index_constraint ::=                                           [LRM93 §3.2.1]
//     ( discrete_range { , discrete_range } )
auto const index_constraint_def =
     '(' >> (discrete_range % ',') >> ')'
     ;



// index_specification ::=                                        [LRM93 §1.3.1]
//       discrete_range
//     | static_expression
auto const index_specification_def =
      discrete_range
    | expression
    ;



// index_subtype_definition ::=                                   [LRM93 §3.2.1]
//     type_mark range <>
auto const index_subtype_definition_def =
       type_mark
    >> RANGE
    >> "<>"
    ;



// indexed_name ::=                                                 [LRM93 §6.4]
//     prefix ( expression { , expression } )
auto const indexed_name_def =
       prefix
    >> '(' >> (expression % ',') >> ')'
    ;



// instantiated_unit ::=                                            [LRM93 §9.6]
//       [ component ] component_name
//     | entity entity_name [ ( architecture_identifier ) ]
//     | configuration configuration_name
auto const instantiated_unit_def =
      x3::as<ast::instantiated_unit_component>[-COMPONENT >> name]
    | x3::as<ast::instantiated_unit_entity>[ENTITY >> name >> -( '(' >> identifier >> ')' )]
    | x3::as<ast::instantiated_unit_configuration>[CONFIGURATION   >> name]
    ;



// instantiation_list ::=                                           [LRM93 §5.2]
//       instantiation_label { , instantiation_label }
//     | others
//     | all
auto const instantiation_list_def =
      (label % ',')
    | OTHERS
    | ALL
    ;



// integer ::=                                                         § 13.4.1]
//     digit { [ underline ] digit }
auto const integer_def =
    x3::as<ast::string_span>[
        raw[ lexeme [
            digit >> *( -lit("_") >> digit )
        ]]
    ]
    ;


#if 0 // DISABLED, embedded into scalar_type_definition
// integer_type_definition ::=                                    [LRM93 §3.1.2]
//     range_constraint
auto const integer_type_definition_def =
    range_constraint
    ;
#endif


// interface_constant_declaration ::=                             [LRM93 §4.3.2]
//     [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]
auto const interface_constant_declaration_def =
       -CONSTANT
    >> identifier_list
    >> ':'
    >> -IN
    >> subtype_indication
    >> -( ":=" >> expression )
    ;



// interface_declaration ::=                                      [LRM93 §4.3.2]
//       interface_constant_declaration
//     | interface_signal_declaration
//     | interface_variable_declaration
//     | interface_file_declaration
auto const interface_declaration_def =
      interface_constant_declaration
    | interface_signal_declaration
    | interface_variable_declaration
    | interface_file_declaration
    ;



// interface_element ::=                                        [LRM93 §4.3.2.1]
//      interface_declaration
auto const interface_element_def =
    interface_declaration
    ;



// interface_file_declaration ::=                                 [LRM93 §4.3.2]
//     file identifier_list : subtype_indication
auto const interface_file_declaration_def =
       FILE
    >> identifier_list
    >> ':'
    >> subtype_indication
    ;



// interface_list ::=                                           [LRM93 §4.3.2.1]
//     interface_element { ; interface_element }
auto const interface_list_def =
    interface_element % ';'
    ;



// interface_signal_declaration ::=                               [LRM93 §4.3.2]
//     [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]
auto const interface_signal_declaration_def =
       -SIGNAL
    >> identifier_list
    >> ':'
    >> -mode
    >> subtype_indication
    >> -BUS
    >> -( ":=" >>  expression )
    ;



// interface_variable_declaration ::=                             [LRM93 §4.3.2]
//     [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]
auto const interface_variable_declaration_def =
       -VARIABLE
    >> identifier_list
    >> ':'
    >> -mode
    >> subtype_indication
    >> -( ":=" >>  expression )
    ;



// iteration_scheme ::=                                             [LRM93 §8.9]
//       while condition
//     | for loop_parameter_specification
auto const iteration_scheme_def =
      (WHILE >> condition)
    | (FOR >> parameter_specification)
    ;



// label ::=                                                        [LRM93 §9.7]
//     identifier
auto const label_def =
    identifier
    ;



// library_clause ::=                                              [LRM93 §11.2]
//     library logical_name_list ;
auto const library_clause_def = ( // operator precedence
       LIBRARY
    >> logical_name_list
    )
    >  ';'
    ;



// library_unit ::=                                                [LRM93 §11.1]
//       primary_unit
//     | secondary_unit
auto const library_unit_def =
      primary_unit
    | secondary_unit
    ;



// literal ::=                                                    [LRM93 §7.3.1]
//       numeric_literal
//     | enumeration_literal
//     | string_literal
//     | bit_string_literal
//     | null
auto const literal_def = /* order matters */
      enumeration_literal
    | string_literal
    | bit_string_literal
    | numeric_literal
    | NULL_
    ;



// logical_name ::=                                                [LRM93 §11.2]
//     identifier
auto const logical_name_def =
    identifier
    ;



// logical_name_list ::=                                           [LRM93 §11.2]
//     logical_name { , logical_name }
auto const logical_name_list_def =
    logical_name % ','
    ;



// loop_statement ::=                                               [LRM93 §8.9]
//     [ loop_label : ]
//         [ iteration_scheme ] loop
//             sequence_of_statements
//         end loop [ loop_label ] ;
auto const loop_statement_def = ( // operator precedence
      -label_colon
    >> -iteration_scheme
    >> LOOP
    >> sequence_of_statements
    >> END >> LOOP
    >> -label
    )
    >  ';'
    ;



// mode ::=                                                       [LRM93 §4.3.2]
//     in | out | inout | buffer | linkage
namespace detail {

x3::symbols<ast::keyword_token> const mode_symbols(
    {
        {"in"     , ast::keyword_token::IN},
        {"out"    , ast::keyword_token::OUT},
        {"inout"  , ast::keyword_token::INOUT},
        {"buffer" , ast::keyword_token::BUFFER},
        {"linkage", ast::keyword_token::LINKAGE}
    },
    "mode"
);

}// namespace detail

auto const mode_def =
    distinct(detail::mode_symbols)
    ;




// name ::=                                                         [LRM93 §6.1]
//       simple_name
//     | operator_symbol
//     | selected_name
//     | indexed_name
//     | slice_name
//     | attribute_name
auto const name_def =
/* Note, using LRM BNF rule for selected_name results into left recursion, see
 * selected_name for details. */
        simple_name
      | operator_symbol
//      | selected_name
//    | indexed_name // FixMe
//    | slice_name
//    | attribute_name
    ;



// next_statement ::=                                              [LRM93 §8.10]
//     [ label : ] next [ loop_label ] [ when condition ] ;
auto const next_statement_def = ( // operator precedence
       -label_colon
    >> NEXT
    >> -label
    >> -( WHEN >> condition )
    )
    >  ';'
;



// null_statement ::=                                              [LRM93 §8.13]
//      [ label : ] null ;
auto const null_statement_def = ( // operator precedence
       -label_colon
    >> omit[ NULL_ ]
    )
    >  ';'
    ;



// numeric_literal ::=                                            [LRM93 §7.3.1]
//       abstract_literal
//     | physical_literal
auto const numeric_literal_def =  /* order matters */
      physical_literal
    | abstract_literal
    ;


#if 0 // UNUSED, no refererer in BNF (even unused declaration)
// object_declaration ::=                                         [LRM93 §4.3.1]
//       constant_declaration
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


// operator_symbol ::=                                              [LRM93 §2.1]
//     string_literal
auto const operator_symbol_def =
    string_literal
    ;



// options ::=                                                      [LRM93 §9.5]
//     [ guarded ] [ delay_mechanism ]
auto const options_def =
       -GUARDED
    >> -delay_mechanism
    ;



// package_body ::=                                                 [LRM93 §2.6]
//     package body package_simple_name is
//         package_body_declarative_part
//     end [ package body ] [ package_simple_name ] ;
auto const package_body_def = ( // operator precedence
       PACKAGE
    >> BODY
    >> simple_name
    >> IS
    >> package_body_declarative_part
    >> END
    >> -(PACKAGE >> BODY)
    >> -simple_name
    )
    >  ';'
    ;



// package_body_declarative_item ::=                                [LRM93 §2.6]
//       subprogram_declaration
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
    | variable_declaration  // shared_variable_declaration
    | file_declaration
    | alias_declaration
    | use_clause
    | group_template_declaration
    | group_declaration
    ;



// package_body_declarative_part ::=                                [LRM93 §2.6]
//     { package_body_declarative_item }
auto const package_body_declarative_part_def =
    *package_body_declarative_item
    ;



// package_declaration ::=                                          [LRM93 §2.5]
//     package identifier is
//         package_declarative_part
//     end [ package ] [ package_simple_name ] ;
auto const package_declaration_def = ( // operator precedence
       PACKAGE
    >> identifier
    >> IS
    >> package_declarative_part
    >> END
    >> -PACKAGE
    >> -simple_name   // package_simple_name, aka identifier
    )
    >  ';'
    ;



// package_declarative_item ::=                                     [LRM93 §2.5]
//       subprogram_declaration
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



// package_declarative_part ::=                                     [LRM93 §2.5]
//     { package_declarative_item }
auto const package_declarative_part_def =
    *package_declarative_item
    ;



// parameter_specification ::=                                      [LRM93 §8.9]
//     identifier in discrete_range
auto const parameter_specification_def =
       identifier
    >> omit[ IN ]
    >> discrete_range
    ;



// physical_literal ::=                                           [LRM93 §3.1.3]
//     [ abstract_literal ] unit_name
namespace physical_literal_detail {

/* Note, the LRM doesn't specify the allowed characters, hence it's assumed
 * that it follows the natural conventions. */
auto const unit_name = x3::as<ast::string_span>[
    raw[ lexeme[
        +(lower_case_letter | upper_case_letter)
    ]]
];
} // end detail

auto const physical_literal_def =
    -abstract_literal >> (physical_literal_detail::unit_name - keyword)
    ;



// physical_type_definition ::=                                   [LRM93 §3.1.3]
//     range_constraint
//         units
//             primary_unit_declaration
//             { secondary_unit_declaration }
//         end units [ physical_type_simple_name ]
auto const physical_type_definition_def =
       range_constraint
    >> UNITS
    >> primary_unit_declaration
    >> *secondary_unit_declaration
    >> END >> UNITS
    >> -simple_name
    ;



// port_clause ::=                                                [LRM93 §1.1.1]
//     port ( port_list ) ;
auto const port_clause_def = ( // operator precedence
       PORT
    >> '('
    >> interface_list
    >> ')'
    )
    >  ';'
    ;


#if 0 // DISABLED; embedded into port_clause
// port_list ::=                                                [LRM93 §1.1.1.2]
//     port_interface_list
auto const port_list_def =
    interface_list
    ;
#endif


// port_map_aspect ::=                                          [LRM93 §5.2.1.2]
//     port map ( port_association_list )
auto const port_map_aspect_def =
       PORT
    >> MAP
    >> '('
    >> association_list
    >> ')'
    ;



// prefix ::=                                                       [LRM93 §6.1]
//       name
//     | function_call
auto const prefix_def =
      name
    | function_call
    ;



// primary ::=                                                      [LRM93 §7.1]
//       name
//     | literal
//     | aggregate
//     | function_call
//     | qualified_expression
//     | type_conversion
//     | allocator
//     | ( expression )
auto const primary_def =
    /* Order matters; if aggregate is prior expression as of the BNF, a
     * backtracking problem occurred at:
     * aggregate -> element_association -> choices  */
      !char_('"') >> name // ignore string_literals which follow below
    | literal
    | function_call
    | qualified_expression
    //     | type_conversion
    | allocator
    | ( '(' >> expression >> ')' )
    | aggregate
    ;



// primary_unit ::=                                                [LRM93 §11.1]
//       entity_declaration
//     | configuration_declaration
//     | package_declaration
auto const primary_unit_def =
      entity_declaration
    | configuration_declaration
    | package_declaration
    ;




// primary_unit_declaration ::=
//     identifier ;
auto const primary_unit_declaration_def =
       identifier
    >  ';'
    ;



// procedure_call ::=                                               [LRM93 §8.6]
//     procedure_name [ ( actual_parameter_part ) ]
auto const procedure_call_def =
       name
    >> -(
            '(' >> actual_parameter_part >> ')'
        )
    ;



// procedure_call_statement ::=                                     [LRM93 §8.6]
//     [ label : ] procedure_call ;
auto const procedure_call_statement_def = ( // operator precedence
       -label_colon
    >> procedure_call
    )
    >  ';'
    ;



// process_declarative_item ::=                                     [LRM93 §9.2]
//       subprogram_declaration
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



// process_declarative_part ::=                                     [LRM93 §9.2]
//     { process_declarative_item }
auto const process_declarative_part_def =
    *process_declarative_item
    ;



// process_statement ::=                                            [LRM93 §9.2]
//     [ process_label : ]
//         [ postponed ] process [ ( sensitivity_list ) ] [ is ]
//             process_declarative_part
//         begin
//             process_statement_part
//         end [ postponed ] process [ process_label ] ;
auto const process_statement_def = ( // operator precedence
       -label_colon
    >> -POSTPONED
    >> PROCESS
    >> -( '(' >> sensitivity_list >> ')' )
    >> -IS
    >> process_declarative_part
    >> BEGIN
    >> process_statement_part
    >> END
    >> -POSTPONED
    >> PROCESS
    >> -label
    )
    >  ';'
    ;



// process_statement_part ::=                                       [LRM93 §9.2]
//     { sequential_statement }
auto const process_statement_part_def =
    sequence_of_statements
    ;



// qualified_expression ::=                                       [LRM93 §7.3.4]
// type_mark ' ( expression )
//     | type_mark ' aggregate
auto const qualified_expression_def =
    /* Note: This BNF rule is ambiguous, since
     * aggregate           ::= ( element_association { , element_association } )
     * element_association ::= [ choices => ] expression
     * again. AST node takes care on this. */
       type_mark
    >> "\'"
    >> ( "(" >> expression >> ")"
       |  aggregate
       )
    ;



// range ::=                                                        [LRM93 §3.1]
//       range_attribute_name
//     | simple_expression direction simple_expression
namespace range_detail {

auto const range_expression = x3::rule<struct _, ast::range_expression> { "range_expression" } =
       simple_expression
    >> direction
    >> simple_expression
    ;
} // end detail

auto const range_def =
    /* The order is changed to get the longest match, since simple_expression
     * can also be a name as of range_attribute_name */
      range_detail::range_expression
    | attribute_name
    ;



// range_constraint ::=                                             [LRM93 §3.1]
//     range range
auto const range_constraint_def =
    RANGE >> range
    ;



// record_type_definition ::=                                     [LRM93 §3.2.2]
//     record
//         element_declaration
//         { element_declaration }
//     end record [ record_type_simple_name ]
auto const record_type_definition_def =
       RECORD
    >> +element_declaration
    >> END >> RECORD
    >> -simple_name
    ;



// relation ::=                                                     [LRM93 §7.1]
//     shift_expression [ relational_operator shift_expression ]
namespace relation_detail {

auto const chunk = x3::rule<struct _, ast::relation::chunk> { "relation" } =
    relational_operator >> shift_expression
    ;
} // end detail

auto const relation_def =
       shift_expression
    >> -relation_detail::chunk
    ;



// report_statement ::=                                             [LRM93 §8.3]
//     [ label : ]
//     report expression
//     [ severity expression ] ;
auto const report_statement_def = ( // operator precedence
       -label_colon
    >> ( REPORT   >> expression )
    >> -( SEVERITY >> expression )
    )
    >  ';'
    ;



// return_statement ::=                                            [LRM93 §8.12]
//     [ label : ] return [ expression ] ;
auto const return_statement_def = ( // operator precedence
       -label_colon
    >> RETURN
    >> -expression
    )
    >  ';'
;



// scalar_type_definition ::=                                       [LRM93 §3.1]
//       enumeration_type_definition   | integer_type_definition
//     | floating_type_definition      | physical_type_definition
auto const scalar_type_definition_def = /* order matters */
      physical_type_definition
    | enumeration_type_definition
    | range_constraint              // {integer,floating}_type_definition
    ;



// secondary_unit ::=                                              [LRM93 §11.1]
//       architecture_body
//     | package_body
auto const secondary_unit_def =
      architecture_body
    | package_body
    ;



// secondary_unit_declaration ::=                                 [LRM93 §3.1.3]
//     identifier = physical_literal ;
auto const secondary_unit_declaration_def = ( // operator precedence
       identifier
    >> "="
    >> physical_literal
    )
    >  ';'
    ;



// selected_name ::=                                                [LRM93 §6.3]
//     prefix . suffix
namespace detail {

/* LRM93 [§6.3] defined a concept of an expanded name: A selected name (in
 * the syntactic sense) that denotes one or all of the primary units in a
 * library or any named entity within a primary unit.
 * [...]
 * The prefix of an expanded name may not be a function call.
 *
 * The BNF rule results into recursive calling of prefix (which is a name).
 *
 * selected_name ::= prefix . suffix
 * prefix        ::= name | function_call
 * name          ::= ... | selected_name | ...
 * suffix        ::= simple_name | character_literal | operator_symbol | ALL
 *
 * The solution is to mimic the prefix without the name self (limit the name
 * rules). This allows the name to be selected_name too. No rewrote of the name
 * rule so far.*/

struct name_class_;
struct prefix_class_;

using name_type = x3::rule<struct name_class_, ast::name>;
using prefix_list_type = x3::rule<struct prefix_class_, std::vector<ast::prefix>>;

name_type const name { "name" };
prefix_list_type const prefix { "prefix" };

auto const name_def =
      simple_name
    | operator_symbol
//    | indexed_name
//    | slice_name
//    | attribute_name
    ;

// function_call doesn't make sense here
auto const prefix_def = x3::repeat(1, 2)[
        name % '.'
    ]
    ;

BOOST_SPIRIT_DEFINE(name);
BOOST_SPIRIT_DEFINE(prefix);

} // namespace detail

auto const selected_name_def =
    x3::lexeme[
           /*detail::*/prefix
        >> '.'
        >> suffix
    ]
    ;



// selected_signal_assignment ::=                                 [LRM93 §9.5.2]
//     with expression select
//         target    <= options selected_waveforms ;
auto const selected_signal_assignment_def = ( // operator precedence
        WITH
     >> expression
     >> SELECT
     >> target
     >> "<="
     >> options
     >> selected_waveforms
     )
     >  ';'
    ;



// selected_waveforms ::=                                         [LRM93 §9.5.2]
//     { waveform when choices , }
//     waveform when choices
auto const selected_waveforms_def =
    (      waveform
        >> WHEN
        >> choices
    )
    % ','
    ;



// sensitivity_clause ::=                                           [LRM93 §8.1]
//     on sensitivity_list
auto const sensitivity_clause_def =
    ON >> sensitivity_list
    ;



// sensitivity_list ::=                                             [LRM93 §8.1]
//     signal_name { , signal_name }
auto const sensitivity_list_def =
    name % ','
    ;



// sequence_of_statements ::=                                         [LRM93 §8]
//     { sequential_statement }
auto const sequence_of_statements_def =
    *sequential_statement
    ;



// sequential_statement ::=                                           [LRM93 §8]
//       wait_statement
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
//    | procedure_call_statement
    | if_statement
    | case_statement
    | loop_statement
    | next_statement
    | exit_statement
    | return_statement
    | null_statement
    ;



// shift_expression ::=                                             [LRM93 §7.1]
//     simple_expression [ shift_operator simple_expression ]
namespace shift_expression_detail {

auto const chunk = x3::rule<struct _, ast::shift_expression::chunk> { "shift_expression" } =
    shift_operator >> simple_expression
    ;
} // end detail

auto const shift_expression_def =
       simple_expression
    >> -shift_expression_detail::chunk
    ;



// sign ::=                                                         [LRM93 §7.2]
//     + | -
auto const sign_def =
      ("-" >> x3::attr(ast::operator_token::SIGN_NEG))
    | ("+" >> x3::attr(ast::operator_token::SIGN_POS))
    ;



// signal_assignment_statement ::=                                  [LRM93 §8.4]
//     [ label : ] target <= [ delay_mechanism ] waveform ;
auto const signal_assignment_statement_def = ( // operator precedence
       -label_colon
    >> target
    >> "<="
    >> -delay_mechanism
    >> waveform
    )
    >  ';'
    ;



// signal_declaration ::=                                       [LRM93 §4.3.1.2]
//     signal identifier_list : subtype_indication [ signal_kind ] [ := expression ] ;
auto const signal_declaration_def = ( // operator precedence
       omit[ SIGNAL ]
    >> identifier_list
    >> ':'
    >> subtype_indication
    >> -signal_kind
    >> -( ":=" >>  expression )
    )
    >  ';'
    ;



// signal_kind ::=                                              [LRM93 §4.3.1.2]
//     register  |  bus
auto const signal_kind_def =
      REGISTER
    | BUS
    ;



// signal_list ::=                                                  [LRM93 §5.3]
//       signal_name { , signal_name }
//     | others
//     | all
auto const signal_list_def =
      (name % ',')
    | OTHERS
    | ALL
    ;



// signature ::=                                                  [LRM93 §2.3.2]
//     [ [ type_mark { , type_mark } ] [ return type_mark ] ]
auto const signature_def =
       '['
    >> -(type_mark % ',')
    >> -(
          RETURN
       >> type_mark
       )
    >> ']'
    ;



// simple_expression ::=
//     [ sign ] term { adding_operator term }
auto const simple_expression_def =
       -sign
    >> term
    >> *(adding_operator >> term)
    ;



// simple_name ::=                                                  [LRM93 §6.2]
//     identifier
auto const simple_name_def =
    identifier
    ;



// slice_name ::=                                                   [LRM93 §6.5]
//     prefix ( discrete_range )
auto const slice_name_def =
       prefix
    >> '('
    >> discrete_range
    >> ')'
    ;



// string_literal ::=                                              [LRM93 §13.6]
//     " { graphic_character } "
namespace string_literal_detail {

auto const string_literal_1 = x3::rule<struct _, ast::string_span> { "string_literal" } =
    x3::raw[
        *( ( graphic_character - '"'  )
         | ( char_('"')       >> '"' )
         )
    ]
    ;

auto const string_literal_2 = x3::rule<struct _, ast::string_span> { "string_literal" } =
    x3::raw[
        *( ( graphic_character - '%'  )
         | ( char_('%')       >> '%' )
         )
    ]
    ;

} // end detail

auto const string_literal_def =
    lexeme [
          '"' >> x3::raw[string_literal_detail::string_literal_1] >> '"'
        | '%' >> x3::raw[string_literal_detail::string_literal_2] >> '%'
    ]
    ;



// subprogram_body ::=                                              [LRM93 §2.2]
//     subprogram_specification is
//         subprogram_declarative_part
//     begin
//         subprogram_statement_part
//     end [ subprogram_kind ] [ designator ] ;
auto const subprogram_body_def = ( // operator precedence
       subprogram_specification
    >> IS
    >> subprogram_declarative_part
    >> BEGIN
    >> subprogram_statement_part
    >> END
    >> -subprogram_kind
    >> -designator
    )
    >  ';'
    ;



// subprogram_declaration ::=                                       [LRM93 §2.1]
//     subprogram_specification ;
auto const subprogram_declaration_def =
      subprogram_specification
    >  ';'
    ;



// subprogram_declarative_item ::=                                  [LRM93 §2.2]
//       subprogram_declaration
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



// subprogram_declarative_part ::=                                  [LRM93 §2.2]
//     { subprogram_declarative_item }
auto const subprogram_declarative_part_def =
    *subprogram_declarative_item
    ;



// subprogram_kind ::=                                              [LRM93 §2.2]
//     procedure | function
auto const subprogram_kind_def =
      distinct("procedure", ast::keyword_token::PROCEDURE)
    | distinct("function", ast::keyword_token::FUNCTION)
    ;



// subprogram_specification ::=                                     [LRM93 §2.1]
//       procedure designator [ ( formal_parameter_list ) ]
//     | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
//       return type_mark
namespace subprogram_specification_detail {

auto const procedure = x3::rule<struct _, ast::subprogram_specification_procedure> { "subprogram_specification.procedure" } =
       PROCEDURE
    >> designator
    >> -(      '('
            >> formal_parameter_list
            >> ')'
        )
    ;

auto const function = x3::rule<struct _, ast::subprogram_specification_function> { "subprogram_specification.function" } =
       -(IMPURE | PURE)
    >> FUNCTION
    >> designator
    >> -(      '('
            >> formal_parameter_list
            >> ')'
        )
    >> RETURN
    >> type_mark
    ;
} // end detail

auto const subprogram_specification_def =
      subprogram_specification_detail::procedure
    | subprogram_specification_detail::function
    ;



// subprogram_statement_part ::=                                    [LRM93 §2.2]
//     { sequential_statement }
auto const subprogram_statement_part_def =
    sequence_of_statements
    ;



// subtype_declaration ::=
//     subtype identifier is subtype_indication ;
auto const subtype_declaration_def = ( // operator precedence
       SUBTYPE
    >> identifier
    >> IS
    >> subtype_indication
    )
    >  ';'
    ;



// subtype_indication ::=                                           [LRM93 §4.2]
//     [ resolution_function_name ] type_mark [ constraint ]
auto const subtype_indication_def =
    /* parse a list of unspecified names, since
     *      resolution_function_name ::= name
     *      type_mark                ::= type_name | subtype_name
     * is ambiguous, even with optional. Nevertheless, syntactically
     * resolution_function_name and type_mark are names, semantically matters on
     * context as of VHDL.
     * Further more, 2nd name can be a keyword (which can't be a name), hence
     * the alternative parse branch. */
    (
       x3::repeat(1 ,2)[
          name          // range as keyword can follow; name forbids keywords!
       ]
       >> -constraint
    )
    |
    (
       x3::repeat(1)[
          name          // mandatory type_mark ...
       ]
       >> -constraint   // followed by keyword RANGE ...
    )
    ;



// suffix ::=                                                       [LRM93 §6.3]
//       simple_name
//     | character_literal
//     | operator_symbol
//     | all
auto const suffix_def =
      simple_name
    | character_literal
    | operator_symbol
    | ALL
    ;



// target ::=                                                       [LRM93 §8.4]
//       name
//     | aggregate
auto const target_def =
      name
    | aggregate
    ;



// term ::=                                                         [LRM93 §7.1]
//     factor { multiplying_operator factor }
auto const term_def =
    /* There is no expectation point: Consider the case of '-5 mod -3', where
     * mod is a multiplying operator with an higher operator precedence as the
     * sign operator. This is no valid VHDL and would in case of use of an
     * expectation point result into expectation_failure. See
     * 'test_case/expression_failure/expression_failure_003', or even the
     * [Sigasi: Be careful with VHDL operator precedence](
     * http://insights.sigasi.com/tech/be-careful-vhdl-operator-precedence.html)
     */
    factor >> *( multiplying_operator >> factor )
    ;



// timeout_clause ::=                                               [LRM93 §8.1]
//     for time_expression
auto const timeout_clause_def =
    FOR >> expression
    ;



// type_conversion ::=                                            [LRM93 §7.3.5]
//     type_mark ( expression )
auto const type_conversion_def =
       type_mark
    >> '(' >> expression >> ')'
    ;



// type_declaration ::=                                             [LRM93 §4.1]
//       full_type_declaration
//     | incomplete_type_declaration
auto const type_declaration_def = ( // operator precedence
       /* Note, this node covers both alternatives from BNF:
        * full_type_declaration       ::= TYPE identifier IS type_definition ;
        * incomplete_type_declaration ::= TYPE identifier ;
        */
       TYPE
    >> identifier
    >> -( IS >> type_definition )
    )
    >  ';'
    ;



// type_definition ::=                                              [LRM93 §4.1]
//       scalar_type_definition
//     | composite_type_definition
//     | access_type_definition
//     | file_type_definition
auto const type_definition_def =
      scalar_type_definition
    | composite_type_definition
    | access_type_definition
    | file_type_definition
    ;



// type_mark ::=
//       type_name
//     | subtype_name
auto const type_mark_def =
    /* There is no way to distinguish between type_name and subtype_name at
     * parser level. Further read
     * [Question about type_mark bnf](
     * https://groups.google.com/forum/#!topic/comp.lang.vhdl/exUhoMrFavU) */
    name
    ;



// unconstrained_array_definition ::=                             [LRM93 §3.2.1]
//     array ( index_subtype_definition { , index_subtype_definition } )
//         of element_subtype_indication
auto const unconstrained_array_definition_def =
       ARRAY
    >> '(' >> (index_subtype_definition % ',') >>  ')'
    >> OF
    >> subtype_indication
    ;



// use_clause ::=                                                  [LRM93 §10.4]
//     use selected_name { , selected_name } ;
namespace use_clause_detail {

/* LRM93 [§6.3] defined a concept of an expanded name: A selected name (in
 * the syntactic sense) that denotes one or all of the primary units in a
 * library or any named entity within a primary unit.
 * [...]
 * The prefix of an expanded name may not be a function call.
 *
 * For the use clause hence a specialized version is required. See Notes
 * at the AST node ast::use_clause. */

auto const lib_prefix = x3::rule<struct _, std::vector<ast::name>> { "prefix" } =
    x3::lexeme[
        name >> '.' >> name
    ];

auto const pkg_prefix = x3::rule<struct _, std::vector<ast::name>> { "prefix" } =
    x3::repeat(1)[ // enforce artificial vector to unify ast node
        name
    ];

auto const lib_selected_name = x3::rule<struct _, ast::use_clause::selected_name> { "selected_name" } =
    x3::lexeme[
           lib_prefix
        >> '.'
        >> suffix
    ]
    ;

auto const pkg_selected_name = x3::rule<struct _, ast::use_clause::selected_name> { "selected_name" } =
    x3::lexeme[
           pkg_prefix
        >> '.'
        >> suffix
    ]
    ;

auto const selected_name = x3::rule<struct _, ast::use_clause::selected_name> { "selected_name" } =
      lib_selected_name
    | pkg_selected_name
    ;
} // end detail

auto const use_clause_def = ( // operator precedence
       USE
    >> (use_clause_detail::selected_name % ',')
    )
    >  ';'
    ;



// variable_assignment_statement ::=                                [LRM93 §8.5]
//     [ label : ] target  := expression ;
auto const variable_assignment_statement_def = ( // operator precedence
       -label_colon
    >> target
    >> ":="
    >> expression
    )
    >  ';'
    ;



// variable_declaration ::=                                     [LRM93 §4.3.1.3]
//     [ shared ] variable identifier_list : subtype_indication [ := expression ] ;
auto const variable_declaration_def = ( // operator precedence
      -SHARED
    >> omit[ VARIABLE ]
    >> identifier_list
    >> ':'
    >> subtype_indication
    >> -(  ":=" >>  expression )
    )
    >  ';'
    ;



// wait_statement ::=                                               [LRM93 §8.1]
//     [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ] ;
auto const wait_statement_def = ( // operator precedence
       -( label >> ':' )
    >> WAIT
    >> -sensitivity_clause
    >> -condition_clause
    >> -timeout_clause
    )
    >  ';'
    ;



// waveform ::=                                                     [LRM93 §8.4]
//       waveform_element { , waveform_element }
//     | unaffected
auto const waveform_def =
      (waveform_element % ',')
    | UNAFFECTED
    ;



// waveform_element ::=                                           [LRM93 §8.4.1]
//       value_expression [ after time_expression ]
//     | null [ after time_expression ]
auto const waveform_element_def =
       ( expression | NULL_ )
    >>  -( AFTER >> expression )
    ;


} // namespace parser
} // namespace vhdl
} // namespace eda


/*******************************************************************************
 * Spirit.X3 BNF Rule Definitions
 */
namespace eda {
namespace vhdl {
namespace parser {

#include <eda/compiler/warnings_off.hpp>


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
      base
    , based_integer
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

#include <eda/compiler/warnings_on.hpp>


} // namespace parser
} // namespace vhdl
} // namespace eda


/*******************************************************************************
 * Annotation and Error handling
 *
 * Note, the AST odes are tagged with ast::position_tagged which is of type
 * x3::position_tagged. The intension was to extend this approach to tag
 * also the file (id) where the node belongs to as show by Baptiste Wicht's
 * [Compiler of the EDDI programming language](
 * https://github.com/wichtounet/eddic).
 * For convenience (and since this approach isn't realized yet), Spirit.X3's
 * ID are derived from on_success_base (obviously must be changed in
 * the future).
 */
namespace eda {
namespace vhdl {
namespace parser {

// clang-format off
struct abstract_literal_class : on_success_base {};
struct access_type_definition_class : on_success_base {};
struct actual_designator_class : on_success_base {};
struct actual_parameter_part_class : on_success_base {};
struct actual_part_class : on_success_base {};
struct aggregate_class : on_success_base {};
struct alias_declaration_class : on_success_base {};
struct alias_designator_class : on_success_base {};
struct allocator_class : on_success_base {};
struct architecture_body_class : on_success_base {};
struct architecture_declarative_part_class : on_success_base {};
struct architecture_statement_part_class : on_success_base {};
struct array_type_definition_class : on_success_base {};
struct assertion_class : on_success_base {};
struct assertion_statement_class : on_success_base {};
struct association_element_class : on_success_base {};
struct association_list_class : on_success_base {};
struct attribute_declaration_class : on_success_base {};
struct attribute_designator_class : on_success_base {};
struct attribute_name_class : on_success_base {};
struct attribute_specification_class : on_success_base {};
struct base_class : on_success_base {};
struct based_integer_class : on_success_base {};
struct based_literal_class : on_success_base {};
//struct basic_graphic_character_class : on_success_base {};    // char isn't tagable
struct basic_identifier_class : on_success_base {};
struct binding_indication_class : on_success_base {};
struct bit_string_literal_class : on_success_base {};
struct block_configuration_class : on_success_base {};
struct block_declarative_item_class : on_success_base {};
struct block_declarative_part_class : on_success_base {};
struct block_header_class : on_success_base {};
struct block_specification_class : on_success_base {};
struct block_statement_class : on_success_base {};
struct block_statement_part_class : on_success_base {};
struct case_statement_class : on_success_base {};
struct case_statement_alternative_class : on_success_base {};
struct character_literal_class : on_success_base {};
struct choice_class : on_success_base {};
struct choices_class : on_success_base {};
struct component_configuration_class : on_success_base {};
struct component_declaration_class : on_success_base {};
struct component_instantiation_statement_class : on_success_base {};
struct component_specification_class : on_success_base {};
struct composite_type_definition_class : on_success_base {};
struct concurrent_assertion_statement_class : on_success_base {};
struct concurrent_procedure_call_statement_class : on_success_base {};
struct concurrent_signal_assignment_statement_class : on_success_base {};
struct concurrent_statement_class : on_success_base {};
struct condition_class : on_success_base {};
struct condition_clause_class : on_success_base {};
struct conditional_signal_assignment_class : on_success_base {};
struct conditional_waveforms_class : on_success_base {};
struct configuration_declaration_class : on_success_base {};
struct configuration_declarative_item_class : on_success_base {};
struct configuration_declarative_part_class : on_success_base {};
struct configuration_item_class : on_success_base {};
struct configuration_specification_class : on_success_base {};
struct constant_declaration_class : on_success_base {};
struct constrained_array_definition_class : on_success_base {};
struct constraint_class : on_success_base {};
struct context_clause_class : on_success_base {};
struct context_item_class : on_success_base {};
struct decimal_literal_class : on_success_base {};
struct delay_mechanism_class : on_success_base {};
struct design_file_class : on_success_base, on_error_base {}; // our start rule
struct design_unit_class : on_success_base {};
struct designator_class : on_success_base {};
struct direction_class : on_success_base {};
struct disconnection_specification_class : on_success_base {};
struct discrete_range_class : on_success_base {};
struct element_association_class : on_success_base {};
struct element_declaration_class : on_success_base {};
struct element_subtype_definition_class : on_success_base {};
struct entity_aspect_class : on_success_base {};
struct entity_class_class : on_success_base {};
struct entity_class_entry_class : on_success_base {};
struct entity_class_entry_list_class : on_success_base {};
struct entity_declaration_class : on_success_base {};
struct entity_declarative_item_class : on_success_base {};
struct entity_declarative_part_class : on_success_base {};
struct entity_designator_class : on_success_base {};
struct entity_header_class : on_success_base {};
struct entity_name_list_class : on_success_base {};
struct entity_specification_class : on_success_base {};
struct entity_statement_class : on_success_base {};
struct entity_statement_part_class : on_success_base {};
struct entity_tag_class : on_success_base {};
struct enumeration_literal_class : on_success_base {};
struct enumeration_type_definition_class : on_success_base {};
struct exit_statement_class : on_success_base {};
struct exponent_class : on_success_base {};
struct expression_class : on_success_base {};
struct extended_identifier_class : on_success_base {};
struct factor_class : on_success_base {};
struct file_declaration_class : on_success_base {};
struct file_logical_name_class : on_success_base {};
struct file_open_information_class : on_success_base {};
struct file_type_definition_class : on_success_base {};
struct formal_designator_class : on_success_base {};
struct formal_parameter_list_class : on_success_base {};
struct formal_part_class : on_success_base {};
struct function_call_class : on_success_base {};
struct generate_statement_class : on_success_base {};
struct generation_scheme_class : on_success_base {};
struct generic_clause_class : on_success_base {};
struct generic_list_class : on_success_base {};
struct generic_map_aspect_class : on_success_base {};
//struct graphic_character_class : on_success_base {};     // char isn't tagable
struct group_constituent_class : on_success_base {};
struct group_constituent_list_class : on_success_base {};
struct group_template_declaration_class : on_success_base {};
struct group_declaration_class : on_success_base {};
struct guarded_signal_specification_class : on_success_base {};
struct identifier_class : on_success_base {};
struct identifier_list_class : on_success_base {};
struct if_statement_class : on_success_base {};
struct index_constraint_class : on_success_base {};
struct index_specification_class : on_success_base {};
struct index_subtype_definition_class : on_success_base {};
struct indexed_name_class : on_success_base {};
struct instantiated_unit_class : on_success_base {};
struct instantiation_list_class : on_success_base {};
struct integer_class : on_success_base {};
struct interface_constant_declaration_class : on_success_base {};
struct interface_declaration_class : on_success_base {};
struct interface_element_class : on_success_base {};
struct interface_file_declaration_class : on_success_base {};
struct interface_list_class : on_success_base {};
struct interface_signal_declaration_class : on_success_base {};
struct interface_variable_declaration_class : on_success_base {};
struct iteration_scheme_class : on_success_base {};
struct label_class : on_success_base {};
struct letter_class : on_success_base {};
struct letter_or_digit_class : on_success_base {};
struct library_clause_class : on_success_base {};
struct library_unit_class : on_success_base {};
struct literal_class : on_success_base {};
struct logical_name_class : on_success_base {};
struct logical_name_list_class : on_success_base {};
struct loop_statement_class : on_success_base {};
struct mode_class : on_success_base {};
struct name_class : on_success_base {};
struct next_statement_class : on_success_base {};
struct null_statement_class : on_success_base {};
struct numeric_literal_class : on_success_base {};
struct operator_symbol_class : on_success_base {};
struct options_class : on_success_base {};
struct package_body_class : on_success_base {};
struct package_body_declarative_item_class : on_success_base {};
struct package_body_declarative_part_class : on_success_base {};
struct package_declaration_class : on_success_base {};
struct package_declarative_item_class : on_success_base {};
struct package_declarative_part_class : on_success_base {};
struct parameter_specification_class : on_success_base {};
struct physical_literal_class : on_success_base {};
struct physical_type_definition_class : on_success_base {};
struct port_clause_class : on_success_base {};
struct port_list_class : on_success_base {};
struct port_map_aspect_class : on_success_base {};
struct prefix_class : on_success_base {};
struct primary_class : on_success_base {};
struct primary_unit_class : on_success_base {};
struct primary_unit_declaration_class : on_success_base {};
struct procedure_call_class : on_success_base {};
struct procedure_call_statement_class : on_success_base {};
struct process_declarative_item_class : on_success_base {};
struct process_declarative_part_class : on_success_base {};
struct process_statement_class : on_success_base {};
struct process_statement_part_class : on_success_base {};
struct qualified_expression_class : on_success_base {};
struct range_class : on_success_base {};
struct range_constraint_class : on_success_base {};
struct record_type_definition_class : on_success_base {};
struct relation_class : on_success_base {};
struct report_statement_class : on_success_base {};
struct return_statement_class : on_success_base {};
struct scalar_type_definition_class : on_success_base {};
struct secondary_unit_class : on_success_base {};
struct secondary_unit_declaration_class : on_success_base {};
struct selected_name_class : on_success_base {};
struct selected_signal_assignment_class : on_success_base {};
struct selected_waveforms_class : on_success_base {};
struct sensitivity_clause_class : on_success_base {};
struct sensitivity_list_class : on_success_base {};
struct sequence_of_statements_class : on_success_base {};
struct sequential_statement_class : on_success_base {};
struct shift_expression_class : on_success_base {};
struct sign_class : on_success_base {};
struct signal_assignment_statement_class : on_success_base {};
struct signal_declaration_class : on_success_base {};
struct signal_kind_class : on_success_base {};
struct signal_list_class : on_success_base {};
struct signature_class : on_success_base {};
struct simple_expression_class : on_success_base {};
struct simple_name_class : on_success_base {};
struct slice_name_class : on_success_base {};
struct string_literal_class : on_success_base {};
struct subprogram_body_class : on_success_base {};
struct subprogram_declaration_class : on_success_base {};
struct subprogram_declarative_item_class : on_success_base {};
struct subprogram_declarative_part_class : on_success_base {};
struct subprogram_kind_class : on_success_base {};
struct subprogram_specification_class : on_success_base {};
struct subprogram_statement_part_class : on_success_base {};
struct subtype_declaration_class : on_success_base {};
struct subtype_indication_class : on_success_base {};
struct suffix_class : on_success_base {};
struct target_class : on_success_base {};
struct term_class : on_success_base {};
struct timeout_clause_class : on_success_base {};
struct type_conversion_class : on_success_base {};
struct type_declaration_class : on_success_base {};
struct type_definition_class : on_success_base {};
struct type_mark_class : on_success_base {};
struct unconstrained_array_definition_class : on_success_base {};
struct use_clause_class : on_success_base {};
struct variable_assignment_statement_class : on_success_base {};
struct variable_declaration_class : on_success_base {};
struct wait_statement_class : on_success_base {};
struct waveform_class : on_success_base {};
struct waveform_element_class : on_success_base {};
// clang-format on

} // namespace parser
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_DEF_HPP_ */
