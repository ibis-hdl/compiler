/*
 * keyword_token.cpp
 *
 *  Created on: 07.04.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/keyword_token.hpp>

#include <iostream>


#if defined(NULL)
#undef NULL
#endif


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, keyword_token kw_token)
{
    switch(kw_token) {
        case keyword_token::ABS:         os << "abs"; break;
        case keyword_token::ACCESS:      os << "access"; break;
        case keyword_token::AFTER:       os << "after"; break;
        case keyword_token::ALIAS:       os << "alias"; break;
        case keyword_token::ALL:         os << "all"; break;
        case keyword_token::AND:         os << "and"; break;
        case keyword_token::ARCHITECTURE: os << "architecture"; break;
        case keyword_token::ARRAY:       os << "array"; break;
        case keyword_token::ASSERT:      os << "assert"; break;
        case keyword_token::ATTRIBUTE:   os << "attribute"; break;
        case keyword_token::BEGIN:       os << "begin"; break;
        case keyword_token::BLOCK:       os << "block"; break;
        case keyword_token::BODY:        os << "body"; break;
        case keyword_token::BUFFER:      os << "buffer"; break;
        case keyword_token::BUS:         os << "bus"; break;
        case keyword_token::CASE:        os << "case"; break;
        case keyword_token::COMPONENT:   os << "component"; break;
        case keyword_token::CONFIGURATION: os << "configuration"; break;
        case keyword_token::CONSTANT:    os << "constant"; break;
        case keyword_token::DISCONNECT:  os << "disconnect"; break;
        case keyword_token::DOWNTO:      os << "downto"; break;
        case keyword_token::ELSE:        os << "else"; break;
        case keyword_token::ELSIF:       os << "elsif"; break;
        case keyword_token::END:         os << "end"; break;
        case keyword_token::ENTITY:      os << "entity"; break;
        case keyword_token::EXIT:        os << "exit"; break;
        case keyword_token::FILE:        os << "file"; break;
        case keyword_token::FOR:         os << "for"; break;
        case keyword_token::FUNCTION:    os << "function"; break;
        case keyword_token::GENERATE:    os << "generate"; break;
        case keyword_token::GENERIC:     os << "generic"; break;
        case keyword_token::GROUP:       os << "group"; break;
        case keyword_token::GUARDED:     os << "guarded"; break;
        case keyword_token::IF:          os << "if"; break;
        case keyword_token::IMPURE:      os << "impure"; break;
        case keyword_token::IN:          os << "in"; break;
        case keyword_token::INERTIAL:    os << "inertial"; break;
        case keyword_token::INOUT:       os << "inout"; break;
        case keyword_token::IS:          os << "is"; break;
        case keyword_token::LABEL:       os << "label"; break;
        case keyword_token::LIBRARY:     os << "library"; break;
        case keyword_token::LINKAGE:     os << "linkage"; break;
        case keyword_token::LITERAL:     os << "literal"; break;
        case keyword_token::LOOP:        os << "loop"; break;
        case keyword_token::MAP:         os << "map"; break;
        case keyword_token::MOD:         os << "mod"; break;
        case keyword_token::NAND:        os << "nand"; break;
        case keyword_token::NEW:         os << "new"; break;
        case keyword_token::NEXT:        os << "next"; break;
        case keyword_token::NOR:         os << "nor"; break;
        case keyword_token::NOT:         os << "not"; break;
        case keyword_token::NULL:        os << "null"; break;
        case keyword_token::OF:          os << "of"; break;
        case keyword_token::ON:          os << "on"; break;
        case keyword_token::OPEN:        os << "open"; break;
        case keyword_token::OR:          os << "or"; break;
        case keyword_token::OTHERS:      os << "others"; break;
        case keyword_token::OUT:         os << "out"; break;
        case keyword_token::PACKAGE:     os << "package"; break;
        case keyword_token::PORT:        os << "port"; break;
        case keyword_token::POSTPONED:   os << "postponed"; break;
        case keyword_token::PROCEDURE:   os << "procedure"; break;
        case keyword_token::PROCESS:     os << "process"; break;
        case keyword_token::PURE:        os << "pure"; break;
        case keyword_token::RANGE:       os << "range"; break;
        case keyword_token::RECORD:      os << "record"; break;
        case keyword_token::REGISTER:    os << "register"; break;
        case keyword_token::REJECT:      os << "reject"; break;
        case keyword_token::REM:         os << "rem"; break;
        case keyword_token::REPORT:      os << "report"; break;
        case keyword_token::RETURN:      os << "return"; break;
        case keyword_token::ROL:         os << "rol"; break;
        case keyword_token::ROR:         os << "ror"; break;
        case keyword_token::SELECT:      os << "select"; break;
        case keyword_token::SEVERITY:    os << "severity"; break;
        case keyword_token::SIGNAL:      os << "signal"; break;
        case keyword_token::SHARED:      os << "shared"; break;
        case keyword_token::SLA:         os << "sla"; break;
        case keyword_token::SLL:         os << "sll"; break;
        case keyword_token::SRA:         os << "sra"; break;
        case keyword_token::SRL:         os << "srl"; break;
        case keyword_token::SUBTYPE:     os << "subtype"; break;
        case keyword_token::THEN:        os << "then"; break;
        case keyword_token::TO:          os << "to"; break;
        case keyword_token::TRANSPORT:   os << "transport"; break;
        case keyword_token::TYPE:        os << "type"; break;
        case keyword_token::UNAFFECTED:  os << "unaffected"; break;
        case keyword_token::UNITS:       os << "units"; break;
        case keyword_token::UNTIL:       os << "until"; break;
        case keyword_token::USE:         os << "use"; break;
        case keyword_token::VARIABLE:    os << "variable"; break;
        case keyword_token::WAIT:        os << "wait"; break;
        case keyword_token::WHEN:        os << "when"; break;
        case keyword_token::WHILE:       os << "while"; break;
        case keyword_token::WITH:        os << "with"; break;
        case keyword_token::XNOR:        os << "xnor"; break;
        case keyword_token::XOR:         os << "xor"; break;

        default:                         os << "INVALID";
    }

    return os;
}

} } } // namespace eda.vhdl93.ast
