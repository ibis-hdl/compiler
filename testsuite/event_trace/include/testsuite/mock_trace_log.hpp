#pragma once

#include <ibis/tool/event_trace/trace_log.hpp>

namespace testsuite {

///
/// Mock class to test the behaviour of TraceLog's TraceLog:copy() support. Tested are the internal
/// helper class to accumulate the size, allocate memory and the deep copy members.
///
struct TraceLogMock {
    using TraceLog = ibis::tool::event_trace::TraceLog;
    using TraceEvent = ibis::tool::event_trace::TraceEvent;

    template <typename T>
    static std::size_t accumulate_size(std::size_t& alloc_size, T str)
    {
        return TraceLog::accumulate_size(alloc_size, str);
    }

    static TraceEvent::storage_ptr allocate(std::size_t alloc_size)
    {
        return TraceLog::allocate(alloc_size);
    }

    template <typename T>
    static void deep_copy(TraceEvent::storage_ptr& ptr, std::size_t& offset, T& str)
    {
        TraceLog::deep_copy(ptr, offset, str);
    }
};

}  // namespace testsuite
