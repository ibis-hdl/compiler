#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/prefix.hpp>
#include <eda/vhdl/ast/node/signature.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct attribute_name : position_tagged {
    ast::prefix prefix;
    optional<ast::signature> signature;
    ast::simple_name attribute_designator;
    optional<ast::expression> expression;
};

}  // namespace eda::vhdl::ast
