//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/type.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <tuple>
#include <iosfwd>
#include <numeric>
#include <limits>

namespace ibis::vhdl::ast {
// AST node forward
struct bit_string_literal;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl {
template <typename IteratorT>
class diagnostic_handler;
}
namespace ibis::vhdl::ast {

///
/// @brief Convert bit string literal to numeric.
///
/// @tparam IntegerT The integer type of the numeric converted into.
///
template <typename IntegerT>
class convert_bit_string {
    static_assert(std::numeric_limits<IntegerT>::is_integer,  // --
                  "TagetType must be of type integer");

public:
    ///
    /// The type, to which all literals will be converted.
    using integer_type = typename std::make_unsigned<IntegerT>::type;

    ///
    /// Return a tuple with the converted value and a boolean flag of
    /// success/failure of converting. If False, the parsing process on the AST
    /// node's literal string may be failed (means the top level VHDL parser
    /// wasn't strict enough -> bug), or numeric problems rises (e.g. the numeric
    /// literal can fit the integer_type).
    using return_type = std::tuple<bool, integer_type>;

    /// error handler used for error reporting
    using diagnostic_handler_type = ibis::vhdl::diagnostic_handler<parser::iterator_type>;

    ///
    /// Construct a new numeric convert object.
    ///
    /// @param diagnostic_handler_  Error reporter.
    ///
    convert_bit_string(diagnostic_handler_type& diagnostic_handler_);

    ///
    /// Convert the a bit string literal to numeric value.
    ///
    /// @param node AST literal node
    /// @return return_type The converted value
    return_type operator()(ast::bit_string_literal const& node) const;

private:
    diagnostic_handler_type& diagnostic_handler;
};

}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

/// Explicit template instantiation declaration
extern template class convert_bit_string<intrinsic::signed_integer_type>;

}  // namespace ibis::vhdl::ast
