#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/selected_name.hpp>
#include <vector>

namespace eda::vhdl::ast {

//
// The simple copy & paste of VHDL's BNF doesn't work here. The 93'er LRM
// introduces for the selected_name a context aware form of an expanded name
// which covers the use_clause (e.g. no function_call at prefix of selected_name).
//
//   use_clause ::=                                                     [§ 10.4]
//     use selected_name { , selected_name } ;
//
// with
//
//   selected_name ::=  prefix . suffix                                  [§ 6.3]
//
// and
//
//   prefix ::= name | function_call                                     [§ 6.1]
//   suffix ::= simple_name                                              [§ 6.3]
//            | character_literal
//            | operator_symbol
//            | all
//
// Further, use_clause optionally can have a library clause, but there is only
// a single dot, which doesn't cover e.g. 'use ieee.std_logic_1164.all;'
// respectively 'library_name.package_name.item' can't parsed that way.
// Hence an own, specific ast node is used.
//
struct use_clause : position_tagged {
    struct selected_name : position_tagged {
        std::vector<ast::name> prefix_list;
        ast::suffix suffix;
    };

    std::vector<selected_name> list;
};

}  // namespace eda::vhdl::ast
