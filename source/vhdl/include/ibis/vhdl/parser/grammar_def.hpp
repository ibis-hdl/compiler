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
    /// Attribute-less overload.
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
auto const FUNCTION = distinct("function", ast::keyword_token::FUNCTION);
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
auto const PROCEDURE = distinct("procedure", ast::keyword_token::PROCEDURE);
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

///
/// Symbols of all keyword to distinguish them from identifier by rule
///
x3::symbols<> const keywords(
    { "abs",          "access",     "after",      "alias",     "all",       "and",
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
      "xor" },  // --
    "keyword");

auto const keyword = x3::rule<struct keyword_class>{ "keyword" } = distinct(keywords);

}  // namespace ibis::vhdl::parser::keywords

//******************************************************************************
// Operators
//
namespace ibis::vhdl::parser::operators {

using detail::distinct;

///
/// @name miscellaneous_operator                                    [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// miscellaneous_operator ::=  ** | abs | not
/// @endcode
///
///@{
auto const binary_miscellaneous_operator =
    x3::rule<struct binary_miscellaneous_operator_class, ast::operator_token>{
        "miscellaneous operator"
    } = x3::lit("**") >> x3::attr(ast::operator_token::EXPONENT);

auto const ABS = distinct("abs", ast::operator_token::ABS);
auto const NOT = distinct("not", ast::operator_token::NOT);

auto const unary_miscellaneous_operator =
    x3::rule<struct unary_miscellaneous_operator_class, ast::operator_token>{
        "miscellaneous operator"
    } = ABS | NOT;
///@}

///
/// @name logical_operator                                          [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// logical_operator ::=  and | or | nand | nor | xor | xnor
/// @endcode
///
///@{
x3::symbols<ast::operator_token> const binary_logical_operator_symbols(
    // clang-format off
    {
        { "and",  ast::operator_token::AND },
        { "or",   ast::operator_token::OR },
        { "xor",  ast::operator_token::XOR },
        { "xnor", ast::operator_token::XNOR }
    },
    "logical operator"
    // clang-format on
);

// clang-format off
auto const binary_logical_operator =
    x3::rule<struct binary_logical_operator_class, ast::operator_token>{ "logical operator" } =
        distinct(binary_logical_operator_symbols);

auto const NAND = distinct("nand", ast::operator_token::NAND);
auto const NOR = distinct("nor", ast::operator_token::NOR);

auto const unary_logical_operator =
    x3::rule<struct unary_logical_operator_class, ast::operator_token>{ "logical operator" } =
        NAND | NOR;
// clang-format on
///@}

///
/// @name relational_operator                                        [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// relational_operator ::=   =  |  /=  |  <  |  <=  |  >  |  >=
/// @endcode
///@{
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
    "relational operator"
    // clang-format on
);
///@}

///
/// @name adding_operator                                            [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// adding_operator ::=  + | -  | &
/// @endcode
///@{
x3::symbols<ast::operator_token> const adding_operator(
    // clang-format off
    {
        { "+", ast::operator_token::ADD },
        { "-", ast::operator_token::SUB },
        { "&", ast::operator_token::CONCAT }
    },
    "adding operator"
    // clang-format on
);
///@}

///
/// @name multiplying_operator ::=                                  [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// multiplying_operator ::=  * | / | mod | rem
/// @endcode
///@{
auto const MUL = x3::lit('*') >> x3::attr(ast::operator_token::MUL);
auto const DIV = x3::lit('/') >> x3::attr(ast::operator_token::DIV);
auto const MOD = distinct("mod", ast::operator_token::MOD);
auto const REM = distinct("rem", ast::operator_token::REM);

// clang-format off
auto const multiplying_operator =
    x3::rule<struct multiplying_operator_class, ast::operator_token>{ "multiplying operator" } =
        MUL | DIV | MOD | REM;
// clang-format on        
///@}

///
/// @name shift_operator                                            [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// shift_operator ::=  sll | srl | sla | sra | rol | ror
/// @endcode
///@{
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
    "shift operator"
    // clang-format on
);

// clang-format off
auto const shift_operator = x3::rule<struct shift_operator_class, ast::operator_token>{ "shift operator" } =
    distinct(shift_operator_symbols);
// clang-format on        
///@}

}  // namespace ibis::vhdl::parser::operators

//******************************************************************************
// Rule Instances
//
namespace ibis::vhdl::parser {

configuration_item_type const configuration_item{ "configuration item" };
concurrent_statement_type const concurrent_statement{ "concurrent statement" };
constraint_type const constraint{ "constraint" };
sequence_of_statements_type const sequence_of_statements{ "sequence of statements" };
subprogram_declarative_item_type const subprogram_declarative_item{ "subprogram declarative item" };

/// top level
design_file_type const design_file{ "design file" };

// start rule
grammar_type const grammar_entry{ "VHDL" };

// other
attribute_name_type const attribute_name{ "attribute name" };
expression_type const expression{ "expression" };
function_call_type const function_call{ "function call" };
indexed_name_type const indexed_name{ "indexed name" };
literal_type const literal{ "literal" };
name_type const name{ "name" };
prefix_type const prefix{ "prefix" };
primary_type const primary{ "primary" };
range_type const range{ "range" };
selected_name_type const selected_name{ "selected name" };
slice_name_type const slice_name{ "slice name" };

}  // namespace ibis::vhdl::parser

//******************************************************************************
// BNF rule definitions
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
using iso8859_1::space;
using iso8859_1::lit;
using x3::lexeme;
using x3::omit;
using x3::raw;

using detail::distinct;

// ----------------------------------------------------------------------------
// Character Sets                                                 [LRM93 §13.1]
// ----------------------------------------------------------------------------

//
// basic_character ::= basic_graphic_character | format_effector
//
// @todo write unit test for correct support of VHDL's character sets 
#if 0
// clang-format off
auto const upper_case_letter = x3::rule<struct upper_case_letter_class, char>{ "upper case letter" } =
    char_("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ")
    ;
auto const lower_case_letter = x3::rule<struct lower_case_letter_class, char>{ "lower case letter" } =
    char_("abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ")
    ;
auto const special_character = x3::rule<struct special_character_class, char>{ "special character" } =
    char_("\"#&'()*+,-./:;<=>[]_|")
    ;
auto const other_special_character = x3::rule<struct other_special_character_class, char>{ "other special character" } =
    char_("!$%?@\\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷")
    ;
auto const space_character = x3::rule<struct space_character_class, char>{ "space character" } =
    iso8859_1::space
    ;
auto const format_effector = x3::rule<struct format_effector_class>{ "format effector" } =
    char_("\t\n\v\r\f")
    ;
// clang-format on


///
/// basic_graphic_character ::=                                    [LRM93 §13.1]
///     upper_case_letter | digit | special_character| space_character
// clang-format off
auto const basic_graphic_character = x3::rule<struct basic_graphic_character_class, char>{ "basic graphic character" } =
      upper_case_letter
    | digit
    | special_character
    | space_character
    ;
// clang-format on
#endif

// clang-format off
auto const digit = x3::rule<struct digit_class, char>{ "digit" } =
    x3::digit // char_("0-9");
    ;
// clang-format on

///
/// extended_digit                                               [LRM93 §13.4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// extended_digit ::=
///     digit | letter
/// @endcode
///
// clang-format off
auto const extended_digit = x3::rule<struct extended_digit_class, char>{ "extended digit" } =
    x3::xdigit  // char_("0-9a-fA-F");
    ;
// clang-format on

///
/// graphic_character                                              [LRM93 §13.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// graphic_character ::=
///      basic_graphic_character
///    | lower_case_letter
///    | other_special_character
/// @endcode
///
/// The VHDL93 charset encoding is ISO-8859-1.
/// The graph below shows the the interaction of the individual rules from LRM.
/// Not sure how this can be replaced with the x3 char parser, see testsuite
/// ``vhdl93_charset_test``. The copy & paste charset  from LRM93 starts with
/// 32d until 126d, 127d is "delete", continues with 129d-191d, leave out 192d to 194d,
/// and ends with 195d. Formally 196d until 255d is also printable ... To simplify
/// ``x3::print`` is used which matches a character based on the equivalent of
/// ``std::isprint``.
///
/// @dot
/// digraph graphic_character {
///     graphic_character[style=filled];
///     basic_character[style=filled,color=lightgray];
///     letter_or_digit[style=filled,color=lightgray];
///     extended_digit[style=filled,color=lightgray];
///
/// 	basic_graphic_character -> basic_character;
/// 	format_effector         -> basic_character;
///
/// 	upper_case_letter -> basic_graphic_character;
/// 	digit             -> basic_graphic_character;
/// 	special_character -> basic_graphic_character;
/// 	space_character   -> basic_graphic_character;
///
/// 	digit  -> extended_digit;
/// 	letter -> extended_digit;
///
/// 	basic_graphic_character -> graphic_character;
/// 	lower_case_letter       -> graphic_character;
/// 	other_special_character -> graphic_character;
///
/// 	upper_case_letter -> letter;
/// 	lower_case_letter -> letter;
///
/// 	letter -> letter_or_digit;
/// 	digit  -> letter_or_digit;
///
/// 	graphic_character -> character_literal;
///
///     // used by, e.g. ...
/// 	graphic_character -> extended_identifier;
/// 	graphic_character -> string_literal;
/// }
/// @enddot
///
/// @see Boost Spirit X3 [iso8859_1.hpp](
///      https://github.com/boostorg/spirit/blob/master/include/boost/spirit/home/support/char_encoding/iso8859_1.hpp)
/// @see Boost Spirit X3 [Character Parsers](
///     https://www.boost.org/doc/libs/1_76_0/libs/spirit/doc/x3/html/spirit_x3/quick_reference/char.html)
///
/// @todo Check for X3 character parser to use them in the related/this rule.
///
// clang-format off
auto const graphic_character = x3::rule<struct graphic_character_class, char>{ "graphic character" } =
    x3::graph
    ;
// clang-format on

///
/// letter                                                       [LRM93 §13.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// letter ::= upper_case_letter | lower_case_letter
/// @endcode
///
/// @see [X3 Character Classification Parsers (alnum, digit, etc.)](
///       https://www.boost.org/doc/libs/1_76_0/libs/spirit/doc/html/spirit/qi/reference/char/char_class.html)
/// @see [cppreference.com isalpha](https://en.cppreference.com/w/cpp/string/byte/isalpha)
///
// clang-format off
auto const letter = x3::rule<struct letter_class, char>{ "letter" } =
    x3::alpha
    ;
// clang-format on

///
/// letter_or_digit                                              [LRM93 §13.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// letter_or_digit ::= letter | digit
/// @endcode
///
/// @see [X3 Character Classification Parsers (alnum, digit, etc.)](
///       https://www.boost.org/doc/libs/1_76_0/libs/spirit/doc/html/spirit/qi/reference/char/char_class.html)
/// @see [cppreference.com isalnum](https://en.cppreference.com/w/cpp/string/byte/isalnum)
///
// clang-format off
auto const letter_or_digit = x3::rule<struct letter_or_digit_class, char>{ "letter or digit" } =
    x3::alnum   // letter | digit
    ;
// clang-format on    

// ----------------------------------------------------------------------------
// Non recursive rules (without dependencies to other rules)
// ----------------------------------------------------------------------------

///
/// comment                                                            [§ 13.8]
///
// clang-format off
auto const comment = x3::rule<struct comment_class, x3::unused_type>{ "comment" } =
    "--" >> *(char_ - x3::eol) >> x3::eol
    ;
// clang-format on

///
/// integer                                                          [§ 13.4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// integer ::=
///     digit { [ underline ] digit }
/// @endcode
///
// clang-format off
auto const integer = x3::rule<struct integer_class, ast::string_span>{ "integer" } =
    raw[ lexeme [
        digit >> *( -lit("_") >> digit )
    ]]
    ;
// clang-format on

///
/// base                                                         [LRM93 §13.4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// base ::=
///     integer
/// @endcode
///
// clang-format off
auto const base = x3::rule<struct base_class, ast::string_span>{ "base" } =
    integer
    ;
// clang-format on

///
/// based_integer                                                [LRM93 §13.4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// based_integer ::=
///     extended_digit { [ underline ] extended_digit }
/// @endcode
///
// clang-format off
auto const based_integer = x3::rule<struct based_integer_class, ast::string_span>{ "based integer" } =
    raw [ lexeme[
        extended_digit >> *( -lit('_') >> extended_digit )
    ]]
    ;
// clang-format on

