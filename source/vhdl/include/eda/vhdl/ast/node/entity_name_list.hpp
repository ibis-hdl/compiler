#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/entity_designator.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct entity_designator_list : std::vector<ast::entity_designator> {
};

struct entity_name_list
    : variant<nullary, entity_designator_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
