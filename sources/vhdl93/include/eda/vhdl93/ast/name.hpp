/*
 * name.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <eda/vhdl93/ast/nullary.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct attribute_name;
struct indexed_name;
struct operator_symbol;
struct selected_name;
struct simple_name;
struct slice_name;

struct name :
    x3::variant<
        nullary,
//        x3::forward_ast<attribute_name>,
//        x3::forward_ast<indexed_name>,
        x3::forward_ast<operator_symbol>,
//        x3::forward_ast<selected_name>,
        x3::forward_ast<simple_name>
//        x3::forward_ast<slice_name>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_ */
