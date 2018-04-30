/*
 * block_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/index_specification.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct block_specification_chunk
{
    ast::label                          label;  // {block_statement, generate_statement}_label
    optional<ast::index_specification>  index_specification;
};


struct block_specification : variant<
    ast::nullary,
    ast::name,
    ast::block_specification_chunk  // generate_statement....
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_ */
