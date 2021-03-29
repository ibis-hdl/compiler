#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/condition.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct condition_clause : position_tagged {
    ast::condition condition;

    /* Spirit.X3 single-element sequence adaptation bug fix
     * [Spirit Qi attribute propagation issue with single-member struct](
     * https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top)
     */
    condition_clause() = default;

    condition_clause(ast::condition&& condition_)
        : condition{ std::move(condition_) }
    {
    }
};

}  // namespace eda::vhdl::ast
