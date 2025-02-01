//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/source_location.hpp>
#include <ibis/vhdl/diagnostic_context.hpp>
#include <ibis/util/const_value.hpp>
#include <ibis/util/cxx_bug_fatal.hpp>

#include <format>
#include <string>
#include <string_view>
#include <cassert>

namespace ibis::vhdl {

using ibis::util::const_value;

///
/// @brief Gutter with number, intended to be used with line numbers
/// for proof of concept @see https://godbolt.org/z/ca7ejMjMz
///
struct number_gutter {
    const_value<std::size_t> number{ 0 };
};

///
/// @brief Wrapper for spacer
/// for proof of concept @see https://coliru.stacked-crooked.com/a/15fe1a8b1c2d6991
///
struct spacer {
    constexpr spacer() = default;
    constexpr spacer(std::size_t const width_, std::string_view chr_sv = " ")
        : width{ width_ }
        , chr{ chr_sv.front() }
    {
        // FixMe no way for static_assert?
        assert(chr_sv.size() == 1 && "spacer accept only single char string!");
    }

    const_value<std::size_t> width{ 0 };
    const_value<char> chr{ ' ' };
};

///
/// @brief Wrapper for failure/issue indication as single location or range.
/// If there is an optional @arg last argument, there is a range to be markup, otherwise single
/// issue point at @arg first is to emphasize.
///
template <typename IteratorT>
struct issue_range {
    using difference_type = typename std::iterator_traits<IteratorT>::difference_type;

    constexpr issue_range(IteratorT begin, std::optional<IteratorT> end)
        : iter{ begin }
        , distance{ [&]() -> difference_type {
            if (end.has_value()) return std::distance(begin, end.value());
            return 0;
        }() }
    {
        // Can be disabled on Release build, no static_assert possible
        assert(!(distance < 0) && "unexpected order of iterators, end() comes before begin()");
    }

    // iterator to begin of issue
    IteratorT position() const { return iter; }

    // issue width, equals to 0 if no range available
    std::size_t width() const { return static_cast<std::size_t>(distance); }

private:
    IteratorT iter;
    difference_type distance;
};

/// @brief Wrapper for issue locator/indicator
/// @tparam IteratorT
template <typename IteratorT = std::string_view::iterator>
struct issue_marker {
    constexpr issue_marker(IteratorT start_, IteratorT failure_begin,
                           std::optional<IteratorT> failure_end)
        : start{ start_ }
        , failure{ failure_begin, failure_end }
    {
    }
    // const_value impl, see https://godbolt.org/z/7Yf8n4ojs
    IteratorT const start;
    issue_range<IteratorT> const failure;
};

}  // namespace ibis::vhdl

template <>
struct std::formatter<ibis::vhdl::source_location> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <vhdl::source_location>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::source_location const& location, FmtContext& ctx) const
    {
        std::string temp;
        temp.reserve(256);  // inital guess

        // Based on GNU standard of [Formatting Error Messages](
        // https://www.gnu.org/prep/standards/html_node/Errors.html)
        return std::format_to(ctx.out(), "{}:{}:{}",  // --
                              location.file_name(),   // --
                              location.line(),        // --
                              location.column()       // --
        );
    }
};

template <>
struct std::formatter<ibis::vhdl::diagnostic_context::failure_type> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error(
            "non-empty format specification for <vhdl::diagnostic_context::failure_type>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::diagnostic_context::failure_type failure, FmtContext& ctx) const
    {
        using namespace ibis::vhdl;
        using boost::locale::translate;

        auto const as_str = [](auto failure) {
            using enum ibis::vhdl::diagnostic_context::failure_type;
            // clang-format off
            switch (failure) {
                case unspecific:
                    return translate("unspecific").str();
                case parser:
                    return translate("parse error").str();
                case syntax:
                    return translate("syntax error").str();
                case semantic:
                    return translate("semantic error").str();
                case numeric:
                    return translate("numeric error").str();
                case not_supported:
                    return translate("unsupported").str();
                // *No* default branch: let the compiler generate warning about enumeration
                // value not handled in switch
            }
            // clang-format on

            std::unreachable();
        };

        return std::format_to(ctx.out(), "{}", as_str(failure));
    }
};

