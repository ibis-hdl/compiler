#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct decimal_literal : position_tagged {
    enum class numeric_type_specifier { integer, real };

    ast::string_span literal;
    numeric_type_specifier type_specifier;

    /// convenience access to numeric type represented.
    numeric_type_specifier numeric_type() const { return type_specifier; }
};

#if defined(BOOST_SPIRIT_X3_DEBUG)
inline std::ostream& operator<<(std::ostream& os, ast::decimal_literal::numeric_type_specifier specifier)
{
    using numeric_type_specifier = ast::decimal_literal::numeric_type_specifier;
    auto const lookup = [&os](numeric_type_specifier specifier) {
        switch (specifier) {
            case numeric_type_specifier::integer:
                os << "[integer]";
                break;
            case numeric_type_specifier::real:
                os << "[real]";
                break;
            default:
                os << "[N/A]";
        }
    };
    lookup(specifier);
    return os;
}
#endif

}  // namespace ibis::vhdl::ast
