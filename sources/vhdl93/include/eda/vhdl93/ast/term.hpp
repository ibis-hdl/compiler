/*
 * term.hpp
 *
 *  Created on: 09.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/factor.hpp>
#include <list>


namespace eda { namespace vhdl93 { namespace ast {


struct term : position_tagged
{
    struct chunk {
        operator_token          operator_;
        ast::factor             factor;
    };

    ast::factor                 factor;
    std::list<chunk>            rest_list;
};



} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_ */
