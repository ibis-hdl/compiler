/*
 * literal_printer.hpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */


#include <eda/vhdl/ast/bit_string_literal.hpp>
#include <eda/vhdl/ast/decimal_literal.hpp>
#include <eda/vhdl/ast/based_literal.hpp>
#include <eda/vhdl/ast/string_literal.hpp>

#include <iostream>
#include <boost/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


class literal_printer
{
public:
    literal_printer(bit_string_literal const& literal_);
    literal_printer(decimal_literal const& literal_);
    literal_printer(based_literal const& literal_);
    literal_printer(string_literal const& literal_);

    std::ostream& operator()(std::ostream& os) const;

private:
    boost::variant<
        ast::bit_string_literal,
        ast::decimal_literal,
        ast::based_literal,
        ast::string_literal
    > const                                         literal;
};


static inline
std::ostream& operator<<(std::ostream& os, literal_printer const& printer)
{
    return printer(os);
}


} } } // namespace eda.vhdl.ast

