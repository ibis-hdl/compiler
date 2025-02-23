//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_bit_string.hpp>

#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/numeric_convert/detail/convert_util.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/util/numeric_base_specifier.hpp>
// #include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/type.hpp>
#include <ibis/concepts.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
#include <boost/spirit/home/x3/auxiliary/eoi.hpp>
#include <boost/spirit/home/x3/core/parse.hpp>
#include <boost/spirit/home/x3/core/parser.hpp>
#include <boost/spirit/home/x3/operator/sequence.hpp>

#include <range/v3/iterator/basic_iterator.hpp>
#include <range/v3/view/view.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <iterator>
#include <string_view>
#include <string>
#include <utility>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::ast {

template <ibis::integer IntegerT>
convert_bit_string<IntegerT>::convert_bit_string(diagnostic_handler_type& diagnostic_handler_)
    : diagnostic_handler{ diagnostic_handler_ }
{
}

template <ibis::integer IntegerT>
typename convert_bit_string<IntegerT>::return_type convert_bit_string<IntegerT>::operator()(
    ast::bit_string_literal const& node) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const parse = [&](ast::bit_string_literal::numeric_base_specifier base,
                           auto const& literal) {
        using numeric_base_specifier = ast::bit_string_literal::numeric_base_specifier;
        // select the concrete x3::uint-parser<> using the base_specifier
        auto const uint_parser = [](numeric_base_specifier base_spec, auto iter_t) {
            using numeric_base_specifier = ast::bit_string_literal::numeric_base_specifier;
            using iterator_type = decltype(iter_t);

            // clang-format off
            switch (base_spec) {
                case numeric_base_specifier::base2: 
                    return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base2);
                case numeric_base_specifier::base8: 
                    return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base8);
                case numeric_base_specifier::base16: 
                    return detail::uint_parser<iterator_type, integer_type>::base(ast::numeric_base_specifier::base16);
                // definitely wrong enum, the caller has not worked out properly
                [[unlikely]] case numeric_base_specifier::unspecified: [[fallthrough]];
                [[unlikely]] case numeric_base_specifier::unsupported:
                    cxx_bug_fatal("unspecified or unsupported numeric base type for bit string");
                //
                // *No* default branch: let the compiler generate warning about enumeration
                // value not handled in switch
                //
            }
            // clang-format on

            std::unreachable();
        };

        auto range_f = numeric_convert::detail::filter_range(literal);
        auto iter = std::begin(range_f);
        auto const end = std::end(range_f);

        integer_type attribute = 0;

        bool const parse_ok = x3::parse(iter, end, uint_parser(base, iter) >> x3::eoi, attribute);

        //  intentionally disabled
        if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
            dbg_trace(literal, range_f, parse_ok, attribute);
        }

        if (!parse_ok) {
            static constexpr std::string_view const literal_name{ "bit string literal" };
            // parse failed - can't fit the integer_type, iter is rewind to begin.
            diagnostic_handler.parser_error(  // --
                node.literal.begin(),         // --
                (format(translate("in {1} the integer number can't fit the numeric type")) %
                 literal_name)
                    .str());
            std::tuple{ false, 0 };
        }

        return std::tuple{ parse_ok, attribute };
    };

    return parse(node.base_specifier, node.literal);
}

}  // namespace ibis::vhdl::ast

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::ast {

template class convert_bit_string<intrinsic::unsigned_integer_type>;

}  // namespace ibis::vhdl::ast
