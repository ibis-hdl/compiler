// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later

#include <testsuite/testsuite_parser.hpp>

#include <ibis/literals.hpp>
#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/context.hpp>  // failure_status
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <exception>
#include <format>
#include <functional>
#include <iostream>
#include <string_view>
#include <utility>

#include <testsuite/namespace_alias.hpp>

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
        parser::parse const parse{ os };
        parser::context vhdl_ctx;

        // no std::move of the variable 'contents' (trivially-copyable type 'std::string_view')
        auto current_file = file_mapper.add_file(this->file_name(), contents);

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
