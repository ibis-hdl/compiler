#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/type_definition.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct type_declaration : position_tagged {
    ast::identifier identifier;
    optional<ast::type_definition> type_definition;
};

}  // namespace eda::vhdl::ast
