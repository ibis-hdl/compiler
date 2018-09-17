/*
 * literal_printer.cpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/literal_printer.hpp>

#include <eda/support/boost/hana_overload.hpp>
#include <eda/util/cxx_bug_fatal.hpp>

#include <boost/iterator/filter_iterator.hpp>

#include <iostream>

namespace /* anonymous */ {

struct unquote_predicate {
    unquote_predicate()
        : prev_char{ 0 }
        , dbl_quote_printed{ false }
    {
    }

    bool operator()(char chr)
    {
        auto const check = [this](char c, char quote) {
            if ((prev_char != c) || (prev_char != quote) || dbl_quote_printed) {
                dbl_quote_printed = false;
                return true;
            }
            dbl_quote_printed = true;
            return false;
        };

        bool flag{ false };

        switch (chr) {
            case '"':
                flag = check(chr, '"');
                break;
            case '%':
                flag = check(chr, '%');
                break;
            default:
                flag = true;
        }

        prev_char = chr;
        return flag;
    }

    char prev_char;
    bool dbl_quote_printed;
};

} // anonymous namespace

namespace eda {
namespace vhdl {
namespace ast {

literal_printer::literal_printer(bit_string_literal const& literal_)
    : literal{ literal_ }
{
}

literal_printer::literal_printer(decimal_literal const& literal_)
    : literal{ literal_ }
{
}

literal_printer::literal_printer(based_literal const& literal_)
    : literal{ literal_ }
{
}

literal_printer::literal_printer(string_literal const& literal_)
    : literal{ literal_ }
{
}

std::ostream& literal_printer::print(std::ostream& os) const
{
    util::visit_in_place(this->literal,

        [&os](bit_string_literal const& lit) {
            using base_specifier = bit_string_literal::base_specifier;

            switch (lit.base_type) {
                case base_specifier::bin:
                    os << "B";
                    break;
                case base_specifier::oct:
                    os << "O";
                    break;
                case base_specifier::hex:
                    os << "X";
                    break;
                default:
                    cxx_unreachable_bug_triggered();
            }

            os << lit.literal;

        },

        [&os](decimal_literal const& lit) {
            using kind_specifier = ast::decimal_literal::kind_specifier;

            switch (lit.kind_type) {
                case kind_specifier::integer: {
                    os << lit.literal;
                    break;
                }
                case kind_specifier::real: {
                    os << lit.literal;
                    break;
                }
                default:
                    cxx_unreachable_bug_triggered();
            }
        },

        [&os](based_literal const& lit) {

            using kind_specifier = ast::based_literal::kind_specifier;

            os << lit.base << '#';

            switch (lit.number.kind_type) {
                case kind_specifier::integer: {
                    os << lit.number.integer_part;
                    break;
                }
                case kind_specifier::real: {
                    os << lit.number.integer_part << '.' << lit.number.fractional_part;
                    break;
                }
                default:
                    cxx_unreachable_bug_triggered();
            }

            os << '#';

            if (lit.number.exponent) {
                os << lit.number.exponent;
            }

        },

        [&os](string_literal const& str) {

            // clang-format off
            auto const literal_f = boost::make_iterator_range(
                boost::make_filter_iterator(unquote_predicate{},
                        str.literal.begin(), str.literal.end()),
                boost::make_filter_iterator(unquote_predicate{},
                        str.literal.end())
            );
            // clang-format on

            os << literal_f;
        });

    return os;
}

} // namespace ast
} // namespace vhdl
} // namespace eda
