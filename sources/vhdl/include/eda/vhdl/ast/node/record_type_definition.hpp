/*
 * record_type_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RECORD_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RECORD_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/element_declaration.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct record_type_definition : position_tagged
{
    std::vector<ast::element_declaration>   element_declarations;
    optional<ast::simple_name>              name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RECORD_TYPE_DEFINITION_HPP_ */