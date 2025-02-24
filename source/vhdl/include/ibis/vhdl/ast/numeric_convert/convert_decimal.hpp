//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/concepts.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/type.hpp>

#include <tuple>
#include <variant>

namespace ibis::vhdl::ast {

struct decimal_literal;

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl {

template <typename IteratorT>
class diagnostic_handler;

}

namespace ibis::vhdl::ast {

///
/// @brief Convert decimal literal to numeric.
///
/// @tparam IntegerT The integer type of the numeric converted into.
/// @tparam RealT The real type of the numeric converted into.
///
template <ibis::integer IntegerT, ibis::real RealT>
class convert_decimal {
public:
    using integer_type = IntegerT;
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
    /// @param diag_handler  Error reporter.
    ///
    explicit convert_decimal(diagnostic_handler_type& diag_handler);

    ///
    /// Convert the a bit string literal to numeric value.
    ///
    /// @param node AST literal node
    /// @return return_type The converted value
    return_type operator()(ast::decimal_literal const& node) const;

private:
    std::tuple<bool, integer_type> parse_integer(ast::string_span const& literal) const;
    std::tuple<bool, real_type> parse_real(ast::string_span const& literal) const;

private:
    diagnostic_handler_type& diagnostic_handler;
};

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

/// Explicit template instantiation declaration
extern template class convert_decimal<intrinsic::signed_integer_type, intrinsic::real_type>;

}  // namespace ibis::vhdl::ast
