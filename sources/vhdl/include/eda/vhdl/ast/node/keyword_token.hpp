/*
 * keyword_token.hpp
 *
 *  Created on: 07.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_KEYWORD_TOKEN_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_KEYWORD_TOKEN_HPP_

#include <iosfwd>

namespace eda { namespace vhdl { namespace ast {

enum class keyword_token
{
    UNSPECIFIED, // used as default constructible marker
    ABS, ACCESS, AFTER, ALIAS, ALL, AND, ARCHITECTURE, ARRAY,
    ASSERT, ATTRIBUTE, BEGIN, BLOCK, BODY, BUFFER, BUS, CASE,
    COMPONENT, CONFIGURATION, CONSTANT, DISCONNECT, DOWNTO,
    ELSE, ELSIF, END, ENTITY, EXIT, FILE, FOR, FUNCTION,
    GENERATE, GENERIC, GROUP, GUARDED, IF, IMPURE, IN, INERTIAL,
    INOUT, IS, LABEL, LIBRARY, LINKAGE, LITERAL, LOOP, MAP, MOD,
    NAND, NEW, NEXT, NOR, NOT, NULL_, OF, ON, OPEN, OR, OTHERS,
    OUT, PACKAGE, PORT, POSTPONED, PROCEDURE, PROCESS, PURE,
    RANGE, RECORD, REGISTER, REJECT, REM, REPORT, RETURN, ROL,
    ROR, SELECT, SEVERITY, SIGNAL, SHARED, SLA, SLL, SRA, SRL,
    SUBTYPE, THEN, TO, TRANSPORT, TYPE, UNAFFECTED, UNITS,
    UNTIL, USE, VARIABLE, WAIT, WHEN, WHILE, WITH, XNOR, XOR
};


std::ostream& operator<<(std::ostream& os, keyword_token token);


} } } // namespace eda.vhdl.ast

/*
 * Support Spirit.X3's attribute handling.
 * Several nodes on AST has an boolean attribute on simply existence of an
 * keyword, this simplifies evaluating on cosst of spirit's move_to traits.
 */
namespace boost { namespace spirit { namespace x3 { namespace traits {

static inline void
move_to(eda::vhdl::ast::keyword_token token, bool& dest)
{
    dest = static_cast<bool>(token);
}

} } } } // boost.spirit.x3.traits

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_KEYWORD_TOKEN_HPP_ */
