#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/waveform_element.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct waveform_element_list : std::vector<waveform_element> {
};

struct waveform
    : variant<waveform_element_list,
              ast::keyword_token  // UNAFFECTED
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
