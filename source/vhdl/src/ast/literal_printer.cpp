//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/ast/literal_printer.hpp>

#include <ibis/util/overloaded.hpp>  // IWYU pragma: keep

#include <ibis/util/cxx_bug_fatal.hpp>

#include <boost/variant/apply_visitor.hpp>

#include <iostream>

namespace {  // anonymous

class unquote_predicate {
public:
    bool operator()(char chr)
    {
        if (chr == prev_quote) {
            prev_quote = 0;
            return false;
        }
        if (chr == '"' || chr == '%') {
            prev_quote = chr;
        }
        else {
            prev_quote = 0;
        }
        return true;
    }

private:
    char prev_quote = 0;
};

}  // anonymous namespace

namespace ibis::vhdl::ast {

std::ostream& literal_printer::print_on(std::ostream& os) const
{
    boost::apply_visitor(
        util::overloaded{
            [&os](bit_string_literal const& lit) {
                using base_specifier = bit_string_literal::base_specifier;

                switch (lit.base_type) {
                    case base_specifier::bin:
                        os << 'B';
                        break;
                    case base_specifier::oct:
                        os << 'O';
                        break;
                    case base_specifier::hex:
                        os << 'X';
                        break;
                    default:  // unreachable_bug_triggered
                        cxx_unreachable_bug_triggered();
                }

                os << lit.literal;
            },
            [&os](decimal_literal const& lit) {
                // same for numeric_type_specifier integer and real
                os << lit.literal;
            },
            [&os](based_literal const& lit) {
                using numeric_type_specifier = ast::based_literal::numeric_type_specifier;

                os << lit.base << '#';

                switch (lit.numeric_type()) {
                    case numeric_type_specifier::integer: {
                        os << lit.number.integer_part;
                        break;
                    }
                    case numeric_type_specifier::real: {
                        os << lit.number.integer_part << '.' << lit.number.fractional_part;
                        break;
                    }
                    default:  // unreachable_bug_triggered
                        cxx_unreachable_bug_triggered();
                }

                os << '#';

                if (!lit.number.exponent.empty()) {
                    os << lit.number.exponent;
                }
            },
            [&os](string_literal const& str) {
                auto predicate = unquote_predicate{};
                for (auto const chr : str.literal) {
                    if (predicate(chr)) {
                        os << chr;
                    }
                }
            }          // --
        },             // overloaded{ ... }
        this->literal  // variant
    );

    return os;
}

}  // namespace ibis::vhdl::ast
