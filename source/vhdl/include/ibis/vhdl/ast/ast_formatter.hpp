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
#include <memory_resource>
#include <array>

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

// ToDo [Clang] This code doesn't compile with Clang/libc++ v18, but v19 is OK, see
// https://godbolt.org/z/rc1sszThT

namespace ibis::vhdl::ast::detail {

///
/// upstream polymorphic allocator used for formatting
///
/// @note Concept using std::pmr [coliru](https://coliru.stacked-crooked.com/a/f01afbac75d7723c)
/// @see [Special Allocators with C++17](
///       https://www.modernescpp.com/index.php/special-allocators-with-c17/)
template <bool verbose = false>
class TrackingAllocator : public std::pmr::memory_resource {
public:
    constexpr TrackingAllocator(std::string_view name_ = std::string_view{ "N/A" })
        : name{ name_ }
    {
    }

    void* do_allocate(std::size_t bytes, std::size_t alignment) override
    {
        void* ptr = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        if constexpr (verbose) {
            std::cout << std::format("  pmr::allocate {:6} bytes at {} ({})\n", bytes, ptr, name);
        }
        return ptr;
    }

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override
    {
        if constexpr (verbose) {
            std::cout << std::format("  pmr::deallocate {:4} bytes at {} ({})\n", bytes, ptr, name);
        }
        return std::pmr::new_delete_resource()->deallocate(ptr, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
    {
        return std::pmr::new_delete_resource()->is_equal(other);
    }

private:
    std::string_view const name;
};

}  // namespace ibis::vhdl::ast::detail

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
struct std::formatter<ibis::vhdl::ast::bit_string_literal::numeric_base_specifier>
    : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::bit_string_literal::numeric_base_specifier specifier,
                std::format_context& ctx) const
    {
        using numeric_base_specifier = ibis::vhdl::ast::bit_string_literal::numeric_base_specifier;
        using namespace std::literals::string_view_literals;

        // clang-format off
        switch (specifier) {
            case numeric_base_specifier::base2:
                return std::formatter<std::string_view>::format("b"sv, ctx);
            case numeric_base_specifier::base8:
                return std::formatter<std::string_view>::format("o"sv, ctx);
            case numeric_base_specifier::base16:
                return std::formatter<std::string_view>::format("x"sv, ctx);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case numeric_base_specifier::unspecified:
                return std::formatter<std::string_view>::format("unspecified"sv, ctx);
            // be graceful, definitely wrong enum - the caller has not worked out properly
            [[unlikely]] case numeric_base_specifier::unsupported:
                return std::formatter<std::string_view>::format("unsupported"sv, ctx);
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
struct std::formatter<ibis::vhdl::ast::bit_string_literal> : std::formatter<string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::bit_string_literal const& bit_string,
                std::format_context& ctx) const
    {
        using namespace ibis::vhdl;

        ast::detail::TrackingAllocator<true> upstream_allocator{ "'bit_string_literal' formatter" };

        static constexpr std::size_t BUF_SIZE{
            // optimistic 'worst case' for 32-bit considered
            std::string_view{ "1111_1111_1111_1111_1111_1111_1111_1111" }.size()
        };

        std::array<string_view::value_type, BUF_SIZE> buf;
        std::pmr::monotonic_buffer_resource pool{ buf.data(), buf.size(), &upstream_allocator };
        std::pmr::string temp_literal{ &pool };

        std::format_to(std::back_inserter(temp_literal), "{}{}", bit_string.base_specifier,
                       bit_string.literal);

        return std::formatter<string_view>::format(temp_literal, ctx);
    }
};

///
/// formatter for ast::based_literal::numeric_type_specifier enumerator
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

