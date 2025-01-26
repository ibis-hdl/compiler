// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later

#include <testsuite/vhdl/grammar/testsuite_parse.hpp>

#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/context.hpp>

#include <string_view>
#include <format>
#include <exception>

namespace testsuite {

using namespace ibis;

bool testsuite_parse::operator()(std::string_view contents, ast::design_file& design_file)
{
    bool parse_ok = false;
    using iterator_type = parser::iterator_type;

    try {
        ibis::util::file_mapper file_mapper{};
        auto const file_id = file_mapper.add_file(filename.generic_string(), contents);

        parser::position_cache<iterator_type> position_cache{};
        auto position_proxy = position_cache.annotator_for(file_id);

        vhdl::parser::parse parse{ os };
        vhdl::parser::context ctx;

        parse_ok = parse(std::move(position_proxy), ctx, design_file);

        using vhdl::failure_status;

        os << failure_status(ctx) << '\n';
    }
    catch (std::exception const& e) {
        os << std::format("Test Suite parse caught exception '{}'\n", e.what());
    }
    catch (...) {
        os << "Test Suite parse caught *unexpected* exception\n";
    }
    return parse_ok;
}

}  // namespace testsuite
