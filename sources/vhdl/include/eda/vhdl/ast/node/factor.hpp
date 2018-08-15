/*
 * factor.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FACTOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FACTOR_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/primary.hpp>


namespace eda { namespace vhdl { namespace ast {


struct factor_binary_operation : position_tagged
{
    ast::primary                    primary_lhs;
    operator_token                  operator_;
    ast::primary                    primary_rhs;
};

struct factor_unary_operation : position_tagged
{
    operator_token                  operator_;
    ast::primary                    primary;
};


// factor ::=
//     primary [ ** primary ]
//     | ABS primary
//     | NOT primary
struct factor : variant<
    nullary,
    primary,
    factor_binary_operation,
    factor_unary_operation
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FACTOR_HPP_ */