        // clang-format off
        switch (specifier) {
            case numeric_type_specifier::integer:
                return std::formatter<std::string_view>::format("integer"sv, ctx);
            case numeric_type_specifier::real:
                return std::formatter<std::string_view>::format("real"sv, ctx);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case numeric_type_specifier::unspecified:
                return std::formatter<std::string_view>::format("unspecified"sv, ctx);
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
struct std::formatter<ibis::vhdl::ast::based_literal::numeric_base_specifier>
    : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::based_literal::numeric_base_specifier specifier,
                std::format_context& ctx) const
    {
        using namespace ibis::vhdl;
        using numeric_base_specifier = ast::based_literal::numeric_base_specifier;
        using namespace std::literals::string_view_literals;

        // clang-format off
        switch (specifier) {
            case numeric_base_specifier::base2:
                return std::formatter<std::string_view>::format("2"sv, ctx);
            case numeric_base_specifier::base8:
                return std::formatter<std::string_view>::format("8"sv, ctx);
            case numeric_base_specifier::base10:
                return std::formatter<std::string_view>::format("10"sv, ctx);
            case numeric_base_specifier::base16:
                return std::formatter<std::string_view>::format("16"sv, ctx);
            // be graceful, probably an unintentionally constructed enum by default
            [[unlikely]] case numeric_base_specifier::unspecified:
                return std::formatter<std::string_view>::format("unspecified"sv, ctx);
            // be graceful, definitely wrong enum - the caller has not worked out properly
            [[unlikely]] case numeric_base_specifier::unsupported:
                return std::formatter<std::string_view>::format("unsupported"sv, ctx);
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
struct std::formatter<ibis::vhdl::ast::based_literal> : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::based_literal based, std::format_context& ctx) const
    {
        using namespace ibis::vhdl;
        using numeric_type_specifier = ast::based_literal::numeric_type_specifier;
        using numeric_base_specifier = ast::based_literal::numeric_base_specifier;

        // ToDo: Let the parser grammar the AST node fill in
        // *Attention* assignment is locally only!
        based.base_specifier = ast::convert_to<numeric_base_specifier>(based.base_id);

        ast::detail::TrackingAllocator<true> upstream_allocator{ "'based_literal' formatter" };

        static constexpr std::size_t BUF_SIZE{
            // optimistic 'worst case' for 32-bit considered
            std::string_view{ "10#4_294_967_295.4_294_967_295#+E1024" }.size()
        };

        std::array<string_view::value_type, BUF_SIZE> buf;
        std::pmr::monotonic_buffer_resource pool{ buf.data(), buf.size(), &upstream_allocator };
        std::pmr::string temp_literal{ &pool };

        if (based.number.type_specifier == numeric_type_specifier::integer) {
            std::format_to(std::back_inserter(temp_literal), "{}#{}#{}",
                           based.base_specifier,       // --
                           based.number.integer_part,  // --
                           based.number.exponent);
        }
        else {
            std::format_to(std::back_inserter(temp_literal), "{}#{}.{}#{}",
                           based.base_specifier,                                     // --
                           based.number.integer_part, based.number.fractional_part,  // --
                           based.number.exponent);
        }

        return std::formatter<string_view>::format(temp_literal, ctx);
    }
};

///
/// formatter for ast::decimal_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::decimal_literal> : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    auto format(ibis::vhdl::ast::decimal_literal decimal, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(std::string_view{ decimal.literal }, ctx);
    }
};

///
/// formatter for ast::string_literal
///
template <>
struct std::formatter<ibis::vhdl::ast::string_literal> : std::formatter<std::string_view> {
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    constexpr auto parse(std::format_parse_context& ctx)
    {
        for (auto it = begin(ctx); it != end(ctx); ++it) {
            if (std::string_view{ ctx }.starts_with(raw_spec)) {
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
            return std::formatter<std::string_view>::format(std::string_view{ string.literal },
                                                            ctx);
        }

        using namespace ibis::vhdl;

        ast::detail::TrackingAllocator<true> upstream_allocator{ "'string_literal' formatter" };

        // simple buffer size estimation
        static constexpr std::size_t BUF_SIZE{ 64 };

        std::array<string_view::value_type, BUF_SIZE> buf;
        std::pmr::monotonic_buffer_resource pool{ buf.data(), buf.size(), &upstream_allocator };
        std::pmr::string temp_literal{ &pool };

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
                std::format_to(std::back_inserter(temp_literal), "{}", chr);
            }
        }

        return std::formatter<std::string_view>::format(temp_literal, ctx);
    }

private:
    static constexpr std::string_view raw_spec{ "raw" };
    bool raw_format = false;
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
