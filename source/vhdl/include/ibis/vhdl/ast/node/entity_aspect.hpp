//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct entity_aspect_entity : position_tagged {
    ast::name name;
    optional<ast::identifier> architecture_identifier;
};

struct entity_aspect_configuration : position_tagged {
    ast::name name;
};

struct entity_aspect
    : variant<ast::nullary, ast::entity_aspect_entity, ast::entity_aspect_configuration,
              ast::keyword_token  // OPEN
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
