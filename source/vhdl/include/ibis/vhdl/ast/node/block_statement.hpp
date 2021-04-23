#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/block_header.hpp>
#include <ibis/vhdl/ast/node/block_declarative_part.hpp>
#include <ibis/vhdl/ast/node/block_statement_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct block_statement : position_tagged {
    ast::label label;
    optional<ast::expression> guard_expression;
    ast::block_header header;
    ast::block_declarative_part declarative_part;
    ast::block_statement_part statement_part;
    optional<ast::label> end_label;
};

}  // namespace ibis::vhdl::ast
