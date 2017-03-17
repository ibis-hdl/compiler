/*
 * ast_adapted.hpp
 *
 *  Created on: 15.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_


#include <eda/vhdl93/ast.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>



namespace eda { namespace vhdl93 { namespace ast {

using boost::fusion::operator<<;

} } } // namespace eda.vhdl93.ast


BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::based_literal,
    (std::string,                                                      base)
    (std::string,                                                   literal)
)

BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::bit_string_literal,
    (std::string,                                                   literal)
    (eda::vhdl93::ast::bit_string_literal::tag,                        hint)
)

BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::decimal_literal,
    (std::string,                                                   literal)
    (eda::vhdl93::ast::decimal_literal::tag,                           hint)
)

BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::physical_literal,
    (boost::spirit::x3::forward_ast<eda::vhdl93::ast::abstract_literal>,   literal)
    (std::string,                                                 unit_name)
)




#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_ */
