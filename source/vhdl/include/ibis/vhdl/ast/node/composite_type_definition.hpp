#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/array_type_definition.hpp>
#include <ibis/vhdl/ast/node/record_type_definition.hpp>

namespace ibis::vhdl::ast {

struct composite_type_definition : variant<nullary, array_type_definition, record_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
