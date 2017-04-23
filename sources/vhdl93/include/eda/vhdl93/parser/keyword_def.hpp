/*
 * keywords.hpp
 *
 *  Created on: 18.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_KEYWORDS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_KEYWORDS_HPP_


#include <eda/vhdl93/parser/utils.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>

#include <boost/spirit/home/x3.hpp>
#include <eda/vhdl93/parser/namespace_alias.hpp>


/*
 * IEEE Standard VHDL Language Reference Manual
 * (IEEE Std. 1076-1993)
 * http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_TOC.HTM
 *
 * http://www.amos.eguru-il.com/vhdl_info/vhdl93_syntax.html
 */


namespace eda { namespace vhdl93 { namespace parser {


/*
 * Parser keyword definitions
 */
#if defined(NULL)
#undef NULL
#endif

auto kw = [](auto xx) {
    return x3::lexeme [ x3::no_case[ xx ] >> !(iso8859_1::alnum | '_') ];
};

auto const ABS = kw("abs");
auto const ACCESS = kw("access");
auto const AFTER = kw("after");
auto const ALIAS = kw("alias");
auto const ALL = as_type<ast::keyword_token>(
    kw("all") >> x3::attr(ast::keyword_token::ALL)
);
auto const AND = kw("and");
auto const ARCHITECTURE = kw("architecture");
auto const ARRAY = kw("array");
auto const ASSERT = kw("assert");
auto const ATTRIBUTE = kw("attribute");
auto const BEGIN = kw("begin");
auto const BLOCK = kw("block");
auto const BODY = kw("body");
auto const BUFFER = kw("buffer");
auto const BUS = as_type<ast::keyword_token>(
    kw("bus") >> x3::attr(ast::keyword_token::BUS)
);
auto const CASE = kw("case");
auto const COMPONENT = kw("component");
auto const CONFIGURATION = kw("configuration");
auto const CONSTANT = kw("constant");
auto const DISCONNECT = kw("disconnect");
auto const DOWNTO = as_type<ast::keyword_token>(
    kw("downto") >> x3::attr(ast::keyword_token::DOWNTO)
);
auto const ELSE = kw("else");
auto const ELSIF = kw("elsif");
auto const END = kw("end");
auto const ENTITY = kw("entity");
auto const EXIT = kw("exit");
auto const FILE = kw("file");
auto const FOR = kw("for");
auto const FUNCTION = kw("function");
auto const GENERATE = kw("generate");
auto const GENERIC = kw("generic");
auto const GROUP = kw("group");
auto const GUARDED = kw("guarded");
auto const IF = kw("if");
auto const IMPURE = kw("impure");
auto const IN = kw("in");
auto const INERTIAL = kw("inertial");
auto const INOUT = kw("inout");
auto const IS = kw("is");
auto const LABEL = kw("label");
auto const LIBRARY = kw("library");
auto const LINKAGE = kw("linkage");
auto const LITERAL = as_type<ast::keyword_token>(
    kw("literal") >> x3::attr(ast::keyword_token::LITERAL)
);
auto const LOOP = kw("loop");
auto const MAP = kw("map");
auto const MOD = kw("mod");
auto const NAND = kw("nand");
auto const NEW = kw("new");
auto const NEXT = kw("next");
auto const NOR = kw("nor");
auto const NOT = kw("not");
auto const NULL = as_type<ast::keyword_token>(
    kw("null") >> x3::attr(ast::keyword_token::NULL)
);
auto const OF = kw("of");
auto const ON = kw("on");
auto const OPEN = kw("open");
auto const OR = kw("or");
auto const OTHERS = as_type<ast::keyword_token>(
    kw("others") >> x3::attr(ast::keyword_token::OTHERS)
);
auto const OUT = kw("out");
auto const PACKAGE = kw("package");
auto const PORT = kw("port");
auto const POSTPONED = kw("postponed");
auto const PROCEDURE = kw("procedure");
auto const PROCESS = kw("process");
auto const PURE = kw("pure");
auto const RANGE = kw("range");
auto const RECORD = kw("record");
auto const REGISTER = as_type<ast::keyword_token>(
    kw("register") >> x3::attr(ast::keyword_token::REGISTER)
);
auto const REJECT = kw("reject");
auto const REM = kw("rem");
auto const REPORT = kw("report");
auto const RETURN = kw("return");
auto const ROL = kw("rol");
auto const ROR = kw("ror");
auto const SELECT = kw("select");
auto const SEVERITY = kw("severity");
auto const SIGNAL = kw("signal");
auto const SHARED = kw("shared");
auto const SLA = kw("sla");
auto const SLL = kw("sll");
auto const SRA = kw("sra");
auto const SRL = kw("srl");
auto const SUBTYPE = kw("subtype");
auto const THEN = kw("then");
auto const TO = as_type<ast::keyword_token>(
    kw("to") >> x3::attr(ast::keyword_token::TO)
);
auto const TRANSPORT = kw("transport");
auto const TYPE = kw("type");
auto const UNAFFECTED = kw("unaffected");
auto const UNITS = kw("units");
auto const UNTIL = kw("until");
auto const USE = kw("use");
auto const VARIABLE = kw("variable");
auto const WAIT = kw("wait");
auto const WHEN = kw("when");
auto const WHILE = kw("while");
auto const WITH = kw("with");
auto const XNOR = kw("xnor");
auto const XOR = kw("xor");


/*
 * Symbols of all keyword to them distinguish from identifier by rule
 */
struct keyword_symbols : x3::symbols<> {

    keyword_symbols() {

        name("keyword");

        add("abs") ("access") ("after") ("alias") ("all") ("and")
           ("architecture") ("array") ("assert") ("attribute") ("begin")
           ("block") ("body") ("buffer") ("bus") ("case") ("component")
           ("configuration") ("constant") ("disconnect") ("downto") ("else")
           ("elsif") ("end") ("entity") ("exit") ("file") ("for")
           ("function") ("generate") ("generic") ("group") ("guarded")
           ("if") ("impure") ("in") ("inertial") ("inout") ("is") ("label")
           ("library") ("linkage") ("literal") ("loop") ("map") ("mod")
           ("nand") ("new") ("next") ("nor") ("not") ("null") ("of") ("on")
           ("open") ("or") ("others") ("out") ("package") ("port")
           ("postponed") ("procedure") ("process") ("pure") ("range")
           ("record") ("register") ("reject") ("rem") ("report") ("return")
           ("rol") ("ror") ("select") ("severity") ("signal") ("shared")
           ("sla") ("sll") ("sra") ("srl") ("subtype") ("then") ("to")
           ("transport") ("type") ("unaffected") ("units") ("until") ("use")
           ("variable") ("wait") ("when") ("while") ("with") ("xnor")
           ("xor")
           ;
    }
} const keywords;

auto const keyword = x3::rule<struct _> { "keyword" } =
    kw( keywords )
    ;


} } } // namespace eda.vhdl93.parser


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_KEYWORDS_HPP_ */
