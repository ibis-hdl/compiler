#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/variant.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

using waveform_element_form = variant<ast::expression,
                                      ast::keyword_token  // NULL
                                      >;

struct waveform_element : position_tagged {
    waveform_element_form form;
    optional<ast::expression> time_expression;
};

}  // namespace eda::vhdl::ast
