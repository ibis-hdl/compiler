#pragma once

#include <chrono>

namespace ibis::tool::event_trace::clock {

using clock_type = std::chrono::steady_clock;
using time_point_type = std::chrono::time_point<clock_type>;
using duration_type = clock::time_point_type::duration;

///
/// clock source for generating time stamps.
///
/// @note: For the testsuite we have to fake the std::clock.
///
/// @see Concept [Coliru](https://coliru.stacked-crooked.com/a/9374003ad8dc61c8)
inline time_point_type now() { return clock_type::now(); }

// Marker for no duration
inline constexpr auto time_point_zero =
    std::chrono::time_point<clock_type, std::chrono::nanoseconds>(std::chrono::nanoseconds(0));
inline constexpr auto duration_zero = clock_type::duration::zero();

}  // namespace ibis::tool::event_trace::clock
