//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//
#pragma once

#include <ibis/concepts.hpp>

#include <limits>
#include <type_traits>
#include <stdexcept>

namespace ibis::util {

///
/// Tagged treshold counter
///
/// Simply increments events and throws treshold_counter::overflow if a configurable
/// limit has been reached.
///
/// @see Proof of concept [coliru](https://coliru.stacked-crooked.com/a/4bf440f2fe69dab7)
///
template <typename T, typename Tag>
// requires ibis::unsigned_integer<T>
class tagged_treshold_counter {
public:
    ///
    /// @brief Exception thrown if the counter limit has been reached.
    ///
    struct overflow : public std::overflow_error {
        overflow()
            : std::overflow_error{ "limit reached" }
        {
        }
    };

public:
    ///
    /// Underlying value_type of the counter.
    ///
    using value_type = std::remove_cv_t<T>;

    /// The maximum numeric/count count_value.
    static constexpr value_type MAX_THRESHOLD = std::numeric_limits<value_type>::max();

public:
    ///
    /// Constructs the tagged counter.
    ///
    /// @param threshold threshold of count value. Must be in range of `[0 ... MAX_THRESHOLD]`
    ///
    explicit tagged_treshold_counter(value_type threshold)
        : threshold_value{ threshold }
    {
    }

    tagged_treshold_counter() = default;
    ~tagged_treshold_counter() = default;

    tagged_treshold_counter(tagged_treshold_counter&&) = default;
    tagged_treshold_counter& operator=(tagged_treshold_counter&&) = default;

    tagged_treshold_counter(tagged_treshold_counter const&) = delete;
    tagged_treshold_counter& operator=(tagged_treshold_counter const&) = delete;

public:
    ///
    /// prefix increment
    ///
    tagged_treshold_counter& operator++()
    {
        if (!(count_value < threshold_value)) {
            throw overflow{};
        }
        ++count_value;
        return *this;
    }

    ///
    /// postfix increment
    ///
    tagged_treshold_counter operator++(int)
    {
        tagged_treshold_counter result{ *this };
        ++(*this);
        return result;
    }

    ///
    /// user-defined conversion to get the curent count value.
    ///
    operator value_type() const { return count_value; }

    ///
    /// Get the curent count value.
    ///
    value_type get() const { return count_value; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Non-const reference to the threshold count_value.
    ///
    value_type& threshold() { return threshold_value; }

    ///
    /// Threshold at where the overflow exception will be thrown.
    ///
    /// @return Threshold value.
    ///
    value_type threshold() const { return threshold_value; }

private:
    value_type threshold_value = MAX_THRESHOLD;
    value_type count_value = 0;
};

}  // namespace ibis::util
