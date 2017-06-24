/*
 * signature.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_


#include <eda/vhdl/ast/type_mark.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct signature : position_tagged
{
    std::vector<ast::type_mark>         parameter_type_list;
    optional<ast::type_mark>            return_type;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_ */
