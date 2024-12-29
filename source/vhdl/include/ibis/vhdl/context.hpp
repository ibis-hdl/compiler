//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/ast/util/string_span_hash.hpp>

#include <unordered_map>
#include <exception>
#include <limits>
#include <iosfwd>
#include <format>
#include <cstdint>

namespace ibis::vhdl {

namespace detail {

///
/// Tagged treshold counter
///
/// Simply increments events and throws treshold_counter::overflow if a configurable
/// limit has been reached.
///
/// @see Concept at [coliru](https://coliru.stacked-crooked.com/a/a9780ceb475570bf)
///
template <typename Tag>
class treshold_counter {
public:
    ///
    /// @brief Exception thrown if the counter limit has been reached.
    ///
    /// ToDo Make it more expressive with string message, configured threshold_ etc.
    struct overflow : public std::exception {};

public:
    ///
    /// Underlying type of counter.
    /// @note: It would be only natural to use type of `std::size_t`, but then there are compiler
    /// warnings like `[-Wshorten-64-to-32]` at Clang '-Weverything' Diagnostic. The reason is the
    // use of `boost::locale`'s `translate()` function, where the singular/plural argument is of
    /// type `uint32`. Since the count_value range of `uint32` is sufficient here for errors and
    /// warnings, a work-around with lambda functions is unnecessary.
    ///
    using value_type = std::uint32_t;

    /// The maximum numeric/count count_value.
    static constexpr value_type MAX_THRESHOLD = std::numeric_limits<value_type>::max() - 1;

public:
    ///
    /// constructs the tagged counter.
    ///
    /// @param threshold threshold of count value. Must be in range of `[0 ... MAX_THRESHOLD)`
    ///
    explicit treshold_counter(value_type threshold)
        : threshold_value{ threshold }
    {
    }

    ~treshold_counter() = default;

    treshold_counter(treshold_counter const&) = delete;
    treshold_counter& operator=(treshold_counter const&) = delete;

    treshold_counter(treshold_counter&&) = default;
    treshold_counter& operator=(treshold_counter&&) = default;

public:
    ///
    /// prefix increment
    ///
    /// @fn     treshold_counter::operator++()
    /// @return incremented count count_value.
    ///
    treshold_counter& operator++()
    {
        if (count_value > threshold_value) {
            throw overflow{};
        }
        ++count_value;
        return *this;
    }

    ///
    /// postfix increment
    ///
    /// @fn     treshold_counter::operator++(int)
    /// @return the count count_value before increment.
    ///
    treshold_counter operator++(int)
    {
        treshold_counter result{ *this };
        ++(*this);
        return result;
    }

    ///
    /// user-defined conversion
    ///
    operator value_type() const { return count_value; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Reference to the threshold count_value.
    ///
    value_type& threshold() { return threshold_value; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Const reference to the threshold count_value.
    ///
    value_type threshold() const { return threshold_value; }

private:
    value_type threshold_value;
    value_type count_value = 0;
};

}  // namespace detail

///
/// The VHDL context used for analyze and elaboration
///
/// The error_count will throw if the limit of errors is reached:
/// @code{.cpp}
/// try {
///   ... // analyze
/// }
/// catch(context::error_counter::overflow const&) {
///    std::cerr << "fatal error: too many errors emitted, stopping now "
///              << "[-ferror-limit=]"
///    // ...
/// }
/// @endcode
///
/// Todo Find a better name, too much context classes with different purpose in ibis.
///
class context {
public:
    using error_counter = detail::treshold_counter<struct error_tag>;
    using warning_counter = detail::treshold_counter<struct warning_tag>;

    using value_type = typename error_counter::value_type;

public:
    ///
    /// Creates the VHDL context
    ///
    /// @param error_limit threshold of error count value.
    ///
    explicit context(value_type error_limit = 42)
        : error_count{ error_limit }
        , warning_count{ warning_counter::MAX_THRESHOLD }
    {
    }

    context(context&) = delete;
    context& operator=(context&) = delete;
    context(context&&) = default;
    context& operator=(context&&) = default;
    ~context() = default;

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
/// IO-manipulator to print the context error/warning status of context
///
class failure_status {
    using value_type = context::value_type;

public:
    failure_status(context const& ctx_)
        : ctx{ ctx_ }
    {
    }

    bool error_free() const { return ctx.error_free(); }
    bool has_errors() const { return ctx.has_errors(); }
    bool has_warnings() const { return ctx.has_warnings(); }

    value_type errors() const { return ctx.errors(); }
    value_type warnings() const { return ctx.warnings(); }

private:
    context const& ctx;
};

std::ostream& operator<<(std::ostream& os, vhdl::failure_status const& status);

}  // namespace ibis::vhdl

template <>
struct std::formatter<ibis::vhdl::failure_status>;
