#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/waveform_element.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct waveform_element_list : std::vector<waveform_element> {};

struct waveform
    : variant<waveform_element_list,
              ast::keyword_token  // UNAFFECTED
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
