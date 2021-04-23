#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

using waveform_element_form = variant<ast::expression,
                                      ast::keyword_token  // NULL
                                      >;

struct waveform_element : position_tagged {
    waveform_element_form form;
    optional<ast::expression> time_expression;
};

}  // namespace ibis::vhdl::ast
