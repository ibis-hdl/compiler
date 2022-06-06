//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/ast/node/keyword_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <iostream>

namespace ibis::vhdl::ast {

std::ostream& operator<<(std::ostream& os, keyword_token token)
{
    // clang-format off
    switch (token) {
        case keyword_token::ABS:             os << "ABS";           break;
        case keyword_token::ACCESS:          os << "ACCESS";        break;
        case keyword_token::AFTER:           os << "AFTER";         break;
        case keyword_token::ALIAS:           os << "ALIAS";         break;
        case keyword_token::ALL:             os << "ALL";           break;
        case keyword_token::AND:             os << "AND";           break;
        case keyword_token::ARCHITECTURE:    os << "ARCHITECTURE";  break;
        case keyword_token::ARRAY:           os << "ARRAY";         break;
        case keyword_token::ASSERT:          os << "ASSERT";        break;
        case keyword_token::ATTRIBUTE:       os << "ATTRIBUTE";     break;
        case keyword_token::BEGIN:           os << "BEGIN";         break;
        case keyword_token::BLOCK:           os << "BLOCK";         break;
        case keyword_token::BODY:            os << "BODY";          break;
        case keyword_token::BUFFER:          os << "BUFFER";        break;
        case keyword_token::BUS:             os << "BUS";           break;
        case keyword_token::CASE:            os << "CASE";          break;
        case keyword_token::COMPONENT:       os << "COMPONENT";     break;
        case keyword_token::CONFIGURATION:   os << "CONFIGURATION"; break;
        case keyword_token::CONSTANT:        os << "CONSTANT";      break;
        case keyword_token::DISCONNECT:      os << "DISCONNECT";    break;
        case keyword_token::DOWNTO:          os << "DOWNTO";        break;
        case keyword_token::ELSE:            os << "ELSE";          break;
        case keyword_token::ELSIF:           os << "ELSIF";         break;
        case keyword_token::END:             os << "END";           break;
        case keyword_token::ENTITY:          os << "ENTITY";        break;
        case keyword_token::EXIT:            os << "EXIT";          break;
        case keyword_token::FILE:            os << "FILE";          break;
        case keyword_token::FOR:             os << "FOR";           break;
        case keyword_token::FUNCTION:        os << "FUNCTION";      break;
        case keyword_token::GENERATE:        os << "GENERATE";      break;
        case keyword_token::GENERIC:         os << "GENERIC";       break;
        case keyword_token::GROUP:           os << "GROUP";         break;
        case keyword_token::GUARDED:         os << "GUARDED";       break;
        case keyword_token::IF:              os << "IF";            break;
        case keyword_token::IMPURE:          os << "IMPURE";        break;
        case keyword_token::IN:              os << "IN";            break;
        case keyword_token::INERTIAL:        os << "INERTIAL";      break;
        case keyword_token::INOUT:           os << "INOUT";         break;
        case keyword_token::IS:              os << "IS";            break;
        case keyword_token::LABEL:           os << "LABEL";         break;
        case keyword_token::LIBRARY:         os << "LIBRARY";       break;
        case keyword_token::LINKAGE:         os << "LINKAGE";       break;
        case keyword_token::LITERAL:         os << "LITERAL";       break;
        case keyword_token::LOOP:            os << "LOOP";          break;
        case keyword_token::MAP:             os << "MAP";           break;
        case keyword_token::MOD:             os << "MOD";           break;
        case keyword_token::NAND:            os << "NAND";          break;
        case keyword_token::NEW:             os << "NEW";           break;
        case keyword_token::NEXT:            os << "NEXT";          break;
        case keyword_token::NOR:             os << "NOR";           break;
        case keyword_token::NOT:             os << "NOT";           break;
        case keyword_token::NULL_:           os << "NULL";          break;
        case keyword_token::OF:              os << "OF";            break;
        case keyword_token::ON:              os << "ON";            break;
        case keyword_token::OPEN:            os << "OPEN";          break;
        case keyword_token::OR:              os << "OR";            break;
        case keyword_token::OTHERS:          os << "OTHERS";        break;
        case keyword_token::OUT:             os << "OUT";           break;
        case keyword_token::PACKAGE:         os << "PACKAGE";       break;
        case keyword_token::PORT:            os << "PORT";          break;
        case keyword_token::POSTPONED:       os << "POSTPONED";     break;
        case keyword_token::PROCEDURE:       os << "PROCEDURE";     break;
        case keyword_token::PROCESS:         os << "PROCESS";       break;
        case keyword_token::PURE:            os << "PURE";          break;
        case keyword_token::RANGE:           os << "RANGE";         break;
        case keyword_token::RECORD:          os << "RECORD";        break;
        case keyword_token::REGISTER:        os << "REGISTER";      break;
        case keyword_token::REJECT:          os << "REJECT";        break;
        case keyword_token::REM:             os << "REM";           break;
        case keyword_token::REPORT:          os << "REPORT";        break;
        case keyword_token::RETURN:          os << "RETURN";        break;
        case keyword_token::ROL:             os << "ROL";           break;
        case keyword_token::ROR:             os << "ROR";           break;
        case keyword_token::SELECT:          os << "SELECT";        break;
        case keyword_token::SEVERITY:        os << "SEVERITY";      break;
        case keyword_token::SIGNAL:          os << "SIGNAL";        break;
        case keyword_token::SHARED:          os << "SHARED";        break;
        case keyword_token::SLA:             os << "SLA";           break;
        case keyword_token::SLL:             os << "SLL";           break;
        case keyword_token::SRA:             os << "SRA";           break;
        case keyword_token::SRL:             os << "SRL";           break;
        case keyword_token::SUBTYPE:         os << "SUBTYPE";       break;
        case keyword_token::THEN:            os << "THEN";          break;
        case keyword_token::TO:              os << "TO";            break;
        case keyword_token::TRANSPORT:       os << "TRANSPORT";     break;
        case keyword_token::TYPE:            os << "TYPE";          break;
        case keyword_token::UNAFFECTED:      os << "UNAFFECTED";    break;
        case keyword_token::UNITS:           os << "UNITS";         break;
        case keyword_token::UNTIL:           os << "UNTIL";         break;
        case keyword_token::USE:             os << "USE";           break;
        case keyword_token::VARIABLE:        os << "VARIABLE";      break;
        case keyword_token::WAIT:            os << "WAIT";          break;
        case keyword_token::WHEN:            os << "WHEN";          break;
        case keyword_token::WHILE:           os << "WHILE";         break;
        case keyword_token::WITH:            os << "WITH";          break;
        case keyword_token::XNOR:            os << "XNOR";          break;
        case keyword_token::XOR:             os << "XOR";           break;

        case keyword_token::UNSPECIFIED:
            cxx_bug_fatal("keyword_token not specified!");

        default:// unreachable_bug_triggered
            cxx_unreachable_bug_triggered();
    }
    // clang-format on

    return os;
}

}  // namespace ibis::vhdl::ast
