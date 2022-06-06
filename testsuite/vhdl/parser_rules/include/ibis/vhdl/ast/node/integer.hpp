//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

///
/// Some rules of the VHDL Spirit.X3 grammar are directly embedded into the
/// grammar self, hence no AST nodes or grammar symbols exist, but there are
/// test case files with address this rules for simplicity of testing.
///
/// To get these, and not to pollute the grammar with testing code, this
/// header fakes this node
///

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

using integer = ast::string_span;

}
