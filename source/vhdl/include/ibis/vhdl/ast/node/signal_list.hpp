//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct signal_list_list : std::vector<ast::name> {};

// signal_list ::=
//           signal_name { , signal_name }
//         | others
//         | all
struct signal_list
    : variant<nullary, signal_list_list,
              keyword_token  // OTHERS | ALL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
