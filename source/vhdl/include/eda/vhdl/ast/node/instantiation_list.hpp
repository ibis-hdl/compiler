#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <vector>

namespace eda::vhdl::ast {

using instantiation_label_list = std::vector<ast::label>;

struct instantiation_list
    : variant<nullary, instantiation_label_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
