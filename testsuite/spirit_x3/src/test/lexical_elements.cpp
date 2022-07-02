// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

#include <string_view>
#include <array>
#include <iomanip>

#include <boost/test/unit_test.hpp>  // IWYU pragma: keep

namespace {

// [How to concatenate static strings at compile time?]
//  https://stackoverflow.com/questions/38955940/how-to-concatenate-static-strings-at-compile-time)
template <std::string_view const&... Strs>
struct join
{
    // Join all strings into a single std::array of chars
    static constexpr auto impl() noexcept
    {
        constexpr std::size_t len = (Strs.size() + ... + 0);
        std::array<char, len + 1> arr{};
        auto append = [i = 0, &arr](auto const& s) mutable {
            for (auto c : s) arr[i++] = c;
        };
        (append(Strs), ...);
        arr[len] = 0;
        return arr;
    }
    // Give the joined string static storage
    static constexpr auto arr = impl();
    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
};
// Helper to get the value out
template <std::string_view const&... Strs>
static constexpr auto join_v = join<Strs...>::value;

} // namespace anonymous

using namespace std::literals::string_view_literals;
namespace x3 = boost::spirit::x3;

namespace vhdl {

///
/// basic_graphic_character ::=                                    [LRM93 §13.1]
///     upper_case_letter | digit | special_character| space_character
///
/// graphic_character ::=                                          [LRM93 §13.1]
///      basic_graphic_character
///    | lower_case_letter
///    | other_special_character
///
auto constexpr upper_case_letter = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞU)"sv;
auto constexpr digit = R"(0123456789)"sv;
auto constexpr special_character = R"("#&'()*+,-./:;<=>[]_|)"sv;
auto constexpr lower_case_letter = R"(abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ)"sv;
// Note: VS Code doesn't render soft hyphen (U+00AD) at string's end!, e.g. use emacs/vi, notepad++
auto constexpr other_special_character = R"(!$%?@\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷­)"sv;

}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(lexical_elements)

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(character_set)
{
    constexpr auto basic_graphic_character_v = join_v<
        vhdl::upper_case_letter,
        vhdl::digit,
        vhdl::special_character
    >;
    constexpr auto graphic_character_v = join_v<
        vhdl::upper_case_letter,
        vhdl::digit,
        vhdl::special_character,     
        vhdl::lower_case_letter, 
        vhdl::other_special_character
    >;

    auto const graphic_character = x3::rule<struct _, char>{ "graphic_character" } = [&]() {
        if constexpr ((false)) { // intentionally disabled
            // FixMe: Spirit.X3 shall support iso8859_1, which it doesn't
            // @see [X3: Provide documentation for different encodings/unicode usage](
            //       https://github.com/boostorg/spirit/issues/614)
            return x3::iso8859_1::graph;
        } else {
            // FixMe: How to initialize x3's char_parser from joined_view?
            return x3::char_(std::string(graphic_character_v));
        }
    }();
    
    for(auto const chr_set: {
        // graphic_character
        vhdl::upper_case_letter,
        vhdl::digit,
        vhdl::special_character,     
        vhdl::lower_case_letter, 
        vhdl::other_special_character
    }) {
        std::string attr;
        bool const parse_ok = x3::parse(begin(chr_set), end(chr_set), 
            +graphic_character >> x3::eoi, attr);
        BOOST_TEST(parse_ok == true);
        BOOST_TEST(chr_set == attr);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(identifiers)
{
    constexpr auto identifier_v = join_v<
        vhdl::upper_case_letter,
        vhdl::lower_case_letter
    >;

    //
    // Check requirements for basic_identifier
    //
    // @code{.bnf}
    // letter ::= upper_case_letter | lower_case_letter
    // basic_identifier ::=  letter { [ underline ] letter_or_digit }
    // @endcode
    //
    auto const identifier = x3::rule<struct _, char>{ "identifier" } = [&]() {
        if constexpr ((false)) { // intentionally disabled
            return x3::iso8859_1::alpha;
        } else {
            // FixMe: How to initialize x3's char_parser from joined_view?
            return x3::char_(std::string(identifier_v));
        }
    }();
    
    for(auto const chr_set: {
        // letter
        vhdl::upper_case_letter,
        vhdl::lower_case_letter
    }) {
        std::string attr;
        bool const parse_ok = x3::parse(begin(chr_set), end(chr_set), 
            // FixMe: If using VHDL's {upper, lower}_case_letters as parsers, there isn't
            // a way to compare them case-insensitive out-of-the-box. ISO-1076-2008 clarifies this, 
            // where ÿ and ß doesn't have corresponding uppercase letter. Probably one has to write
            // own compare function by extending Spirit X3.
            x3::no_case[ +identifier ]  >> x3::eoi,
        attr);
        BOOST_TEST(parse_ok == true);
        BOOST_TEST(vhdl::lower_case_letter == attr);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
