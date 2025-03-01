//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

// #include <ibis/vhdl/ast_fwd.hpp>
// #include <ibis/vhdl/ast.hpp>  // FixMe: not the best solution to include all
#include <ibis/vhdl/ast/node/design_file.hpp>

#include <boost/test/tools/output_test_stream.hpp>

#include <filesystem>
#include <string_view>
#include <string>

#include <testsuite/namespace_alias.hpp>  // IWYU pragma: keep

namespace testsuite {
namespace fs = std::filesystem;
}

namespace testsuite {

class testsuite_parse {
public:
    testsuite_parse(fs::path const filename_)
        : fs_pathname{ filename_ }
    {
    }

public:
    bool operator()(std::string_view contents, ibis::vhdl::ast::design_file& design_file);

public:
    std::string file_name() const { return fs_pathname.string(); }

public:
    ///
    /// Return the output written by the parser and error/diagnostic handler.
    ///
    /// @return std::string_view The output; valid as long the class is alive.
    ///
    std::string output() const { return os.str(); }

    ///
    /// Return the captured output stream from testsuite_parse::operator()
    ///
    /// @return btt::output_test_stream&
    ///
    btt::output_test_stream& ostream() { return os; }

private:
    btt::output_test_stream os;
    fs::path const fs_pathname;
};

}  // namespace testsuite
