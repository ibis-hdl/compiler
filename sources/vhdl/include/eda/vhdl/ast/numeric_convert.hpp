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
    struct report_error;

private:
    // clang-format off
    std::ostream&                                   os;
    // clang-format on
};

} // namespace ast
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_NUMERIC_CONVERT_HPP_ */
