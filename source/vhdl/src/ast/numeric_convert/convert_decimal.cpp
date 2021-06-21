#include <ibis/vhdl/ast/numeric_convert/convert_decimal.hpp>
#include <ibis/vhdl/ast/numeric_convert/filter_range.hpp>
#include <ibis/vhdl/ast/numeric_convert/dbg_trace.hpp>

#include <ibis/vhdl/error_handler.hpp>

#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

#include <ibis/vhdl/ast/literal_printer.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>
#include <ibis/compiler/compiler_support.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

// IWYU replaces a lot of other header, we stay with this one
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

namespace /* anonymous */ {

namespace x3 = boost::spirit::x3;

template <typename T, typename IteratorT = ibis::vhdl::parser::iterator_type>
auto const as = [](auto p) { return x3::any_parser<IteratorT, T>{ x3::as_parser(p) }; };

using namespace std::literals;
auto const literal_name = "decimal literal"sv;

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

template <typename IntegerT, typename RealT>
convert_decimal<IntegerT, RealT>::convert_decimal(error_handler_type& error_handler_)
    : report_error{ error_handler_ }
{
}

template <typename IntegerT, typename RealT>
typename convert_decimal<IntegerT, RealT>::return_type convert_decimal<IntegerT, RealT>::operator()(
    ast::decimal_literal const& node) const
{
    auto const parse = [&](ast::decimal_literal::numeric_type_specifier type_specifier,
                           auto const& literal) {
        using numeric_type_specifier = ast::decimal_literal::numeric_type_specifier;

        switch (type_specifier) {
            case numeric_type_specifier::integer: {
                auto const [parse_ok, attribute] = parse_integer(literal);
                return std::tuple{ parse_ok, result_type(attribute) };
            }
            case numeric_type_specifier::real: {
                auto const [parse_ok, attribute] = parse_real(literal);
                return std::tuple{ parse_ok, result_type(attribute) };
            }
            default:  // cxx_unreachable_bug
                cxx_unreachable_bug_triggered();
        }
    };

    return parse(node.type_specifier, node.literal);
}

template <typename IntegerT, typename RealT>
std::tuple<bool, typename convert_decimal<IntegerT, RealT>::integer_type>
convert_decimal<IntegerT, RealT>::parse_integer(ast::string_span const& literal) const
{
    using boost::locale::format;
    using boost::locale::translate;

    auto const parser = [](auto iter_t) {
        using iterator_type = decltype(iter_t);
        using parser_type = x3::real_parser<integer_type, integer_policies<integer_type>>;

        parser_type const parse_int = parser_type{};
        return as<integer_type, iterator_type>(parse_int);
    };

    auto const range_f = numeric_convert::detail::filter_range(literal);
    auto iter = std::cbegin(range_f);
    auto const end = std::cend(range_f);

    integer_type attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(iter) >> x3::eoi, attribute);

    if constexpr ((false)) {
        dbg_trace(literal, range_f, parse_ok, attribute);
    }

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        report_error(        // --
            literal.begin(),  // --
            (format(translate("in {1} the integer number can't fit the numeric type")) %
             literal_name)
                .str());
        return std::tuple{ false, 0 };
    }

    return std::tuple{ parse_ok, attribute };
}

template <typename IntegerT, typename RealT>
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

    auto const range_f = numeric_convert::detail::filter_range(literal);
    auto iter = std::cbegin(range_f);
    auto const end = std::cend(range_f);

    real_type attribute = 0;
    bool const parse_ok = x3::parse(iter, end, parser(iter) >> x3::eoi, attribute);

    if constexpr ((false)) {
        dbg_trace(literal, range_f, parse_ok, attribute);
    }

    if (!parse_ok) {
        // parse failed - can't fit the target_type, iter is rewind to begin.
        report_error(        // --
            literal.begin(),  // --
            (format(translate("in {1} the real number can't fit the numeric type")) % literal_name)
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

template class convert_decimal<intrinsic::signed_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
