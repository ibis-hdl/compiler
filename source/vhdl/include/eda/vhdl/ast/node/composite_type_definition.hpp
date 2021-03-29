#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/array_type_definition.hpp>
#include <eda/vhdl/ast/node/record_type_definition.hpp>

namespace eda::vhdl::ast {

struct composite_type_definition : variant<nullary, array_type_definition, record_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
