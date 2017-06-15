/*
 * subprogram_specification.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/designator.hpp>
#include <eda/vhdl93/ast/formal_parameter_list.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>
#include <eda/vhdl93/ast/type_mark.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct subprogram_specification_procedure : position_tagged
{
    ast::designator                             designator;
    optional<ast::formal_parameter_list>        formal_parameter_list;
};


struct subprogram_specification_function : position_tagged
{
    /* LRM93 2.1
     * A function is impure if its specification contains the
     * reserved word IMPURE; otherwise it is said to be pure. */
    bool                                        impure;
    ast::designator                             designator;
    optional<ast::formal_parameter_list>        formal_parameter_list;
    ast::type_mark                              return_type_mark;

    subprogram_specification_function()
    : impure{}
    { }
};


struct subprogram_specification : x3::variant<
    ast::subprogram_specification_procedure,
    ast::subprogram_specification_function
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBPROGRAM_SPECIFICATION_HPP_ */
