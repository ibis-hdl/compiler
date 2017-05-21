/*
 * type_mark.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_


#include <eda/vhdl93/ast/name.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct type_mark : ast::name
{
    using name::base_type;
    using name::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_ */
