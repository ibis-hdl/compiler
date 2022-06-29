//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/block_specification.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <ibis/vhdl/ast/node/configuration_item.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct block_configuration : position_tagged {
    ast::block_specification block_specification;
    std::vector<ast::use_clause> use_clause_list;
    std::vector<ast::configuration_item> configuration_item_list;
};

}  // namespace ibis::vhdl::ast