///
/// @fn basic_identifier                                            [LRM93 §13.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// basic_identifier ::=
///     letter { [ underline ] letter_or_digit }
/// @endcode
///
namespace detail {

// clang-format off
auto const basic_identifier_feasible = x3::rule<struct basic_identifier_feasible_, ast::string_span>{ "basic identifier" } =
    raw[ lexeme [
           letter
        >> !lit('"') // reject bit_string_literal
        >> *( '_' >> letter_or_digit | letter_or_digit )
    ]]
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const basic_identifier = x3::rule<struct basic_identifier_class, ast::string_span>{ "basic identifier" } =
    detail::basic_identifier_feasible - keyword
    ;
// clang-format on

///
/// @fn bit_string_literal                                         [LRM93 §13.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// bit_string_literal ::=
///     base_specifier " bit_value "
/// @endcode
///
/// with:
///
/// @code{.bnf}
/// base_specifier ::=
///     B | O | X
///
/// bit_value ::=
///     extended_digit { [ underline ] extended_digit }
/// @endcode
///
namespace detail {

// Helper function to generate parsers for different types of bit_string_literal.
// clang-format off
auto const bit_string_literal = [](auto&& base, auto&& char_range, auto&& attr)
{
    using CharT = decltype(char_range);
    using AttrT = decltype(attr);

    auto const char_set = [](auto&& char_range_) {
        return x3::rule<struct _, ast::string_span>{ "bit string literal" } = x3::as_parser(
             raw[ lexeme[
                    char_(std::forward<CharT>(char_range_))
                 >> *( -lit("_") >> char_(std::forward<CharT>(char_range_) ))
             ]]
        );
    };

    return x3::rule<struct _, ast::bit_string_literal>{ "bit string literal" } = x3::as_parser(
        lexeme[
               x3::omit[char_(std::forward<decltype(base)>(base))]
            >> lit('"')
            >> char_set(std::forward<CharT>(char_range))
            >> lit('"')
        ]
        >> x3::attr(std::forward<AttrT>(attr))
    );
};
// clang-format on

}  // namespace detail

// clang-format off
auto const bit_string_literal = x3::rule<struct bit_string_literal_class, ast::bit_string_literal>{ "bit string literal" } =
      detail::bit_string_literal("Bb", "01",        ast::bit_string_literal::base_specifier::bin)
    | detail::bit_string_literal("Xx", "0-9a-fA-F", ast::bit_string_literal::base_specifier::hex)
    | detail::bit_string_literal("Oo", "0-7",       ast::bit_string_literal::base_specifier::oct)
    ;
// clang-format on

///
/// character_literal                                              [LRM93 §13.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// character_literal ::=
///     ' graphic_character '
/// @endcode
///
// clang-format off
auto const character_literal = x3::rule<struct character_literal_class, ast::character_literal>{ "character literal" } =
    x3::lexeme [
        "\'" >> ( ( graphic_character - '\'' ) | char_("\'") ) >> "\'"
    ]
    ;
// clang-format on

///
/// condition                                                       [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// condition ::=
///     boolean_expression
/// @endcode
///
// clang-format off
auto const condition = x3::rule<struct condition_class, ast::condition>{ "condition" } =
    expression
    ;
// clang-format on

///
/// delay_mechanism                                                 [LRM93 §8.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// delay_mechanism
///       transport
///     | [ reject time_expression ] inertial
/// @endcode
///
// clang-format off
auto const delay_mechanism = x3::rule<struct delay_mechanism_class, ast::delay_mechanism>{ "delay mechanism" } =
      TRANSPORT
    | -( REJECT >> expression ) >> INERTIAL
    ;
// clang-format on

///
/// options                                                         [LRM93 §9.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// options ::=
///     [ guarded ] [ delay_mechanism ]
/// @endcode
///
// clang-format off
auto const options = x3::rule<struct options_class, ast::options>{ "options" } =
    -GUARDED >> -delay_mechanism
    ;
// clang-format on

///
/// exponent                                                     [LRM93 §13.4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// exponent ::=
///     E [ + ] integer | E - integer
/// @endcode
///
/// Note, following IEEE1076-93 Ch. 13.4, the exponent on integer type must not have a minus
/// sign. This means implicit (even from NBF) that a positive (optional) sign is allowed.
///
// clang-format off
auto const exponent = [](auto&& signs) {
    using CharT = decltype(signs);
    return x3::rule<struct exponent_class, ast::string_span>{ "exponent" } = x3::as_parser(
        raw[ lexeme [
            char_("Ee") >> -char_(std::forward<CharT>(signs)) >> integer
        ]]
    );
};
// clang-format on

///
/// @fn extended_identifier                                       [LRM93 §13.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// extended_identifier ::=
///     \ graphic_character { graphic_character } \
/// @endcode
///
namespace detail {

// clang-format off
auto const ext_identifier_atom = x3::rule<struct ext_id_atom, ast::string_span>{ "extended identifier" } =
    raw[ lexeme [
           char_('\\')
        >> +( graphic_character - char_('\\') )
        >> char_('\\')
    ]]
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const extended_identifier = x3::rule<struct extended_identifier_class, ast::string_span>{ "extended identifier" } =
    x3::as<ast::string_span>[
        raw[ lexeme [
               detail::ext_identifier_atom
            >> *(detail::ext_identifier_atom % (char_(R"(\\)")))
        ]]
    ]
    ;
// clang-format on

///
/// file_logical_name                                           [LRM93 §4.3.1.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// file_logical_name ::=
///     string_expression
/// @endcode
///
// clang-format off
auto const file_logical_name = x3::rule<struct file_logical_name_class, ast::file_logical_name>{ "file logical name" } =
    expression
    ;
// clang-format on

///
/// file_open_information                                       [LRM93 §4.3.1.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// file_open_information ::=
///     [ open file_open_kind_expression ] is file_logical_name
/// @endcode
///
// clang-format off
auto const file_open_information = x3::rule<struct file_open_information_class, ast::file_open_information>{ "file open information" } =
    -( omit[ OPEN ] >> expression )>> IS >> file_logical_name
    ;
// clang-format on

///
/// identifier                                                     [LRM93 §13.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// identifier ::=
///     basic_identifier | extended_identifier
/// @endcode
///
// clang-format off
auto const identifier = x3::rule<struct identifier_class, ast::identifier>{ "identifier" } =
      basic_identifier
    | extended_identifier
    ;
// clang-format on

///
/// identifier_list                                               [LRM93 §3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// identifier_list ::=
///     identifier { , identifier }
/// @endcode
///
// clang-format off
auto const identifier_list = x3::rule<struct identifier_list_class, ast::identifier_list>{ "identifier list" } =
    identifier % ','
    ;
// clang-format on

///
/// logical_name_list                                              [LRM93 §11.2]
///
/// Implementation of the BNF rule:
///
/// @code {.bnf}
/// logical_name_list ::=
///     logical_name { , logical_name }
/// @endcode
///
/// with
///
/// @code {.bnf}
/// logical_name ::=
///     identifier
/// @endcode
///
// clang-format off
auto const logical_name_list = x3::rule<struct logical_name_list_class, ast::logical_name_list>{ "logical name list" } =
    identifier % ','
    ;
// clang-format on

///
/// label                                                           [LRM93 §9.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// label ::=
///     identifier
/// @endcode
///
// clang-format off
auto const label = x3::rule<struct label_class, ast::identifier>{ "label" } =
    identifier
    ;
// clang-format on

/// Convenience rule for "label :"
// clang-format off
auto const label_colon = x3::rule<struct label_colon_class, ast::identifier>{ "label" } =
    label >> lexeme[ ':' >> !char_('=') ]  // exclude ":=" variable assignment
    ;
// clang-format on

///
/// @fn mode                                                       [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// mode ::=
///     in | out | inout | buffer | linkage
/// @endcode
///
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
auto const mode = x3::rule<struct mode_class, ast::keyword_token>{ "mode" } =
    distinct(detail::mode_symbols)
    ;
// clang-format on

///
/// range_constraint                                                [LRM93 §3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// range_constraint ::=
///     range range
/// @endcode
///
// clang-format off
auto const range_constraint = x3::rule<struct range_constraint_class, ast::range_constraint>{ "range constraint" } =
    RANGE >> range
    ;
// clang-format on

///
/// sign                                                            [LRM93 §7.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// sign ::=
///     + | -
/// @endcode
///
// clang-format off
auto const sign = x3::rule<struct sign_class, ast::operator_token>{ "sign" } =
      ("-" >> x3::attr(ast::operator_token::SIGN_NEG))
    | ("+" >> x3::attr(ast::operator_token::SIGN_POS))
    ;
// clang-format on

///
/// simple_name                                                     [LRM93 §6.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// simple_name ::=
///     identifier
/// @endcode
///
// clang-format off
auto const simple_name = x3::rule<struct simple_name_class, ast::simple_name>{ "simple name" } =
    identifier
    ;
// clang-format on

///
/// signal_list                                                     [LRM93 §5.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// signal_list ::=
///       signal_name { , signal_name }
///     | others
///     | all
/// @endcode
///
// clang-format off
auto const signal_list = x3::rule<struct signal_list_class, ast::signal_list>{ "signal list" } =
      (name % ',')
    | OTHERS
    | ALL
    ;
// clang-format on

///
/// @fn string_literal                                              [LRM93 §13.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// string_literal ::=
///     " { graphic_character } "
/// @endcode
///
namespace detail {

// clang-format off
auto const string_literal = [](auto&& chr) {
    using CharT = decltype(chr);
    return x3::rule<struct string_literal_lambda, ast::string_span>{ "string literal" } = x3::as_parser(
        raw[
             *( ( graphic_character - char_(std::forward<CharT>(chr))  )
            | ( char_(std::forward<CharT>(chr)) >> char_(std::forward<CharT>(chr)) )
            )
        ]
    );
};
// clang-format on

}  // namespace detail

// clang-format off
auto const string_literal = x3::rule<struct string_literal_class, ast::string_literal>{ "string literal" } =
    lexeme [
          '"' >> detail::string_literal('"') >> '"'
        | '%' >> detail::string_literal('%') >> '%'
    ]
    ;
// clang-format on

///
/// operator_symbol                                                 [LRM93 §2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// operator_symbol ::=
///     string_literal
/// @endcode
///
// clang-format off
auto const operator_symbol = x3::rule<struct operator_symbol_class, ast::operator_symbol>{ "operator symbol" } =
    string_literal
    ;
// clang-format on

///
/// suffix                                                          [LRM93 §6.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// suffix ::=
///       simple_name
///     | character_literal
///     | operator_symbol
///     | all
/// @endcode
///
// clang-format off
auto const suffix = x3::rule<struct suffix_class, ast::suffix>{ "suffix" } =
      simple_name
    | character_literal
    | operator_symbol
    | ALL
    ;
// clang-format on

///
/// subprogram_kind                                                 [LRM93 §2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_kind ::=
///     procedure | function
/// @endcode
///
// clang-format off
auto const subprogram_kind = x3::rule<struct subprogram_kind_class, ast::keyword_token>{ "subprogram kind" } =
      PROCEDURE
    | FUNCTION
    ;
// clang-format on

///
/// type_mark
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const type_mark = x3::rule<struct type_mark_class, ast::name>{ "type mark" } =
    name
    ;
// clang-format on

///
/// signature                                                     [LRM93 §2.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// signature ::=
///     [ [ type_mark { , type_mark } ] [ return type_mark ] ]
/// @endcode
///
// clang-format off
auto const signature = x3::rule<struct signature_class, ast::signature>{ "signature" } =
    '[' >> -(type_mark % ',') >> -( RETURN >> type_mark ) >> ']'
    ;
// clang-format on

///
/// type_conversion                                               [LRM93 §7.3.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// type_conversion ::=
///     type_mark ( expression )
/// @endcode
///
/// FixMe:  ``Integer ( 74.94 * real(Param_Calc) )`` fails to parse since primary
/// isn't fully functional, fails due to expression - primary - function_call.
///
/// @note NOTE, ANTLR VHDL grammar and hdlConvertor haven't this rule!
///
// clang-format off
auto const type_conversion = x3::rule<struct type_conversion_class, ast::type_conversion>{ "type conversion" } =
    type_mark >> '(' >> expression >> ')'
    ;
// clang-format on

///
/// waveform_element                                              [LRM93 §8.4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// waveform_element ::=
///       value_expression [ after time_expression ]
///     | null [ after time_expression ]
/// @endcode
///
// clang-format off
auto const waveform_element = x3::rule<struct waveform_element_class, ast::waveform_element>{ "waveform element" } =
       ( expression | NULL_ )
    >> -( AFTER >> expression )
    ;
// clang-format on

///
/// waveform                                                        [LRM93 §8.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// waveform ::=
///       waveform_element { , waveform_element }
///     | unaffected
/// @endcode
///
// clang-format off
auto const waveform = x3::rule<struct waveform_class, ast::waveform>{ "waveform" } =
      (waveform_element % ',')
    | UNAFFECTED
    ;
// clang-format on

///
/// conditional_waveforms                                         [LRM93 §9.5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// conditional_waveforms ::=
///     { waveform when condition else }
///       waveform [ when condition ]
/// @endcode
///
/// FixMe: Probably rewrite required, no test cases in testsuite!
/// @code{.bnf}
/// // https://github.com/antlr/grammars-v4/blob/master/vhdl/vhdl.g4
/// conditional_waveforms
///   : waveform ( WHEN condition (ELSE conditional_waveforms)?)?
///
/// // https://github.com/Nic30/hdlConvertor/blob/master/grammars/vhdlParser.g4
/// conditional_waveforms:
///   waveform KW_WHEN condition
///   ( KW_ELSE waveform KW_WHEN condition )*
///   ( KW_ELSE waveform | {_input->LA(1) != KW_ELSE}? ) // LA(1) -> LookAhead(1)
/// @endcode
///
// clang-format off
auto const conditional_waveforms = x3::rule<struct conditional_waveforms_class, ast::conditional_waveforms>{ "conditional waveforms" } =
       *( waveform >> WHEN >> condition >> ELSE )
    >> waveform
    >> -( WHEN >> condition )
    ;
// clang-format on

///
/// assertion                                                       [LRM93 §8.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// assertion ::=
///     assert condition
///     [ report expression ]
///     [ severity expression ]
/// @endcode
///
// clang-format off
auto const assertion = x3::rule<struct assertion_class, ast::assertion>{ "assertion" } =
        ( ASSERT   >> condition)
    >> -( REPORT   >> expression )
    >> -( SEVERITY >> expression )
    ;
// clang-format on

///
/// entity_aspect                                               [LRM93 §5.2.1.1]
///
/// @code {.bnf}
/// entity_aspect ::=
///       entity entity_name [ ( architecture_identifier) ]
///     | configuration configuration_name
///     | open
/// @endcode
///
/// FixMe: test case with selected_name, e.g.``work.NAND2`` not working yet.
/// @todo Check use of two rules in detail ns reduces compile time
///
// clang-format off
auto const entity_aspect = x3::rule<struct entity_aspect_class, ast::entity_aspect>{ "entity aspect" } =
      x3::as<ast::entity_aspect_entity>[
        ENTITY >> name >> -( '(' >> identifier >> ')' )
      ]
    | x3::as<ast::entity_aspect_configuration>[
        CONFIGURATION >> name
      ]
    | OPEN
    ;
// clang-format on

///
/// @fn entity_class                                              [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_class ::=
///       entity        | architecture  | configuration
///     | procedure     | function      | package
///     | type          | subtype       | constant
///     | signal        | variable      | component
///     | label         | literal       | units
///     | group         | file
/// @endcode
///
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
    "entity class"
);
// clang-format on

}  // namespace detail

// clang-format off
auto const entity_class = x3::rule<struct entity_class_class, ast::keyword_token>{ "entity class" } =
     distinct(detail::entity_class_symbols)
     ;
// clang-format on

