#pragma once

#include <variant>
#include <string_view>
#include <string>
#include <cstring>
#include <cassert>

namespace ibis::tool::event_trace {

class TraceValue {
public:
    /// The variant type of the types supported as arguments.
    /// The ```std::variant``` is able to hold more than these values
    /// @see Concept at [Coliru](https://coliru.stacked-crooked.com/a/cf7664e5aab1e340) and
    /// basic std::variant testing done at
    /// [Coliru](https://coliru.stacked-crooked.com/a/5838b6bed8339df1)
    ///
    using variant_type = std::variant<  // --
        std::monostate,                 // mark default constructible empty state
        bool, uint64_t, int64_t, double, char const *, void const *>;

public:
    TraceValue() = default;
    TraceValue(TraceValue const &) = default;
    TraceValue &operator=(TraceValue const &) = default;

    TraceValue(TraceValue &&) = default;
    TraceValue &operator=(TraceValue &&) = default;

    template <typename T>
    TraceValue(T value_)
        : value{ value_ }
    {
    }

    TraceValue(std::string_view sv)
        : value{ sv.data() }
    {
        // check on correct terminated string literals since variant is using C string
        assert(strlen(std::get<char const *>(value)) == sv.size()  // --
               && "unexpected strlen for string_view");
    }

    ~TraceValue() = default;

    bool empty() const
    {
        // test on std::monostate which marks the empty variant
        return value.index() == 0;
    }

    variant_type const &data() const { return value; }

public:
    void AppendAsJSON(std::stringstream &ss) const;

private:
    variant_type value;
};

}  // namespace ibis::tool::event_trace
