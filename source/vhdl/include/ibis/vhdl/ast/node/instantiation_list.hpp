#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/label.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using instantiation_label_list = std::vector<ast::label>;

struct instantiation_list
    : variant<nullary, instantiation_label_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
