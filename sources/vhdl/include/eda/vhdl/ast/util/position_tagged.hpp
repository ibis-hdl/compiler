/*
 * position_tagged.hpp
 *
 *  Created on: 23.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_


#include <eda/utils/compiler_warnings_off.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <eda/utils/compiler_warnings_on.hpp>

#include <eda/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace ast {


/*
 * Annotation and Error handling
 *
 * Note, the AST odes are tagged with ast::position_tagged which is of type
 * x3::position_tagged. The intension was to extend this approach to tag
 * also the file (id) where the node belongs to as show by Baptiste Wicht's
 * [Compiler of the EDDI programming language](
 * https://github.com/wichtounet/eddic).
 * For convenience (and since this approach isn't realized yet), Spirit.X3's
 * ID are derived from x3::annotate_on_success (obviously must be changed in
 * the future).
 */
using position_tagged = x3::position_tagged;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_ */
