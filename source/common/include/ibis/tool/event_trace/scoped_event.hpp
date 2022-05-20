#pragma once

#include <ibis/tool/event_trace/trace_log.hpp>
#include <ibis/tool/event_trace/category.hpp>
#include <ibis/tool/event_trace/trace_id.hpp>

#include <string_view>
#include <variant>
#include <optional>
#include <iostream>

#include <fstream>
#include <memory>

namespace ibis::tool::event_trace {

///
/// @brief
///
///
class TraceEndOnScopeClose {
public:
    TraceEndOnScopeClose(category::proxy entry, std::string_view event_name_)
        : category_proxy(entry)
        , event_name(event_name_)
    {
    }
    ~TraceEndOnScopeClose()
    {
        if (category_proxy) {
            AddEvent();
        }
    }

public:
    TraceEndOnScopeClose() = delete;
    TraceEndOnScopeClose(TraceEndOnScopeClose&) = delete;
    TraceEndOnScopeClose& operator=(TraceEndOnScopeClose&) = delete;
    TraceEndOnScopeClose(TraceEndOnScopeClose&&) = delete;
    TraceEndOnScopeClose& operator=(TraceEndOnScopeClose&&) = delete;

private:
    void AddEvent()
    {
        TraceLog::GetInstance().AddTraceEventInternal(                           // --
            TraceEvent::phase::END, category_proxy.category_name(), event_name,  // --
            TraceID::NONE, TraceEvent::flag::NONE,                               // --
            std::string_view(), TraceValue(),                                    // -- no arguments
            TraceLog::EVENT_ID_NONE, clock::duration_zero,                       // --
            nullptr);
    }

private:
    category::proxy const category_proxy;
    std::string_view const event_name;
};

///
/// @brief
///
/// threshold id must be set later after constructing the corresponding
/// start event ID, since TraceEndOnScopeCloseThreshold is created before
/// and writes the contents on destruction.
class TraceEndOnScopeCloseThreshold {
public:
    TraceEndOnScopeCloseThreshold(category::proxy entry, std::string_view event_name_,
                                  clock::duration_type threshold_)
        : category_proxy(entry)
        , event_name(event_name_)
        , threshold(threshold_)
        , threshold_begin_id(TraceLog::EVENT_ID_NONE)
    {
    }
    ~TraceEndOnScopeCloseThreshold()
    {
        if (category_proxy) {
            AddEvent();
        }
    }

public:
    void set_threshold_begin_id(std::int32_t event_id) { threshold_begin_id = event_id; }

public:
    TraceEndOnScopeCloseThreshold() = delete;
    TraceEndOnScopeCloseThreshold(TraceEndOnScopeCloseThreshold&) = delete;
    TraceEndOnScopeCloseThreshold& operator=(TraceEndOnScopeCloseThreshold&) = delete;
    TraceEndOnScopeCloseThreshold(TraceEndOnScopeCloseThreshold&&) = delete;
    TraceEndOnScopeCloseThreshold& operator=(TraceEndOnScopeCloseThreshold&&) = delete;

private:
    void AddEvent()
    {
        TraceLog::GetInstance().AddTraceEventInternal(                           // --
            TraceEvent::phase::END, category_proxy.category_name(), event_name,  // --
            TraceID::NONE, TraceEvent::flag::NONE,                               // --
            std::string_view(), TraceValue(),                                    // -- no arguments
            threshold_begin_id, threshold,                                       // --
            nullptr);
    }

private:
    category::proxy const category_proxy;
    std::string_view const event_name;
    clock::duration_type const threshold;
    std::int32_t threshold_begin_id;
};

}  // namespace ibis::tool::event_trace
