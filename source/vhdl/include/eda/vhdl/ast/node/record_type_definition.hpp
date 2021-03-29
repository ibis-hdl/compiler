#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/element_declaration.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct record_type_definition : position_tagged {
    std::vector<ast::element_declaration> element_declarations;
    optional<ast::simple_name> name;
};

}  // namespace eda::vhdl::ast
