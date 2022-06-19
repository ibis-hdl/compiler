// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only

#include <testsuite/vhdl/grammar/testsuite_parse.hpp>


namespace testsuite {

bool testsuite_parse::operator()(std::string_view contents, vhdl::ast::design_file& design_file)
{
    bool parse_ok = false;

    try {
        parser::position_cache<parser::iterator_type> position_cache;
        parser::parse parse{ os };
        parser::context ctx;

        auto position_cache_proxy = position_cache.add_file(filename.generic_string(), contents);

        parse_ok = parse(position_cache_proxy, ctx, design_file);

        using ibis::vhdl::failure_status;

        os << failure_status(ctx) << '\n';
    }
    catch (std::exception const& e) {
        os << "Test Suite caught exception ''" << e.what() << "'\n";
    }
    catch (...) {
        os << "Test Suite caught *unexpected* exception\n";
    }
    return parse_ok;
}

}  // namespace testsuite
