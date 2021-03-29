#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/aggregate.hpp>
#include <eda/vhdl/ast/node/name.hpp>

namespace eda::vhdl::ast {

struct target : variant<nullary, name, aggregate> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
