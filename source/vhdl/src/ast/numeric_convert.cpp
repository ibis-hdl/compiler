//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/numeric_convert.hpp>

#include <ibis/vhdl/ast/numeric_convert/convert_based.hpp>
#include <ibis/vhdl/ast/numeric_convert/convert_bit_string.hpp>
#include <ibis/vhdl/ast/numeric_convert/convert_decimal.hpp>

#include <ibis/vhdl/ast/node/based_literal.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

#include <ibis/vhdl/ast/literal_printer.hpp>
#include <ibis/vhdl/type.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
// IWYU replaces a lot of other header, we stay with this one
#include <boost/spirit/home/x3.hpp>  // IWYU pragma: keep
#include <ibis/util/compiler/warnings_on.hpp>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
//#include <boost/range/iterator_range.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/iterator_range_io.hpp>
#include <boost/range/join.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <iostream>

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
    ast::convert_bit_string<basic_integer_type> const convert(diagnostic_handler);
    return convert(literal);
}

//******************************************************************************
// decimal_literal
//
numeric_convert::return_type numeric_convert::operator()(ast::decimal_literal const& literal) const
{
    ast::convert_decimal<basic_integer_type, real_type> const convert(diagnostic_handler);
    return convert(literal);
}

//******************************************************************************
// based_literal
//
numeric_convert::return_type numeric_convert::operator()(ast::based_literal const& literal) const
{
    ast::convert_based<basic_integer_type, real_type> const convert(diagnostic_handler);
    return convert(literal);
}

}  // namespace ibis::vhdl::ast
