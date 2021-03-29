#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/sensitivity_list.hpp>

namespace eda::vhdl::ast {

struct sensitivity_clause : position_tagged {
    ast::sensitivity_list sensitivity_list;

    /* Spirit.X3 single-element sequence adaptation bug fix
     * [Spirit Qi attribute propagation issue with single-member struct](
     * https://stackoverflow.com/questions/19823413/spirit-qi-attribute-propagation-issue-with-single-member-struct?answertab=active#tab-top)
     */
    sensitivity_clause() = default;

    sensitivity_clause(ast::sensitivity_list&& sensitivity_list_)
        : sensitivity_list{ std::move(sensitivity_list_) }
    {
    }
};

}  // namespace eda::vhdl::ast
