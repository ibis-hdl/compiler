/*
 * numeric_convert.hpp
 *
 *  Created on: 26.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_NUMERIC_CONVERT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_NUMERIC_CONVERT_HPP_

#include <iosfwd>
#include <tuple>

#include <eda/vhdl/ast_fwd.hpp>

namespace eda {
namespace vhdl {
namespace ast {

/**
 * Convert the numeric literals to numeric types
 *
 * Note #1: About numeric literals
 * ----------------------------------
 * The correct tagged kind_type of {based, decimal}_literal is elementary on
 * elaboration time, since after converting to numeric the informations about
 * the integer/real string are lost, see concrete why it's important e.g.
 * [vhdl error: integer literal cannot have negative exponent](
 * https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent)
 *
 * Strong rules here on parser level simplifies simplifies numeric conversion
 * since more sloppy rules can be used for conversion from literals to concrete
 * intrinsic types.
 *
 * Note #2:
 * --------
 * VDL decimal literals does allow exponents on integers, to simplify evaluating
 * a x3 real parser with policies is used. The correct 2nd pass parsing and hence
 * correct converting depends on correct parsing of the VHDL grammar, since the
 * exponent of integer doesn't allow a negative sign.
 */
class numeric_convert {
public:
    /**
     * The type, to which all literals will be converted. */
    using value_type = double;

    /**
     * Return a tuple with the converted value and a boolean flag of
     * success/failure of converting. If False, the parsing process on the AST
     * node's literal string may be failed (means the top level VHDL parser
     * wasn't strict enough -> bug), or numeric problems rises (e.g. the numeric
     * literal can fit the value_type). */
    using return_type = std::tuple<bool, value_type>;

    numeric_convert(std::ostream& os_);

    return_type operator()(ast::bit_string_literal const& literal) const;
    return_type operator()(ast::decimal_literal const& literal) const;
    return_type operator()(ast::based_literal const& literal) const;

private:
    class report_error;

private:
    // clang-format off
    std::ostream&                                   os;
    // clang-format on
};

} // namespace ast
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_NUMERIC_CONVERT_HPP_ */
