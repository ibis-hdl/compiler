/*
 * block_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/variant.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/index_specification.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct block_specification_chunk : position_tagged
{
    ast::label                          label;  // {block, generate}_statement_label
    optional<ast::index_specification>  index_specification;
};


struct block_specification : variant<
    ast::nullary,
    ast::name,                          // architecture_name
    ast::block_specification_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BLOCK_SPECIFICATION_HPP_ */
