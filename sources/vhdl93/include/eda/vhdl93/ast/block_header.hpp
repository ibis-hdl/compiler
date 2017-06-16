/*
 * block_header.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/generic_clause.hpp>
#include <eda/vhdl93/ast/generic_map_aspect.hpp>
#include <eda/vhdl93/ast/port_clause.hpp>
#include <eda/vhdl93/ast/port_map_aspect.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct block_header : position_tagged
{
    struct generic_part_chunk
    {
        ast::generic_clause                 generic_clause;
        optional<ast::generic_map_aspect>   generic_map_aspect;
    };

    struct port_part_chunk
    {
        ast::port_clause                    port_clause;
        optional<ast::port_map_aspect>      port_map_aspect;
    };

    optional<generic_part_chunk>            generic_part;
    optional<port_part_chunk>               port_part;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_HEADER_HPP_ */
