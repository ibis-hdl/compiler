#include <ibis/tool/event_trace/detail/json_ostream.hpp>
#include <ibis/tool/event_trace/trace_id.hpp>

#include <ibis/support/cxx/overloaded.hpp>

#include <ibis/util/make_iomanip.hpp>

#include <iomanip>

namespace /* anonymous */ {

auto const hex = [](auto value, int width) {
    return ibis::util::make_iomanip([value, width](std::ostream& os) {
        // FixMe: [c++20] std::format to avoid “Chevron Hell”
        os << std::hex << std::uppercase << std::setw(width) << std::setfill('0')
           << static_cast<std::uint64_t>(value);
    });
};

}

namespace ibis::tool::event_trace {

std::ostream& operator<<(std::ostream& os, const quoted& quoted)
{
    os << '"';

    auto const is_control = [](char chr) { return chr >= 0x00 && chr <= 0x1F; };

    for (auto chr = quoted.str.cbegin(); chr != quoted.str.cend(); chr++) {
        switch (*chr) {
            case '"':
                os << R"(\")";
                break;
            case '\\':
                os << R"(\\)";
                break;
            case '\b':
                os << R"(\b)";
                break;
            case '\f':
                os << R"(\f)";
                break;
            case '\n':
                os << R"(\n)";
                break;
            case '\r':
                os << R"(\r)";
                break;
            case '\t':
                os << R"(\t)";
                break;
            default:
                if (is_control(*chr)) {
                    os << R"(\u)" << hex(*chr, 4);
                }
                else {
                    os << *chr;
                }
        }
    }

    os << '"';

    return os;
}

void json_ostream::visit(TraceValue const& value)
{
    using ibis::util::overloaded;

    // FixMe: use std::fmt  or fmtlib/fmt

    std::visit(  // --
        overloaded{
            [this]([[maybe_unused]] std::monostate v) { os << "null"; },
            [this](bool v) { os << (v ? "true" : "false"); },
            [this](uint64_t v) { os << std::to_string(v); },
            [this](int64_t v) { os << std::to_string(v); },
            [this](double v) {
                // format("%.*g", std::numeric_limits<double>::max_digits10, v)
                os << std::to_string(v);
            },
            [this](std::string_view sv) {
                if (sv.empty()) {
                    os << "null";
                }
                else {
                    os << std::quoted(sv);
                }
            },
            [this](void const* ptr) {
                // JSON only supports double and int numbers. So output as a hex string.
                if (ptr == nullptr) {
                    os << "null";
                }
                else {
                    // if it fails we haven't a 64-bit system any more
                    static_assert(sizeof(std::intptr_t) == sizeof(std::uint64_t),
                                  "expected 64-bit pointer");
                    // FixMe: use std::format or fmtlib::fmt
                    os << "\"0x"
                       << hex(static_cast<std::uint64_t>(reinterpret_cast<std::intptr_t>(ptr)), 8)
                       << '"';
                }
            },
        },
        value.data());
}

void json_ostream::attribute(std::string_view Key, TraceID id)
{
    // print it as hex string (it might be a 64-bit pointer).
    attributeImpl(Key, [&]() { os << "\"0x" << hex(id.value(), 8) << '"'; });
}

}  // namespace ibis::tool::event_trace
