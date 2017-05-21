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
#include <eda/vhdl93/ast/constraint.hpp>
#include <boost/optional.hpp>
#include <deque>


namespace eda { namespace vhdl93 { namespace ast {


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
    std::deque<ast::name>               unspecified_name_list;
    boost::optional<ast::constraint>    constraint;


    boost::optional<ast::name const&> resolution_function_name() const {
        if(unspecified_name_list.size() == 2) {
            return boost::optional<ast::name const&>{unspecified_name_list.front()};
        }
        else {
            return boost::optional<ast::name const&>{/* empty */};
        }
    };

    ast::type_mark const& type_mark() const {
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