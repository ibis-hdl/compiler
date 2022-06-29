//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/architecture_declarative_part.hpp>
#include <ibis/vhdl/ast/node/architecture_statement_part.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct architecture_body : position_tagged {
    ast::identifier identifier;
    ast::name entity_name;
    ast::architecture_declarative_part declarative_part;
    ast::architecture_statement_part statement_part;
    optional<ast::identifier> end_identifier;
};

}  // namespace ibis::vhdl::ast
