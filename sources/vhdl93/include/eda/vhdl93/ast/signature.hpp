/*
 * signature.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/type_mark.hpp>
#include <vector>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct signature : position_tagged
{
    std::vector<ast::type_mark>         parameter_type_list;
    optional<ast::type_mark>            return_type;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIGNATURE_HPP_ */
