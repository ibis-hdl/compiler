/*
 * label.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct label : ast::identifier
{
    label& operator=(std::string_view&& sv)
    {
        name = std::move(sv);
        return *this;
    }
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LABEL_HPP_ */
