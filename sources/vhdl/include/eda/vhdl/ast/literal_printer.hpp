/*
 * literal_printer.hpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_PRINTER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_PRINTER_HPP_

#include <eda/vhdl/ast/node/based_literal.hpp>
#include <eda/vhdl/ast/node/bit_string_literal.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>
#include <eda/vhdl/ast/node/string_literal.hpp>

#include <boost/variant/variant.hpp>

#include <iosfwd>

namespace eda {
namespace vhdl {
namespace ast {

class literal_printer {
public:
    literal_printer(ast::bit_string_literal const& literal_);
    literal_printer(ast::decimal_literal const& literal_);
    literal_printer(ast::based_literal const& literal_);
    literal_printer(ast::string_literal const& literal_);

    std::ostream& print(std::ostream& os) const;

private:

    // FixMe: The use of variant requires full definition of the class, hence the
    // includes of the elements used and no forward declarations can be used. Maybe
    // write an internal wrapper class to avoid this.
    // clang-format off
    using literal_variant_type = boost::variant<
        ast::bit_string_literal,
        ast::decimal_literal,
        ast::based_literal,
        ast::string_literal
    >;
    // clang-format on

    literal_variant_type const literal;
};

static inline std::ostream& operator<<(std::ostream& os, literal_printer const& printer)
{
    return printer.print(os);
}

}  // namespace ast
}  // namespace vhdl
}  // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LITERAL_PRINTER_HPP_ */
