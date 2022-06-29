//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <stdexcept>

#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

namespace ibis {

///
/// This class defines the type of objects thrown as exceptions to report range
/// errors in internal computations.
///
struct range_error
    : public boost::exception
    , public std::range_error {
    using std::range_error::range_error;
};

using range_error_min = boost::error_info<struct tag_int32_range_min, int32_t>;
using range_error_max = boost::error_info<struct tag_int32_range_max, int32_t>;

}  // namespace ibis
