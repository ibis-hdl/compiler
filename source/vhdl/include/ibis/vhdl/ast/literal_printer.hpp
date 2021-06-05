#pragma once

#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/node/string_literal.hpp>

#include <boost/variant/variant.hpp>

#include <iosfwd>

namespace ibis::vhdl::ast {

class literal_printer {
public:
    literal_printer(ast::bit_string_literal const& literal_);
    literal_printer(ast::decimal_literal const& literal_);
    literal_printer(ast::based_literal const& literal_);
    literal_printer(ast::string_literal const& literal_);

    std::ostream& print_on(std::ostream& os) const;

private:
    // FixMe: The use of variant requires full definition of the class, hence the
    // includes of the elements used and no forward declarations can be used. Maybe
    // write an internal wrapper class to avoid this.
    using literal_variant_type = boost::variant<ast::bit_string_literal, ast::decimal_literal,
                                                ast::based_literal, ast::string_literal>;

    literal_variant_type const literal;
};

inline std::ostream& operator<<(std::ostream& os, literal_printer const& printer)
{
    return printer.print_on(os);
}

}  // namespace ibis::vhdl::ast
