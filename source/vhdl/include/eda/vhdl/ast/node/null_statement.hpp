#pragma once

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct null_statement : position_tagged {
    optional<ast::label> label;
};

}  // namespace eda::vhdl::ast
