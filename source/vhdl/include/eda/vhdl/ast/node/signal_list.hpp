#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct signal_list_list : std::vector<ast::name> {
};

// signal_list ::=
//           signal_name { , signal_name }
//         | others
//         | all
struct signal_list
    : variant<nullary, signal_list_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
