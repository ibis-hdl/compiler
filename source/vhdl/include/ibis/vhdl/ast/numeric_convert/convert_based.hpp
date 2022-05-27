#pragma once

#include <ibis/vhdl/type.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <tuple>
#include <variant>
#include <iosfwd>
#include <numeric>
#include <limits>
#include <variant>
#include <type_traits>

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
/// @tparam IntegerT The integer type of the numeric converted into.
/// @tparam RealT The real type of the numeric converted into.
///
template <typename IntegerT, typename RealT>
class convert_based {
    static_assert(std::numeric_limits<IntegerT>::is_integer,  // --
                  "TagetType must be of type integer");

    static_assert(std::numeric_limits<RealT>::is_iec559,  // --
                  "TagetType must be IEC 559 (IEEE 754) real/float");

public:
    using integer_type = typename std::make_unsigned<IntegerT>::type;
    using real_type = RealT;

    using result_type = std::variant<integer_type, real_type>;

    ///
    /// Return a tuple with the converted value and a boolean flag of
    /// success/failure of converting. If False, the parsing process on the AST
    /// node's literal string may be failed (means the top level VHDL parser
    /// wasn't strict enough -> bug), or numeric problems rises (e.g. the numeric
    /// literal can fit the target_type).
    using return_type = std::tuple<bool, result_type>;

    /// error handler used for error reporting
    using diagnostic_handler_type = ibis::vhdl::diagnostic_handler<parser::iterator_type>;

    ///
    /// Construct a new numeric convert object.
    ///
    /// @param diagnostic_handler_ Error reporter.
    ///
    convert_based(diagnostic_handler_type& diagnostic_handler_);

    ///
    /// Convert the a bit string literal to numeric value.
    ///
    /// @param node AST literal node
    /// @return return_type The converted value
    return_type operator()(ast::based_literal const& node) const;

private:
    /// LRM93 13.4.2: "The base and the exponent, if any, are in decimal notation."
    std::tuple<bool, std::uint32_t> parse_base(ast::based_literal const& literal) const;

    std::tuple<bool, std::uint64_t> parse_integer(unsigned base,
                                                  ast::based_literal const& literal) const;

    std::tuple<bool, double> parse_fractional(unsigned base,
                                              ast::based_literal const& literal) const;

    /// LRM93 13.4.2: "The base and the exponent, if any, are in decimal notation."
    std::tuple<bool, std::int32_t> parse_exponent(ast::based_literal const& literal) const;

    std::tuple<bool, double> parse_real10(ast::based_literal const& literal) const;

    bool supported_base(unsigned base) const;

private:
    diagnostic_handler_type& diagnostic_handler;
};

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

/// Explicit template instantiation declaration
extern template class convert_based<intrinsic::signed_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
