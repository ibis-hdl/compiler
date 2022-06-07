//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

// C++
#include <filesystem>
#include <fstream>
#include <iterator>
#include <limits>
#include <optional>
#include <regex>
#include <set>
#include <string_view>
#include <unordered_set>

// Boost
#include <boost/bind/bind.hpp>

#include <boost/range/iterator_range.hpp>
// <boost/range/iterator_range_hash.hpp> results into error: redefinition of 'hash_value'
#include <boost/functional/hash.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/results_collector.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/size.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/for_each_sample.hpp>
#include <boost/test/utils/string_cast.hpp>

// The header <boost/spirit/home/x3/auxiliary.hpp>, which includes the problemtic header
// <boost/spirit/home/x3/util/any_parser.hpp>, runs into compile problems due to Spirit X3's
// `move_to` traits. Even forwarding of enum class ast's `keyword_token` doesn't helped
// here.
#include <boost/spirit/home/x3/char.hpp>
#include <boost/spirit/home/x3/directive.hpp>
#include <boost/spirit/home/x3/nonterminal.hpp>
#include <boost/spirit/home/x3/numeric.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/string.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
