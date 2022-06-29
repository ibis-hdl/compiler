//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/scalar_type_definition.hpp>
#include <ibis/vhdl/ast/node/composite_type_definition.hpp>
#include <ibis/vhdl/ast/node/access_type_definition.hpp>
#include <ibis/vhdl/ast/node/file_type_definition.hpp>

namespace ibis::vhdl::ast {

struct type_definition
    : variant<ast::nullary, ast::scalar_type_definition, ast::composite_type_definition,
              ast::access_type_definition, ast::file_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
