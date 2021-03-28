/*
 * package_body.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/package_body_declarative_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct package_body : position_tagged
{
    ast::identifier                     identifier;
    ast::package_body_declarative_part  declarative_part;
    optional<ast::identifier>           end_identifier;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PACKAGE_BODY_HPP_ */
