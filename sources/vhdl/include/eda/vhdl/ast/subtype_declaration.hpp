/*
 * subtype_declaration.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>

#include <boost/range/iterator_range.hpp>


namespace eda { namespace vhdl { namespace ast {


struct subtype_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::subtype_indication     subtype_indication;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBTYPE_DECLARATION_HPP_ */
