//
// Copyright (c) 2017-2024 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/node/string_literal.hpp>
#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <format>

// clang-format off
///
/// This header contains the specializations of the `ast` nodes custom types for rendering
/// with `std::format`.
/// In addition to the documentation on CppReference.com
/// ([Formatting library (since C++20)](https://en.cppreference.com/w/cpp/utility/format),
/// see more-in-depth MC++ blog:
/// - [The Formatting Library in C++20](https://www.modernescpp.com/index.php/the-formatting-library-in-c20/)
/// - [The Formatting Library in C++20: The Format String](https://www.modernescpp.com/index.php/the-formatting-library-in-c20-the-format-string/)
/// - [The Formatting Library in C++20: The Format String (2)](https://www.modernescpp.com/index.php/the-formatting-library-in-c20-the-format-string-2/)
/// - [Formatting User-Defined Types in C++20](https://www.modernescpp.com/index.php/formatting-user-defined-types-in-c20/)
/// - [More Details to Formatting User-Defined Types in C++20](https://www.modernescpp.com/index.php/more-details-to-formatting-user-defined-types-in-c20/)
/// also Arthur O’Dwyer Stuff mostly about C++:
/// - [std::format from scratch, part 1](https://quuxplusone.github.io/blog/2023/04/21/format-part-1/)
/// - [std::format from scratch, part 2](https://quuxplusone.github.io/blog/2023/04/22/format-part-2/)
/// - [std::format from scratch, part 3](https://quuxplusone.github.io/blog/2023/04/23/format-part-3/)
// clang-format on

//
// clang-format off
// Test field 
// https://coliru.stacked-crooked.com/a/e742770da18d2d43
// https://coliru.stacked-crooked.com/a/f2eaad89999517e4
// templated https://coliru.stacked-crooked.com/a/0b2d7492245fbb77
// https://coliru.stacked-crooked.com/a/3be354f85e84f461 (C++23)
// "prefer composition over inheritance": https://coliru.stacked-crooked.com/a/4a3a355b1b6a6963 (C++23)
// using std::pmr doesn't work as expected: https://coliru.stacked-crooked.com/a/ae71f49d8e2007c2
// clang-format on
//

///
/// formatter helper for std::span
///
template <typename CharT>
struct std::formatter<std::span<const CharT>> : std::formatter<basic_string_view<CharT>> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(std::span<const CharT> const& string_span, std::format_context& ctx) const
    {
        // FixMe [C++23] C++23 std::format will support formatting ranges right out of the box
        return std::formatter<std::basic_string_view<CharT>>::format(
            std::basic_string_view<CharT>{ begin(string_span), end(string_span) }, ctx);
    }
};

///
/// formatter helper for ast::string_span's boost iterator range
///
template <>
struct std::formatter<ibis::vhdl::ast::string_span> : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::string_span const& string_span, std::format_context& ctx) const
    {
        // FixMe [C++23] C++23 std::format will support formatting ranges right out of the box
        return std::formatter<std::string_view>::format(
            std::string_view{ begin(string_span), end(string_span) }, ctx);
    }
};

///
/// formatter for ast::bit_string_literal::base_specifier
/// required for BOOST_SPIRIT_X3_DEBUG
///
template <>
struct std::formatter<ibis::vhdl::ast::bit_string_literal::base_specifier> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::bit_string_literal::base_specifier specifier,
                std::format_context& ctx) const
    {
        using base_specifier = ibis::vhdl::ast::bit_string_literal::base_specifier;
        using namespace std::literals::string_view_literals;

        static auto const as_sv = [](base_specifier specifier) {
            // clang-format off
            switch (specifier) {
                case base_specifier::bin:                       return "b"sv;
                case base_specifier::oct:                       return "o"sv;
                case base_specifier::hex:                       return "x"sv;
                // probably an unintentionally constructed enum by default, be graceful
                [[unlikely]] case base_specifier::unspecified:  return "?"sv;
                //
                // *No* default branch: let the compiler generate warning about enumeration
                // value not handled in switch
                //
            }
            // clang-format on

            ::cxx23::unreachable();
        };

        return std::format_to(ctx.out(), "{}", as_sv(specifier));
    }
};

///
/// formatter for ast::bit_string_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::bit_string_literal> : std::formatter<string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::bit_string_literal bit_string, std::format_context& ctx) const
    {
        std::string literal;
        literal.reserve(bit_string.literal.size());
        std::format_to(std::back_inserter(literal), "{}{}", bit_string.base_type,
                       bit_string.literal);

        return std::formatter<string_view>::format(literal, ctx);
    }
};

