/*
 * literal_printer.hpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/node/based_literal.hpp>
#include <eda/vhdl/ast/node/bit_string_literal.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>
#include <eda/vhdl/ast/node/string_literal.hpp>

#include <boost/variant.hpp>
#include <iostream>

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
    // clang-format off
    using literal_variant_type = boost::variant<
        ast::bit_string_literal,
        ast::decimal_literal,
        ast::based_literal,
        ast::string_literal
    >;
    // clang-format on

    // clang-format off
    literal_variant_type const                      literal;
    // clang-format on
};

static inline std::ostream& operator<<(std::ostream& os, literal_printer const& printer)
{
    return printer.print(os);
}

} // namespace ast
} // namespace vhdl
} // namespace eda
