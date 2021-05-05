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
/// Simply increments events and throws basic_counter::overflow if a configurable
/// limit has been reached.
///
/// @see [Wandbox](https://wandbox.org/permlink/7o4pPgrmHDQUJj1x)
///
template <typename Tag>
class basic_counter {
public:
    ///
    /// @brief Exception thrown if the counter limit has been reached.
    ///
    /// @todo Make it more expressive with string message, configured
    /// treshold etc.
    struct overflow : public std::exception {
    };

public:
    using value_type = std::size_t;

public:
    basic_counter(value_type limit_ = std::numeric_limits<value_type>::max())
        : treshold{ limit_ }
    {
    }

    basic_counter(basic_counter const&) = delete;
    basic_counter& operator=(basic_counter const&) = delete;

public:
    ///
    /// prefix increment
    ///
    /// @fn     basic_counter::operator++()
    /// @return incremented value.
    ///
    basic_counter& operator++()
    {
        ++value;
        if (value > treshold) {
            throw overflow{};
        }
        return *this;
    }

    ///
    /// postfix increment
    ///
    /// @fn     const basic_counter::operator++(int)
    /// @return the value before increment.
    ///
    basic_counter operator++(int)
    {
        basic_counter result(*this);
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
    value_type& limit() { return treshold; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Const reference to the threshold value.
    ///
    value_type limit() const { return treshold; }

    ///
    /// Common ostream API
    ///
    /// @param  os std::ostream handle to write
    /// @return The written ostream handle.
    ///
    std::ostream& print(std::ostream& os) const
    {
        os << value;
        return os;
    }

private:
    value_type treshold;
    value_type value{ 0 };
};

template <typename Tag>
std::ostream& operator<<(std::ostream& os, basic_counter<Tag> const& counter)
{
    return counter.print(os);
}

}  // namespace detail

///
/// The VHDL context used for analyze and elaboration
///
/// The error_count will throw if the limit of errors is reached:
/// \code
/// try {
///   ... // analyse
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
    context(std::size_t error_limit = 42);

public:
    using error_counter = detail::basic_counter<struct error_tag>;
    using warning_counter = detail::basic_counter<struct warning_tag>;

public:
    bool error_free() const { return error_count == 0; }

public:
    error_counter error_count;
    warning_counter warning_count;

private:
    std::unordered_map<ast::string_span, int> dummy;
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
    std::ostream& print(std::ostream& os) const;

private:
    context const& ctx;
};

static inline std::ostream& operator<<(std::ostream& os, failure_status const& status)
{
    return status.print(os);
}

}  // namespace ibis::vhdl
