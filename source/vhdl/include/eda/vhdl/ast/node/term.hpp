/*
 * term.hpp
 *
 *  Created on: 09.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TERM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TERM_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/factor.hpp>
#include <eda/vhdl/ast/node/operator_token.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct term : position_tagged
{
    struct chunk {
        operator_token          multiplying_operator;
        ast::factor             factor;
    };

    ast::factor                 factor;
    std::vector<chunk>          rest_list;
};



} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TERM_HPP_ */
