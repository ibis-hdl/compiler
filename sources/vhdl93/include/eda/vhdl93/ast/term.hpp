/*
 * term.hpp
 *
 *  Created on: 09.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/vhdl93/ast/factor.hpp>

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


enum class operator_token;


struct term : x3::position_tagged
{
    struct chunk {
        operator_token          operator_;
        ast::factor             factor;
    };

    ast::factor                 factor;
    std::list<chunk>            chunk_list;
};



} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_ */
