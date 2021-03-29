#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>

#include <boost/range/iterator_range.hpp>

namespace eda::vhdl::ast {

struct subtype_declaration : position_tagged {
    ast::identifier identifier;
    ast::subtype_indication subtype_indication;
};

}  // namespace eda::vhdl::ast
