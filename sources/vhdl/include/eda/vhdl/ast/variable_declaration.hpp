/*
 * variable_declaration.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_DECLARATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier_list.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct variable_declaration : position_tagged
{
    bool                            shared;
    ast::identifier_list            identifier_list;
    ast::subtype_indication         subtype_indication;
    optional<ast::expression>       expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_VARIABLE_DECLARATION_HPP_ */
