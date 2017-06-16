/*
 * subtype_indication.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/type_mark.hpp>
//#include <eda/vhdl93/ast/constraint.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct constraint;


struct subtype_indication : position_tagged
{
    std::vector<ast::name>                              unspecified_name_list;
    optional<x3::forward_ast<ast::constraint>>          constraint;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_ */
