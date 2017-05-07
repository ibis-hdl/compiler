/*
 * expression_def.hpp
 *
 *  Created on: 07.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_DEF_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_DEF_HPP_


#include <eda/vhdl93/ast_adapted.hpp>
#include <eda/vhdl93/parser/namespace_alias.hpp>
#include <eda/vhdl93/parser/keyword_def.hpp>

#include <eda/vhdl93/parser/spirit_x3.hpp>


/*
 * Operators
 */
namespace eda { namespace vhdl93 { namespace parser { namespace operators {

/*
 * Rule IDs
 */
struct logical_operator_class;
struct logical_operator_option_class;
struct logical_operator_option_class;
struct unary_miscellaneous_operator_class;
struct multiplying_operator_class;
struct shift_operator_class;


/*
 * Rule Types
 */
typedef x3::rule<logical_operator_class, ast::operator_token> logical_operator_type;
typedef x3::rule<logical_operator_option_class, ast::operator_token> logical_operator_option_type;
typedef x3::rule<unary_miscellaneous_operator_class, ast::operator_token> unary_miscellaneous_operator_type;
typedef x3::rule<multiplying_operator_class, ast::operator_token> multiplying_operator_type;
typedef x3::rule<shift_operator_class, ast::operator_token> shift_operator_type;
typedef x3::symbols<ast::operator_token> relational_operator_type;
typedef x3::symbols<ast::operator_token> binary_miscellaneous_operator_type;
typedef x3::symbols<ast::operator_token> adding_operator_type;
typedef x3::symbols<ast::operator_token> sign_operator_type;


/*
 * Rule Instances
 */
logical_operator_type const logical_operator{ "logical_operator" };
logical_operator_option_type const logical_operator_option{ "logical_operator" };
unary_miscellaneous_operator_type const unary_miscellaneous_operator{ "miscellaneous_operator" };
multiplying_operator_type const multiplying_operator{ "multiplying_operator" };
shift_operator_type const shift_operator{ "shift_operator" };


/*
 * Rule Declarations
 */
BOOST_SPIRIT_DECLARE(logical_operator_type);
BOOST_SPIRIT_DECLARE(logical_operator_option_type);
BOOST_SPIRIT_DECLARE(relational_operator_type);
BOOST_SPIRIT_DECLARE(unary_miscellaneous_operator_type);
BOOST_SPIRIT_DECLARE(binary_miscellaneous_operator_type);
BOOST_SPIRIT_DECLARE(adding_operator_type);
BOOST_SPIRIT_DECLARE(multiplying_operator_type);
BOOST_SPIRIT_DECLARE(shift_operator_type);
BOOST_SPIRIT_DECLARE(sign_operator_type);


/*
 * Rule Definitions
 */


/*
 * logical_operator ::=  and | or | nand | nor | xor | xnor              [§ 7.2]
 */

struct logical_operator_symbols : x3::symbols<ast::operator_token> {

    logical_operator_symbols() {

        name("logical_operator");

        add("and",  ast::operator_token::AND)
           ("or",   ast::operator_token::OR)
           ("xor",  ast::operator_token::XOR)
           ("xnor", ast::operator_token::XNOR)
           ;
    }
} const logical_operator_symbols;

struct logical_operator_option_symbols : x3::symbols<ast::operator_token> {

    logical_operator_option_symbols() {

        name("logical_operator");

        add("nand", ast::operator_token::NAND)
           ("nor",  ast::operator_token::NOR)
           ;
    }
} const logical_operator_option_symbols;


auto const logical_operator_def =
    x3::no_case[
        logical_operator_symbols
    ]
    ;

auto const logical_operator_option_def =
    x3::no_case[
        logical_operator_option_symbols
    ]
    ;


/*
 * relational_operator ::=   =  |  /=  |  <  |  <=  |  >  |  >=          [§ 7.2]
 */

struct relational_operator_symbols : x3::symbols<ast::operator_token> {

    relational_operator_symbols() {

        name("relational_operator");

        add("=",  ast::operator_token::EQUAL)
           ("/=", ast::operator_token::NOT_EQUALS)
           ("<",  ast::operator_token::LESS)
           ("<=", ast::operator_token::LESS_EQUALS)
           (">",  ast::operator_token::GREATER)
           (">=", ast::operator_token::GREATER_EQUALS)
           ;
    }
} const relational_operator;


/*
 * miscellaneous_operator ::=  ** | abs | not                            [§ 7.2]
 */

struct unary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    unary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("abs", ast::operator_token::ABS)
           ("not", ast::operator_token::NOT)
           ;
    }
} const unary_miscellaneous_operator_symbols;


auto const unary_miscellaneous_operator_def =
    x3::no_case[
        unary_miscellaneous_operator_symbols
    ]
    ;


struct binary_miscellaneous_operator_symbols : x3::symbols<ast::operator_token> {

    binary_miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("**", ast::operator_token::EXPONENT)
           ;
    }
} const binary_miscellaneous_operator;


/*
 * adding_operator ::=  + | -  | &                                       [§ 7.2]
 */

struct adding_operator_symbols : x3::symbols<ast::operator_token> {

    adding_operator_symbols() {

        name("adding_operator");

        add("+", ast::operator_token::ADD)
           ("-", ast::operator_token::SUB)
           ("&", ast::operator_token::CONCAT)
           ;
    }
} const adding_operator;


/*
 * multiplying_operator ::=  * | / | mod | rem                           [§ 7.2]
 */

struct multiplying_operator_symbols : x3::symbols<ast::operator_token> {

    multiplying_operator_symbols() {

        name("multiplying_operator");

        add("*",   ast::operator_token::MUL)
           ("/",   ast::operator_token::DIV)
           ("mod", ast::operator_token::MOD)
           ("rem", ast::operator_token::REM)
           ;
    }
} const multiplying_operator_symbols;


auto const multiplying_operator_def =
    x3::no_case[
        multiplying_operator_symbols
    ]
    ;


/*
 * shift_operator ::=  sll | srl | sla | sra | rol | ror                 [§ 7.2]
 */

struct shift_operator_symbols : x3::symbols<ast::operator_token> {

    shift_operator_symbols() {

        name("shift_operator");

        add("sll", ast::operator_token::SLL)
           ("srl", ast::operator_token::SRL)
           ("sla", ast::operator_token::SLA)
           ("sra", ast::operator_token::SRA)
           ("rol", ast::operator_token::ROL)
           ("ror", ast::operator_token::ROR)
           ;
    }
} const shift_operator_symbols;


auto const shift_operator_def =
    x3::no_case[
        shift_operator_symbols
    ]
    ;


/*
 * sign ::=  + | -                                                       [§ 7.2]
 */
struct sign_operator_symbols : x3::symbols<ast::operator_token> {

    sign_operator_symbols() {

        name("sign_operator");

        add("+", ast::operator_token::SIGN_POS)
           ("-", ast::operator_token::SIGN_NEG)
           ;
    }
} const sign;


/* get rid off the annoying unused parameter warnings from x3 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

BOOST_SPIRIT_DEFINE(
    logical_operator,
    logical_operator_option,
    unary_miscellaneous_operator,
    multiplying_operator,
    shift_operator
)

#pragma GCC diagnostic pop


} } } } // namespace eda.vhdl93.parser.operators


/*
 * Operators
 */
namespace eda { namespace vhdl93 { namespace parser {

using namespace parser::operators;

using iso8859_1::char_;
using iso8859_1::lit;
using x3::lexeme;
using x3::raw;



} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_EXPRESSION_DEF_HPP_ */
