//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

#include <string_view>
#include <format>

///
/// formatter for ast::operator_token
///
std::string_view std::formatter<ibis::vhdl::ast::operator_token>::as_sv(
    ibis::vhdl::ast::operator_token token)
{
    using operator_token = ibis::vhdl::ast::operator_token;
    using namespace std::literals::string_view_literals;

    // clang-format off
    switch (token) {
        // miscellaneous_operator
        case operator_token::EXPONENT:        return "EXPONENT"sv;
        case operator_token::ABS:             return "ABS"sv;
        case operator_token::NOT:             return "NOT"sv;
        // multiplying_operator
        case operator_token::MUL:             return "MUL"sv;
        case operator_token::DIV:             return "DIV"sv;
        case operator_token::MOD:             return "MOD"sv;
        case operator_token::REM:             return "REM"sv;
        // sign_operator
        case operator_token::SIGN_POS:        return "SIGN_POS"sv;
        case operator_token::SIGN_NEG:        return "SIGN_NEG"sv;
        // adding_operator
        case operator_token::ADD:             return "ADD"sv;
        case operator_token::SUB:             return "SUB"sv;
        case operator_token::CONCAT:          return "CONCAT"sv;
        // shift_operator
        case operator_token::SLL:             return "SLL"sv;
        case operator_token::SRL:             return "SRL"sv;
        case operator_token::SLA:             return "SLA"sv;
        case operator_token::SRA:             return "SRA"sv;
        case operator_token::ROL:             return "ROL"sv;
        case operator_token::ROR:             return "ROR"sv;
        // relational_operator
        case operator_token::EQUAL:           return "EQUAL"sv;
        case operator_token::NOT_EQUALS:      return "NOT_EQUALS"sv;
        case operator_token::LESS:            return "LESS"sv;
        case operator_token::LESS_EQUALS:     return "LESS_EQUALS"sv;
        case operator_token::GREATER:         return "GREATER"sv;
        case operator_token::GREATER_EQUALS:  return "GREATER_EQUALS"sv;
        // logical_operator
        case operator_token::AND:             return "AND"sv;
        case operator_token::OR:              return "OR"sv;
        case operator_token::NAND:            return "NAND"sv;
        case operator_token::NOR:             return "NOR"sv;
        case operator_token::XOR:             return "XOR"sv;
        case operator_token::XNOR:            return "XNOR"sv;
        // probably an unintentionally constructed enum by default
        [[unlikely]] case operator_token::UNSPECIFIED:
            // something in the grammar is wired, stop here
            cxx_bug_fatal("operator_token is *unspecified*!");
        //
        // *No* default branch: let the compiler generate warning about enumeration 
        // value not handled in switch
        //
    }
    // clang-format on

    std::unreachable();
}