template <>
struct std::formatter<ibis::vhdl::number_gutter> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <vhdl::number_gutter>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::number_gutter gutter, FmtContext& ctx) const
    {
        static constexpr std::string_view default_fmt{ "{:>{}} " };
        static constexpr std::string_view merciful_fmt{ "{:>{}}" };

        // ToDo [C++26] fixed-size static array for empty gutter, not constexpr - neither
        // format_to_n() nor format() are constexpr in C++23
        auto const void_gutter = [&]() {
            // *Note* array isn't '\0' terminated, hence intended to be used with string_view only!!
            static std::array<std::string_view::value_type, BUF_SZ - 1> const buf = [&]() {
                std::array<std::string_view::value_type, BUF_SZ - 1> buf{};
                std::ignore =
                    std::format_to_n(std::begin(buf), BUF_SZ - 1, default_fmt, "", number_width);
                return buf;
            }();
            return std::string_view{ buf };
        };

        if (gutter.number == 0UL) {
            // empty gutter without line number to align e.g. error/warning locator
            return std::format_to(ctx.out(), "{}", void_gutter());
        }

        if (gutter.number < number_limit) {
            return std::format_to(ctx.out(), default_fmt, gutter.number.get(), number_width);
        }

        // Use a forgiving format to output numbers that are larger than the number_limit digit
        // with, even if it doesn't look as pretty and subsequent elements are out of balance.
        return std::format_to(ctx.out(), merciful_fmt, gutter.number.get(), number_width);
    }

private:
    // pow(base, exp) using C++23 deducing this; for proof of concept
    // @see https://coliru.stacked-crooked.com/a/9ff087b87abb54fc
    static constexpr auto pow = [](this auto const& self, unsigned b,
                                   unsigned e) constexpr -> unsigned {
        return (e == 0) ? 1u : b * self(b, e - 1);
    };

private:
    // up to 9'999 line numbers w/o problems
    static constexpr std::size_t const number_width{ 4 };
    // buffer size for void gutter template, MSVC `strlen` not constexpr???
    // ToDo ... = number_width + strlen(" ") + 1;
    static constexpr std::size_t const BUF_SZ = number_width + std::string_view{ " " }.size() + 1;
    // limit to squeeze some more numbers out of the space/format
    static auto constexpr number_limit = pow(10, number_width);
};

template <>
struct std::formatter<ibis::vhdl::spacer> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <vhdl::spacer>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::spacer spacer_, FmtContext& ctx) const
    {
        if (spacer_.width == 0UL) {
            // format_to() will fail at runtime otherwise
            return ctx.out();
        }
        // ToDo [C++26] format() isn't completely constexpr, hence we'll use vformat_to()!
        return std::vformat_to(ctx.out(),  // C++26 std::runtime_format()
                               std::format("{{:{}>{}}}", spacer_.chr.get(), spacer_.width.get()),
                               std::make_format_args(""));
    }
};

template <typename IteratorT>
struct std::formatter<ibis::vhdl::issue_range<IteratorT>> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <vhdl::issue_range>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::issue_range<IteratorT> issue, FmtContext& ctx) const
    {
        using ibis::vhdl::spacer;

        if (issue.width() == 0) {
            return std::format_to(ctx.out(), "{}", locator_symbol);
        }

        return std::format_to(ctx.out(), "{}", spacer{ issue.width(), squiggle_symbol });
    }

private:
    static constexpr std::string_view locator_symbol{ "^" };
    static constexpr std::string_view squiggle_symbol{ "~" };
};

template <typename IteratorT>
struct std::formatter<ibis::vhdl::issue_marker<IteratorT>> {
    template <class ParseContext>
    static constexpr auto parse(ParseContext& ctx)
    {
        if (auto const begin = ctx.begin(); begin == ctx.end() || *begin == '}') {
            return begin;
        }
        throw std::format_error("non-empty format specification for <vhdl::issue_marker>");
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    template <class FmtContext>
    auto format(ibis::vhdl::issue_marker<IteratorT> const& issue, FmtContext& ctx) const
    {
        using ibis::vhdl::spacer;

        // left margin/offset to issue marker begin
        auto const distance = std::distance(issue.start, issue.failure.position());
        cxx_assert(!(distance < 0), "unexpected order of iterators, end() comes before begin()");
        std::size_t const width = static_cast<std::size_t>(distance);

        return std::format_to(ctx.out(), "{}{}", spacer{ width }, issue.failure);
    }
};
