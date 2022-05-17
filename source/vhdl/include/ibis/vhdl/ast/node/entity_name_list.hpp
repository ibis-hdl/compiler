#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/entity_designator.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct entity_designator_list : std::vector<ast::entity_designator> {};

struct entity_name_list
    : variant<nullary, entity_designator_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
