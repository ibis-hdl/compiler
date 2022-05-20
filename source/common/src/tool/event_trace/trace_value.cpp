#include <ibis/tool/event_trace/detail/trace_value.hpp>

#include <ibis/support/cxx/overloaded.hpp>

#include <sstream>
#include <iomanip>
#include <cstdint>
#include <iostream>

namespace ibis::tool::event_trace {

void TraceValue::AppendAsJSON(std::stringstream& ss) const
{
    using ibis::util::overloaded;

    // FixMe: use std::fmt  or fmtlib/fmt

    std::visit(  // --
        overloaded{
            [&ss]([[maybe_unused]] std::monostate v) {
                std::cerr << "\n\n***WARNING***: call of empty TraceValue!\n\n";
                ss << R"("N/A")";
            },
            [&ss](bool v) { ss << (v ? "true" : "false"); },
            [&ss](uint64_t v) { ss << std::to_string(v); },
            [&ss](int64_t v) { ss << std::to_string(v); },
            [&ss](double v) { ss << std::to_string(v); },
            [&ss](std::string_view sv) {
                if (sv.empty()) {
                    ss << "null";
                }
                else {
                    ss << std::quoted(sv);
                }
            },
            [&ss](void const* ptr) {
                // JSON only supports double and int numbers. So output as a hex string.
                if (ptr == nullptr) {
                    ss << "null";
                }
                else {
                    ss << "\"0x" << std::hex << std::setw(8) << std::setfill('0') << ptr << '"';
                }
            },
        },
        value);
}

}  // namespace ibis::tool::event_trace
