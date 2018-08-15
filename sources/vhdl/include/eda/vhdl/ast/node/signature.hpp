/*
 * signature.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct signature : position_tagged
{
    std::vector<ast::name>              parameter_type_list;    // type_mark
    optional<ast::name>                 return_type;            // type_mark
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SIGNATURE_HPP_ */
