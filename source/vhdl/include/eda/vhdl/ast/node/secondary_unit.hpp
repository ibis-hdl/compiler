#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/architecture_body.hpp>
#include <eda/vhdl/ast/node/package_body.hpp>

namespace eda::vhdl::ast {

struct secondary_unit : variant<ast::nullary, ast::architecture_body, ast::package_body> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
