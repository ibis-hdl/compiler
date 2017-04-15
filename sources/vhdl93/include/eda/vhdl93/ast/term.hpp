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

#include <list>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct factor;
enum class operator_token;


struct term_chunk {
    operator_token              operator_;
    factor                      factor_;
};


struct term : x3::position_tagged
{
    factor                      factor_;
    std::list<term_chunk>       chunk_list;
};



} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TERM_HPP_ */
