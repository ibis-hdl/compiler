#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/file_logical_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct file_open_information : position_tagged {
    optional<ast::expression> file_open_kind_expression;
    ast::file_logical_name file_logical_name;  // type: string_expression
};

}  // namespace eda::vhdl::ast
