#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct signature : position_tagged {
    std::vector<ast::name> parameter_type_list;  // type_mark
    optional<ast::name> return_type;             // type_mark
};

}  // namespace eda::vhdl::ast
