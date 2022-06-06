//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>  // for explicit template instantiation

namespace ibis::vhdl::parser {

// Explicit template instantiation
template class position_cache<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
