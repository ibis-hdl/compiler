//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/component_specification.hpp>
#include <ibis/vhdl/ast/node/binding_indication.hpp>
#include <ibis/vhdl/ast/node/block_configuration.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct component_configuration : position_tagged {
    ast::component_specification component_specification;
    optional<ast::binding_indication> binding_indication;
    optional<ast::block_configuration> block_configuration;
};

}  // namespace ibis::vhdl::ast
