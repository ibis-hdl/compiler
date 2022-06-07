//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <testsuite/mock_std_clock.hpp>

#include <chrono>

namespace std::chrono {

ibis::tool::event_trace::clock::time_point_type steady_clock::now() noexcept
{
    using namespace ibis::tool::event_trace;

    auto const count = testsuite::clock_fixture::instance().count();
    return clock::time_point_type(nanoseconds(count));
}

}  // namespace std::chrono
