#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/constraint.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct subtype_indication : position_tagged {
    std::vector<ast::name> unspecified_name_list;
    optional<ast::constraint> constraint;
};

}  // namespace ibis::vhdl::ast
