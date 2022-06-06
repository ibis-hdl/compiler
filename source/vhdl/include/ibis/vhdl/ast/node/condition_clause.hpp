//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/condition.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct condition_clause : position_tagged {
    ast::condition condition;

    // Spirit.X3 single-element sequence adaptation bug fix
    // [Spirit Qi attribute propagation issue with single-member struct](
    // https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top)
    //
    condition_clause() = default;

    condition_clause(ast::condition&& condition_)
        : condition{ std::move(condition_) }
    {
    }
};

}  // namespace ibis::vhdl::ast
