//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

// Std C++
#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <locale>
#include <string_view>
#include <string>

#if defined(_WIN32)
#include <Windows.h>
#endif

// Boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <boost/iostreams/stream.hpp>
