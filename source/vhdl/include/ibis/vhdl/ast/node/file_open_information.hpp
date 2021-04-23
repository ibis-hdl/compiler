#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/file_logical_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct file_open_information : position_tagged {
    optional<ast::expression> file_open_kind_expression;
    ast::file_logical_name file_logical_name;  // type: string_expression
};

}  // namespace ibis::vhdl::ast
