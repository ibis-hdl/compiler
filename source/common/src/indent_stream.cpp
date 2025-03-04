//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/indent_stream.hpp>

namespace ibis::util {

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
indent_sbuf::~indent_sbuf()
{
    // BUG overflow() crashes on destruction of static created printer class instances, e.g. at
    // numeric_convert/convert_based.cpp at git
    // 'convert based literal - make diagnostic_handler ref-wrapped'
    // hash eba75365fc2dc02f53d601790ce250c04878a51c
    // -------------------------------------------------------------------------------------------------
    // Program received signal SIGSEGV, Segmentation fault. gdb backtrace:
    // in ?? ()
    // ibis::util::indent_sbuf::overflow (
    // ibis::util::indent_sbuf::~indent_sbuf (
    // ibis::util::indent_ostream::~indent_ostream (
    // ibis::util::indent_ostream::~indent_ostream (
    // ibis::vhdl::ast::printer::~printer (
    // at /workspaces/compiler/source/vhdl/include/ibis/vhdl/ast/ast_printer.hpp:35
    // -------------------------------------------------------------------------------------------------

    // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.VirtualCall) -- functionally intended
    overflow('\n');  // start at column 0 again
}

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
indent_ostream::~indent_ostream() = default;

}  // namespace ibis::util
