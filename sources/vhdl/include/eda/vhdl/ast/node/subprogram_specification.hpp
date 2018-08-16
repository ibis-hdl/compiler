/*
 * subprogram_specification.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/designator.hpp>
#include <eda/vhdl/ast/node/formal_parameter_list.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


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
    ast::name                                   return_type_mark;

    subprogram_specification_function()
    : impure{}
    { }
};


struct subprogram_specification : variant<
    ast::subprogram_specification_procedure,
    ast::subprogram_specification_function
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_SPECIFICATION_HPP_ */