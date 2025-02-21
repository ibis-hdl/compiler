//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert.hpp>
#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>
#include <ibis/vhdl/ast/numeric_convert/convert_bit_string.hpp>
#include <ibis/vhdl/ast/numeric_convert/convert_decimal.hpp>

namespace ibis::vhdl::ast {

numeric_convert::numeric_convert(diagnostic_handler_type& diagnostic_handler_)
    : diagnostic_handler{ diagnostic_handler_ }
{
}

//******************************************************************************
// bit_string_literal
//
numeric_convert::return_type numeric_convert::operator()(
    ast::bit_string_literal const& literal) const
{
    ast::convert_bit_string<integer_type> const convert(diagnostic_handler);
    return convert(literal);
}

//******************************************************************************
// decimal_literal
//
numeric_convert::return_type numeric_convert::operator()(ast::decimal_literal const& literal) const
{
    // ToDo Clang -Weverything Warning regards
    //  instantiation of function 'ibis::vhdl::ast::convert_decimal<unsigned long,
    //  double>::convert_decimal' required here, but no definition is available
    //  [-Wundefined-func-template]
    // note: add an explicit instantiation declaration to suppress this warning if
    // 'ibis::vhdl::ast::convert_decimal<unsigned long, double>::convert_decimal' is explicitly
    // instantiated in another translation unit
    ast::convert_decimal<integer_type, real_type> const convert(diagnostic_handler);
    return convert(literal);
}

//******************************************************************************
// based_literal
//
numeric_convert::return_type numeric_convert::operator()(ast::based_literal const& literal) const
{
    ast::convert_based<integer_type, real_type> const convert(diagnostic_handler);
    return convert(literal);
}

}  // namespace ibis::vhdl::ast
