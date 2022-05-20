#pragma once

#include <ibis/tool/event_trace/detail/trace_value.hpp>
#include <ibis/tool/event_trace/trace_event.hpp>

#include <iostream>
#include <string_view>
#include <functional>

namespace ibis::tool::event_trace {
class TraceID;
}

namespace ibis::tool::event_trace {

// https://github.com/llvm/llvm-project/blob/main/llvm/include/llvm/Support/TimeProfiler.h
// https://github.com/llvm/llvm-project/blob/main/llvm/lib/Support/TimeProfiler.cpp
//

///
/// Quote JSON strings which must be quoted with double quotes.
///
/// @see
/// - [ECMA](
///    https://www.ecma-international.org/publications-and-standards/standards/ecma-404/)
/// - [IETF](https://datatracker.ietf.org/doc/html/rfc7159)
///
/// Notice missing '/', see [JSON: why are forward slashes escaped?](
///  https://stackoverflow.com/questions/1580647/json-why-are-forward-slashes-escaped)
///
/// @see Concept: [Coliru](https://coliru.stacked-crooked.com/a/30d627dc9e8dfb1f)
///
class quoted {
public:
    quoted(std::string_view str_)
        : str{ str_ }
    {
    }
    friend std::ostream& operator<<(std::ostream& os, quoted const& quoted);

private:
    std::string_view const str;
};

///
/// Non-formatting, quick & dirty JSON stream writer API
///
/// No checks are performed, so one can easily generate invalid JSON files.
///
/// Credits go to the llvm project, based on
/// [JSON.h](https://github.com/llvm/llvm-project/blob/main/llvm/include/llvm/Support/JSON.h) and
/// [JSON.cpp](https://github.com/llvm/llvm-project/blob/main/llvm/lib/Support/JSON.cpp).
///
class json_ostream {
public:
    json_ostream(std::ostream& os_)
        : os{ os_ }
    {
    }

    /// Flushes the underlying ostream.
    void flush() { os.flush(); }

public:
    using BlockFcn = std::function<void()>;

public:
    /// Emit an array whose elements are emitted in the provided BlockFcn.
    void array(BlockFcn Contents)
    {
        arrayBegin();
        Contents();
        arrayEnd();
    }

    /// Emit an object whose elements are emitted in the provided BlockFcn.
    void object(BlockFcn Contents)
    {
        comma = "";
        objectBegin();
        Contents();
        objectEnd();
    }

    /// Emit an attribute whose value is an argument TraceValue
    void attribute(std::string_view Key, TraceValue const& Contents)
    {
        attributeImpl(Key, [&]() { visit(Contents); });
    }

    /// Emit an attribute whose value is a TraceEvent::phase
    void attribute(std::string_view Key, TraceEvent::phase phase)
    {
        attributeImpl(Key, [&]() { os << '"' << phase << '"'; });
    }

    /// Emit an attribute whose value is a TraceEvent::TraceID
    void attribute(std::string_view Key, TraceID id);

    /// Emit an attribute whose value is a string_view
    void attribute(std::string_view Key, std::string_view sv)
    {
        attributeImpl(Key, [&]() { os << quoted(sv); });
    }

    /// Emit an attribute whose value is a c-string
    void attribute(std::string_view Key, char const* cstr)
    {
        attributeImpl(Key, [&]() { os << quoted(cstr); });
    }

    /// Emit an attribute whose value is a boolean
    void attribute(std::string_view Key, bool b)
    {
        attributeImpl(Key, [&]() { os << std::boolalpha << b; });
    }

    /// Emit an attribute whose value is an array with elements from the BlockFcn.
    void attributeArray(std::string_view Key, BlockFcn Contents)
    {
        attributeImpl(Key, [&]() { array(Contents); });
    }

    /// Emit an attribute whose value is an object with attributes from the BlockFcn.
    void attributeObject(std::string_view Key, BlockFcn Contents)
    {
        attributeImpl(Key, [&]() { object(Contents); });
    }

    /// Emit an attribute whose value is of non-overloaded type
    template <typename T>
    void attribute(std::string_view Key, T value)
    {
        attributeImpl(Key, [&]() { os << value; });
    }

public:
    void objectBegin();
    void objectEnd();

    void attributeBegin(std::string_view key);
    void attributeEnd();

    void arrayBegin();
    void arrayEnd();

private:
    /// Emit a self-contained trace value (number, string(view) etc).
    void visit(TraceValue const& val);

    void attributeImpl(std::string_view Key, BlockFcn Contents)
    {
        attributeBegin(Key);
        Contents();
        attributeEnd();
        comma = ",";
    }

private:
    std::string_view comma = "";
    std::ostream& os;
};

inline void json_ostream::objectBegin() { os << comma << "{"; }

inline void json_ostream::objectEnd() { os << "}"; }

inline void json_ostream::attributeBegin(std::string_view key)
{
    os << comma << quoted(key) << ":";
}

inline void json_ostream::attributeEnd() {}

inline void json_ostream::arrayBegin() { os << "["; }

inline void json_ostream::arrayEnd()
{
    os << "]";
    comma = ",";
}

}  // namespace ibis::tool::event_trace
