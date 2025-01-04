//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/trim.hpp>

#include <boost/test/tools/interface.hpp>  // BOOST_TEST()
#include <boost/test/unit_test_suite.hpp>  // BOOST_AUTO_TEST_CASE()
#include <boost/test/unit_test.hpp>        // IWYU pragma: keep

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <utility>
#include <initializer_list>
#include <string_view>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(common_utils)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(ltrim_sv)
{
    using namespace std::literals::string_view_literals;
    using ibis::util::ltrim;

    for (auto const& test : { std::pair
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
        BOOST_TEST(ltrim(test.first) == test.second, btt::per_element());
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(rtrim_sv)
{
    using namespace std::literals::string_view_literals;
    using ibis::util::rtrim;

    for (auto const& test : { std::pair
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
        BOOST_TEST(rtrim(test.first) == test.second, btt::per_element());
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(trim_sv)
{
    using namespace std::literals::string_view_literals;
    using ibis::util::trim;

    for (auto const& test : { std::pair
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
        BOOST_TEST(trim(test.first) == test.second, btt::per_element());
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
