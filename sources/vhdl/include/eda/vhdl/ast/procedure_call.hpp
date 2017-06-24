/*
 * procedure_call.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCEDURE_CALL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCEDURE_CALL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

//#include <eda/vhdl/ast/name.hpp>
#include <string_view>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;


struct procedure_call : position_tagged
{
    x3::forward_ast<ast::name>  procedure_name;
    std::string_view            actual_parameter_part;

    /* XXX: Fix for actual_parameter_part's ast::name problem */
    procedure_call& operator=(std::string_view const&& str_v) {
        actual_parameter_part = std::move(str_v);
        return *this;
    }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PROCEDURE_CALL_HPP_ */
