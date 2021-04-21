#pragma once

#include <tuple>
#include <iosfwd>

namespace eda::vhdl::ast {
struct based_literal;
}
namespace eda::vhdl::ast {
struct bit_string_literal;
}
namespace eda::vhdl::ast {
struct decimal_literal;
}

namespace eda::vhdl::ast {

///
/// Convert the numeric literals to numeric types
///
/// Note #1: About numeric literals
/// ----------------------------------
/// The correct tagged kind_type of {based, decimal}_literal is elementary on
/// elaboration time, since after converting to numeric the informations about
/// the integer/real string are lost, see concrete why it's important e.g.
/// [vhdl error: integer literal cannot have negative exponent](
/// https://stackoverflow.com/questions/22113223/vhdl-error-integer-literal-cannot-have-negative-exponent)
///
/// Strong rules here on parser level simplifies simplifies numeric conversion
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
class numeric_convert {
public:
    ///
    /// The type, to which all literals will be converted.
    using value_type = double;

    ///
    /// Return a tuple with the converted value and a boolean flag of
    /// success/failure of converting. If False, the parsing process on the AST
    /// node's literal string may be failed (means the top level VHDL parser
    /// wasn't strict enough -> bug), or numeric problems rises (e.g. the numeric
    /// literal can fit the value_type).
    using return_type = std::tuple<bool, value_type>;

    ///
    /// Construct a new numeric convert object.
    ///
    /// @param os_ The stream where informations and messages during time of
    /// conversion goes.
    ///
    numeric_convert(std::ostream& os_);

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
    class report_error;

private:
    std::ostream& os;
};

}  // namespace eda::vhdl::ast
