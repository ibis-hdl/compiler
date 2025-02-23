//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/type.hpp>

#include <tuple>
#include <variant>

namespace ibis::vhdl::ast {
struct based_literal;
struct bit_string_literal;
struct decimal_literal;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl {
template <typename IteratorT>
class diagnostic_handler;
}

namespace ibis::vhdl::ast {

///
/// Convert the numeric literals to numeric types
///
/// Note #1: About numeric literals
/// ----------------------------------
/// The correct tagged type_specifier of {based, decimal}_literal is elementary on
/// elaboration time, since after converting to numeric the information about
/// the integer/real string are lost, see concrete why it's important e.g.
/// [vhdl error: integer literal cannot have negative exponent](
/// https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent)
///
/// Strong rules here on parser level simplifies numeric conversion
/// since more sloppy rules can be used for conversion from literals to concrete
/// intrinsic types.
///
/// Note #2:
/// --------
/// VDL decimal literals does allow exponents on integers, to simplify evaluating
/// a x3 real parser with policies is used. The correct 2nd pass parsing and hence
/// correct converting depends on correct parsing of the VHDL grammar, since the
/// exponent of integer doesn't allow a negative sign.
///
/// Note #3:
/// --------
/// The conversion always takes place to an unsigned type. However, this also means
/// that the sign from the AST must be taken into account during the actual assignment
/// and a range overflow of the signed target type must be checked.
///
class numeric_convert {
public:
    /// integer type.
    using integer_type = intrinsic::unsigned_integer_type;

    /// real type for floats/doubles.
    using real_type = intrinsic::real_type;

    /// literal result type as variant of integer and real type.
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
    numeric_convert(diagnostic_handler_type& diagnostic_handler_);

    ///
    /// Convert the a bit string literal to numeric value.
    ///
    /// @param literal AST node
    /// @return return_type The converted value
    ///
    /// @todo Check [llonesmiz Wandbox answer](https://wandbox.org/permlink/Pw1suRuYhgPX3iq8)
    /// at [Spirit.X3 with lambda returning different parser types](
    /// https://stackoverflow.com/questions/50444016/spirit-x3-with-lambda-returning-different-parser-types/51126057#51126057)
    return_type operator()(ast::bit_string_literal const& literal) const;

    return_type operator()(ast::decimal_literal const& literal) const;

    return_type operator()(ast::based_literal const& literal) const;

private:
    diagnostic_handler_type& diagnostic_handler;
};

}  // namespace ibis::vhdl::ast
