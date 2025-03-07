//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/diagnostic/util.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/tree/decorator.hpp>  // utf::label

#include <boost/range/iterator_range_core.hpp>

#include <string_view>
#include <array>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace ibis::diagnostic::testsuite {

namespace input_data {
/* https://www.online-python.com/AlXKoYrIDG
 * @code{.py}
 * def foo():
 *     string = "Line 1;\r\n\tLine 2;\r\nLine 3;\r\n"
 *     print(string)
 *     for i, char in enumerate(string):
 *         print(f"'{char.encode('unicode_escape').decode('utf-8')}', ", end='')
 *     print()
 *     print(*range(0, i, 1), sep = "    ")
 * @endcode
 */
auto constexpr string_array_EolWin = std::to_array<char const>({
    // clang-format off
    'L', 'i', 'n', 'e', ' ', '1', ';', '\r', '\n', '\t', 'L', 'i', 'n', 'e', ' ', '2', ';', '\r', '\n', 'L', 'i', 'n', 'e', ' ', '3', ';', '\r', '\n', '\0'
    //    1    2    3    4    5    6    7     8     9     10   11   12   13   14   15   16   17    18    19   20   21   22   23   24   25   26    27
    // clang-format on
});

auto constexpr string_array_EolUnix = std::to_array<char const>({
    // clang-format off
    'L', 'i', 'n', 'e', ' ', '1', ';', '\n', '\t', 'L', 'i', 'n', 'e', ' ', '2', ';', '\n', 'L', 'i', 'n', 'e', ' ', '3', ';', '\n', '\0'
    //    1    2    3    4    5    6    7     8     9    10   11   12   13   14   15   16   17    18   19   20   21   22   23   24
    // clang-format on
});

}  // namespace input_data

namespace /* anonymous */ {
constexpr auto set_position = [](auto iter, auto offset) {
    std::advance(iter, offset);
    return iter;
};
}  // namespace

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(diagnostic_text_utils)

// ClangTidy - don't touch the iterators, since this may be an iterator class
// NOLINTBEGIN(readability-qualified-auto)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(test_current_line_EolWin, *utf::label("diagnostic"))
{
    constexpr std::string_view document{ input_data::string_array_EolWin };
    auto const begin = document.begin();
    auto const end = document.end();

    // Test first line
    {
        auto const position = set_position(begin, 0);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "Line 1;");
    }

    // Test second line with tab
    {
        auto const position = set_position(begin, 9);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "\tLine 2;");
    }

    // Test third line
    {
        auto const position = set_position(begin, 19);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "Line 3;");
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(test_current_line_EolUnix, *utf::label("diagnostic"))
{
    constexpr std::string_view document{ input_data::string_array_EolUnix };
    auto const begin = document.begin();
    auto const end = document.end();

    // Test first line
    {
        auto const position = set_position(begin, 0);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "Line 1;");
    }

    // Test second line with tab
    {
        auto const position = set_position(begin, 8);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "\tLine 2;");
    }

    // Test third line
    {
        auto const position = set_position(begin, 17);
        auto const result = util::current_line(boost::make_iterator_range(begin, end), position);
        BOOST_CHECK_EQUAL(result, "Line 3;");
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(test_line_column_number_EolWin, *utf::label("diagnostic"))
{
    constexpr std::string_view document{ input_data::string_array_EolWin };
    auto const begin = document.begin();
    auto const end = document.end();
    std::uint32_t const tab_sz = 4;

    // Test first line position
    {
        auto const position = set_position(begin, 3);
        auto pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 0);
        BOOST_CHECK_EQUAL(pos_info.character, 3);
    }

    // Test second line position
    {
        auto const position = set_position(begin, 10);
        auto const pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 1);
        BOOST_CHECK_EQUAL(pos_info.character, 4);  // tab counted as 4 spaces
    }

    // Test third line position
    {
        auto const position = set_position(begin, 20);
        auto const pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 2);
        BOOST_CHECK_EQUAL(pos_info.character, 1);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(test_line_column_number_EolUnix, *utf::label("diagnostic"))
{
    constexpr std::string_view document{ input_data::string_array_EolUnix };
    auto const begin = document.begin();
    auto const end = document.end();
    std::uint32_t const tab_sz = 4;

    // Test first line position
    {
        auto const position = set_position(begin, 3);
        auto pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 0);
        BOOST_CHECK_EQUAL(pos_info.character, 3);
    }

    // Test second line position
    {
        auto const position = set_position(begin, 9);
        auto const pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 1);
        BOOST_CHECK_EQUAL(pos_info.character, 4);  // tab counted as 4 spaces
    }

    // Test third line position
    {
        auto const position = set_position(begin, 18);
        auto const pos_info =
            util::line_column_number(boost::make_iterator_range(begin, end), position, tab_sz);
        BOOST_CHECK_EQUAL(pos_info.line, 2);
        BOOST_CHECK_EQUAL(pos_info.character, 1);
    }
}

// NOLINTEND(readability-qualified-auto)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()

}  // namespace ibis::diagnostic::testsuite
