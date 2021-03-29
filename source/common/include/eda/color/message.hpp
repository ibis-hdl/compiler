#pragma once

#include <eda/color/detail/color.hpp>

#include <eda/color/decorator.hpp>
#include <eda/color/facet.hpp>

namespace eda::color::message {

typedef struct {  // VHDL severities
    struct note;
    struct warning;
    struct error;
    struct failure;
} severity;

using note = message_decorator<severity::note>;
using warning = message_decorator<severity::warning>;
using error = message_decorator<severity::error>;
using failure = message_decorator<severity::failure>;

using note_facet = message_facet<severity::note>;
using warning_facet = message_facet<severity::warning>;
using error_facet = message_facet<severity::error>;
using failure_facet = message_facet<severity::failure>;

}  // namespace eda::color::message
