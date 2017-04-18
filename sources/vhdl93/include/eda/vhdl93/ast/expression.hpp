/*
 * expression.hpp
 *
 *  Created on: 15.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/vhdl93/ast/operator_token.hpp>
#include <eda/vhdl93/ast/relation.hpp>

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct expression : x3::position_tagged
{
    struct chunk
    {
        operator_token              operator_;
        ast::relation               relation;
    };

    ast::relation                   relation;
    std::list<chunk>                rest_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_EXPRESSION_HPP_ */
