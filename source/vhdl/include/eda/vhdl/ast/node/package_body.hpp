#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/package_body_declarative_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct package_body : position_tagged {
    ast::identifier identifier;
    ast::package_body_declarative_part declarative_part;
    optional<ast::identifier> end_identifier;
};

}  // namespace eda::vhdl::ast
