//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/concepts.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/type.hpp>

#include <cstdint>
#include <tuple>
#include <variant>

namespace ibis::vhdl::ast {
// AST node forward
struct based_literal;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl {
template <typename IteratorT>
class diagnostic_handler;
}

namespace ibis::vhdl::ast {

///
/// @brief Convert based literal to numeric.
///
/// BNF
/// @code{.bnf}
/// base # based_integer [ . based_integer ] # [ exponent ]
/// @endcode
///
/// @note IEEE1076-93 Ch. 13.4 specifies:
/// - exponent is in decimal notation
/// - specifies based decimal literal must not have negative sign for the exponent.
///
/// @tparam IntegerT The integer type of the numeric converted into.
///
/// @tparam RealT The real type of the numeric converted into.
///
template <ibis::integer IntegerT, ibis::real RealT>
class convert_based {
public:
    using integer_type = IntegerT;
    using real_type = RealT;

    /// Result type is variant, since based literal can be of type integer or real.
    using result_type = std::variant<integer_type, real_type>;

    ///
    /// Return a tuple with the converted value and a boolean flag of
    /// success/failure of converting. If False, the parsing process on the AST
    /// node's literal string may be failed (means the top level VHDL parser
    /// wasn't strict enough -> bug), or numeric problems rises (e.g. the numeric
    /// literal can fit the target_type).
    using return_type = std::tuple<bool, result_type>;

    /// diagnostic/error handler used for error reporting
    using diagnostic_handler_type = ibis::vhdl::diagnostic_handler<parser::iterator_type>;

    ///
    /// Construct a new numeric convert object.
    ///
    /// @param diag_handler Error reporter.
    ///
    explicit convert_based(diagnostic_handler_type& diag_handler);

    ///
    /// Convert the a bit string literal to numeric value.
    ///
    /// @param node AST literal node
    /// @return return_type The converted value
    return_type operator()(ast::based_literal const& node) const;

private:
    /// Parse the integer part of based literal.
    std::tuple<bool, integer_type> parse_integer(unsigned base,
                                                 ast::based_literal const& literal) const;

    /// Parse the fractional part of based literal.
    std::tuple<bool, double> parse_fractional(unsigned base,
                                              ast::based_literal const& literal) const;

    /// parses the exponent of based literals
    /// @note IEEE1076-93 Ch. 13.4 specifies:
    /// - "The base and the exponent, if any, are in decimal notation."
    /// - "An exponent for a based integer literal must not have a minus sign."; but, examples
    ///   show: `16#F.FF#E+2`
    std::tuple<bool, std::int32_t> parse_exponent(ast::based_literal const& literal) const;

    /// parse the the `ast::based_literal` as real with base of 10.
    std::tuple<bool, double> parse_real10(ast::based_literal const& literal) const;

private:
    diagnostic_handler_type& diagnostic_handler;

private:
    /// The BNF name of the literal to convert, '\0' terminated
    static constexpr char const* node_name{ "based literal" };  // NOLINT(hicpp-avoid-c-arrays)
};

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

/// Explicit template instantiation declaration
extern template class convert_based<intrinsic::unsigned_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
