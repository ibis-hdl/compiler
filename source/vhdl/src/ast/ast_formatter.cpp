//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/ast_formatter.hpp>
#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <string_view>
#include <utility>
#include <format>  // formatter (Clang-Tidy)

///
/// formatter for ast::operator_token
///
std::string_view std::formatter<ibis::vhdl::ast::operator_token>::as_sv(
    ibis::vhdl::ast::operator_token token)
{
    using namespace std::literals::string_view_literals;

    // ToDo [LINT] Clang-Tidy 19.1.7 has problems with C++20 Using Enum??
    // NOLINT_BEGIN(misc-include-cleaner)
    // clang-format off
    switch (token) {
        using enum ibis::vhdl::ast::operator_token;
        // miscellaneous_operator
        case EXPONENT:        return "EXPONENT"sv;
        case ABS:             return "ABS"sv;
        case NOT:             return "NOT"sv;
        // multiplying_operator
        case MUL:             return "MUL"sv;
        case DIV:             return "DIV"sv;
        case MOD:             return "MOD"sv;
        case REM:             return "REM"sv;
        // sign_operator
        case SIGN_POS:        return "SIGN_POS"sv;
        case SIGN_NEG:        return "SIGN_NEG"sv;
        // adding_operator
        case ADD:             return "ADD"sv;
        case SUB:             return "SUB"sv;
        case CONCAT:          return "CONCAT"sv;
        // shift_operator
        case SLL:             return "SLL"sv;
        case SRL:             return "SRL"sv;
        case SLA:             return "SLA"sv;
        case SRA:             return "SRA"sv;
        case ROL:             return "ROL"sv;
        case ROR:             return "ROR"sv;
        // relational_operator
        case EQUAL:           return "EQUAL"sv;
        case NOT_EQUALS:      return "NOT_EQUALS"sv;
        case LESS:            return "LESS"sv;
        case LESS_EQUALS:     return "LESS_EQUALS"sv;
        case GREATER:         return "GREATER"sv;
        case GREATER_EQUALS:  return "GREATER_EQUALS"sv;
        // logical_operator
        case AND:             return "AND"sv;
        case OR:              return "OR"sv;
        case NAND:            return "NAND"sv;
        case NOR:             return "NOR"sv;
        case XOR:             return "XOR"sv;
        case XNOR:            return "XNOR"sv;
        // probably an unintentionally constructed enum by default
        [[unlikely]] case UNSPECIFIED:
            // something in the grammar is wired, stop here
            cxx_bug_fatal("operator_token is *unspecified*!");
        //
        // *No* default branch: let the compiler generate warning about enumeration 
        // value not handled in switch
        //
    }
    // clang-format on
    // NOLINT_END(misc-include-cleaner)
    std::unreachable();
}

