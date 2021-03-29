#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/constraint.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct subtype_indication : position_tagged {
    std::vector<ast::name> unspecified_name_list;
    optional<ast::constraint> constraint;
};

}  // namespace eda::vhdl::ast
