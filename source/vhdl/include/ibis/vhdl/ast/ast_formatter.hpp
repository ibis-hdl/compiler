//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
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
#include <span>
#include <array>

///
/// formatter helper for std::span
///
template <typename CharT>
struct std::formatter<std::span<const CharT>> : std::formatter<basic_string_view<CharT>> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(std::span<const CharT> const& string_span, std::format_context& ctx) const
    {
        return std::formatter<std::basic_string_view<CharT>>::format(
            std::basic_string_view<CharT>{ string_span }, ctx);
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
        return std::formatter<std::string_view>::format(std::string_view{ string_span }, ctx);
    }
};

///
/// formatter for ast::bit_string_literal::base_specifier enumerator
/// required for BOOST_SPIRIT_X3_DEBUG
///
template <>
struct std::formatter<ibis::vhdl::ast::bit_string_literal::numeric_base_specifier> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }

        throw std::format_error(
            "non-empty format specification for <ast::bit_string_literal::numeric_base_specifier>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::bit_string_literal::numeric_base_specifier specifier,
                FmtContext& ctx) const
    {
        using namespace std::literals::string_view_literals;

        // clang-format off
        switch (specifier) {
            using enum ibis::vhdl::ast::bit_string_literal::numeric_base_specifier;
            case base2:
                return std::format_to(ctx.out(), "{}", "b"sv);
            case base8:
                return std::format_to(ctx.out(), "{}", "o"sv);
            case base16:
                return std::format_to(ctx.out(), "{}", "x"sv);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case unspecified:
                return std::format_to(ctx.out(),"{}","unspecified"sv);
            // be graceful, definitely wrong enum - the caller has not worked out properly
            [[unlikely]] case unsupported:
                return std::format_to(ctx.out(),"{}","unsupported"sv);
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    }
};

///
/// formatter for ast::bit_string_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::bit_string_literal> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }

        throw std::format_error("non-empty format specification for <ast::bit_string_literal>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::bit_string_literal const& bit_string, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}{}", bit_string.base_specifier, bit_string.literal);
    }
};

///
/// formatter for ast::based_literal::numeric_type_specifier enumerator
///
template <>
struct std::formatter<ibis::vhdl::ast::based_literal::numeric_type_specifier> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error(
            "non-empty format specification for <ast::based_literal::numeric_type_specifier>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::based_literal::numeric_type_specifier specifier,
                FmtContext& ctx) const
    {
        using namespace std::literals::string_view_literals;

        // clang-format off
        switch (specifier) {
            using enum ibis::vhdl::ast::based_literal::numeric_type_specifier;
            case integer:
                return std::format_to(ctx.out(), "{}", "integer"sv);
            case real:
                return std::format_to(ctx.out(), "{}", "real"sv);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case unspecified:
                return std::format_to(ctx.out(), "{}", "unspecified"sv);
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    }
};

///
/// formatter for ast::based_literal::numeric_base_specifier enumerator
///
template <>
struct std::formatter<ibis::vhdl::ast::based_literal::numeric_base_specifier> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error(
            "non-empty format specification for <ast::based_literal::numeric_base_specifier>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::based_literal::numeric_base_specifier specifier,
                FmtContext& ctx) const
    {
        using namespace std::literals::string_view_literals;

        // clang-format off
        switch (specifier) {
            using enum ibis::vhdl::ast::based_literal::numeric_base_specifier;
            case base2:
                return std::format_to(ctx.out(), "{}", "2"sv);
            case base8:
                return std::format_to(ctx.out(), "{}", "8"sv);
            case base10:
                return std::format_to(ctx.out(), "{}", "10"sv);
            case base16:
                return std::format_to(ctx.out(), "{}", "16"sv);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case unspecified:
                return std::format_to(ctx.out(), "{}", "unspecified"sv);
            // be graceful, definitely wrong enum - the caller has not worked out properly
            [[unlikely]] case unsupported:
                return std::format_to(ctx.out(), "{}", "unsupported"sv);
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    }
};

///
/// formatter for ast::based_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::based_literal> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <ast::based_literal>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::based_literal based, FmtContext& ctx) const
    {
        using namespace ibis::vhdl;
        using numeric_type_specifier = ast::based_literal::numeric_type_specifier;
        using numeric_base_specifier = ast::based_literal::numeric_base_specifier;

        // ToDo: Let the parser grammar the AST node fill in
        // *Attention* assignment is locally only!
        based.base_specifier = ast::convert_to<numeric_base_specifier>(based.base_id);

        // clang-format off
        switch (based.number.type_specifier) {
            using enum ast::based_literal::numeric_type_specifier;
            case integer:
                return std::format_to(ctx.out(), "{}#{}#{}",
                                      based.base_specifier,       // --
                                      based.number.integer_part,  // --
                                      based.number.exponent);
                break;
            case real:
                return std::format_to(ctx.out(), "{}#{}.{}#{}",
                                      based.base_specifier,  // --
                                      based.number.integer_part,
                                      based.number.fractional_part,  // --
                                      based.number.exponent);
                break;
            [[unlikely]] case unspecified:
                // probably an unintentionally constructed enum by default
                cxx_bug_fatal("based literal numeric_type *unspecified*!");
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    }
};

///
/// formatter for ast::decimal_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::decimal_literal> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <ast::decimal_literal>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::decimal_literal decimal, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", decimal.literal);
    }
};

///
/// formatter for ast::string_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::string_literal> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        for (auto it = begin(ctx); it != end(ctx); ++it) {
            if (std::string_view{ ctx }.starts_with(raw_spec)) {
                raw_format = true;
                ctx.advance_to(begin(ctx) + raw_spec.size());
            }
            if (*it == '}') {
                return it;
            }
        }
        throw std::format_error("invalid format specification for <ast::string_literal>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::string_literal string, FmtContext& ctx) const
    {
        if (raw_format) [[unlikely]] /* rarely used, only for debugging purpose */ {
            return std::format_to(ctx.out(), "{}", string.literal);
        }

        // ToDo: Find a better way to unquote, not robust in all cases (maybe Boost.Parser?)
        /* from clack channel:
            prev_quote is just:
            % -> the second % is then cancelled, and prev_quote is assigned to \0;
            repeat 1;
            %, nothing to read

            Then it's %%% inserted into the context. If you want only a single % to output, you're
            not supposed to assign prev_quote to \0 when quit, or do some loop inside the lambda.
        */
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

        for (auto const chr : string.literal) {
            if (unquote(chr)) {
                std::format_to(ctx.out(), "{}", chr);
            }
        }

        return ctx.out();
    }

private:
    static constexpr std::string_view raw_spec{ "raw" };
    bool raw_format = false;
};

///
/// formatter for ast::operator_token
///
template <>
struct std::formatter<ibis::vhdl::ast::operator_token> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <ast::operator_token>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::operator_token token, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", as_sv(token));
    }

private:
    static std::string_view as_sv(ibis::vhdl::ast::operator_token token);
};

///
/// formatter for ast::keyword_token
///
template <>
struct std::formatter<ibis::vhdl::ast::keyword_token> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <ast::keyword_token>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::ast::keyword_token token, FmtContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", as_sv(token));
    }

private:
    static std::string_view as_sv(ibis::vhdl::ast::keyword_token token);
};

///
/// ostream operators required for BOOST_SPIRIT_X3_DEBUG
///
namespace ibis::vhdl::ast {

inline std::ostream& operator<<(std::ostream& os,
                                bit_string_literal::numeric_base_specifier specifier)
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
