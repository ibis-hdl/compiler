/*
 * subtype_indication.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_INDICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_INDICATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/constraint.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct subtype_indication : position_tagged
{
    std::vector<ast::name>          unspecified_name_list;
    optional<ast::constraint>       constraint;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_INDICATION_HPP_ */
