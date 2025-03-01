//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert/convert_decimal.hpp>

#include <ibis/concepts.hpp>
#include <ibis/vhdl/ast/node/decimal_literal.hpp>
// #include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/type.hpp>  // for explicit instanciation

#include <ibis/util/cxx_bug_fatal.hpp>

#include <boost/range/iterator_range_core.hpp>  // for iterator_range

#include <boost/spirit/home/x3.hpp>                        // IWYU pragma: keep
#include <boost/spirit/home/x3/auxiliary/any_parser.hpp>   // for any_parser
#include <boost/spirit/home/x3/auxiliary/eoi.hpp>          // for eoi_parser, eoi
#include <boost/spirit/home/x3/core/parse.hpp>             // for parse
#include <boost/spirit/home/x3/core/parser.hpp>            // for as_parser
#include <boost/spirit/home/x3/numeric/real.hpp>           // for real_parser
#include <boost/spirit/home/x3/numeric/real_policies.hpp>  // for ureal_policies
#include <boost/spirit/home/x3/operator/sequence.hpp>      // for sequence, operator>>

#include <range/v3/functional/invoke.hpp>        // for invoke_result_t
#include <range/v3/iterator/basic_iterator.hpp>  // for operator==, operator!=, basic_iterator
#include <range/v3/view/all.hpp>                 // for all_t
#include <range/v3/view/facade.hpp>              // for facade_iterator_t
#include <range/v3/view/view.hpp>                // for operator|

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <iterator>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

namespace /* anonymous */ {

namespace x3 = boost::spirit::x3;

// FixMe get rid of this, used to create integer|real parser at parse_real|parse_integer
template <typename T, typename IteratorT = ibis::vhdl::parser::iterator_type>
auto const as = [](auto derived_parser) {
    return x3::any_parser<IteratorT, T>{ x3::as_parser(derived_parser) };
};

std::string_view const literal_name = "decimal literal";

}  // namespace

namespace ibis::vhdl::ast {

template <typename T>
struct integer_policies : x3::ureal_policies<T> {
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

template <typename T>
struct real_policies : x3::ureal_policies<T> {
    static bool const allow_leading_dot = false;
    static bool const allow_trailing_dot = false;
    static bool const expect_dot = false;
};

template <ibis::integer IntegerT, ibis::real RealT>
convert_decimal<IntegerT, RealT>::convert_decimal(diagnostic_handler_type& diag_handler)
    : diagnostic_handler{ diag_handler }
{
}

template <ibis::integer IntegerT, ibis::real RealT>
typename convert_decimal<IntegerT, RealT>::return_type convert_decimal<IntegerT, RealT>::operator()(
    ast::decimal_literal const& node) const
{
    using numeric_type_specifier = ast::decimal_literal::numeric_type_specifier;

    // ToDo document the intend, result_type -> variant<IntegerT, RealT>> , explain x3 policies
    auto const parse = [&](numeric_type_specifier type_specifier, auto const& literal) {
        // clang-format off
        switch (type_specifier) {
            using enum ast::decimal_literal::numeric_type_specifier;
            case integer: 
            {
                auto const [parse_ok, attribute] = parse_integer(literal);
                // FixMe static_assert(std::is_same_v<decltype(attribute), integer_type>);
                return return_type{ parse_ok, result_type(attribute) };
            }
            case real: 
            {
                auto const [parse_ok, attribute] = parse_real(literal);
                // FixMe static_assert(std::is_same_v<decltype(attribute), real_type>);
                return return_type{ parse_ok, result_type(attribute) };
            }
            [[unlikely]] case unspecified:
                cxx_bug_fatal("caller must pass checked base_specifier");
            //
            // *No* default branch: let the compiler generate warning about enumeration
            // value not handled in switch
            //
        }
        // clang-format on

        std::unreachable();
    };

    return parse(node.type_specifier, node.literal);
}

template <ibis::integer IntegerT, ibis::real RealT>
std::tuple<bool, typename convert_decimal<IntegerT, RealT>::integer_type>
convert_decimal<IntegerT, RealT>::parse_integer(ast::string_span const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    // really any_parser required??
    auto const parser = [](auto iter_t) {
        using iterator_type = decltype(iter_t);
        using parser_type = x3::real_parser<integer_type, integer_policies<integer_type>>;

        parser_type const parse_int = parser_type{};
        return as<integer_type, iterator_type>(parse_int);
    };

    auto range_f = numeric_convert::detail::filter_range(literal);
    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    integer_type attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(iter) >> x3::eoi, attribute);

    // intentionally disabled
    if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
        dbg_trace(literal, range_f, parse_ok, attribute);
    }

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        diagnostic_handler.parser_error(                                                // --
            literal.begin(),                                                            // --
            (format(translate("in {1} the integer number can't fit the numeric type"))  // --
             % literal_name)
                .str());
        return std::tuple{ false, 0 };
    }

    return std::tuple{ parse_ok, attribute };
}

template <ibis::integer IntegerT, ibis::real RealT>
std::tuple<bool, typename convert_decimal<IntegerT, RealT>::real_type>
convert_decimal<IntegerT, RealT>::parse_real(ast::string_span const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const parser = [](auto iter_t) {
        using iterator_type = decltype(iter_t);
        using parser_type = x3::real_parser<real_type, real_policies<real_type>>;

        parser_type const parse_real = parser_type{};
        return as<real_type, iterator_type>(parse_real);
    };

    auto range_f = numeric_convert::detail::filter_range(literal);
    auto iter = std::begin(range_f);
    auto const end = std::end(range_f);

    real_type attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(iter) >> x3::eoi, attribute);

    // intentionally disabled
    if constexpr ((false)) {  // NOLINT(readability-simplify-boolean-expr)
        dbg_trace(literal, range_f, parse_ok, attribute);
    }

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        diagnostic_handler.parser_error(                                             // --
            literal.begin(),                                                         // --
            (format(translate("in {1} the real number can't fit the numeric type"))  // --
             % literal_name)
                .str());
        return std::tuple{ false, 0 };
    }

    return std::tuple{ parse_ok, attribute };
}

}  // namespace ibis::vhdl::ast

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::ast {

template class convert_decimal<intrinsic::unsigned_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