///
/// formatter for ast::keyword_token
///
// see https://coliru.stacked-crooked.com/a/3c5b89a0815a7615
std::string_view std::formatter<ibis::vhdl::ast::keyword_token>::as_sv(
    ibis::vhdl::ast::keyword_token token)
{
    using namespace std::literals::string_view_literals;

    // ToDo [LINT] Clang-Tidy 19.1.7 has problems with C++20 Using Enum??
    // NOLINT_BEGIN(misc-include-cleaner)
    // clang-format off
    switch (token) {
        using enum ibis::vhdl::ast::keyword_token;
        case ABS:             return "ABS"sv;
        case ACCESS:          return "ACCESS"sv;
        case AFTER:           return "AFTER"sv;
        case ALIAS:           return "ALIAS"sv;
        case ALL:             return "ALL"sv;
        case AND:             return "AND"sv;
        case ARCHITECTURE:    return "ARCHITECTURE"sv;
        case ARRAY:           return "ARRAY"sv;
        case ASSERT:          return "ASSERT"sv;
        case ATTRIBUTE:       return "ATTRIBUTE"sv;
        case BEGIN:           return "BEGIN"sv;
        case BLOCK:           return "BLOCK"sv;
        case BODY:            return "BODY"sv;
        case BUFFER:          return "BUFFER"sv;
        case BUS:             return "BUS"sv;
        case CASE:            return "CASE"sv;
        case COMPONENT:       return "COMPONENT"sv;
        case CONFIGURATION:   return "CONFIGURATION"sv;
        case CONSTANT:        return "CONSTANT"sv;
        case DISCONNECT:      return "DISCONNECT"sv;
        case DOWNTO:          return "DOWNTO"sv;
        case ELSE:            return "ELSE"sv;
        case ELSIF:           return "ELSIF"sv;
        case END:             return "END"sv;
        case ENTITY:          return "ENTITY"sv;
        case EXIT:            return "EXIT"sv;
        case FILE:            return "FILE"sv;
        case FOR:             return "FOR"sv;
        case FUNCTION:        return "FUNCTION"sv;
        case GENERATE:        return "GENERATE"sv;
        case GENERIC:         return "GENERIC"sv;
        case GROUP:           return "GROUP"sv;
        case GUARDED:         return "GUARDED"sv;
        case IF:              return "IF"sv;
        case IMPURE:          return "IMPURE"sv;
        case IN:              return "IN"sv;
        case INERTIAL:        return "INERTIAL"sv;
        case INOUT:           return "INOUT"sv;
        case IS:              return "IS"sv;
        case LABEL:           return "LABEL"sv;
        case LIBRARY:         return "LIBRARY"sv;
        case LINKAGE:         return "LINKAGE"sv;
        case LITERAL:         return "LITERAL"sv;
        case LOOP:            return "LOOP"sv;
        case MAP:             return "MAP"sv;
        case MOD:             return "MOD"sv;
        case NAND:            return "NAND"sv;
        case NEW:             return "NEW"sv;
        case NEXT:            return "NEXT"sv;
        case NOR:             return "NOR"sv;
        case NOT:             return "NOT"sv;
        case NULL_:           return "NULL"sv;
        case OF:              return "OF"sv;
        case ON:              return "ON"sv;
        case OPEN:            return "OPEN"sv;
        case OR:              return "OR"sv;
        case OTHERS:          return "OTHERS"sv;
        case OUT:             return "OUT"sv;
        case PACKAGE:         return "PACKAGE"sv;
        case PORT:            return "PORT"sv;
        case POSTPONED:       return "POSTPONED"sv;
        case PROCEDURE:       return "PROCEDURE"sv;
        case PROCESS:         return "PROCESS"sv;
        case PURE:            return "PURE"sv;
        case RANGE:           return "RANGE"sv;
        case RECORD:          return "RECORD"sv;
        case REGISTER:        return "REGISTER"sv;
        case REJECT:          return "REJECT"sv;
        case REM:             return "REM"sv;
        case REPORT:          return "REPORT"sv;
        case RETURN:          return "RETURN"sv;
        case ROL:             return "ROL"sv;
        case ROR:             return "ROR"sv;
        case SELECT:          return "SELECT"sv;
        case SEVERITY:        return "SEVERITY"sv;
        case SIGNAL:          return "SIGNAL"sv;
        case SHARED:          return "SHARED"sv;
        case SLA:             return "SLA"sv;
        case SLL:             return "SLL"sv;
        case SRA:             return "SRA"sv;
        case SRL:             return "SRL"sv;
        case SUBTYPE:         return "SUBTYPE"sv;
        case THEN:            return "THEN"sv;
        case TO:              return "TO"sv;
        case TRANSPORT:       return "TRANSPORT"sv;
        case TYPE:            return "TYPE"sv;
        case UNAFFECTED:      return "UNAFFECTED"sv;
        case UNITS:           return "UNITS"sv;
        case UNTIL:           return "UNTIL"sv;
        case USE:             return "USE"sv;
        case VARIABLE:        return "VARIABLE"sv;
        case WAIT:            return "WAIT"sv;
        case WHEN:            return "WHEN"sv;
        case WHILE:           return "WHILE"sv;
        case WITH:            return "WITH"sv;
        case XNOR:            return "XNOR"sv;
        case XOR:             return "XOR"sv;
        // probably an unintentionally constructed enum by default
        [[unlikely]] case UNSPECIFIED:
            // something in the grammar is wired, stop here
            cxx_bug_fatal("keyword_token is *unspecified*!");
        //
        // *No* default branch: let the compiler generate warning about enumeration 
        // value not handled in switch
        //
    }
    // clang-format on
    // NOLINT_END(misc-include-cleaner)

    std::unreachable();
}
