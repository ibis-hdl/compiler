/*
 * factor.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/primary.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {

#if 0
struct factor_stuff : position_tagged
{
    struct chunk {
        operator_token              operator_;
        ast::primary                primary;

    };
    ast::primary                    primary;
    boost::optional<chunk>          rest;
};
#endif


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


/*
 * factor ::=
 *     primary [ ** primary ]
 *     | ABS primary
 *     | NOT primary
 */
struct factor :
    x3::variant<
        nullary,
        primary,
        factor_binary_operation,
        factor_unary_operation
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_ */
