//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/parser/error_handler.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <unordered_map>

namespace ibis::vhdl::parser {

using namespace std::string_view_literals;

std::string_view error_handler::lookup(std::string_view which)
{
    using map_type = std::unordered_map<std::string_view, std::string_view>;

    static const map_type map{
        // keywords
        { "abs"sv, "keyword 'abs'"sv },
        { "access"sv, "keyword 'access'"sv },
        { "after"sv, "keyword 'after'"sv },
        { "alias"sv, "keyword 'alias'"sv },
        { "all"sv, "keyword 'all'"sv },
        { "and"sv, "keyword 'and'"sv },
        { "architecture"sv, "keyword 'architecture'"sv },
        { "array"sv, "keyword 'array'"sv },
        { "assert"sv, "keyword 'assert'"sv },
        { "attribute"sv, "keyword 'attribute'"sv },
        { "begin"sv, "keyword 'begin'"sv },
        { "block"sv, "keyword 'block'"sv },
        { "body"sv, "keyword 'body'"sv },
        { "buffer"sv, "keyword 'buffer'"sv },
        { "bus"sv, "keyword 'bus'"sv },
        { "case"sv, "keyword 'case'"sv },
        { "component"sv, "keyword 'component'"sv },
        { "configuration"sv, "keyword 'configuration'"sv },
        { "constant"sv, "keyword 'constant'"sv },
        { "disconnect"sv, "keyword 'disconnect'"sv },
        { "downto"sv, "keyword 'downto'"sv },
        { "else"sv, "keyword 'else'"sv },
        { "elsif"sv, "keyword 'elsif'"sv },
        { "end"sv, "keyword 'end'"sv },
        { "entity"sv, "keyword 'entity'"sv },
        { "exit"sv, "keyword 'exit'"sv },
        { "file"sv, "keyword 'file'"sv },
        { "for"sv, "keyword 'for'"sv },
        { "function"sv, "keyword 'function'"sv },
        { "generate"sv, "keyword 'generate'"sv },
        { "generic"sv, "keyword 'generic'"sv },
        { "group"sv, "keyword 'group'"sv },
        { "guarded"sv, "keyword 'guarded'"sv },
        { "if"sv, "keyword 'if'"sv },
        { "impure"sv, "keyword 'impure'"sv },
        { "in"sv, "keyword 'in'"sv },
        { "inertial"sv, "keyword 'inertial'"sv },
        { "inout"sv, "keyword 'inout'"sv },
        { "is"sv, "keyword 'is'"sv },
        { "label"sv, "keyword 'label'"sv },
        { "library"sv, "keyword 'library'"sv },
        { "linkage"sv, "keyword 'linkage'"sv },
        { "literal"sv, "keyword 'literal'"sv },
        { "loop"sv, "keyword 'loop'"sv },
        { "map"sv, "keyword 'map'"sv },
        { "mod"sv, "keyword 'mod'"sv },
        { "nand"sv, "keyword 'nand'"sv },
        { "new"sv, "keyword 'new'"sv },
        { "next"sv, "keyword 'next'"sv },
        { "nor"sv, "keyword 'nor'"sv },
        { "not"sv, "keyword 'not'"sv },
        { "null"sv, "keyword 'null'"sv },
        { "of"sv, "keyword 'of'"sv },
        { "on"sv, "keyword 'on'"sv },
        { "open"sv, "keyword 'open'"sv },
        { "or"sv, "keyword 'or'"sv },
        { "others"sv, "keyword 'others'"sv },
        { "out"sv, "keyword 'out'"sv },
        { "package"sv, "keyword 'package'"sv },
        { "port"sv, "keyword 'port'"sv },
        { "postponed"sv, "keyword 'postponed'"sv },
        { "procedure"sv, "keyword 'procedure'"sv },
        { "process"sv, "keyword 'process'"sv },
        { "pure"sv, "keyword 'pure'"sv },
        { "range"sv, "keyword 'range'"sv },
        { "record"sv, "keyword 'record'"sv },
        { "register"sv, "keyword 'register'"sv },
        { "reject"sv, "keyword 'reject'"sv },
        { "rem"sv, "keyword 'rem'"sv },
        { "report"sv, "keyword 'report'"sv },
        { "return"sv, "keyword 'return'"sv },
        { "rol"sv, "keyword 'rol'"sv },
        { "ror"sv, "keyword 'ror'"sv },
        { "select"sv, "keyword 'select'"sv },
        { "severity"sv, "keyword 'severity'"sv },
        { "signal"sv, "keyword 'signal'"sv },
        { "shared"sv, "keyword 'shared'"sv },
        { "sla"sv, "keyword 'sla'"sv },
        { "sll"sv, "keyword 'sll'"sv },
        { "sra"sv, "keyword 'sra'"sv },
        { "srl"sv, "keyword 'srl'"sv },
        { "subtype"sv, "keyword 'subtype'"sv },
        { "then"sv, "keyword 'then'"sv },
        { "to"sv, "keyword 'to'"sv },
        { "transport"sv, "keyword 'transport'"sv },
        { "type"sv, "keyword 'type'"sv },
        { "unaffected"sv, "keyword 'unaffected'"sv },
        { "units"sv, "keyword 'units'"sv },
        { "until"sv, "keyword 'until'"sv },
        { "use"sv, "keyword 'use'"sv },
        { "variable"sv, "keyword 'variable'"sv },
        { "wait"sv, "keyword 'wait'"sv },
        { "when"sv, "keyword 'when'"sv },
        { "while"sv, "keyword 'while'"sv },
        { "with"sv, "keyword 'with'"sv },
        { "xnor"sv, "keyword 'xnor'"sv },
        { "xor"sv, "keyword 'xor'"sv },

        // Typographical
        { "';'"sv, "semicolon ';'"sv },
        { "':'"sv, "colon ':'"sv },
        { "','"sv, "comma ':'"sv },
        { "'{'"sv, "opening '{' curly brace"sv },
        { "'}'"sv, "closing '}' curly brace"sv },
        { "'['"sv, "opening '[' square bracket"sv },
        { "']'"sv, "closing ']' square bracket"sv },
        { "'('"sv, "opening '(' brace/parentheses"sv },
        { "'('"sv, "closing ')' brace/parentheses"sv },

        // other
        // Fixme: Where are the rules for this?

        { "signal_name"sv, "signal name"sv },

        { "boolean_expression"sv, "boolean expression"sv },
        { "time_expression"sv, "time expression"sv },
        { "value_expression"sv, "value expression"sv },
    };

    auto const iter = map.find(which);

    if (iter != map.end()) {
        return iter->second;
    }

    // FixMe: lookup failed, give a warning to developer
    return which;
}

std::string error_handler::make_error_description(std::string_view which)
{
    using boost::locale::format;
    using boost::locale::translate;

    return (format(translate("expecting '{1}' here:")) % lookup(which)).str();
}

}  // namespace ibis::vhdl::parser
