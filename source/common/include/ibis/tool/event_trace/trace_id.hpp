#pragma once

#include <ibis/tool/event_trace/trace_event.hpp>

#include <type_traits>

#include <atomic>
#include <random>

namespace ibis::tool::event_trace {

///
/// @brief TraceID encapsulates an ID that can either be an integer or pointer. Pointers  are
/// mangled with the Process ID so that they are unlikely to collide when the same pointer is used
/// on different processes.
///
/// Concept: @see [Coliru](https://coliru.stacked-crooked.com/a/8ffbcf33de92f088)
///
class TraceID {
public:
    using value_type = std::uint64_t;

public:
    static constexpr value_type NONE = 0;

public:
    template <typename T, typename = typename std::enable_if_t<std::is_integral_v<std::decay_t<T>>>>
    explicit TraceID(T id_, [[maybe_unused]] TraceEvent::flag& flags)
        : id(static_cast<value_type>(id_))
    {
    }

    explicit TraceID(void const* ptr, TraceEvent::flag& id_flags)
        : id(static_cast<value_type>(reinterpret_cast<std::uintptr_t>(ptr)))
    {
        id_flags |= TraceEvent::flag::MANGLE_ID;
    }

    template <typename T,
              typename = typename std::enable_if_t<!std::is_integral_v<T> && !std::is_array_v<T>>>
    explicit TraceID([[maybe_unused]] const T& id_, [[maybe_unused]] TraceEvent::flag& flags)
    {
        static_assert(std::is_integral_v<T>, "T is no integral type");
    }

    value_type value() const { return id; }

    /// construct an ID only for json_ostream, to allow overloading
    static TraceID as_TraceID(value_type id_) { return TraceID(id_); }

    ///
    /// @brief Generate a per process random number biased counter value.
    ///
    /// @return TraceID::value_type an globally-unique id which can be used as a flow id or async
    /// event id.
    ///
    /// Use this to get an unique ID instead of implementing an own counter and hashing it with a
    /// random value. Nevertheless, consider using TRACE_ID_LOCAL(this) to avoid storing
    /// additional data if possible.
    ///
    /// @see Concept at [Coliru](https://coliru.stacked-crooked.com/a/e65efef70e346670)
    static TraceID::value_type next_global()
    {
        static const uint64_t random = []() {
            static std::mt19937_64 gen64;
            return gen64();
        }();
        static std::atomic<std::uint_fast64_t> counter;
        return random ^ counter++;
    }

private:
    explicit TraceID(value_type id_)
        : id(id_)
    {
    }

private:
    value_type const id;
};

}  // namespace ibis::tool::event_trace
