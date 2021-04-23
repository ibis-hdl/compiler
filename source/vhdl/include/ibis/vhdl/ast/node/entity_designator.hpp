#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/entity_tag.hpp>
#include <ibis/vhdl/ast/node/signature.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct entity_designator : position_tagged {
    ast::entity_tag entity_tag;
    optional<ast::signature> signature;
};

}  // namespace ibis::vhdl::ast
