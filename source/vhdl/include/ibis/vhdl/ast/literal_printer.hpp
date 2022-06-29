//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

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
    literal_printer(bit_string_literal const& literal_)
        : literal{ literal_ }
    {
    }

    literal_printer(decimal_literal const& literal_)
        : literal{ literal_ }
    {
    }

    literal_printer(based_literal const& literal_)
        : literal{ literal_ }
    {
    }

    literal_printer(string_literal const& literal_)
        : literal{ literal_ }
    {
    }

    std::ostream& print_on(std::ostream& os) const;

private:
    // FixMe: The use of variant requires full definition of the class, hence the
    // include header of the elements are used and no forward declarations are useable. Maybe
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
