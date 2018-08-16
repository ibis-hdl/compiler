/*
 * choice.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <eda/vhdl/ast/node/simple_expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


using choice = variant<
    nullary,
    simple_name,
    discrete_range,
    simple_expression,
    keyword_token       // OTHERS
>;


using choices = std::vector<choice>;

} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CHOICES_HPP_ */