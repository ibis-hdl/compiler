//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/ast/node/keyword_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <iostream>

namespace ibis::vhdl::ast {

std::string_view as_string_view(keyword_token token)
{
    std::string_view token_sv{};

    // clang-format off
    switch (token) {
        case keyword_token::ABS:             token_sv = "ABS";           break;
        case keyword_token::ACCESS:          token_sv = "ACCESS";        break;
        case keyword_token::AFTER:           token_sv = "AFTER";         break;
        case keyword_token::ALIAS:           token_sv = "ALIAS";         break;
        case keyword_token::ALL:             token_sv = "ALL";           break;
        case keyword_token::AND:             token_sv = "AND";           break;
        case keyword_token::ARCHITECTURE:    token_sv = "ARCHITECTURE";  break;
        case keyword_token::ARRAY:           token_sv = "ARRAY";         break;
        case keyword_token::ASSERT:          token_sv = "ASSERT";        break;
        case keyword_token::ATTRIBUTE:       token_sv = "ATTRIBUTE";     break;
        case keyword_token::BEGIN:           token_sv = "BEGIN";         break;
        case keyword_token::BLOCK:           token_sv = "BLOCK";         break;
        case keyword_token::BODY:            token_sv = "BODY";          break;
        case keyword_token::BUFFER:          token_sv = "BUFFER";        break;
        case keyword_token::BUS:             token_sv = "BUS";           break;
        case keyword_token::CASE:            token_sv = "CASE";          break;
        case keyword_token::COMPONENT:       token_sv = "COMPONENT";     break;
        case keyword_token::CONFIGURATION:   token_sv = "CONFIGURATION"; break;
        case keyword_token::CONSTANT:        token_sv = "CONSTANT";      break;
        case keyword_token::DISCONNECT:      token_sv = "DISCONNECT";    break;
        case keyword_token::DOWNTO:          token_sv = "DOWNTO";        break;
        case keyword_token::ELSE:            token_sv = "ELSE";          break;
        case keyword_token::ELSIF:           token_sv = "ELSIF";         break;
        case keyword_token::END:             token_sv = "END";           break;
        case keyword_token::ENTITY:          token_sv = "ENTITY";        break;
        case keyword_token::EXIT:            token_sv = "EXIT";          break;
        case keyword_token::FILE:            token_sv = "FILE";          break;
        case keyword_token::FOR:             token_sv = "FOR";           break;
        case keyword_token::FUNCTION:        token_sv = "FUNCTION";      break;
        case keyword_token::GENERATE:        token_sv = "GENERATE";      break;
        case keyword_token::GENERIC:         token_sv = "GENERIC";       break;
        case keyword_token::GROUP:           token_sv = "GROUP";         break;
        case keyword_token::GUARDED:         token_sv = "GUARDED";       break;
        case keyword_token::IF:              token_sv = "IF";            break;
        case keyword_token::IMPURE:          token_sv = "IMPURE";        break;
        case keyword_token::IN:              token_sv = "IN";            break;
        case keyword_token::INERTIAL:        token_sv = "INERTIAL";      break;
        case keyword_token::INOUT:           token_sv = "INOUT";         break;
        case keyword_token::IS:              token_sv = "IS";            break;
        case keyword_token::LABEL:           token_sv = "LABEL";         break;
        case keyword_token::LIBRARY:         token_sv = "LIBRARY";       break;
        case keyword_token::LINKAGE:         token_sv = "LINKAGE";       break;
        case keyword_token::LITERAL:         token_sv = "LITERAL";       break;
        case keyword_token::LOOP:            token_sv = "LOOP";          break;
        case keyword_token::MAP:             token_sv = "MAP";           break;
        case keyword_token::MOD:             token_sv = "MOD";           break;
        case keyword_token::NAND:            token_sv = "NAND";          break;
        case keyword_token::NEW:             token_sv = "NEW";           break;
        case keyword_token::NEXT:            token_sv = "NEXT";          break;
        case keyword_token::NOR:             token_sv = "NOR";           break;
        case keyword_token::NOT:             token_sv = "NOT";           break;
        case keyword_token::NULL_:           token_sv = "NULL";          break;
        case keyword_token::OF:              token_sv = "OF";            break;
        case keyword_token::ON:              token_sv = "ON";            break;
        case keyword_token::OPEN:            token_sv = "OPEN";          break;
        case keyword_token::OR:              token_sv = "OR";            break;
        case keyword_token::OTHERS:          token_sv = "OTHERS";        break;
        case keyword_token::OUT:             token_sv = "OUT";           break;
        case keyword_token::PACKAGE:         token_sv = "PACKAGE";       break;
        case keyword_token::PORT:            token_sv = "PORT";          break;
        case keyword_token::POSTPONED:       token_sv = "POSTPONED";     break;
        case keyword_token::PROCEDURE:       token_sv = "PROCEDURE";     break;
        case keyword_token::PROCESS:         token_sv = "PROCESS";       break;
        case keyword_token::PURE:            token_sv = "PURE";          break;
        case keyword_token::RANGE:           token_sv = "RANGE";         break;
        case keyword_token::RECORD:          token_sv = "RECORD";        break;
        case keyword_token::REGISTER:        token_sv = "REGISTER";      break;
        case keyword_token::REJECT:          token_sv = "REJECT";        break;
        case keyword_token::REM:             token_sv = "REM";           break;
        case keyword_token::REPORT:          token_sv = "REPORT";        break;
        case keyword_token::RETURN:          token_sv = "RETURN";        break;
        case keyword_token::ROL:             token_sv = "ROL";           break;
        case keyword_token::ROR:             token_sv = "ROR";           break;
        case keyword_token::SELECT:          token_sv = "SELECT";        break;
        case keyword_token::SEVERITY:        token_sv = "SEVERITY";      break;
        case keyword_token::SIGNAL:          token_sv = "SIGNAL";        break;
        case keyword_token::SHARED:          token_sv = "SHARED";        break;
        case keyword_token::SLA:             token_sv = "SLA";           break;
        case keyword_token::SLL:             token_sv = "SLL";           break;
        case keyword_token::SRA:             token_sv = "SRA";           break;
        case keyword_token::SRL:             token_sv = "SRL";           break;
        case keyword_token::SUBTYPE:         token_sv = "SUBTYPE";       break;
        case keyword_token::THEN:            token_sv = "THEN";          break;
        case keyword_token::TO:              token_sv = "TO";            break;
        case keyword_token::TRANSPORT:       token_sv = "TRANSPORT";     break;
        case keyword_token::TYPE:            token_sv = "TYPE";          break;
        case keyword_token::UNAFFECTED:      token_sv = "UNAFFECTED";    break;
        case keyword_token::UNITS:           token_sv = "UNITS";         break;
        case keyword_token::UNTIL:           token_sv = "UNTIL";         break;
        case keyword_token::USE:             token_sv = "USE";           break;
        case keyword_token::VARIABLE:        token_sv = "VARIABLE";      break;
        case keyword_token::WAIT:            token_sv = "WAIT";          break;
        case keyword_token::WHEN:            token_sv = "WHEN";          break;
        case keyword_token::WHILE:           token_sv = "WHILE";         break;
        case keyword_token::WITH:            token_sv = "WITH";          break;
        case keyword_token::XNOR:            token_sv = "XNOR";          break;
        case keyword_token::XOR:             token_sv = "XOR";           break;

        case keyword_token::UNSPECIFIED:
            // probably got a default constructed token
            cxx_bug_fatal("keyword_token not specified!");

        default: // unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
    // clang-format on

    return token_sv;
}

}  // namespace ibis::vhdl::ast