///
/// formatter for ast::based_literal::numeric_type_specifier
/// required for BOOST_SPIRIT_X3_DEBUG
///
template <>
struct std::formatter<ibis::vhdl::ast::based_literal::numeric_type_specifier>
    : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::based_literal::numeric_type_specifier specifier,
                std::format_context& ctx) const
    {
        using numeric_type_specifier = ibis::vhdl::ast::based_literal::numeric_type_specifier;
        using namespace std::literals::string_view_literals;

        static auto const as_sv = [](numeric_type_specifier specifier) {
            // clang-format off
            switch (specifier) {
                case numeric_type_specifier::integer:                   return "integer"sv;
                case numeric_type_specifier::real:                      return "real"sv;
                // probably an unintentionally constructed enum by default, be graceful
                [[unlikely]] case numeric_type_specifier::unspecified:  return "?"sv;
                //
                // *No* default branch: let the compiler generate warning about enumeration
                // value not handled in switch
                //
            }
            // clang-format on

            ::cxx23::unreachable();
        };

        return std::formatter<std::string_view>::format(as_sv(specifier), ctx);
    }
};

///
/// formatter for ast::based_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::based_literal> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::based_literal based, std::format_context& ctx) const
    {
        using numeric_type_specifier = ibis::vhdl::ast::based_literal::numeric_type_specifier;
        if (based.number.type_specifier == numeric_type_specifier::integer) {
            return std::format_to(ctx.out(), "{}#{}#{}",  // --
                                  based.base, based.number.integer_part, based.number.exponent);
        }
        return std::format_to(ctx.out(), "{}#{}.{}#{}",
                              based.base,                                               //
                              based.number.integer_part, based.number.fractional_part,  //
                              based.number.exponent);
    }
};

///
/// formatter for ast::decimal_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::decimal_literal> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::decimal_literal decimal, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}", decimal.literal);
    }
};

///
/// formatter for ast::string_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::string_literal> : std::formatter<std::string_view> {
    static constexpr std::string_view raw_spec{ "raw" };
    bool raw_format = false;

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx)
    {
        for (auto it = begin(ctx); it != end(ctx); ++it) {
            // FixMe [C++23] C++23 can construct std::basic_string_view over range
            if (std::string_view{ begin(ctx), end(ctx) }.starts_with(raw_spec)) {
                raw_format = true;
                ctx.advance_to(begin(ctx) + raw_spec.size());
            }
        }
        return std::formatter<std::string_view>::parse(ctx);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::string_literal string, std::format_context& ctx) const
    {
        if (raw_format) [[unlikely]] /* rarely used, only for debugging purpose */ {
            return std::formatter<std::string_view>::format(
                // FixMe [C++23] C++23 can construct std::basic_string_view over range
                std::string_view{ begin(string.literal), end(string.literal) }, ctx);
        }

        // maybe better use Andreas Spindler answer?
        // https://stackoverflow.com/questions/7378902/how-to-efficiently-remove-double-quotes-from-stdstring-if-they-exist
        auto unquote = [prev_quote = '\0'](char chr) mutable {
            if (chr == prev_quote) {
                prev_quote = '\0';
                return false;
            }
            if (chr == '"' || chr == '%') {
                prev_quote = chr;
            }
            else {
                prev_quote = '\0';
            }
            return true;
        };

        std::string temp;
        for (auto const chr : string.literal) {
            if (unquote(chr)) {
                std::format_to(std::back_inserter(temp), "{}", chr);
            }
        }

        return std::formatter<std::string_view>::format(temp, ctx);
    }
};

///
/// formatter for ast::operator_token
///
template <>
struct std::formatter<ibis::vhdl::ast::operator_token> : std::formatter<std::string_view> {
    static std::string_view as_sv(ibis::vhdl::ast::operator_token token);

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::operator_token token, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(as_sv(token), ctx);
    }
};

///
/// formatter for ast::keyword_token
///
template <>
struct std::formatter<ibis::vhdl::ast::keyword_token> : std::formatter<std::string_view> {
    static std::string_view as_sv(ibis::vhdl::ast::keyword_token token);

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::keyword_token token, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(as_sv(token), ctx);
    }
};

///
/// ostream operators required for BOOST_SPIRIT_X3_DEBUG
///
namespace ibis::vhdl::ast {

inline std::ostream& operator<<(std::ostream& os, bit_string_literal::base_specifier specifier)
{
    os << std::format("{}", specifier);
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                ast::based_literal::numeric_type_specifier specifier)
{
    os << std::format("{}", specifier);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, ast::keyword_token token)
{
    os << std::format("{}", token);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, ast::operator_token token)
{
    os << std::format("{}", token);
    return os;
}

}  // namespace ibis::vhdl::ast
