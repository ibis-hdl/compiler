#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct entity_aspect_entity : position_tagged {
    ast::name name;
    optional<ast::identifier> architecture_identifier;
};

struct entity_aspect_configuration : position_tagged {
    ast::name name;
};

struct entity_aspect
    : variant<ast::nullary, ast::entity_aspect_entity, ast::entity_aspect_configuration,
              ast::keyword_token  // OPEN
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
