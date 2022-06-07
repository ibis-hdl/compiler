//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/util/trim.hpp>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <utility>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(common_utils)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(ltrim_sv)
{
    using namespace std::literals::string_view_literals;
    using namespace ibis::util;

    for (auto test : { std::pair
                       // phrase
                       { "trim me"sv, "trim me"sv },
                       { "  trim me"sv, "trim me"sv },
                       { "trim me  "sv, "trim me  "sv },
                       { "  trim me  "sv, "trim me  "sv },
                       // single char test
                       { "x"sv, "x"sv },
                       { "  x"sv, "x"sv },
                       { "x  "sv, "x  "sv },
                       { "  x  "sv, "x  "sv },
                       // empty string
                       { "  "sv, ""sv } })  // --
    {
        // std::cout << "ltrim: '" << test.first << "' -> '" << ltrim(test.first) << "'\n";
        BOOST_TEST(ltrim(test.first) == test.second);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(rtrim_sv)
{
    using namespace std::literals::string_view_literals;
    using namespace ibis::util;

    for (auto test : { std::pair
                       // phrase
                       { "trim me"sv, "trim me"sv },
                       { "  trim me"sv, "  trim me"sv },
                       { "trim me  "sv, "trim me"sv },
                       { "  trim me  "sv, "  trim me"sv },
                       // single char test
                       { "x"sv, "x"sv },
                       { "  x"sv, "  x"sv },
                       { "x  "sv, "x"sv },
                       { "  x  "sv, "  x"sv },
                       // empty string
                       { "  "sv, ""sv } })  // --
    {
        // std::cout << "rtrim: '" << test.first << "' -> '" << rtrim(test.first) << "'\n";
        BOOST_TEST(rtrim(test.first) == test.second);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(trim_sv)
{
    using namespace std::literals::string_view_literals;
    using namespace ibis::util;

    for (auto test : { std::pair
                       // phrase
                       { "trim me"sv, "trim me"sv },
                       { "  trim me"sv, "trim me"sv },
                       { "trim me  "sv, "trim me"sv },
                       { "  trim me  "sv, "trim me"sv },
                       // single char test
                       { "x"sv, "x"sv },
                       { "  x"sv, "x"sv },
                       { "x  "sv, "x"sv },
                       { "  x  "sv, "x"sv },
                       // empty string
                       { "  "sv, ""sv } }) {
        // std::cout << "trim:  '" << test.first << "' -> '" << trim(test.first) << "'\n";
        BOOST_TEST(trim(test.first) == test.second);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
