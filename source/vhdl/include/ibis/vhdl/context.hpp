#pragma once

#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/ast/util/string_span_hash.hpp>

#include <unordered_map>
#include <exception>
#include <limits>
#include <iosfwd>

namespace ibis::vhdl {

namespace detail {

///
/// Tagged Counter
///
/// Simply increments events and throws tagged_counter::overflow if a configurable
/// limit has been reached.
///
/// @see [coliru](https://coliru.stacked-crooked.com/a/17ad075a66133c27)
///
template <typename Tag>
class tagged_counter {
public:
    ///
    /// @brief Exception thrown if the counter limit has been reached.
    ///
    /// @todo Make it more expressive with string message, configured
    /// threshold etc.
    struct overflow : public std::exception {};

public:
    ///
    /// Underlying type of counter.
    /// @note: It would be only natural to use type of `std::size_t`, but then there are compiler
    /// warnings like `[-Wshorten-64-to-32]` at Clang '-Weverything' Diagnostic. The reason is the
    // use of `boost::locale`'s `translate()` function, where the singular/plural argument is of
    /// type `int32`. Since the value range of `int32` is sufficient for errors and warnings, a
    /// work-around with lambda functions is unnecessary.
    ///
    using value_type = std::int32_t;

    /// The max. ID value of file_id respectively pod_id.
    static constexpr value_type MAX_THRESHOLD = std::numeric_limits<value_type>::max();

public:
    ///
    /// constructs the tagged counter.
    ///
    /// @param limit_ threshold of count value. Must be in range of `[0 ... INT32_MAX)`
    ///
    explicit tagged_counter(value_type limit_ = MAX_THRESHOLD - 1)
        : threshold{ limit_ }
    {
        assert(!(limit_ < 0) && limit_ < MAX_THRESHOLD &&
               "counter threshold out of range must be [0 ... INT32_MAX)");
    }

    ~tagged_counter() = default;

    tagged_counter(tagged_counter const&) = delete;
    tagged_counter& operator=(tagged_counter const&) = delete;

    tagged_counter(tagged_counter&&) = default;
    tagged_counter& operator=(tagged_counter&&) = default;

public:
    ///
    /// prefix increment
    ///
    /// @fn     tagged_counter::operator++()
    /// @return incremented count value.
    ///
    tagged_counter& operator++()
    {
        ++value;
        if (value > threshold) {
            throw overflow{};
        }
        return *this;
    }

    ///
    /// postfix increment
    ///
    /// @fn     tagged_counter::operator++(int)
    /// @return the count value before increment.
    ///
    tagged_counter operator++(int)
    {
        tagged_counter result(*this);
        ++(*this);
        return result;
    }

    ///
    /// user-defined conversion
    ///
    operator value_type() const { return value; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Reference to the threshold value.
    ///
    value_type& limit() { return threshold; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Const reference to the threshold value.
    ///
    value_type limit() const { return threshold; }

    ///
    /// Common ostream API
    ///
    /// @param  os std::ostream handle to write
    /// @return The written ostream handle.
    ///
    std::ostream& print_on(std::ostream& os) const
    {
        os << value;
        return os;
    }

private:
    value_type threshold;
    value_type value = 0;
};

template <typename Tag>
std::ostream& operator<<(std::ostream& os, tagged_counter<Tag> const& counter)
{
    return counter.print_on(os);
}

}  // namespace detail

///
/// The VHDL context used for analyze and elaboration
///
/// The error_count will throw if the limit of errors is reached:
/// \code
/// try {
///   ... // analyze
/// }
/// catch(context::error_counter::overflow const&) {
///    std::cerr << "fatal error: too many errors emitted, stopping now "
///              << "[-ferror-limit=]"
///    // ...
/// }
/// \endcode
///
class context {
public:
    ///
    /// Creates the VHDL context
    ///
    /// @param error_limit  threshold of error count value. Must be in range of `[0 ... INT32_MAX)`
    ///
    explicit context(std::int32_t error_limit = 42);

    context(context&) = delete;
    context& operator=(context&) = delete;
    context(context&&) = default;
    context& operator=(context&&) = default;
    ~context() = default;

public:
    using error_counter = detail::tagged_counter<struct error_tag>;
    using warning_counter = detail::tagged_counter<struct warning_tag>;

public:
    bool error_free() const { return error_count == 0; }

    bool has_errors() const { return error_count != 0; }
    bool has_warnings() const { return warning_count != 0; }

    error_counter& errors() { return error_count; }
    error_counter const& errors() const { return error_count; }

    warning_counter& warnings() { return warning_count; }
    warning_counter const& warnings() const { return warning_count; }

private:
    error_counter error_count;
    warning_counter warning_count;
};

///
/// IO-manipulator to print the context error/warning status on ostream
///
class failure_status {
public:
    failure_status(context const& ctx_)
        : ctx{ ctx_ }
    {
    }

public:
    std::ostream& print_on(std::ostream& os) const;

private:
    context const& ctx;
};

inline std::ostream& operator<<(std::ostream& os, failure_status const& status)
{
    return status.print_on(os);
}

}  // namespace ibis::vhdl
