/*
 * block_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/index_specification.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct block_specification_chunk
{
    ast::label                          label;  // {block_statement, generate_statement}_label
    optional<ast::index_specification>  index_specification;
};


struct block_specification : x3::variant<
    ast::nullary,
    ast::name,
    ast::block_specification_chunk  // generate_statement....
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BLOCK_SPECIFICATION_HPP_ */
