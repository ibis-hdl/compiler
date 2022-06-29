//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

// Std C++
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string_view>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

#if defined(_WIN32)
#include <Windows.h>
#endif

// Boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <boost/iostreams/stream.hpp>

#include <boost/range/iterator_range.hpp>
// <boost/range/iterator_range_hash.hpp> results into error: redefinition of 'hash_value'
#include <boost/functional/hash.hpp>

#include <boost/bind/bind.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

// The header <boost/spirit/home/x3/auxiliary.hpp>, which includes the problemtic header
// <boost/spirit/home/x3/util/any_parser.hpp>, runs into compile problems due to Spirit X3's
// `move_to` traits. Even forwarding of enum class ast's `keyword_token` doesn't helped here.
#include <boost/spirit/home/x3/char.hpp>
#include <boost/spirit/home/x3/directive.hpp>
#include <boost/spirit/home/x3/nonterminal.hpp>
#include <boost/spirit/home/x3/numeric.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/string.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/data/size.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/for_each_sample.hpp>
#include <boost/test/utils/string_cast.hpp>

// 3rd party
#include <CLI/CLI.hpp>
