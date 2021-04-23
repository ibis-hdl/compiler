#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct signature : position_tagged {
    std::vector<ast::name> parameter_type_list;  // type_mark
    optional<ast::name> return_type;             // type_mark
};

}  // namespace ibis::vhdl::ast
