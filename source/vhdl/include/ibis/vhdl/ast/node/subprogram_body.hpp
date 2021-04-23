#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/subprogram_specification.hpp>
#include <ibis/vhdl/ast/node/subprogram_declarative_part.hpp>
#include <ibis/vhdl/ast/node/subprogram_statement_part.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/designator.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct subprogram_body : position_tagged {
    ast::subprogram_specification specification;
    ast::subprogram_declarative_part declarative_part;
    ast::subprogram_statement_part statement_part;
    optional<ast::keyword_token> kind;
    optional<ast::designator> designator;
};

}  // namespace ibis::vhdl::ast
