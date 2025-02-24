//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <iosfwd>

// FixMe: required on Win32, investigate!
#if defined(IN)
#undef IN
#endif
#if defined(OUT)
#undef OUT
#endif

namespace ibis::vhdl::ast {

enum class keyword_token {
    UNSPECIFIED_KEYWORD,
    ABS,
    ACCESS,
    AFTER,
    ALIAS,
    ALL,
    AND,
    ARCHITECTURE,
    ARRAY,
    ASSERT,
    ATTRIBUTE,
    BEGIN,
    BLOCK,
    BODY,
    BUFFER,
    BUS,
    CASE,
    COMPONENT,
    CONFIGURATION,
    CONSTANT,
    DISCONNECT,
    DOWNTO,
    ELSE,
    ELSIF,
    END,
    ENTITY,
    EXIT,
    FILE,
    FOR,
    FUNCTION,
    GENERATE,
    GENERIC,
    GROUP,
    GUARDED,
    IF,
    IMPURE,
    IN,
    INERTIAL,
    INOUT,
    IS,
    LABEL,
    LIBRARY,
    LINKAGE,
    LITERAL,
    LOOP,
    MAP,
    MOD,
    NAND,
    NEW,
    NEXT,
    NOR,
    NOT,
    NULL_,
    OF,
    ON,
    OPEN,
    OR,
    OTHERS,
    OUT,
    PACKAGE,
    PORT,
    POSTPONED,
    PROCEDURE,
    PROCESS,
    PURE,
    RANGE,
    RECORD,
    REGISTER,
    REJECT,
    REM,
    REPORT,
    RETURN,
    ROL,
    ROR,
    SELECT,
    SEVERITY,
    SIGNAL,
    SHARED,
    SLA,
    SLL,
    SRA,
    SRL,
    SUBTYPE,
    THEN,
    TO,
    TRANSPORT,
    TYPE,
    UNAFFECTED,
    UNITS,
    UNTIL,
    USE,
    VARIABLE,
    WAIT,
    WHEN,
    WHILE,
    WITH,
    XNOR,
    XOR
};

// required for BOOST_SPIRIT_X3_DEBUG
std::ostream& operator<<(std::ostream& os, ast::keyword_token token);

}  // namespace ibis::vhdl::ast

//
// Support Spirit.X3's attribute handling.
// Several nodes on AST has an boolean attribute on simply existence of an
// keyword, this simplifies evaluating on costs of spirit's move_to traits.
//
namespace boost::spirit::x3::traits {

inline void move_to(ibis::vhdl::ast::keyword_token token, bool& dest)
{
    dest = static_cast<bool>(token);
}

}  // namespace boost::spirit::x3::traits
