// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later

#include <testsuite/testsuite_parser.hpp>

#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/literals.hpp>

#include <string_view>
#include <format>
#include <exception>

namespace testsuite {

using namespace ibis;

bool testsuite_parse::operator()(std::string_view contents, ast::design_file& design_file)
{
    bool parse_ok = false;
    using iterator_type = parser::iterator_type;
    using namespace ibis::literals::memory;

    try {
        util::file_mapper file_mapper{};
        parser::position_cache<iterator_type> position_cache{ 4_KiB };
        parser::parse parse{ os };
        parser::context vhdl_ctx;

        auto current_file = file_mapper.add_file(this->file_name(), std::move(contents));

        parse_ok = parse(std::move(current_file), position_cache, vhdl_ctx, design_file);

        os << vhdl::failure_status(vhdl_ctx) << '\n';
        return parse_ok;
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
