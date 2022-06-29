//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/sensitivity_list.hpp>

namespace ibis::vhdl::ast {

struct sensitivity_clause : position_tagged {
    ast::sensitivity_list sensitivity_list;

    // Spirit.X3 single-element sequence adaptation bug fix
    // [Spirit Qi attribute propagation issue with single-member struct](
    // https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top)
    //
    sensitivity_clause() = default;

    sensitivity_clause(ast::sensitivity_list&& sensitivity_list_)
        : sensitivity_list{ std::move(sensitivity_list_) }
    {
    }
};

}  // namespace ibis::vhdl::ast
