#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/assertion.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct assertion_statement : position_tagged {
    optional<ast::label> label;
    ast::assertion assertion;
};

}  // namespace eda::vhdl::ast
