//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/actual_part.hpp>
#include <ibis/vhdl/ast/node/formal_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

#include <vector>

namespace ibis::vhdl::ast {

struct association_element : position_tagged {
    optional<ast::formal_part> formal_part;
    ast::actual_part actual_part;
};

struct association_list : std::vector<ast::association_element> {};

}  // namespace ibis::vhdl::ast
