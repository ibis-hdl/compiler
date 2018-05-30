/*
 * literal_printer.hpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */


#include <eda/vhdl/ast/bit_string_literal.hpp>
#include <eda/vhdl/ast/decimal_literal.hpp>
#include <eda/vhdl/ast/based_literal.hpp>

#include <iostream>
#include <variant>


namespace eda { namespace vhdl { namespace ast {


class literal_printer
{
public:
    literal_printer(bit_string_literal const& literal_);
    literal_printer(decimal_literal const& literal_);
    literal_printer(based_literal const& literal_);

    std::ostream& operator()(std::ostream& os) const;

private:
    std::variant<
        std::monostate,
        ast::bit_string_literal,
        ast::decimal_literal,
        ast::based_literal
    > const                                         literal;
};


std::ostream& operator<<(std::ostream& os, literal_printer const& printer);


} } } // namespace eda.vhdl.ast