///
/// formatter for ast::keyword_token
///
// see https://coliru.stacked-crooked.com/a/3c5b89a0815a7615
std::string_view std::formatter<ibis::vhdl::ast::keyword_token>::as_sv(
    ibis::vhdl::ast::keyword_token token)
{
    using keyword_token = ibis::vhdl::ast::keyword_token;
    using namespace std::literals::string_view_literals;

    // clang-format off
    switch (token) {
        case keyword_token::ABS:             return "ABS"sv;
        case keyword_token::ACCESS:          return "ACCESS"sv;
        case keyword_token::AFTER:           return "AFTER"sv;
        case keyword_token::ALIAS:           return "ALIAS"sv;
        case keyword_token::ALL:             return "ALL"sv;
        case keyword_token::AND:             return "AND"sv;
        case keyword_token::ARCHITECTURE:    return "ARCHITECTURE"sv;
        case keyword_token::ARRAY:           return "ARRAY"sv;
        case keyword_token::ASSERT:          return "ASSERT"sv;
        case keyword_token::ATTRIBUTE:       return "ATTRIBUTE"sv;
        case keyword_token::BEGIN:           return "BEGIN"sv;
        case keyword_token::BLOCK:           return "BLOCK"sv;
        case keyword_token::BODY:            return "BODY"sv;
        case keyword_token::BUFFER:          return "BUFFER"sv;
        case keyword_token::BUS:             return "BUS"sv;
        case keyword_token::CASE:            return "CASE"sv;
        case keyword_token::COMPONENT:       return "COMPONENT"sv;
        case keyword_token::CONFIGURATION:   return "CONFIGURATION"sv;
        case keyword_token::CONSTANT:        return "CONSTANT"sv;
        case keyword_token::DISCONNECT:      return "DISCONNECT"sv;
        case keyword_token::DOWNTO:          return "DOWNTO"sv;
        case keyword_token::ELSE:            return "ELSE"sv;
        case keyword_token::ELSIF:           return "ELSIF"sv;
        case keyword_token::END:             return "END"sv;
        case keyword_token::ENTITY:          return "ENTITY"sv;
        case keyword_token::EXIT:            return "EXIT"sv;
        case keyword_token::FILE:            return "FILE"sv;
        case keyword_token::FOR:             return "FOR"sv;
        case keyword_token::FUNCTION:        return "FUNCTION"sv;
        case keyword_token::GENERATE:        return "GENERATE"sv;
        case keyword_token::GENERIC:         return "GENERIC"sv;
        case keyword_token::GROUP:           return "GROUP"sv;
        case keyword_token::GUARDED:         return "GUARDED"sv;
        case keyword_token::IF:              return "IF"sv;
        case keyword_token::IMPURE:          return "IMPURE"sv;
        case keyword_token::IN:              return "IN"sv;
        case keyword_token::INERTIAL:        return "INERTIAL"sv;
        case keyword_token::INOUT:           return "INOUT"sv;
        case keyword_token::IS:              return "IS"sv;
        case keyword_token::LABEL:           return "LABEL"sv;
        case keyword_token::LIBRARY:         return "LIBRARY"sv;
        case keyword_token::LINKAGE:         return "LINKAGE"sv;
        case keyword_token::LITERAL:         return "LITERAL"sv;
        case keyword_token::LOOP:            return "LOOP"sv;
        case keyword_token::MAP:             return "MAP"sv;
        case keyword_token::MOD:             return "MOD"sv;
        case keyword_token::NAND:            return "NAND"sv;
        case keyword_token::NEW:             return "NEW"sv;
        case keyword_token::NEXT:            return "NEXT"sv;
        case keyword_token::NOR:             return "NOR"sv;
        case keyword_token::NOT:             return "NOT"sv;
        case keyword_token::NULL_:           return "NULL"sv;
        case keyword_token::OF:              return "OF"sv;
        case keyword_token::ON:              return "ON"sv;
        case keyword_token::OPEN:            return "OPEN"sv;
        case keyword_token::OR:              return "OR"sv;
        case keyword_token::OTHERS:          return "OTHERS"sv;
        case keyword_token::OUT:             return "OUT"sv;
        case keyword_token::PACKAGE:         return "PACKAGE"sv;
        case keyword_token::PORT:            return "PORT"sv;
        case keyword_token::POSTPONED:       return "POSTPONED"sv;
        case keyword_token::PROCEDURE:       return "PROCEDURE"sv;
        case keyword_token::PROCESS:         return "PROCESS"sv;
        case keyword_token::PURE:            return "PURE"sv;
        case keyword_token::RANGE:           return "RANGE"sv;
        case keyword_token::RECORD:          return "RECORD"sv;
        case keyword_token::REGISTER:        return "REGISTER"sv;
        case keyword_token::REJECT:          return "REJECT"sv;
        case keyword_token::REM:             return "REM"sv;
        case keyword_token::REPORT:          return "REPORT"sv;
        case keyword_token::RETURN:          return "RETURN"sv;
        case keyword_token::ROL:             return "ROL"sv;
        case keyword_token::ROR:             return "ROR"sv;
        case keyword_token::SELECT:          return "SELECT"sv;
        case keyword_token::SEVERITY:        return "SEVERITY"sv;
        case keyword_token::SIGNAL:          return "SIGNAL"sv;
        case keyword_token::SHARED:          return "SHARED"sv;
        case keyword_token::SLA:             return "SLA"sv;
        case keyword_token::SLL:             return "SLL"sv;
        case keyword_token::SRA:             return "SRA"sv;
        case keyword_token::SRL:             return "SRL"sv;
        case keyword_token::SUBTYPE:         return "SUBTYPE"sv;
        case keyword_token::THEN:            return "THEN"sv;
        case keyword_token::TO:              return "TO"sv;
        case keyword_token::TRANSPORT:       return "TRANSPORT"sv;
        case keyword_token::TYPE:            return "TYPE"sv;
        case keyword_token::UNAFFECTED:      return "UNAFFECTED"sv;
        case keyword_token::UNITS:           return "UNITS"sv;
        case keyword_token::UNTIL:           return "UNTIL"sv;
        case keyword_token::USE:             return "USE"sv;
        case keyword_token::VARIABLE:        return "VARIABLE"sv;
        case keyword_token::WAIT:            return "WAIT"sv;
        case keyword_token::WHEN:            return "WHEN"sv;
        case keyword_token::WHILE:           return "WHILE"sv;
        case keyword_token::WITH:            return "WITH"sv;
        case keyword_token::XNOR:            return "XNOR"sv;
        case keyword_token::XOR:             return "XOR"sv;
        // probably an unintentionally constructed enum by default
        [[unlikely]] case keyword_token::UNSPECIFIED:
            // something in the grammar is wired, stop here
            cxx_bug_fatal("keyword_token is *unspecified*!");
        //
        // *No* default branch: let the compiler generate warning about enumeration 
        // value not handled in switch
        //
    }
    // clang-format on

    std::unreachable();
}
