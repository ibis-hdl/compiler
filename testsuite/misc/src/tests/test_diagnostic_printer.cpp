//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/diagnostic_formatter.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/interface.hpp>  // BOOST_TEST()
#include <boost/test/tools/context.hpp>    // BOOST_TEST_CONTEXT()
#include <boost/test/unit_test_suite.hpp>  // BOOST_AUTO_TEST_CASE()
#include <boost/test/tree/decorator.hpp>   // utf::label
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

#include <iostream>
#include <format>
#include <string_view>
#include <optional>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(diagnostic_printer)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(gutter_formatter, *utf::label("formatter"))
{
    using gutter = ibis::vhdl::number_gutter;

    // clang-format off
    BOOST_TEST(std::format("|{}|", gutter{})            == "|     |",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 0 })         == "|     |",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 1 })         == "|   1 |",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 100 })       == "| 100 |",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 9'999 })     == "|9999 |",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 10'000 })    == "|10000|",   btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 123'456 })   == "|123456|",  btt::per_element());
    BOOST_TEST(std::format("|{}|", gutter{ 1'234'567 }) == "|1234567|", btt::per_element());
    // clang-format on
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(spacer_formatter, *utf::label("formatter"))
{
    using spacer = ibis::vhdl::spacer;

    // clang-format off
    BOOST_TEST(std::format("{}", spacer{})         == "",     btt::per_element());
    BOOST_TEST(std::format("{}", spacer{ 0 })      == "",     btt::per_element());
    BOOST_TEST(std::format("{}", spacer{ 0, "*" }) == "",     btt::per_element());
    BOOST_TEST(std::format("{}", spacer{ 1, "*" }) == "*",    btt::per_element());
    BOOST_TEST(std::format("{}", spacer{ 4, "-" }) == "----", btt::per_element());
    BOOST_TEST(std::format("{}", spacer{ 4, " " }) == "    ", btt::per_element());
    // clang-format on
}

namespace valid_data {  // for issue_marker_formatter

// helper function for make_issue() below to create an iterator pointing to char's position
template <typename IteratorT>
constexpr auto find_char = [](IteratorT begin, IteratorT end, char srch_chr) {
    return std::find_if(begin, end, [srch_chr](char chr) { return chr == srch_chr; });
};

// create an issue_marker by generating a set of iterators - mimics x3 parser error handler result
// for proof of concept including wrapper/formatter see https://godbolt.org/z/z5Yrz6e6M
constexpr auto make_issue = [](std::string_view str, char first_chr,
                               std::optional<char> last_chr = {}) {
    using iterator_type = std::string_view::const_iterator;
    using ibis::vhdl::issue_marker;

    auto const start = str.begin();
    auto const failure_begin = find_char<iterator_type>(str.begin(), str.end(), first_chr);
    auto const failure_end = [&]() {
        if (last_chr.has_value()) {
            // clang-format off
            return std::optional<iterator_type>{
                find_char<iterator_type>(failure_begin, str.end(), last_chr.value())
            };
            // clang-format on
        }
        return std::optional<iterator_type>{};
    }();

    return issue_marker{ start, failure_begin, failure_end };
};

using ibis::vhdl::issue_marker;
using iterator_type = std::string_view::const_iterator;
using namespace std::literals;

constexpr auto const input_string =
    // simple input string with unique symbols to avoid unintentional errors such as (end < begin)
    "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"sv;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
struct {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    issue_marker<iterator_type> issue;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    std::string_view expected;
} constexpr gold_data[] = {
    //  --
    { .issue = make_issue(input_string, 'a'),  // single marker at begin
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "^" },
    { .issue = make_issue(input_string, ','),  // single marker in the middle
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                                                     ^" },
    { .issue = make_issue(input_string, ';'),  // single marker at end
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                                                                ^" },
    { .issue = make_issue(input_string, 'a', 'b'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "~" },
    { .issue = make_issue(input_string, 'A', 'B'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                           ~" },
    { .issue = make_issue(input_string, '9', ';'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                                                               ~" },
    { .issue = make_issue(input_string, 'a', '.'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "~~~~~~~~~~~~~~~~~~~~~~~~~~" },
    { .issue = make_issue(input_string, 'q', 'Q'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                ~~~~~~~~~~~~~~~~~~~~~~~~~~~" },
    { .issue = make_issue(input_string, 'A', ';'),
      //          "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,0123456789;"
      .expected = "                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" },
};

}  // namespace valid_data

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(issue_marker_formatter, *utf::label("formatter"))
{
    constexpr bool const verbose = false;

    btt::output_test_stream output;  // reused, flushed/cleared after each test

    for (auto index{ 0U }; auto const& [issue, expected] : valid_data::gold_data) {
        BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
        {
            output << std::format("{}", issue);

            // verbose output for debugging
            if constexpr (verbose) {
                using valid_data::input_string;
                std::cout << std::format(
                    "{0:-^76}\n"        // -- top border
                    "input    |{1}|\n"  // -- | <input> |
                    "output   |{2}|\n"  // -- | <issue marker> |
                    "expected |{3}|\n"  // -- | expected |
                    "{4:-^76}\n",       // -- bottom border
                    // --- data ---
                    " verbose ",                    // top border
                    input_string, issue, expected,  // <input>, <issue marker>, <expected>
                    ""                              // bottom border
                );
            }

            BOOST_TEST_REQUIRE(!output.str().empty());
            BOOST_TEST(output.str() == expected, btt::per_element());
        }
        output.flush();  // clear output for next run
        ++index;
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
