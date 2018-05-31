/*
 * literal_printer.cpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/util/literal_printer.hpp>
#include <eda/support/boost/hana_overload.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace ast {


literal_printer::literal_printer(bit_string_literal const& literal_)
: literal{ literal_ }
{ }


std::ostream& literal_printer::operator()(std::ostream& os) const
{
    util::visit_in_place(
        this->literal,

        [&os](bit_string_literal const& literal) {
            using base_specifier = bit_string_literal::base_specifier;

            switch(literal.base_type) {
                case base_specifier::bin: os << "B"; break;
                case base_specifier::oct: os << "O"; break;
                case base_specifier::hex: os << "X"; break;
                default:                  cxx_unreachable_bug_triggered();
            }

            os << "\"" << literal.literal << "\"";

        },

        [&os](decimal_literal const& literal) {
            using kind_specifier = ast::decimal_literal::kind_specifier;

            switch(literal.kind_type) {
                case kind_specifier::integer: {
                    os << literal.literal;
                    break;
                }
                case kind_specifier::real: {
                    os << literal.literal;
                    break;
                }
                default:
                    cxx_unreachable_bug_triggered();
            }
        },

        [&os](based_literal const& literal) {

            using kind_specifier = ast::based_literal::kind_specifier;

            os << literal.base << '#';

            switch(literal.number.kind_type) {
                case kind_specifier::integer: {
                    os << literal.number.integer_part;
                    break;
                }
                case kind_specifier::real: {
                    os << literal.number.integer_part
                       << '.'
                       << literal.number.fractional_part;
                    break;
                }
                default:
                    cxx_unreachable_bug_triggered();
            }

            os << '#';

            if(literal.number.exponent) {
                os << literal.number.exponent;
            }

        }
    );


    return os;
}


std::ostream& operator<<(std::ostream& os, literal_printer const& print)
{
    return print(os);
}


} } } // namespace eda.vhdl.ast


