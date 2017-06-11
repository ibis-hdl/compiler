/*
 * subtype_indication.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/type_mark.hpp>
//#include <eda/vhdl93/ast/constraint.hpp>
#include <eda/vhdl93/ast/optional.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct constraint;


/* Note:
 * The first elements of subtype_indication are ambiguous, since
 *
 *  resolution_function_name ::= name
 *  and
 *  type_mark ::= name
 *
 * To simplify processing parse and access/evaluating is provided by
 * different API's. */
struct subtype_indication : position_tagged
{
    // parse API
    std::vector<ast::name>                              unspecified_name_list;
    optional<x3::forward_ast<ast::constraint>>          constraint;


    optional<ast::name const&>        resolution_function_name() const {
        // FixMe: assert( unspecified_name_list.size() < 3, "internal parser logic error")
        if(unspecified_name_list.size() == 2) {
            return optional<ast::name const&>       {unspecified_name_list.front()};
        }
        else {
            return optional<ast::name const&>       {/* empty */};
        }
    };

    ast::type_mark const& type_mark() const {
        // FixMe: assert( unspecified_name_list.size() < 3, "internal parser logic error")
        if(unspecified_name_list.size() == 1) {
            return static_cast<ast::type_mark const&>(unspecified_name_list.front());
        }
        else { // 2nd element
            return static_cast<ast::type_mark const&>(unspecified_name_list.back());
        }
    }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_INDICATION_HPP_ */
