#pragma once

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct null_statement : position_tagged {
    optional<ast::label> label;
};

}  // namespace ibis::vhdl::ast
