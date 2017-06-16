/*
 * options.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/keyword_token.hpp>
#include <eda/vhdl93/ast/delay_mechanism.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct options : position_tagged
{
    optional<ast::keyword_token>            guarded; // GUARDED
    optional<ast::delay_mechanism>          delay_mechanism;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPTIONS_HPP_ */
