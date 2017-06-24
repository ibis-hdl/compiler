/*
 * range_constraint.hpp
 *
 *  Created on: 20.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_CONSTRAINT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_CONSTRAINT_HPP_


#include <eda/vhdl/ast/range.hpp>


namespace eda { namespace vhdl { namespace ast {


/* Following the BNF, the range_constraint differs only from range_constraint
 * by the leading keyword RANGE, hence from AST's point of view it's simply a
 * range ...
 * Further, a range as such is used otherwise in the BNF as specifier for other
 * rules.
 * Hence, the BNF is reading much simpler by defining the range_constraint as
 * an own AST node (syntactical sugar). */
using range_constraint = ast::range;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_RANGE_CONSTRAINT_HPP_ */
