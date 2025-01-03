//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/ast.hpp>

#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/util/pretty_typename.hpp>

#include <boost/test/tools/output_test_stream.hpp>

#include <iostream>
#include <filesystem>

#include <testsuite/namespace_alias.hpp>

namespace testsuite {
namespace fs = std::filesystem;
}

namespace testsuite {

class testsuite_parse {
public:
    testsuite_parse(fs::path const filename_)
        : filename{ filename_ }
    {
    }

public:
    bool operator()(std::string_view contents, ibis::vhdl::ast::design_file& design_file);

public:
    ///
    /// Return the output written by the parser and error/diagnostic handler.
    ///
    /// @return std::string_view The output; valid as long the class is alive.
    ///
    std::string output() const { return os.str(); }

    btt::output_test_stream& ostream() { return os; }

private:
    btt::output_test_stream os;
    fs::path const filename;
};

}  // namespace testsuite
