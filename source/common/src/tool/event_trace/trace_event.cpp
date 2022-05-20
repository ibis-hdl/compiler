#include <ibis/tool/event_trace/trace_event.hpp>
#include <ibis/tool/event_trace/event_trace.hpp>  // what a named bullshit
#include <ibis/tool/event_trace/detail/json_ostream.hpp>

#include <chrono>
#include <sstream>  // FixMe: use std::format or fmtlib::fmt

namespace ibis::tool::event_trace {

TraceEvent::TraceEvent()
    : phase_(TraceEvent::phase::BEGIN)
{
}

TraceEvent::TraceEvent(                                                                    // --
    current_thread::id_type thread_id, clock::time_point_type timestamp,                   // --
    TraceEvent::phase phase, std::string_view category_name, std::string_view event_name,  // --
    std::uint64_t trace_id, TraceEvent::flag flags_,                                       // --
    std::string_view arg1_name, TraceValue arg1_value,                                     // --
    storage_ptr ptr)
    : category_name_(category_name.data())
    , event_name_(event_name.data())
    , arg1_name_(arg1_name.data())
    , arg1_value_(arg1_value)
    , thread_id_(thread_id)
    , timestamp_(timestamp)
    , trace_id_(trace_id)
    , copy_storage(std::move(ptr))
    , phase_(phase)
    , flags(flags_)
{
    // check on correct terminated string literals since storage is using C strings
    assert(strlen(category_name_) == category_name.size() && "unexpected strlen for category_name");
    assert(strlen(event_name_) == event_name.size() && "unexpected strlen for event_name");
    if (arg1_name_ != nullptr) {
        assert(strlen(arg1_name_) == arg1_name.size() && "unexpected strlen for arg1_name");
    }
}

void TraceEvent::AppendAsJSON(std::string& out) const
{
    using namespace std::chrono;

    std::int64_t const time_int64 =
        time_point_cast<nanoseconds>(timestamp_).time_since_epoch().count();

    current_proc::id_type const process_id = TraceLog::GetInstance().process_id();

    std::stringstream ss;
    json_ostream json(ss);

    json.object([&]() {
        json.attribute("cat", category_name_);
        json.attribute("pid", process_id);
        json.attribute("tid", thread_id_);
        json.attribute("ph", phase_);
        json.attribute("ts", time_int64);
        json.attribute("name", event_name_);
        if (arg1_name_ != nullptr) {
            json.attributeObject("args", [&]() { json.attribute(arg1_name_, arg1_value_); });
        }
        if ((flags & TraceEvent::flag::HAS_ID) != 0) {
            json.attribute("id", TraceID::as_TraceID(trace_id_));
        }
    });

    ss << ",\n";
    out += ss.str();
}

}  // namespace ibis::tool::event_trace
