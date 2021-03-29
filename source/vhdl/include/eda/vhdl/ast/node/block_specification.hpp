#pragma once

#include <eda/vhdl/ast/util/variant.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/index_specification.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct block_specification_chunk : position_tagged {
    ast::label label;  // {block, generate}_statement_label
    optional<ast::index_specification> index_specification;
};

struct block_specification
    : variant<ast::nullary,
              ast::name,  // architecture_name
              ast::block_specification_chunk> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