///
/// entity_class_entry                                              [LRM93 §4.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_class_entry ::=
///     entity_class [ <> ]
/// @endcode
///
// clang-format off
auto const entity_class_entry = x3::rule<struct entity_class_entry_class, ast::keyword_token>{ "entity class entry" } =
    entity_class >> -lit("<>")
    ;
// clang-format on

///
/// entity_class_entry_list                                         [LRM93 §4.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_class_entry_list ::=
///     entity_class_entry { , entity_class_entry }
/// @endcode
///
// clang-format off
auto const entity_class_entry_list = x3::rule<struct entity_class_entry_list_class, ast::entity_class_entry_list>{ "entity_class_entry_list" } =
    entity_class_entry % ','
    ;
// clang-format on

///
/// entity_tag                                                      [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_tag ::=
/// simple_name | character_literal | operator_symbol
/// @endcode
///
// clang-format off
auto const entity_tag = x3::rule<struct entity_tag_class, ast::entity_tag>{ "entity tag" } =
      simple_name
    | character_literal
    | operator_symbol
    ;
// clang-format on

///
/// entity_designator                                               [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_designator ::=
///     entity_tag [ signature ]
/// @endcode
///
// clang-format off
auto const entity_designator = x3::rule<struct entity_designator_class, ast::entity_designator>{ "entity designator" } =
    entity_tag >> -signature
    ;
// clang-format on

///
/// entity_name_list                                                [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_name_list ::=
///       entity_designator { , entity_designator }
///     | others
///     | all
/// @endcode
///
// clang-format off
auto const entity_name_list = x3::rule<struct entity_name_list_class, ast::entity_name_list>{ "entity name list" } =
      (entity_designator % ',')
    | OTHERS
    | ALL
    ;
// clang-format on

///
/// entity_specification ::=                                        [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_specification ::=                                        [LRM93 §5.1]
///     entity_name_list : entity_class
/// @endcode
///
// clang-format off
auto const entity_specification = x3::rule<struct entity_specification_class, ast::entity_specification>{ "entity specification" } =
    entity_name_list >> ':' >> entity_class
    ;
// clang-format on

///
/// actual_designator                                           [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
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
/// @note Note, expression also matches {signal, variable, file}_name
///
// clang-format off
auto const actual_designator = x3::rule<struct actual_designator_class, ast::actual_designator>{ "actual designator" } =
      expression
    | OPEN
    ;
// clang-format on

///
/// actual_part                                                 [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const actual_part = x3::rule<struct actual_part_class, ast::actual_part>{ "actual part" } =
    // order matters
      x3::as<ast::actual_part_chunk>[
        name >> '(' >> actual_designator >> ')'
      ]
    | actual_designator
    ;
// clang-format on

///
/// formal_designator ::=                                       [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// formal_designator ::=
///       generic_name
///     | port_name
///     | parameter_name
/// @endcode
///
// clang-format off
auto const formal_designator = x3::rule<struct formal_designator_class, ast::name>{ "formal designator" } =
    name
    ;
// clang-format on

///
/// formal_part                                                 [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const formal_part = x3::rule<struct formal_part_class, ast::formal_part>{ "formal part" } =
    x3::as<std::vector<ast::name>>[
        name >> -( '(' >> formal_designator >> ')' )
    ]
    ;
// clang-format on

///
/// association_element                                         [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// association_element ::=
///     [ formal_part => ] actual_part
/// @endcode
///
/// @dot
/// digraph association_element {
///     association_element[style=filled];
///
///     association_element -> formal_part, actual_part;
///     formal_part -> formal_designator, name;
///     actual_part -> actual_designator, name;
///
///     formal_designator -> name;
///     actual_designator -> expression, name, OPEN;
///     expression -> "..." -> primary -> name;
/// }
/// @enddot
///
// clang-format off
auto const association_element = x3::rule<struct association_element_class, ast::association_element>{ "association element" } =
       -x3::as<ast::formal_part>[ // enforce backtracing
           formal_part >> "=>"
       ]
    >> actual_part
    ;
// clang-format on

///
/// association_list                                            [LRM93 §4.3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// association_list ::=
///     association_element { , association_element }
/// @endcode
///
// clang-format off
auto const association_list = x3::rule<struct association_list_class, ast::association_list>{ "association list" } =
    association_element % ','
    ;
// clang-format on

///
/// actual_parameter_part                                         [LRM93 §7.3.3]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const actual_parameter_part = x3::rule<struct actual_parameter_part_class, ast::actual_parameter_part>{ "actual parameter part" } =
    association_list
    ;
// clang-format on

///
/// alias_designator                                              [LRM93 §4.3.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// alias_designator ::=
///       identifier
///     | character_literal
///     | operator_symbol
/// @endcode
///
// clang-format off
auto const alias_designator = x3::rule<struct alias_designator_class, ast::alias_designator>{ "alias designator" } =
      identifier
    | character_literal
    | operator_symbol
    ;
// clang-format on

