#pragma once

#include <ibis/tool/event_trace/detail/trace_value.hpp>
#include <ibis/tool/event_trace/detail/clock.hpp>
#include <ibis/tool/event_trace/detail/platform.hpp>

#include <string_view>
#include <vector>
#include <memory>
#include <type_traits>

#include <atomic>
#include <random>

namespace ibis::tool::event_trace {

class json_ostream;

///
/// The trace event to be stored.
///
class TraceEvent {
public:
    /// Phase indicates the nature of an event entry. E.g. part of a begin/end pair.
    enum phase : char {
        UNSPECIFIED = '?',
        BEGIN = 'B',        ///< Duration event begin.
        END = 'E',          ///< Duration event end.
        COMPLETE = 'X',     ///< Complete events with duration.
        INSTANT = 'I',      ///< Instant event.
        ASYNC_BEGIN = 'S',  ///< start (deprecated)
        ASYNC_STEP = 'T',   ///< step (deprecated)
        ASYNC_END = 'F',    ///< finish (deprecated)
        METADATA = 'M',     ///< Metadata event.
        COUNTER = 'C'       ///< Counter event.
    };

    /// Flags used for several purposes.
    enum flag : uint8_t {
        NONE = 0,
        HAS_ID = 1 << 0,
        MANGLE_ID = 1 << 1,
    };

public:
    using storage_ptr = std::unique_ptr<char[]>;

public:
    TraceEvent();

    TraceEvent(current_thread::id_type thread_id, clock::time_point_type timestamp,
               TraceEvent::phase phase,                                      // --
               std::string_view category_name, std::string_view event_name,  // --
               std::uint64_t trace_id, TraceEvent::flag flags,               // --
               std::string_view arg1_name, TraceValue arg1_value,            // --
               storage_ptr ptr);

    TraceEvent(TraceEvent const&) = delete;
    TraceEvent& operator=(TraceEvent const&) = delete;

    TraceEvent(TraceEvent&&) = default;
    TraceEvent& operator=(TraceEvent&&) = default;

    ~TraceEvent() = default;

public:
    // Serialize event data to JSON
    void AppendAsJSON(std::string& out) const;

public:
    clock::time_point_type timestamp() const { return timestamp_; }

    std::string_view name() const { return event_name_; }

private:
    // Note: these are ordered by size (largest first) for optimal aligned storage.
    using string_type = char const*;

    string_type category_name_;  // 8 bytes
    string_type event_name_;     // 8 bytes

    string_type arg1_name_;  // 8 bytes
    TraceValue arg1_value_;

    current_thread::id_type thread_id_ = current_thread::INVALID_ID;  // 8 bytes
    clock::time_point_type timestamp_ = clock::time_point_zero;       // 8 bytes
    std::uint64_t trace_id_ = 0;                                      // 8 bytes

    storage_ptr copy_storage = nullptr;  // 8 bytes

    TraceEvent::phase phase_ = TraceEvent::phase::UNSPECIFIED;  // 1 byte
    TraceEvent::flag flags = TraceEvent::flag::NONE;            // 1 byte
};

inline TraceEvent::flag operator|(TraceEvent::flag X, TraceEvent::flag Y)
{
    // [How to use enums as flags in C++?](
    //  https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c)
    return static_cast<TraceEvent::flag>(  // --
        static_cast<unsigned int>(X) | static_cast<unsigned int>(Y));
}

inline TraceEvent::flag& operator|=(TraceEvent::flag& X, TraceEvent::flag Y)
{
    X = X | Y;
    return X;
}

}  // namespace ibis::tool::event_trace
