/*
 * options.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_OPTIONS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_OPTIONS_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/delay_mechanism.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct options : position_tagged
{
    bool                                    guarded;
    optional<ast::delay_mechanism>          delay_mechanism;

    options() : guarded{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_OPTIONS_HPP_ */
