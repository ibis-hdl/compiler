//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

// Std C++
#include <filesystem>
#include <functional>
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

// 3rd party
#include <CLI/CLI.hpp>
