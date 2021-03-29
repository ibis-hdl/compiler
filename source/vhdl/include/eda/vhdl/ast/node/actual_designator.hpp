#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>

namespace eda::vhdl::ast {

// actual_designator ::=                                             [§ 4.3.2.2]
//       expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open

struct actual_designator
    : variant<nullary,
              expression,         // also for {signal,variable,file}_name
              ast::keyword_token  // OPEN
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