///
/// @fn based_literal                                             [LRM93 §13.4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// based_literal ::=
///     base # based_integer [ . based_integer ] # [ exponent ]
/// @endcode
///
/// @note IEEE1076-93 Ch. 13.4.2: "The base and the exponent, if any, are in decimal notation." ...
/// Further, "An exponent for a based integer literal must not have a minus sign."
///
namespace detail {

// clang-format off
auto const based_literal_integer = x3::rule<struct based_literal_int_class, ast::based_literal::number_chunk>{ "based literal" } =
       lexeme[
            // note the empty fractional part
            based_integer >> x3::attr(ast::string_span{}) >> '#' >> -exponent('+')
       ]
    >> x3::attr(ast::based_literal::numeric_type_specifier::integer)
    ;

auto const based_literal_real = x3::rule<struct based_literal_real_class, ast::based_literal::number_chunk>{ "based literal" } =
       lexeme[
            based_integer >> lit('.') >> based_integer >> '#' >> -exponent("-+")
       ]
    >> x3::attr(ast::based_literal::numeric_type_specifier::real)
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const based_literal = x3::rule<struct based_literal_class, ast::based_literal>{ "based literal" } =
    lexeme [
        base >> '#' >> ( detail::based_literal_real |detail::based_literal_integer )
    ]
    ;
// clang-format on

///
/// @fn decimal_literal                                           [LRM93 §13.4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// decimal_literal ::=
///     integer [ . integer ] [ exponent ]
/// @endcode
///
namespace detail {

// clang-format off
auto const decimal_literal_real = x3::rule<struct decimal_literal_real_class, ast::decimal_literal>{ "decimal_literal<real>" } =
       x3::as<ast::string_span>[
           raw[ lexeme[
               integer >> char_('.') >> integer >> -exponent("-+")
           ]]
       ]
    >> x3::attr(ast::decimal_literal::numeric_type_specifier::real)
    ;

auto const decimal_literal_integer = x3::rule<struct decimal_literal_int_class, ast::decimal_literal>{ "decimal_literal<int>" } =
       x3::as<ast::string_span>[
           raw[ lexeme[
               integer >> -exponent('+')
           ]]
       ]
    >> x3::attr(ast::decimal_literal::numeric_type_specifier::integer)
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const decimal_literal = x3::rule<struct decimal_literal_class, ast::decimal_literal>{ "decimal_literal<int>" } =
      detail::decimal_literal_real
    | detail::decimal_literal_integer
    ;
// clang-format on

///
/// abstract_literal                                               [LRM93 §13.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// abstract_literal ::=
///     decimal_literal | based_literal
/// @endcode
///
// clang-format off
auto const abstract_literal = boost::spirit::x3::rule<struct abstract_literal_class, ast::abstract_literal>{ "abstract literal" } =
    // order matters
      based_literal
    | decimal_literal
    ;
// clang-format on

///
/// designator                                                      [LRM93 §2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// designator ::=
///       identifier
///     | operator_symbol
/// @endcode
///
// clang-format off
auto const designator = x3::rule<struct designator_class, ast::designator>{ "designator" } =
      identifier
    | operator_symbol
    ;
// clang-format on

///
/// index_subtype_definition                                      [LRM93 §3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// index_subtype_definition ::=
///     type_mark range <>
/// @endcode
///
// clang-format off
auto const index_subtype_definition = x3::rule<struct index_subtype_definition_class, ast::index_subtype_definition>{ "index subtype definition" } =
    type_mark >> RANGE >> "<>"
    ;
// clang-format on

///
/// factor                                                          [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// factor ::=
///       primary [ ** primary ]
///     | abs primary
///     | not primary
/// @endcode
///
/// with [LRM93 §7.2] (miscellaneous operator)
///
/// @code{.bnf}
/// miscellaneous_operator ::=  ** | abs | not
/// @endcode
///
/// @note The AST node reflects the BNF rules as is, ``factor_binary_operation`` may
/// be a primary or even a binary operation!
///
/// @todo Maybe rename the AST node to the real long name
/// ``factor_primary_or_binary_operation`` or find better matching name.
///
// clang-format off
auto const factor = x3::rule<struct factor_class, ast::factor>{ "factor" } =
    // order matters
      x3::as<ast::factor_binary_operation>[
            primary
        >> -x3::as<ast::factor_binary_operation::chunk>[
                binary_miscellaneous_operator >> primary // ** (exponent)
           ]
      ]
    | x3::as<ast::factor_unary_operation>[
        unary_miscellaneous_operator >> primary // ABS | NOT
      ]
    ;
// clang-format on

///
/// term                                                            [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// term ::=
///     factor { multiplying_operator factor }
/// @endcode
///
/// @note Consider the case of '-5 mod -3', where mod is a multiplying operator
/// with an higher operator precedence as the sign operator. This is no valid
/// VHDL. See 'test_case/expression_failure/expression_failure_002', or even the
/// Sigasi [Be careful with VHDL operator precedence](
/// http://insights.sigasi.com/tech/be-careful-vhdl-operator-precedence.html)
///
// clang-format off
auto const term = x3::rule<struct term_class, ast::term>{ "term" } =
    factor >> *( multiplying_operator >> factor )
    ;
// clang-format on

///
/// simple_expression                                               [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// simple_expression ::=
///     [ sign ] term { adding_operator term }
/// @endcode
///
// clang-format off
auto const simple_expression = x3::rule<struct simple_expression_class, ast::simple_expression>{ "simple expression" } =
    -sign >> term >> *(adding_operator >> term)
    ;
// clang-format on

///
/// shift_expression                                                [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// shift_expression ::=
///     simple_expression [ shift_operator simple_expression ]
/// @endcode
///
// clang-format off
auto const shift_expression = x3::rule<struct shift_expression_class, ast::shift_expression>{ "shift expression" } =
       simple_expression
    >> -x3::as<ast::shift_expression::chunk>[
            shift_operator >> simple_expression
        ]
    ;
// clang-format on

///
/// relation                                                        [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// relation ::=
///     shift_expression [ relational_operator shift_expression ]
/// @endcode
///
// clang-format off
auto const relation = x3::rule<struct relation_class, ast::relation>{ "relation" } =
       shift_expression
    >> -x3::as<ast::relation::chunk>[
            relational_operator >> shift_expression
        ]
    ;
// clang-format on

///
/// subtype_indication                                              [LRM93 §4.2]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const subtype_indication = x3::rule<struct subtype_indication_class, ast::subtype_indication>{ "subtype indication" } =
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
// clang-format on

///
/// discrete_range                                                [LRM93 §3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// discrete_range ::=
///     discrete_subtype_indication | range
/// @endcode
///
// clang-format off
auto const discrete_range = x3::rule<struct discrete_range_class, ast::discrete_range>{ "discrete range" } =
    // order matters
      range
    | subtype_indication
    ;
// clang-format on

///
/// parameter_specification                                         [LRM93 §8.9]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// parameter_specification ::=
///     identifier in discrete_range
/// @endcode
///
// clang-format off
auto const parameter_specification = x3::rule<struct parameter_specification_class, ast::parameter_specification>{ "parameter specification" } =
    identifier >> omit[ IN ] >> discrete_range
    ;
// clang-format on

///
/// iteration_scheme                                                [LRM93 §8.9]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// iteration_scheme ::=
///       while condition
///     | for loop_parameter_specification
/// @endcode
///
// clang-format off
auto const iteration_scheme = x3::rule<struct iteration_scheme_class, ast::iteration_scheme>{ "iteration scheme" } =
      (WHILE >> condition)
    | (FOR >> parameter_specification)
    ;
// clang-format on

///
/// enumeration_literal                                           [LRM93 §3.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// enumeration_literal ::=
///     identifier | character_literal
/// @endcode
///
// clang-format off
auto const enumeration_literal = x3::rule<struct enumeration_literal_class, ast::enumeration_literal>{ "enumeration literal" } =
      identifier
    | character_literal
    ;
// clang-format on

///
/// enumeration_type_definition                                   [LRM93 §3.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// enumeration_type_definition ::=
///     ( enumeration_literal { , enumeration_literal } )
/// @endcode
///
// clang-format off
auto const enumeration_type_definition = x3::rule<struct enumeration_type_definition_class, ast::enumeration_type_definition>{ "enumeration type definition" } =
    '(' >> (enumeration_literal % ',') >> ')'
    ;
// clang-format on

///
/// physical_literal                                              [LRM93 §3.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// physical_literal ::=
///     [ abstract_literal ] unit_name
/// @endcode
///
/// @note The LRM doesn't specify the allowed characters for physical unit name, hence it's assumed
/// that it follows the natural conventions.
///
/// @todo *FixMe* There is a special case for 'literal' since it can't
/// distinct from basic_identifier without context !! e.g. 'ns' without
/// leading integer (which is valid). So one may expected here:
/// @code{.unparsed}
/// (literal<v>
///   (numeric_literal<v>
///     (physical_literal
///       (unit_name: ns)
///     )
///   )
/// )
/// @encode
/// instead
/// @code{.unparsed}
/// (literal<v>
///   (enumeration_literal<v>
///     (identifier
///       ns
///     )
///   )
/// )
/// @endcode
/// This implies, that the AST node 'physical_literal' may be used! Otherwise,
/// there are parse ways where the 'physical_literal' AST node is parsed, e.g. waveform.
///
namespace detail {

// clang-format off
auto const physical_unit_name = x3::as<ast::string_span>[
    raw[ lexeme[
        +letter
    ]]
];
// clang-format on

}  // namespace detail

// clang-format off
auto const physical_literal = x3::rule<struct physical_literal_class, ast::physical_literal>{ "physical literal" } =
    -abstract_literal >> (detail::physical_unit_name - keyword)
    ;
// clang-format on

///
/// primary_unit_declaration a.k.a base_unit_declaration          [LRM93 §3.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// primary_unit_declaration ::=
///     identifier ;
/// @endcode
///
// clang-format off
auto const primary_unit_declaration = x3::rule<struct primary_unit_declaration_class, ast::primary_unit_declaration>{ "primary unit declaration" } =
    identifier >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// secondary_unit_declaration                                    [LRM93 §3.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// secondary_unit_declaration ::=
///     identifier = physical_literal ;
/// @endcode
///
// clang-format off
auto const secondary_unit_declaration = x3::rule<struct secondary_unit_declaration_class, ast::secondary_unit_declaration>{ "secondary unit declaration" } =
    identifier >> "=" >> physical_literal >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// physical_type_definition                                      [LRM93 §3.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// physical_type_definition ::=
///     range_constraint
///         units
///             primary_unit_declaration
///             { secondary_unit_declaration }
///         end units [ physical_type_simple_name ]
/// @endcode
///
// clang-format off
auto const physical_type_definition = x3::rule<struct physical_type_definition_class, ast::physical_type_definition>{ "physical type definition" } =
       range_constraint
    >> UNITS
    >> primary_unit_declaration
    >> *secondary_unit_declaration
    >> END >> UNITS >> -simple_name
    ;
// clang-format on

///
/// scalar_type_definition                                          [LRM93 §3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// scalar_type_definition ::=
///       enumeration_type_definition   | integer_type_definition
///     | floating_type_definition      | physical_type_definition
/// @endcode
///
/// with
///
/// @code{.bnf}
/// floating_type_definition ::= range_constraint
/// integer_type_definition  ::= range_constraint
/// @endcode
///
// clang-format off
auto const scalar_type_definition = x3::rule<struct scalar_type_definition_class, ast::scalar_type_definition>{ "scalar type definition" } =
    // order matters
      physical_type_definition
    | enumeration_type_definition
    | range_constraint              // {integer,floating}_type_definition
    ;
// clang-format on

///
/// element_subtype_definition                                    [LRM93 §3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// element_subtype_definition ::=
///     subtype_indication
/// @endcode
///
// clang-format off
auto const element_subtype_definition = x3::rule<struct element_subtype_definition_class, ast::subtype_indication>{ "element subtype definition" } =
    subtype_indication
    ;
// clang-format on

///
/// element_declaration                                           [LRM93 §3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// element_declaration ::=
///     identifier_list : element_subtype_definition ;
/// @endcode
///
// clang-format off
auto const element_declaration = x3::rule<struct element_declaration_class, ast::element_declaration>{ "element declaration" } =
    identifier_list >> ':' >> element_subtype_definition >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// record_type_definition                                        [LRM93 §3.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// record_type_definition ::=
///     record
///         element_declaration
///         { element_declaration }
///     end record [ record_type_simple_name ]
/// @endcode
///
// clang-format off
auto const record_type_definition = x3::rule<struct record_type_definition_class, ast::record_type_definition>{ "record type definition" } =
       RECORD
    >> +element_declaration
    >> END >> RECORD >> -simple_name
    ;
// clang-format on

///
/// unconstrained_array_definition                                [LRM93 §3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// unconstrained_array_definition ::=
///     array ( index_subtype_definition { , index_subtype_definition } )
///         of element_subtype_indication
/// @endcode
///
// clang-format off
auto const unconstrained_array_definition = x3::rule<struct unconstrained_array_definition_class, ast::unconstrained_array_definition>{ "unconstrained array definition" } =
    ARRAY >> '(' >> (index_subtype_definition % ',') >>  ')' >> OF >> subtype_indication
    ;
// clang-format on

///
/// index_constraint                                              [LRM93 §3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// index_constraint ::=
///     ( discrete_range { , discrete_range } )
/// @endcode
///
// clang-format off
auto const index_constraint = x3::rule<struct index_constraint_class, ast::index_constraint>{ "index constraint" } =
    '(' >> (discrete_range % ',') >> ')'
    ;
// clang-format on

///
/// constrained_array_definition                                  [LRM93 §3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// constrained_array_definition ::=
///     array index_constraint of element_subtype_indication
/// @endcode
///
// clang-format off
auto const constrained_array_definition = x3::rule<struct constrained_array_definition_class, ast::constrained_array_definition>{ "constrained array definition" } =
    ARRAY >> index_constraint >> OF >> subtype_indication
    ;
// clang-format on

///
/// array_type_definition                                           [LRM93 §8.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// array_type_definition ::=
///     unconstrained_array_definition | constrained_array_definition
/// @endcode
///
// clang-format off
auto const array_type_definition = x3::rule<struct array_type_definition_class, ast::array_type_definition>{ "array type definition" } =
      unconstrained_array_definition
    | constrained_array_definition
    ;
// clang-format on

///
/// composite_type_definition                                       [LRM93 §3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// composite_type_definition ::=
///       array_type_definition
///     | record_type_definition
/// @endcode
///
// clang-format off
auto const composite_type_definition = x3::rule<struct composite_type_definition_class, ast::composite_type_definition>{ "composite type definition" } =
      array_type_definition
    | record_type_definition
    ;
// clang-format on

///
/// access_type_definition                                          [LRM93 §3.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// access_type_definition ::=
///     access subtype_indication
/// @endcode
///
// clang-format off
auto const access_type_definition = x3::rule<struct access_type_definition_class, ast::access_type_definition>{ "access type definition" } =
    ACCESS >> subtype_indication
    ;
// clang-format on

///
/// file_type_definition                                            [LRM93 §3.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// file_type_definition ::=
///     file of type_mark
/// @endcode
///
// clang-format off
auto const file_type_definition = x3::rule<struct file_type_definition_class, ast::file_type_definition>{ "file type definition" } =
    FILE >> OF >> type_mark
    ;
// clang-format on

///
/// type_definition                                                 [LRM93 §4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// type_definition ::=
///       scalar_type_definition
///     | composite_type_definition
///     | access_type_definition
///     | file_type_definition
/// @endcode
///
// clang-format off
auto const type_definition = x3::rule<struct type_definition_class, ast::type_definition>{ "type definition" } =
      scalar_type_definition
    | composite_type_definition
    | access_type_definition
    | file_type_definition
    ;
// clang-format on

///
/// numeric_literal                                               [LRM93 §7.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// numeric_literal ::=
///       abstract_literal
///     | physical_literal
/// @endcode
///
// clang-format off
auto const numeric_literal = x3::rule<struct numeric_literal_class, ast::numeric_literal>{ "numeric literal" } =
    // order matters
      physical_literal
    | abstract_literal
    ;
// clang-format on

///
/// choice                                                        [LRM93 §7.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// choice ::=
///       simple_expression
///     | discrete_range
///     | element_simple_name
///     | others
/// @endcode
///
/// @note In the original LRM BNF order ``simple_name`` get never been parsed since
/// ``simple_expression`` decays to ``simple_name`` and matches first there:
/// @dot
/// digraph choice {
///     simple_name[style=filled];
///     simple_expression -> term -> factor -> primary;
///     primary -> name, "...";
///     name -> simple_name, "...";
/// }
/// @enddot
/// hence, for simple AST traverse simple_name (identifier) is the first entry.
///
// clang-format off
auto const choice = x3::rule<struct choice_class, ast::choice>{ "choice" } =
    // order matters
      simple_name
    | discrete_range
    | simple_expression
    | OTHERS
    ;
// clang-format on

///
/// choices                                                       [LRM93 §7.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// choices ::=
///     choice { | choice }
/// @endcode
///
// clang-format off
auto const choices = x3::rule<struct choices_class, ast::choices>{ "choices" } =
    choice % '|'
    ;
// clang-format on

///
/// sensitivity_list                                                [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// sensitivity_list ::=
///     signal_name { , signal_name }
/// @endcode
///
// clang-format off
auto const sensitivity_list = x3::rule<struct sensitivity_list_class, ast::sensitivity_list>{ "sensitivity list" } =
    name % ','
    ;
// clang-format on

///
/// sensitivity_clause                                              [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// sensitivity_clause ::=
///     on sensitivity_list
/// @endcode
///
// clang-format off
auto const sensitivity_clause = x3::rule<struct sensitivity_clause_class, ast::sensitivity_clause>{ "sensitivity clause" } =
    ON >> sensitivity_list
    ;
// clang-format on

///
/// condition_clause                                                [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// condition_clause ::=
///       until condition
///     | generate_statement
/// @endcode
///
// clang-format off
auto const condition_clause = x3::rule<struct condition_clause_class, ast::condition_clause>{ "condition clause" } =
    UNTIL >> condition
    ;
// clang-format on

///
/// timeout_clause                                                  [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// timeout_clause ::=
///     for time_expression
/// @endcode
///
// clang-format off
auto const timeout_clause = x3::rule<struct timeout_clause_class, ast::timeout_clause>{ "timeout clause" } =
    FOR >> expression
    ;
// clang-format on

///
/// wait_statement                                                  [LRM93 §8.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// wait_statement ::=
///     [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ] ;
/// @endcode
///
// clang-format off
auto const wait_statement = x3::rule<struct wait_statement_class, ast::wait_statement>{ "wait statement" } =
    -label_colon >> WAIT >> -sensitivity_clause >> -condition_clause >> -timeout_clause >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// assertion_statement                                             [LRM93 §8.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// assertion_statement ::=
///     [ label : ] assertion ;
/// @endcode
///
// clang-format off
auto const assertion_statement = x3::rule<struct assertion_statement_class, ast::assertion_statement>{ "assertion statement" } =
    -label_colon >> assertion >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// report_statement                                                [LRM93 §8.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// report_statement ::=
///     [ label : ]
///     report expression
///     [ severity expression ] ;
/// @endcode
///
/// FixMe: See ``report_statement_002`` test case, unable to parse
/// @code
/// report "The value of 'answer' is " & integer'image(answer);
/// @endcode
/// since attribute_name isn't correctly parsed.
///
// clang-format off
auto const report_statement = x3::rule<struct report_statement_class, ast::report_statement>{ "report statement" } =
    -label_colon >> ( REPORT >> expression ) >> -( SEVERITY >> expression ) >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// element_association                                           [LRM93 §7.3.2]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const element_association = x3::rule<struct element_association_class, ast::element_association>{ "element association" } =
    -x3::as<ast::choices>[choices >> "=>" ] >> expression
    ;
// clang-format on

///
/// aggregate                                                     [LRM93 §7.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// aggregate ::=
///     ( element_association { , element_association } )
/// @endcode
///
// clang-format off
auto const aggregate = x3::rule<struct aggregate_class, ast::aggregate>{ "aggregate" } =
    '(' >> (element_association % ',') >> ')'
    ;
// clang-format on

///
/// target                                                          [LRM93 §8.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// target ::=
///       name
///     | aggregate
/// @endcode
///
// clang-format off
auto const target = x3::rule<struct target_class, ast::target>{ "target" } =
      name
    | aggregate
    ;
// clang-format on

///
/// signal_assignment_statement                                     [LRM93 §8.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// signal_assignment_statement ::=
///     [ label : ] target <= [ delay_mechanism ] waveform ;
/// @endcode
///
// clang-format off
auto const signal_assignment_statement = x3::rule<struct signal_assignment_statement_class, ast::signal_assignment_statement>{ "signal assignment statement" } =
    -label_colon >> target >> "<=" >> -delay_mechanism >> waveform >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// variable_assignment_statement                                   [LRM93 §8.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// variable_assignment_statement ::=
///     [ label : ] target  := expression ;
/// @endcode
///
// clang-format off
auto const variable_assignment_statement = x3::rule<struct variable_assignment_statement_class, ast::variable_assignment_statement>{ "variable assignment statement" } =
    -label_colon >> target >> ":=" >> expression >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// if_statement                                                    [LRM93 §8.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// if_statement ::=
///     [ if_label : ]
///         if condition then
///             sequence_of_statements
///       { elsif condition then
///             sequence_of_statements }
///       [ else
///             sequence_of_statements ]
///         end if [ if_label ] ;
/// @endcode
///
// clang-format off
auto const if_statement = x3::rule<struct if_statement_class, ast::if_statement>{ "if statement" } =
       -label_colon
    >> IF >> condition >> THEN
    >> sequence_of_statements
    >> *( ELSIF >> condition >> THEN >> sequence_of_statements )
    >> -( ELSE >> sequence_of_statements )
    >> END >> IF
    >> -label
    >> x3::expect[ ';' ]
;
// clang-format on

///
/// case_statement_alternative                                      [LRM93 §8.8]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// case_statement_alternative ::=
///     when choices =>
///         sequence_of_statements
/// @endcode
///
// clang-format off
auto const case_statement_alternative = x3::rule<struct case_statement_alternative_class, ast::case_statement_alternative>{ "case statement alternative" } =
    WHEN >> choices >> "=>" >> sequence_of_statements
    ;
// clang-format on

///
/// case_statement                                                  [LRM93 §8.8]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// case_statement ::=
///     [ case_label : ]
///         case expression is
///             case_statement_alternative
///             { case_statement_alternative }
///         end case [ case_label ] ;
/// @endcode
///
// clang-format off
auto const case_statement = x3::rule<struct case_statement_class, ast::case_statement>{ "case statement" } =
       -label_colon
    >> CASE
    >> expression
    >> IS
    >> +case_statement_alternative
    >> END >> CASE >> -label
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// loop_statement                                                  [LRM93 §8.9]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// loop_statement ::=
///     [ loop_label : ]
///         [ iteration_scheme ] loop
///             sequence_of_statements
///         end loop [ loop_label ] ;
/// @endcode
///
// clang-format off
auto const loop_statement = x3::rule<struct loop_statement_class, ast::loop_statement>{ "loop statement" } =
       -label_colon
    >> -iteration_scheme
    >> LOOP
    >> sequence_of_statements
    >> END >> LOOP >> -label
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// next_statement                                                 [LRM93 §8.10]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// next_statement ::=
///     [ label : ] next [ loop_label ] [ when condition ] ;
/// @endcode
///
// clang-format off
auto const next_statement = x3::rule<struct next_statement_class, ast::next_statement>{ "next statement" } =
    -label_colon >> NEXT >> -label >> -( WHEN >> condition ) >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// exit_statement                                                [LRM93 §8.11]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// exit_statement ::=
///     [ label : ] exit [ loop_label ] [ when condition ] ;
/// @endcode
///
// clang-format off
auto const exit_statement = x3::rule<struct exit_statement_class, ast::exit_statement>{ "exit statement" } =
    -label_colon >> EXIT >> -label >> -( WHEN >> condition ) >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// return_statement                                               [LRM93 §8.12]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// return_statement ::=
///     [ label : ] return [ expression ] ;
/// @endcode
///
// clang-format off
auto const return_statement = x3::rule<struct return_statement_class, ast::return_statement>{ "return statement" } =
    -label_colon >> RETURN >> -expression >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// procedure_call                                                  [LRM93 §8.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// procedure_call ::=
///     procedure_name [ ( actual_parameter_part ) ]
/// @endcode
///
// clang-format off
auto const procedure_call = x3::rule<struct procedure_call_class, ast::procedure_call>{ "procedure call" } =
    name >> -( '(' >> actual_parameter_part >> ')' )
    ;
// clang-format on

///
/// procedure_call_statement                                        [LRM93 §8.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// procedure_call_statement ::=
///     [ label : ] procedure_call ;
/// @endcode
///
// clang-format off
auto const procedure_call_statement = x3::rule<struct procedure_call_statement_class, ast::procedure_call_statement>{ "procedure call statement" } =
    -label_colon >> procedure_call >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// null_statement                                                 [LRM93 §8.13]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// null_statement ::=
///      [ label : ] null ;
/// @endcode
///
// clang-format off
auto const null_statement = x3::rule<struct null_statement_class, ast::null_statement>{ "null statement" } =
    -label_colon >> omit[ NULL_ ] >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// sequential_statement                                              [LRM93 §8]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// sequential_statement ::=
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
/// @endcode
///
/// @todo All alternatives have an optional label, resulting in backtracing. Hence bound the
/// label to this AST node - which makes the check of label pairs more complicate otherwise!
///
// clang-format off
auto const sequential_statement = x3::rule<struct sequential_statement_class, ast::sequential_statement>{ "sequential statement" } =
      wait_statement
    | assertion_statement
    | report_statement
    | signal_assignment_statement
    | variable_assignment_statement
    | if_statement
    | case_statement
    | loop_statement
    | next_statement
    | exit_statement
    | return_statement
    | procedure_call_statement
    | null_statement
    ;
// clang-format on

///
/// sequence_of_statements                                            [LRM93 §8]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// sequence_of_statements ::=
///     { sequential_statement }
/// @endcode
///
/// @note **recursive calls**:
/// @dot
/// digraph sequence_of_statements {
///     sequence_of_statements[style=filled];
///
///     sequence_of_statements -> sequential_statement;
///     sequential_statement -> "...", if_statement, case_statement_alternative, loop_statement;
///
///     case_statement_alternative -> choices, sequence_of_statements;
///     case_statement -> case_statement_alternative;
///     if_statement -> label, sequence_of_statements;
///     loop_statement -> label, iteration_scheme, sequence_of_statements;
/// @enddot
///
// clang-format off
auto const sequence_of_statements_def = // recursive call
    *sequential_statement
    ;
// clang-format on

///
/// concurrent_assertion_statement                                  [LRM93 §9.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// concurrent_assertion_statement ::=
/// [ label : ] [ postponed ] assertion ;
/// @endcode
///
// clang-format off
auto const concurrent_assertion_statement = x3::rule<struct concurrent_assertion_statement_class, ast::concurrent_assertion_statement>{ "concurrent assertion statement" } =
    -label_colon >> -POSTPONED >> assertion >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// concurrent_procedure_call_statement                             [LRM93 §9.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// concurrent_procedure_call_statement ::=
///     [ label : ] [ postponed ] procedure_call ;
/// @endcode
///
// clang-format off
auto const concurrent_procedure_call_statement = x3::rule<struct concurrent_procedure_call_statement_class, ast::concurrent_procedure_call_statement>{ "concurrent_procedure_call_statement" } =
    -label_colon >> -POSTPONED >> procedure_call >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// interface_constant_declaration                                [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_constant_declaration ::=
///     [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]
/// @endcode
///
// clang-format off
auto const interface_constant_declaration = x3::rule<struct interface_constant_declaration_class, ast::interface_constant_declaration>{ "interface constant declaration" } =
       -CONSTANT
    >> identifier_list
    >> ':'
    >> -IN
    >> subtype_indication
    >> -( ":=" >> expression )
    ;
// clang-format on

///
/// interface_signal_declaration                                  [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_signal_declaration ::=
///     [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]
/// @endcode
///
// clang-format off
auto const interface_signal_declaration = x3::rule<struct interface_signal_declaration_class, ast::interface_signal_declaration>{ "interface signal declaration" } =
       -SIGNAL
    >> identifier_list
    >> ':'
    >> -mode
    >> subtype_indication
    >> -BUS
    >> -( ":=" >>  expression )
    ;
// clang-format on

///
/// interface_variable_declaration                                [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_variable_declaration ::=
///     [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]
/// @endcode
///
// clang-format off
auto const interface_variable_declaration = x3::rule<struct interface_variable_declaration_class, ast::interface_variable_declaration>{ "interface variable declaration" } =
       -VARIABLE
    >> identifier_list
    >> ':'
    >> -mode
    >> subtype_indication
    >> -( ":=" >>  expression )
    ;
// clang-format on

///
/// interface_file_declaration                                    [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_file_declaration ::=
///     file identifier_list : subtype_indication
/// @endcode
///
// clang-format off
auto const interface_file_declaration = x3::rule<struct interface_file_declaration_class, ast::interface_file_declaration>{ "interface file declaration" } =
    FILE >> identifier_list >> ':' >> subtype_indication
    ;
// clang-format on

///
/// interface_declaration                                         [LRM93 §4.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_declaration ::=
///       interface_constant_declaration
///     | interface_signal_declaration
///     | interface_variable_declaration
///     | interface_file_declaration
/// @endcode
///
// clang-format off
auto const interface_declaration = x3::rule<struct interface_declaration_class, ast::interface_declaration>{ "interface declaration" } =
      interface_constant_declaration
    | interface_signal_declaration
    | interface_variable_declaration
    | interface_file_declaration
    ;
// clang-format on

///
/// interface_element                                           [LRM93 §4.3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_element ::=
///      interface_declaration
/// @endcode
///
// clang-format off
auto const interface_element = x3::rule<struct interface_element_class, ast::interface_element>{ "interface element" } =
    interface_declaration
    ;
// clang-format on

///
/// interface_list                                              [LRM93 §4.3.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// interface_list ::=
///     interface_element { ; interface_element }
/// @endcode
///
// clang-format off
auto const interface_list = x3::rule<struct interface_list_class, ast::interface_list>{ "interface list" } =
    interface_element % ';'
    ;
// clang-format on

///
/// formal_parameter_list                                         [LRM93 §2.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// formal_parameter_list ::=
///     parameter_interface_list
/// @endcode
///
// clang-format off
auto const formal_parameter_list = x3::rule<struct formal_parameter_list_class, ast::formal_parameter_list>{ "formal parameter list" } =
    interface_list
    ;
// clang-format on

///
/// generic_clause                                                [LRM93 §1.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// generic_clause ::=
///     generic ( generic_list ) ;
/// @endcode
///
/// with
///
/// @code{.bnf}
/// generic_list ::=
///     generic_interface_list
/// @endcode
///
// clang-format off
auto const generic_clause = x3::rule<struct generic_clause_class, ast::generic_clause>{ "generic clause" } =
    GENERIC >> '(' >> interface_list >> ')' >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// port_clause                                                   [LRM93 §1.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// port_clause ::=
///     port ( port_list ) ;
/// @endcode
///
/// with
///
/// @code{.bnf}
/// port_list ::=
///     port_interface_list
/// @endcode
///
// clang-format off
auto const port_clause = x3::rule<struct port_clause_class, ast::port_clause>{ "port clause" } =
    PORT >> '(' >> interface_list >> ')' >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// entity_header                                                 [LRM93 §1.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_header ::=
///     [ formal_generic_clause ]
///     [ formal_port_clause ]
/// @endcode
///
// clang-format off
auto const entity_header = x3::rule<struct entity_header_class, ast::entity_header>{ "entity header" } =
       -generic_clause
    >> -port_clause
    ;
// clang-format on

///
/// signal_declaration                                          [LRM93 §4.3.1.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// signal_declaration ::=
///     signal identifier_list : subtype_indication [ signal_kind ] [ := expression ] ;
/// @endcode
///
/// with:
///
/// @code{.bnf}
/// signal_kind ::=
///     register  |  bus
/// @endcode
///
// clang-format off
auto const signal_declaration = x3::rule<struct signal_declaration_class, ast::signal_declaration>{ "signal declaration" } =
       omit[ SIGNAL ]
    >> identifier_list
    >> ':'
    >> subtype_indication
    >> -x3::as<ast::keyword_token>[
            REGISTER | BUS // signal_kind
       ]
    >> -( ":=" >>  expression )
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// subprogram_specification                                        [LRM93 §2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_specification ::=
///       procedure designator [ ( formal_parameter_list ) ]
///     | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
///       return type_mark
/// @endcode
///
namespace detail {

// clang-format off
auto const procedure_specification = x3::rule<struct procedure_specification_class, ast::subprogram_specification_procedure>{ "subprogram_specification.procedure" } =
       x3::omit[ PROCEDURE ] >> designator >> -( '(' >> formal_parameter_list >> ')' )
    ;

auto const function_specification = x3::rule<struct function_specification_class, ast::subprogram_specification_function>{ "subprogram_specification.function" } =
       -(IMPURE | PURE)
     >> x3::omit[ FUNCTION ] >> designator >> -( '(' >> formal_parameter_list >> ')' ) >> RETURN >> type_mark
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const subprogram_specification = x3::rule<struct subprogram_specification_class, ast::subprogram_specification>{ "subprogram specification" } =
      detail::procedure_specification
    | detail::function_specification
    ;
// clang-format on

///
/// subprogram_declaration                                          [LRM93 §2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_declaration ::=
///     subprogram_specification ;
/// @endcode
///
// clang-format off
auto const subprogram_declaration = x3::rule<struct subprogram_declaration_class, ast::subprogram_declaration>{ "subprogram declaration" } =
    subprogram_specification >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// subprogram_declarative_part                                     [LRM93 §2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_declarative_part ::=
///     { subprogram_declarative_item }
/// @endcode
///
// clang-format off
auto const subprogram_declarative_part = x3::rule<struct subprogram_declarative_part_class, ast::subprogram_declarative_part>{ "subprogram declarative part" } =
    *subprogram_declarative_item
    ;
// clang-format on

///
/// subprogram_statement_part                                       [LRM93 §2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_statement_part ::=
///     { sequential_statement }
/// @endcode
///
// clang-format off
auto const subprogram_statement_part = x3::rule<struct subprogram_statement_part_class, ast::subprogram_statement_part>{ "subprogram statement part" } =
    sequence_of_statements
    ;
// clang-format on

///
/// subprogram_body                                                 [LRM93 §2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_body ::=
///     subprogram_specification is
///         subprogram_declarative_part
///     begin
///         subprogram_statement_part
///     end [ subprogram_kind ] [ designator ] ;
/// @endcode
///
// clang-format off
auto const subprogram_body = x3::rule<struct subprogram_body_class, ast::subprogram_body>{ "subprogram body" } =
       subprogram_specification
    >> IS
    >> subprogram_declarative_part
    >> BEGIN
    >> subprogram_statement_part
    >> END
    >> -subprogram_kind
    >> -designator
    >> x3::expect[ ';' ]
    ;
// clang-format on

//
/// type_declaration                                                [LRM93 §4.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// type_declaration ::=
///       full_type_declaration
///     | incomplete_type_declaration
/// @endcode
///
/// with
///
/// @code{.bnf}
/// full_type_declaration       ::= TYPE identifier IS type_definition ;
/// incomplete_type_declaration ::= TYPE identifier ;
/// @endcode
///
/// @note This node covers both alternatives with optional definition.
///
/// FixMe: The VHDL type declaration ``type WORD_INDEX is range 31 down to 0;``
/// is parsed successfully, even it shouldn't. Probably this shouldn't be fixed
/// at parse level self - think about!
///
// clang-format off
auto const type_declaration = x3::rule<struct type_declaration_class, ast::type_declaration>{ "type declaration" } =
    TYPE >> identifier >> -( IS >> type_definition ) >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// subtype_declaration                                             [LRM93 §4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subtype_declaration ::=
///     subtype identifier is subtype_indication ;
/// @endcode
///
// clang-format off
auto const subtype_declaration = x3::rule<struct subtype_declaration_class, ast::subtype_declaration>{ "subtype declaration" } =
    SUBTYPE >> identifier >> IS >> subtype_indication >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// constant_declaration                                        [LRM93 §4.3.1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// constant_declaration ::=
///     constant identifier_list : subtype_indication [ := expression ] ;
/// @endcode
///
// clang-format off
auto const constant_declaration = x3::rule<struct constant_declaration_class, ast::constant_declaration>{ "constant declaration" } =
    omit[ CONSTANT ] >> identifier_list >> ':' >> subtype_indication >> -( ":=" >>  expression ) >> x3::expect[ ';' ]
;
// clang-format on

///
/// variable_declaration                                        [LRM93 §4.3.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// variable_declaration ::=
///     [ shared ] variable identifier_list : subtype_indication [ := expression ] ;
/// @endcode
///
// clang-format off
auto const variable_declaration = x3::rule<struct variable_declaration_class, ast::variable_declaration>{ "variable declaration" } =
       -SHARED >> omit[ VARIABLE ]
    >> identifier_list >> ':' >> subtype_indication >> -(  ":=" >>  expression )
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// file_declaration                                            [LRM93 §4.3.1.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// file_declaration ::=
///     file identifier_list : subtype_indication [ file_open_information ] ;
/// @endcode
///
// clang-format off
auto const file_declaration = x3::rule<struct file_declaration_class, ast::file_declaration>{ "file declaration" } =
    FILE >> identifier_list >> ':' >> subtype_indication >> -file_open_information >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// alias_declaration                                             [LRM93 §4.3.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// alias_declaration ::=
///     alias alias_designator [ : subtype_indication ] is name [ signature ] ;
/// @endcode
///
// clang-format off
auto const alias_declaration = x3::rule<struct alias_declaration_class, ast::alias_declaration>{ "alias declaration" } =
    ALIAS >> alias_designator >> -( ':' >> subtype_indication ) >> IS >> name >> -signature >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// attribute_declaration                                           [LRM93 §4.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// attribute_declaration ::=
///     attribute identifier : type_mark ;
/// @endcode
///
// clang-format off
auto const attribute_declaration = x3::rule<struct attribute_declaration_class, ast::attribute_declaration>{ "attribute declaration" } =
    ATTRIBUTE >> identifier >> ':' >> type_mark >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// attribute_specification                                         [LRM93 §5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// attribute_specification ::=
///     attribute attribute_designator of entity_specification is expression ;
/// @endcode
///
/// with
///
/// @code{.bnf}
/// attribute_designator ::=
///     attribute_simple_name
/// @endcode
///
// clang-format off
auto const attribute_specification = x3::rule<struct attribute_specification_class, ast::attribute_specification>{ "attribute specification" } =
       ATTRIBUTE
    >> simple_name // attribute_designator
    >> OF
    >> entity_specification
    >> IS
    >> expression
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// use_clause                                                     [LRM93 §10.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// use_clause ::=
///     use selected_name { , selected_name } ;
/// @endcode
///
/// with
///
/// @code{.bnf}
/// selected_name ::=
///     prefix . suffix
/// prefix ::=
///	      name
///	    | function_call
/// suffix ::=
///       simple_name
///     | character_literal
///     | operator_symbol
///     | ALL
/// @endcode
///
/// where the LRM states "The prefix of an expanded name may not be a function call." Note,
/// that ``name`` has as alternative ``selected_name``.
/// In the ``use_clause`` there are two use cases for library prefix (``name . name . suffix``,
/// e.g. ``IEEE.std_logic_1164.all``) and packages (``name . suffix``, e.g. ``work.dut``) - the
/// context gives the meaning.
/// It's not sure how the intended AST path is following the BNF - even in [VHDL IEEE 1076-2008](
/// https://insights.sigasi.com/tech/vhdl2008.ebnf/) there are no changes/fixes. Hence a
/// ``use_clause`` specific ``selected_name`` rule is used.
///
/// FixMe: Check rule ``identifier >> +('.' >> suffix)`` if there are test case ready.
/// FixMe: Nevertheless it should work with BNF 'plain' selected_name rule.
///
namespace detail {

// clang-format off
auto const lib_prefix = x3::rule<struct _, std::vector<ast::name>>{ "prefix" } =
    x3::lexeme[
        name >> '.' >> name
    ];

auto const pkg_prefix = x3::rule<struct _, std::vector<ast::name>>{ "prefix" } =
    x3::repeat(1)[ // enforce artificial vector to unify ast node
        name
    ];

auto const lib_selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected name" } =
    x3::lexeme[
        lib_prefix >> '.' >> suffix
    ]
    ;

auto const pkg_selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected name" } =
    x3::lexeme[
        pkg_prefix >> '.' >> suffix
    ]
    ;

auto const selected_name = x3::rule<struct _, ast::use_clause::selected_name>{ "selected name" } =
      lib_selected_name
    | pkg_selected_name
    ;
// clang-format on

}  // namespace detail

// clang-format off
auto const use_clause = x3::rule<struct use_clause_class, ast::use_clause>{ "use clause" } =
    USE >> (detail::selected_name % ',') >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// group_template_declaration                                      [LRM93 §4.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// group_template_declaration ::=
///     group identifier is ( entity_class_entry_list ) ;
/// @endcode
///
// clang-format off
auto const group_template_declaration = x3::rule<struct group_template_declaration_class, ast::group_template_declaration>{ "group template declaration" } =
    GROUP >> identifier >> IS >> '(' >> entity_class_entry_list >> ')' >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// group_constituent                                               [LRM93 §4.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// group_constituent ::
///     name | character_literal
/// @endcode
///
// clang-format off
auto const group_constituent = x3::rule<struct group_constituent_class, ast::group_constituent>{ "group constituent" } =
    name | character_literal
    ;
// clang-format on

///
/// group_constituent_list                                          [LRM93 §4.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// group_constituent_list ::=
///     group_constituent { , group_constituent }
/// @endcode
///
// clang-format off
auto const group_constituent_list = x3::rule<struct group_constituent_list_class, ast::group_constituent_list>{ "group constituent list" } =
    group_constituent % ','
    ;
// clang-format on

///
/// group_declaration                                               [LRM93 §4.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// group_declaration ::=
///     group identifier : group_template_name ( group_constituent_list ) ;
/// @endcode
///
// clang-format off
auto const group_declaration = x3::rule<struct group_declaration_class, ast::group_declaration>{ "group declaration" } =
    GROUP >> identifier >> ':' >> name >> '(' >> group_constituent_list >> ')' >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// subprogram_declarative_item                                     [LRM93 §2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// subprogram_declarative_item ::=
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
/// @endcode
///
/// @note **recursive call** by subprogram_body:
/// @dot
/// digraph subprogram_declarative_item {
///     subprogram_declarative_item[style=filled];
///
///     subprogram_declarative_item -> subprogram_body, " ...";
///     subprogram_body -> "...", subprogram_declarative_part;
///     subprogram_declarative_part -> subprogram_declarative_item;
/// }
/// @enddot
///
// clang-format off
auto const subprogram_declarative_item_def = // recursive call
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

///
/// process_declarative_item                                        [LRM93 §9.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// process_declarative_item ::=
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
/// @endcode
///
// clang-format off
auto const process_declarative_item = x3::rule<struct process_declarative_item_class, ast::process_declarative_item>{ "process declarative item" } =
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

///
/// process_declarative_part                                        [LRM93 §9.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// process_declarative_part ::=
///     { process_declarative_item }
/// @endcode
///
// clang-format off
auto const process_declarative_part = x3::rule<struct process_declarative_part_class, ast::process_declarative_part>{ "process declarative part" } =
    *process_declarative_item
    ;
// clang-format on

///
/// process_statement_part                                          [LRM93 §9.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// process_statement_part ::=
///     { sequential_statement }
/// @endcode
///
// clang-format off
auto const process_statement_part = x3::rule<struct process_statement_part_class, ast::process_statement_part>{ "process statement part" } =
    sequence_of_statements
    ;
// clang-format on

///
/// process_statement                                               [LRM93 §9.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// process_statement ::=
///     [ process_label : ]
///         [ postponed ] process [ ( sensitivity_list ) ] [ is ]
///             process_declarative_part
///         begin
///             process_statement_part
///         end [ postponed ] process [ process_label ] ;
/// @endcode
///
// clang-format off
auto const process_statement = x3::rule<struct process_statement_class, ast::process_statement>{ "process statement" } =
       -label_colon
    >> -POSTPONED >> PROCESS  >> -( '(' >> sensitivity_list >> ')' ) >> -IS
    >> process_declarative_part
    >> BEGIN
    >> process_statement_part
    >> END >> -POSTPONED >> PROCESS >> -label
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// entity_statement                                              [LRM93 §1.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_statement ::=
///       concurrent_assertion_statement
///     | passive_concurrent_procedure_call_statement
///     | passive_process_statement
/// @endcode
///
/// @todo All alternatives have an optional label, resulting in backtracing. Hence bound the
/// label to this AST node - which makes the check of label pairs more complicate otherwise!
///
// clang-format off
auto const entity_statement = x3::rule<struct entity_statement_class, ast::entity_statement>{ "entity statement" } =
      concurrent_assertion_statement
    | concurrent_procedure_call_statement
    | process_statement
    ;
// clang-format on

///
/// entity_statement_part                                         [LRM93 §1.1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_statement_part ::=
///     { entity_statement }
/// @endcode
///
// clang-format off
auto const entity_statement_part = x3::rule<struct entity_statement_part_class, ast::entity_statement_part>{ "entity statement part" } =
    *entity_statement
    ;
// clang-format on

///
/// instantiation_list                                              [LRM93 §5.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// instantiation_list ::=
///       instantiation_label { , instantiation_label }
///     | others
///     | all
/// @endcode
///
// clang-format off
auto const instantiation_list = x3::rule<struct instantiation_list_class, ast::instantiation_list>{ "instantiation list" } =
      (label % ',')
    | OTHERS
    | ALL
    ;
// clang-format on

///
/// component_specification                                         [LRM93 §5.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// component_specification ::=
///     instantiation_list : component_name
/// @endcode
///
// clang-format off
auto const component_specification = x3::rule<struct component_specification_class, ast::component_specification>{ "component specification" } =
    instantiation_list >> ':' >> name
    ;
// clang-format on

///
/// generic_map_aspect                                          [LRM93 §5.2.1.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// generic_map_aspect ::=
///     generic map ( generic_association_list )
/// @endcode
///
// clang-format off
auto const generic_map_aspect = x3::rule<struct generic_map_aspect_class, ast::generic_map_aspect>{ "generic map aspect" } =
    GENERIC >> MAP >> '(' >> association_list >> ')'
    ;
// clang-format on

///
/// port_map_aspect                                             [LRM93 §5.2.1.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// port_map_aspect ::=
///     port map ( port_association_list )
/// @endcode
///
// clang-format off
auto const port_map_aspect = x3::rule<struct port_map_aspect_class, ast::port_map_aspect>{ "port map aspect" } =
    PORT >> MAP >> '(' >> association_list >> ')'
    ;
// clang-format on

///
/// binding_indication                                            [LRM93 §5.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// binding_indication ::=
///     [ use entity_aspect ]
///     [ generic_map_aspect ]
///     [ port_map_aspect ]
/// @endcode
///
/// FixMe: test case with selected_name doesn't work as expected yet.
///
// clang-format off
auto const binding_indication = x3::rule<struct binding_indication_class, ast::binding_indication>{ "binding indication" } =
       -( USE >> entity_aspect )
    >> -generic_map_aspect
    >> -port_map_aspect
    ;
// clang-format on

///
/// index_specification                                           [LRM93 §1.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// index_specification ::=
///       discrete_range
///     | static_expression
/// @endcode
///
// clang-format off
auto const index_specification = x3::rule<struct index_specification_class, ast::index_specification>{ "index specification" } =
      discrete_range
    | expression
    ;
// clang-format on

///
/// block_specification                                           [LRM93 §1.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_specification ::=
///       architecture_name
///     | block_statement_label
///     | generate_statement_label [ ( index_specification ) ]
/// @endcode
///
/// @note name matches also label (identifier), due to the optional index_specification the
/// meaning of parsed label identifier depends on context.
///
// clang-format off
auto const block_specification = x3::rule<struct block_specification_class, ast::block_specification>{ "block specification" } =
    // order matters
      label >> -( '(' >> index_specification >> ')' )
    | name      // architecture_name, block_statement_label (identifier)
    ;
// clang-format on

///
/// block_configuration                                           [LRM93 §1.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_configuration ::=
///     for block_specification
///         { use_clause }
///         { configuration_item }
///     end for ;
/// @endcode
///
// clang-format off
auto const block_configuration = x3::rule<struct block_configuration_class, ast::block_configuration>{ "block configuration" } =
       FOR
    >> block_specification
    >> *use_clause
    >> *configuration_item
    >> END >> FOR
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// component_configuration                                       [LRM93 §1.3.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// component_configuration ::=
///     for component_specification
///         [ binding_indication ; ]
///         [ block_configuration ]
///     end for ;
/// @endcode
///
// clang-format off
auto const component_configuration = x3::rule<struct component_configuration_class, ast::component_configuration>{ "component configuration" } =
       FOR
    >> component_specification
    >> -( binding_indication >> x3::expect[ ';' ] )
    >> -block_configuration
    >> END >> FOR
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// component_declaration                                           [LRM93 §4.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// component_declaration ::=
///     component identifier [ is ]
///         [ local_generic_clause ]
///         [ local_port_clause ]
///     end component [ component_simple_name ] ;
/// @endcode
///
// clang-format off
auto const component_declaration = x3::rule<struct component_declaration_class, ast::component_declaration>{ "component declaration" } =
       COMPONENT
    >> identifier
    >> -IS
    >> -generic_clause
    >> -port_clause
    >> END >> COMPONENT >> -simple_name
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// configuration_specification                                     [LRM93 §5.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// configuration_specification ::=
///     for component_specification binding_indication ;
/// @endcode
///
// clang-format off
auto const configuration_specification = x3::rule<struct configuration_specification_class, ast::configuration_specification>{ "configuration specification" } =
    FOR >> component_specification >> binding_indication >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// guarded_signal_specification                                    [LRM93 §5.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// guarded_signal_specification ::=
///     guarded_signal_list : type_mark
/// @endcode
///
// clang-format off
auto const guarded_signal_specification = x3::rule<struct guarded_signal_specification_class, ast::guarded_signal_specification>{ "guarded signal specification" } =
    signal_list >> ':' >> type_mark
    ;
// clang-format on

///
/// disconnection_specification                                     [LRM93 §5.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// disconnection_specification ::=
///     disconnect guarded_signal_specification after time_expression ;
/// @endcode
///
// clang-format off
auto const disconnection_specification = x3::rule<struct disconnection_specification_class, ast::disconnection_specification>{ "disconnection specification" } =
    DISCONNECT >> guarded_signal_specification >> AFTER >> expression >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// block_declarative_item                                        [LRM93 §1.2.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_declarative_item ::=
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
/// @endcode
///
// clang-format off
auto const block_declarative_item = x3::rule<struct block_declarative_item_class, ast::block_declarative_item>{ "block declarative item" } =
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

///
/// block_declarative_part                                          [LRM93 §9.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_declarative_part ::=
///     { block_declarative_item }
/// @endcode
///
// clang-format off
auto const block_declarative_part = x3::rule<struct block_declarative_part_class, ast::block_declarative_part>{ "block declarative part" } =
    *block_declarative_item
    ;
// clang-format on

///
/// block_header                                                    [LRM93 §9.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_header ::=
///     [ generic_clause
///     [ generic_map_aspect ; ] ]
///     [ port_clause
///     [ port_map_aspect ; ] ]
/// @endcode
///
// clang-format off
auto const block_header = x3::rule<struct block_header_class, ast::block_header>{ "block header" } =
       -x3::as<ast::block_header::generic_part_chunk>[
            generic_clause >> -( generic_map_aspect >> x3::expect[ ';' ] )
       ]
    >> -x3::as<ast::block_header::port_part_chunk>[
            port_clause >> -( port_map_aspect >> x3::expect[ ';' ] )
       ]
    ;
// clang-format on

///
/// block_statement_part                                            [LRM93 §9.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_statement_part ::=
///     { concurrent_statement }
/// @endcode
///
// clang-format off
auto const block_statement_part = x3::rule<struct block_statement_part_class, ast::block_statement_part>{ "block statement part" } =
    *concurrent_statement
    ;
// clang-format on

///
/// block_statement                                                 [LRM93 §9.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// block_statement ::=
///     block_label :
///         block [ ( guard_expression ) ] [ is ]
///             block_header
///             block_declarative_part
///         begin
///             block_statement_part
///         end block [ block_label ] ;
/// @endcode
///
// clang-format off
auto const block_statement = x3::rule<struct block_statement_class, ast::block_statement>{ "block statement" } =
       label_colon
    >> BLOCK
    >> -( '(' >> expression >> ')' )
    >> -IS
    >> block_header
    >> block_declarative_part
    >> BEGIN
    >> block_statement_part
    >> END >> BLOCK >> -label
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// instantiated_unit                                               [LRM93 §9.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// instantiated_unit ::=
///       [ component ] component_name
///     | entity entity_name [ ( architecture_identifier ) ]
///     | configuration configuration_name
/// @endcode
///
// clang-format off
auto const instantiated_unit = x3::rule<struct instantiated_unit_class, ast::instantiated_unit>{ "instantiated unit" } =
      x3::as<ast::instantiated_unit_component>[
        -COMPONENT >> name
      ]
    | x3::as<ast::instantiated_unit_entity>[
        ENTITY >> name >> -( '(' >> identifier >> ')' )
      ]
    | x3::as<ast::instantiated_unit_configuration>[
        CONFIGURATION   >> name
      ]
    ;
// clang-format on

///
/// component_instantiation_statement                               [LRM93 §9.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// component_instantiation_statement ::=
///     instantiation_label :
///         instantiated_unit
///             [ generic_map_aspect ]
///             [ port_map_aspect ] ;
/// @endcode
///
// clang-format off
auto const component_instantiation_statement = x3::rule<struct component_instantiation_statement_class, ast::component_instantiation_statement>{ "component instantiation statement" } =
       label_colon
    >> instantiated_unit
    >> -generic_map_aspect
    >> -port_map_aspect
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// conditional_signal_assignment                                 [LRM93 §9.5.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// conditional_signal_assignment ::=
///     target    <= options conditional_waveforms ;
/// @endcode
///
// clang-format off
auto const conditional_signal_assignment = x3::rule<struct conditional_signal_assignment_class, ast::conditional_signal_assignment>{ "conditional signal assignment" } =
    target >> "<=" >> options >> conditional_waveforms >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// selected_waveforms                                            [LRM93 §9.5.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// selected_waveforms ::=
///     { waveform when choices , }
///     waveform when choices
/// @endcode
///
// clang-format off
auto const selected_waveforms = x3::rule<struct selected_waveforms_class, ast::selected_waveforms>{ "selected waveforms" } =
    ( waveform >> WHEN >> choices ) % ','
    ;
// clang-format on

///
/// selected_signal_assignment                                    [LRM93 §9.5.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// selected_signal_assignment ::=
///     with expression select
///         target    <= options selected_waveforms ;
/// @endcode
///
// clang-format off
auto const selected_signal_assignment = x3::rule<struct selected_signal_assignment_class, ast::selected_signal_assignment>{ "selected signal assignment" } =
    WITH >> expression >> SELECT >> target >> "<=" >> options >> selected_waveforms >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// concurrent_signal_assignment_statement                          [LRM93 §9.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// concurrent_signal_assignment_statement ::=
///       [ label : ] [ postponed ] conditional_signal_assignment
///     | [ label : ] [ postponed ] selected_signal_assignment
/// @endcode
///
// clang-format off
auto const concurrent_signal_assignment_statement = x3::rule<struct concurrent_signal_assignment_statement_class, ast::concurrent_signal_assignment_statement>{ "concurrent_signal_assignment_statement" } =
       -label_colon
    >> -POSTPONED
    >> ( conditional_signal_assignment
       | selected_signal_assignment
       )
    ;
// clang-format on

///
/// generation_scheme                                               [LRM93 §9.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// generation_scheme ::=
///       for generate_parameter_specification
///     | if condition
/// @endcode
///
// clang-format off
auto const generation_scheme = x3::rule<struct generation_scheme_class, ast::generation_scheme>{ "generation scheme" } =
      (FOR >> parameter_specification)
    | (IF  >> condition)
    ;
// clang-format on

///
/// generate_statement                                              [LRM93 §9.7]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// generate_statement ::=
///     generate_label :
///         generation_scheme generate
///             [ { block_declarative_item }
///         begin ]
///             { concurrent_statement }
///         end generate [ generate_label ] ;
/// @endcode
///
/// FixMe: testing this rule failed - never seen
/// concurrent_statement/component_instantiation_statement
///
// clang-format off
auto const generate_statement = x3::rule<struct generate_statement_class, ast::generate_statement>{ "generate statement" } =
       label_colon
    >> generation_scheme >> GENERATE >> -(*block_declarative_item >> BEGIN )
    >> *concurrent_statement
    >> END >> GENERATE  >> -label
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// concurrent_statement                                              [LRM93 §9]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// concurrent_statement ::=
///       block_statement
///     | process_statement
///     | concurrent_procedure_call_statement
///     | concurrent_assertion_statement
///     | concurrent_signal_assignment_statement
///     | component_instantiation_statement
///     | generate_statement
/// @endcode
///
/// @note **recursive calls**:
/// @dot
/// digraph concurrent_statement {
///     concurrent_statement[style=filled];
///
///     concurrent_statement -> generate_statement, " ...";
///     generate_statement -> "...", concurrent_statement;
///     block_statement -> block_statement_part -> concurrent_statement;
/// }
/// @enddot
///
/// FixMe: order matters but is fragile; the problem seems to rise from rule
/// label >> ':', which is same/similar to component_instantiation_statement
///
// clang-format off
auto const concurrent_statement_def = // recursive call
    // order matters
      component_instantiation_statement
    | concurrent_signal_assignment_statement
    | concurrent_procedure_call_statement
    | concurrent_assertion_statement
    | block_statement
    | generate_statement
    | process_statement
    ;
// clang-format on

///
/// architecture_declarative_part                                   [LRM93 §1.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// architecture_declarative_part ::=
///     { block_declarative_item }
/// @endcode
///
// clang-format off
auto const architecture_declarative_part = x3::rule<struct architecture_declarative_part_class, ast::architecture_declarative_part>{ "architecture declarative part" } =
    *block_declarative_item
    ;
// clang-format on

///
/// architecture_statement_part                                   [LRM93 §1.2.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// architecture_statement_part ::=
///     { concurrent_statement }
/// @endcode
///
// clang-format off
auto const architecture_statement_part = x3::rule<struct architecture_statement_part_class, ast::architecture_statement_part>{ "architecture statement part" } =
    *concurrent_statement
    ;
// clang-format on

///
/// architecture_body                                               [LRM93 §1.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// architecture_body ::=
///     architecture identifier of entity_name is
///         architecture_declarative_part
///     begin
///         architecture_statement_part
///     end [ architecture ] [ architecture_simple_name ] ;
/// @endcode
///
// clang-format off
auto const architecture_body = x3::rule<struct architecture_body_class, ast::architecture_body>{ "architecture body" } =
       ARCHITECTURE >> identifier >> OF >> name >> IS
    >> architecture_declarative_part
    >> BEGIN
    >> architecture_statement_part
    >> END >> -ARCHITECTURE >> -simple_name
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// configuration_item                                            [LRM93 §1.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// configuration_item ::=
///       block_configuration
///     | component_configuration
/// @endcode
///
/// @note **recursive calls**:
/// @dot
/// digraph configuration_item {
///     configuration_item[style=filled];
///     configuration_item -> block_configuration, component_configuration;
///     block_configuration ->	block_specification, use_clause, configuration_item;
///     component_configuration -> component_specification, binding_indication, block_configuration;
/// }
/// @enddot
///
// clang-format off
auto const configuration_item_def = // recursive call
      block_configuration
    | component_configuration
    ;
// clang-format on

/// configuration_declarative_item                                  [LRM93 §1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// configuration_declarative_item ::=
///       use_clause
///     | attribute_specification
///     | group_declaration
/// @endcode
///
// clang-format off
auto const configuration_declarative_item = x3::rule<struct configuration_declarative_item_class, ast::configuration_declarative_item>{ "configuration declarative item" } =
      use_clause
    | attribute_specification
    | group_declaration
    ;
// clang-format on

///
/// configuration_declarative_part                                  [LRM93 §1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// configuration_declarative_part ::=
///     { configuration_declarative_item }
/// @endcode
///
// clang-format off
auto const configuration_declarative_part = x3::rule<struct configuration_declarative_part_class, ast::configuration_declarative_part>{ "configuration declarative part" } =
    *configuration_declarative_item
    ;
// clang-format on

///
/// configuration_declaration                                       [LRM93 §1.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// configuration_declaration ::=
///     configuration identifier of entity_name is
///         configuration_declarative_part
///         block_configuration
///     end [ configuration ] [ configuration_simple_name ] ;
/// @endcode
///
// clang-format off
auto const configuration_declaration = x3::rule<struct configuration_declaration_class, ast::configuration_declaration>{ "configuration declaration" } =
       CONFIGURATION
    >> identifier
    >> OF
    >> name
    >> IS
    >> configuration_declarative_part
    >> block_configuration
    >> END >> -CONFIGURATION  >> -simple_name
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// entity_declarative_item                                       [LRM93 §1.1.2]
///
/// Implementation of the BNF rule:
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
///
// clang-format off
auto const entity_declarative_item = x3::rule<struct entity_declarative_item_class, ast::entity_declarative_item>{ "entity declarative item" } =
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
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_declarative_part ::=
///     { entity_declarative_item }
/// @endcode
///
// clang-format off
auto const entity_declarative_part = x3::rule<struct entity_declarative_part_class, ast::entity_declarative_part>{ "entity declarative part" } =
    *entity_declarative_item
    ;
// clang-format on

///
/// entity_declaration                                              [LRM93 §1.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// entity_declaration ::=
///     entity identifier is
///         entity_header
///         entity_declarative_part
///   [ begin
///         entity_statement_part ]
///     end [ entity ] [ entity_simple_name ] ;
/// @endcode
///
// clang-format off
auto const entity_declaration = x3::rule<struct entity_declaration_class, ast::entity_declaration>{ "entity declaration" } =
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
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// package_declarative_item                                        [LRM93 §2.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_declarative_item ::=
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
/// @endcode
///
// clang-format off
auto const package_declarative_item  = x3::rule<struct package_declarative_item_class, ast::package_declarative_item>{ "package declarative item" } =
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

///
/// package_declarative_part                                        [LRM93 §2.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_declarative_part ::=
///     { package_declarative_item }
/// @endcode
///
// clang-format off
auto const package_declarative_part = x3::rule<struct package_declarative_part_class, ast::package_declarative_part>{ "package declarative part" } =
    *package_declarative_item
    ;
// clang-format on

///
/// package_declaration                                             [LRM93 §2.5]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_declaration ::=
///     package identifier is
///         package_declarative_part
///     end [ package ] [ package_simple_name ] ;
/// @endcode
///
// clang-format off
auto const package_declaration = x3::rule<struct package_declaration_class, ast::package_declaration>{ "package declaration" } =
      ( PACKAGE > identifier > IS
    >      package_declarative_part
    > END ) >> -PACKAGE >> -simple_name >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// primary_unit                                                   [LRM93 §11.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// primary_unit ::=
///       entity_declaration
///     | configuration_declaration
///     | package_declaration
/// @endcode
///
// clang-format off
auto const primary_unit = x3::rule<struct primary_unit_class, ast::primary_unit>{ "primary unit" } =
      entity_declaration
    | configuration_declaration
    | package_declaration
    ;
// clang-format on

///
/// package_body_declarative_item                                   [LRM93 §2.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_body_declarative_item ::=
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
/// @endcode
///
// clang-format off
auto const package_body_declarative_item = x3::rule<struct package_body_declarative_item_class, ast::package_body_declarative_item>{ "package_body_declarative_item" } =
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

///
/// package_body_declarative_part                                   [LRM93 §2.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_body_declarative_part ::=
///     { package_body_declarative_item }
/// @endcode
///
// clang-format off
auto const package_body_declarative_part = x3::rule<struct package_body_declarative_part_class, ast::package_body_declarative_part>{ "package_body_declarative_part" } =
    *package_body_declarative_item
    ;
// clang-format on

///
/// package_body                                                    [LRM93 §2.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// package_body ::=
///     package body package_simple_name is
///         package_body_declarative_part
///     end [ package body ] [ package_simple_name ] ;
/// @endcode
///
// clang-format off
auto const package_body = x3::rule<struct package_body_class, ast::package_body>{ "package body" } =
       PACKAGE
    >> BODY
    >> simple_name
    >> IS
    >> package_body_declarative_part
    >> END
    >> -(PACKAGE >> BODY)
    >> -simple_name
    >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// secondary_unit                                                 [LRM93 §11.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// secondary_unit ::=
///       architecture_body
///     | package_body
/// @endcode
///
// clang-format off
auto const secondary_unit = x3::rule<struct secondary_unit_class, ast::secondary_unit>{ "secondary unit" } =
      architecture_body
    | package_body
    ;
// clang-format on

///
/// library_unit                                                   [LRM93 §11.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// library_unit ::=
///       primary_unit
///     | secondary_unit
/// @endcode
///
// clang-format off
auto const library_unit = x3::rule<struct library_unit_class, ast::library_unit>{ "library unit" } =
      primary_unit
    | secondary_unit
    ;
// clang-format on

///
/// literal                                                       [LRM93 §7.3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// literal ::=
///       numeric_literal
///     | enumeration_literal
///     | string_literal
///     | bit_string_literal
///     | null
/// @endcode
///
/// @dot
/// digraph literal {
///     literal[style=filled];
///
///     literal -> numeric_literal,enumeration_literal, string_literal,
///                bit_string_literal, NULL;
///     bit_string_literal -> base_specifier, bit_value;
///     string_literal -> graphic_character;
///     enumeration_literal -> identifier, character_literal;
///     identifier -> basic_identifier, extended_identifier;
///     numeric_literal -> abstract_literal, physical_literal;
///     abstract_literal -> decimal_literal, based_literal;
///     decimal_literal -> integer;
///     based_literal -> integer, extended_digit;
///     physical_literal -> abstract_literal, name;
///     bit_value -> extended_digit;
///
///     // used by e.g. ...
///     primary -> name, literal, "...";
/// }
/// @enddot
///
/// @note Even this rule isn't recursive, it's jammed with BOOSTS_SPIRIT_{DECLARE,DEFINE,INSTANCE}
/// for simple testsuite test case test this days.
///
// clang-format off
auto const literal_def = //  = x3::rule<struct _class, ast::>{ "" } = 
      // order matters
      enumeration_literal
    | string_literal
    | bit_string_literal
    | numeric_literal
    | NULL_
    ;
// clang-format on

///
/// qualified_expression                                          [LRM93 §7.3.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// qualified_expression ::=
///       type_mark ' ( expression )
///     | type_mark ' aggregate
/// @endcode
///
/// This BNF rule is ambiguous, since
///
/// @dot
/// digraph qualified_expression {
///     qualified_expression[style=filled];
///     qualified_expression -> name, expression, aggregate;
///     aggregate -> element_association;
///     element_association -> choices, expression;
///     expression -> // relation-> shift_expression -> simple_expression -> term -> factor
///      "..." -> primary;
///     primary -> name, " ... " , expression;
/// }
/// @enddot
///
/// The AST node takes care on this.
///
// clang-format off
auto const qualified_expression = x3::rule<struct qualified_expression_class, ast::qualified_expression>{ "qualified expression" } =
       type_mark
    >> "\'"
    >> (
         "(" >> expression >> ")"
       |  aggregate
       )
    ;
// clang-format on

///
/// allocator                                                     [LRM93 §7.3.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// allocator ::=                                                 [LRM93 §7.3.6]
///       new subtype_indication
///     | new qualified_expression
/// @endcode
///
// clang-format off
auto const allocator = x3::rule<struct allocator_class, ast::allocator>{ "allocator" } =
    // order matters
       NEW
    >> ( qualified_expression
       | subtype_indication
       )
    ;
// clang-format on

///
/// library_clause                                                 [LRM93 §11.2]
///
/// Implementation of the BNF rule:
///
/// @code {.bnf}
/// library_clause ::=
///     library logical_name_list ;
/// @endcode
///
// clang-format off
auto const library_clause = x3::rule<struct library_clause_class, ast::library_clause>{ "library clause" } =
    LIBRARY >> logical_name_list >> x3::expect[ ';' ]
    ;
// clang-format on

///
/// context_item                                                   [LRM93 §11.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// context_item ::=
///       library_clause
///     | use_clause
/// @endcode
///
// clang-format off
auto const context_item = x3::rule<struct context_item_class, ast::context_item>{ "context item" } =
      library_clause
    | use_clause
    ;
// clang-format on

///
/// context_clause                                                 [LRM93 §11.3]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// context_clause ::=
///     { context_item }
/// @endcode
///
// clang-format off
auto const context_clause = x3::rule<struct context_clause_class, ast::context_clause>{ "context clause" } =
    *context_item
    ;
// clang-format on

///
/// design_unit                                                    [LRM93 §11.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// design_unit ::=
///     context_clause library_unit
/// @endcode
///
// clang-format off
auto const design_unit = x3::rule<struct design_unit_class, ast::design_unit>{ "design unit" } =
    context_clause >> library_unit
    ;
// clang-format on

///
/// design_file                                                    [LRM93 §11.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// design_file ::=
///     design_unit { design_unit }
/// @endcode
///
// clang-format off
auto const design_file_def = //x3::rule<struct design_file_class, ast::design_file>{ "design file" } =
    *design_unit
    ;
// clang-format on

///
/// start rule for grammar
///
// clang-format off
auto const grammar_entry_def =
    x3::skip(space | comment)[
        design_file 
    ]
    ;
// clang-format on

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

///
/// constraint                                                      [LRM93 §4.2]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// constraint ::=
///       range_constraint
///     | index_constraint
/// @endcode
///
/// @note **recursive calls**:
/// @dot
/// digraph constraint {
///     constraint[style=filled];
///     constraint -> range_constraint, index_constraint;
///
///     range_constraint -> range;
///     range -> range_attribute_name, simple_expression;
///
///     index_constraint -> discrete_range;
///     discrete_range -> subtype_indication, range;
///
///     subtype_indication -> name, constraint;
/// }
/// @enddot
///
// clang-format off
auto const constraint_def = // recursive call
      range_constraint
    | index_constraint
    ;
// clang-format on

///
/// expression                                                      [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// expression ::=
///       relation { and relation }
///     | relation { or relation }
///     | relation { xor relation }
///     | relation [ nand relation ]
///     | relation [ nor relation ]
///     | relation { xnor relation }
/// @endcode
///
/// with
///
/// @code{.bnf}
/// binary_logical_operator ::=  and | or | xor | xnor
/// unary_logical_operator  ::=  nand | nor
/// @endcode
///
/// @dot
/// digraph expression {
///     expression[style=filled];
///     expression -> relation -> shift_expression -> simple_expression;
///     simple_expression-> term -> factor -> primary;
///     primary -> name, "...";
///     primary -> expression[penwidth=3];
// }
/// @enddot
///
namespace detail {

// clang-format off
auto const binary_expression = x3::rule<struct expression_binary_class, std::vector<ast::expression::chunk>>{ "expression" } =
    *(binary_logical_operator >> relation)
    ;

auto const unary_expression = x3::rule<struct expression_unary_class, std::vector<ast::expression::chunk>>{ "expression" } =
    x3::repeat(1)[ // enforce artificial vector to unify ast node
        unary_logical_operator >> relation
    ];
// clang-format on

}  // namespace detail

// clang-format off
auto const expression_def = //  = x3::rule<struct _class, ast::>{ "" } =
       relation
    >> ( detail::unary_expression    // NAND, NOR
       | detail::binary_expression   // AND, ...
       )
    ;
// clang-format on

/// function_call ::=                                             [LRM93 §7.3.3]
///     function_name [ ( actual_parameter_part ) ]
///
// clang-format off
auto const function_call_def = //  = x3::rule<struct _class, ast::>{ "" } =
    name >> -( '(' >> actual_parameter_part >> ')' )
    ;
// clang-format on

///
/// name                                                            [LRM93 §6.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// name ::=
///       simple_name
///     | operator_symbol
///     | selected_name
///     | indexed_name
///     | slice_name
///     | attribute_name
/// @endcode
///
/// @todo using LRM BNF rule for selected_name results into left recursion, see
/// selected_name for details.
// clang-format off
auto const name_def =
        simple_name
      | operator_symbol
///      | selected_name
///    | indexed_name // FixMe
///    | slice_name
///    | attribute_name
    ;
// clang-format on

///
/// selected_name                                                   [LRM93 §6.3]
///
/// Implementation of the BNF rule:
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
/// FixMe: left recursion, doesn't work with 'plain' use_clause
///
// clang-format off
auto const selected_name_def = //  = x3::rule<struct _class, ast::>{ "" } =
    x3::lexeme[
        prefix >> '.' >> suffix
    ]
    ;
// clang-format on

///
/// indexed_name                                                    [LRM93 §6.4]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// indexed_name ::=
///     prefix ( expression { , expression } )
/// @endcode
///
// clang-format off
auto const indexed_name_def = //  = x3::rule<struct _class, ast::>{ "" } =
    prefix >> '(' >> (expression % ',') >> ')'
    ;
// clang-format on

///
/// slice_name                                                      [LRM93 §6.5]
///
/// @code{.bnf}
/// slice_name
///     prefix ( discrete_range )
/// @endcode
///
// clang-format off
auto const slice_name_def = //  = x3::rule<struct _class, ast::>{ "" } =
    prefix >> '(' >> discrete_range >> ')'
    ;
// clang-format on

///
/// attribute_name                                                  [LRM93 §6.6]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// attribute_name ::=
///     prefix [ signature ] ' attribute_designator [ ( expression ) ]
/// @endcode
///
/// with
///
/// @code{.bnf}
/// attribute_designator ::=
///     attribute_simple_name
/// @endcode
///
// clang-format off
auto const attribute_name_def =
    prefix >> -signature >> '\'' >> simple_name >> -( '(' >> expression >> ')' )
    ;
// clang-format on

///
/// prefix                                                          [LRM93 §6.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// prefix ::=
///       name
///     | function_call
/// @endcode
///
// clang-format off
auto const prefix_def = //  = x3::rule<struct _class, ast::>{ "" } =
      name
    | function_call
    ;
// clang-format on

///
/// primary                                                         [LRM93 §7.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// primary ::=
///       name
///     | literal
///     | aggregate
///     | function_call
///     | qualified_expression
///     | type_conversion
///     | allocator
///     | ( expression )
/// @endcode
///
// clang-format off
auto const primary_def = //  = x3::rule<struct _class, ast::>{ "" } =
    // Order matters; if aggregate is prior expression as of the BNF, a
    // backtracking problem occurred at:
    // aggregate -> element_association -> choices
      !char_('"') >> name // ignore string_literals which follows below
    | literal
    | function_call
    | qualified_expression
    //     | type_conversion
    | allocator
    | '(' >> expression >> ')'
    | aggregate
    ;
// clang-format on

///
/// direction                                                       [LRM93 §3.1]
///
/// @code{.bnf}
/// direction ::=
///     to | downto
/// @endcode
///
// clang-format off
auto const direction = x3::rule<struct direction_class, ast::keyword_token>{ "direction" } =
    TO | DOWNTO
    ;
// clang-format on

///
/// range                                                           [LRM93 §3.1]
///
/// Implementation of the BNF rule:
///
/// @code{.bnf}
/// range ::=
///       range_attribute_name
///     | simple_expression direction simple_expression
/// @endcode
///
/// FixMe: left recursion, factor out explicit_range A to|downto B
/// simple_expression can also be a name as of range_attribute_name.
///
// clang-format off
auto const range_def = //  = x3::rule<struct _class, ast::>{ "" } = // order matters
      x3::as<ast::range_expression>[
        simple_expression >> direction >> simple_expression
      ]
    | attribute_name
    ;
// clang-format on

/////////////////////////////////////////////////////////////////////////////////
///
/// Unused in BNF
///
///
/// object_declaration ::=                                        [LRM93 §4.3.1]
///       constant_declaration
///     | signal_declaration
///     | variable_declaration
///     | file_declaration
///
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

}  // namespace ibis::vhdl::parser

//******************************************************************************
// Spirit.X3 BNF Rule Definitions
//
#if !defined(DOXYGEN_DOCUMENTATION_BUILD)

namespace ibis::vhdl::parser {

#include <ibis/util/compiler/warnings_off.hpp>

// recursive calls
// clang-format off
BOOST_SPIRIT_DEFINE(
      configuration_item
    , concurrent_statement
    , constraint
    , sequence_of_statements
    , subprogram_declarative_item
)
// clang-format on

// top rule
BOOST_SPIRIT_DEFINE(design_file)

// start rule
BOOST_SPIRIT_DEFINE(grammar_entry)

BOOST_SPIRIT_DEFINE(literal)

// other
// clang-format off
BOOST_SPIRIT_DEFINE(
      attribute_name
    , expression
    , function_call
    , indexed_name
    , name
    , prefix
    , primary
    , range
    , selected_name
    , slice_name
)
// clang-format on

#include <ibis/util/compiler/warnings_on.hpp>

}  // namespace ibis::vhdl::parser

#endif  // !defined(DOXYGEN_DOCUMENTATION_BUILD)

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

#if 1  // use hand selected tags, or all tags derived from success_handler

namespace ibis::vhdl::parser {

// clang-format off

// top rule
struct design_file_class : success_handler, error_handler {};

// start rule
struct grammar_class : success_handler, error_handler {};

// currently used by start/end labels etc. to get diagnostic from diagnostic_handler,
// see also label_match.hpp
struct identifier_class : success_handler {};
struct architecture_body_class : success_handler {};
struct block_statement : success_handler {};
struct case_statement : success_handler {};
struct configuration_declaration : success_handler {};
struct entity_declaration : success_handler {};
struct generate_statement : success_handler {};
struct if_statement : success_handler {};
struct loop_statement : success_handler {};
struct package_body : success_handler {};
struct package_declaration : success_handler {};
struct process_statement : success_handler {};

// TBD
struct attribute_name_class : success_handler {};
struct expression_class : success_handler {};
struct function_call_class : success_handler {};
struct indexed_name_class : success_handler {};
struct literal_class : success_handler {};
struct name_class : success_handler {};
struct prefix_class : success_handler {};
struct primary_class : success_handler {};
struct range_class : success_handler {};
struct selected_name_class : success_handler {};
struct slice_name_class : success_handler {};
// clang-format on

}  // namespace ibis::vhdl::parser

#else

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
struct based_literal_class : success_handler {};
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

} // namespace ibis::vhdl::parser

#endif
