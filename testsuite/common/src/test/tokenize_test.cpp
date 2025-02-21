//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/tokenize.hpp>

#include <boost/preprocessor.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/tools/assertion.hpp>
#include <boost/test/tools/detail/indirections.hpp>
#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/utils/basic_cstring/basic_cstring.hpp>
#include <boost/test/utils/lazy_ostream.hpp>

#include <iostream>
#include <string_view>
#include <vector>

#include <testsuite/namespace_alias.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(common_utils)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(tokenize_sv)
{
    using namespace std::literals::string_view_literals;
    using namespace ibis::util;

    std::string_view const sv = " foo , bar,baz,  foo   baz, ,,+foo, *bra,";
    std::vector<std::string_view> const expected{
        " foo "sv, " bar"sv, "baz"sv, "  foo   baz"sv, " "sv, "+foo"sv, " *bra"sv,
    };
    std::vector<std::string_view> result;

    tokenize(sv, result, ',');

    //  intentionally disabled
    if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
        for (auto str_v : result) {
            std::cout << "'" << str_v << "'\n";
        }
    }
    BOOST_TEST(expected.size() == result.size());
    BOOST_TEST(result == expected, btt::per_element());
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
