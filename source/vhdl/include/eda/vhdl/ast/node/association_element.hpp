#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/actual_part.hpp>
#include <eda/vhdl/ast/node/formal_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct association_element : position_tagged {
    optional<ast::formal_part> formal_part;
    ast::actual_part actual_part;
};

}  // namespace eda::vhdl::ast
