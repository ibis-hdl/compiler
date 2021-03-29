#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/indexed_name.hpp>
#include <eda/vhdl/ast/node/operator_symbol.hpp>
#include <eda/vhdl/ast/node/selected_name.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>

namespace eda::vhdl::ast {

// name ::=
//      simple_name
//    | operator_symbol
//    | selected_name
//    | indexed_name
//    | slice_name
//    | attribute_name
struct name
    : variant<nullary, simple_name, operator_symbol, selected_name
              // indexed_name
              // slice_name
              // attribute_name,
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
