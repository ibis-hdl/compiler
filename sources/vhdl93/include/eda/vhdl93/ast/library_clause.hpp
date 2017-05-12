/*
 * library_clause.hpp
 *
 *  Created on: 11.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/selected_name.hpp>
#include <vector>

namespace eda { namespace vhdl93 { namespace ast {


struct library_clause : position_tagged
{
    struct logical_name  : ast::identifier
    {
        logical_name& operator=(std::string_view&& sv)
        {
            name = std::move(sv);
            return *this;
        }
    };

    std::vector<logical_name>       logical_name_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_CLAUSE_HPP_ */
