#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/entity_tag.hpp>
#include <eda/vhdl/ast/node/signature.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct entity_designator : position_tagged {
    ast::entity_tag entity_tag;
    optional<ast::signature> signature;
};

}  // namespace eda::vhdl::ast
