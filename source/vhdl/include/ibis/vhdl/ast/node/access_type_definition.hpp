#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/subtype_indication.hpp>

namespace ibis::vhdl::ast {

struct access_type_definition : position_tagged {
    ast::subtype_indication subtype_indication;
};

}  // namespace ibis::vhdl::ast