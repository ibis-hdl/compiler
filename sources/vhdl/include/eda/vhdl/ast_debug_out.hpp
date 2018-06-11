/*
 * ast_io.hpp
 *
 *  Created on: 23.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DEBUG_OUT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DEBUG_OUT_HPP_


#include <iosfwd>

#include <boost/optional/optional_io.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <eda/vhdl/ast_adapted.hpp>


namespace eda { namespace vhdl { namespace ast {


using boost::fusion::operator<<;


template<typename T>
static inline
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vector) {
    for(auto const& x: vector) { os << x << " "; }
    return os;
}


template<typename T>
static inline
std::ostream& operator<<(std::ostream& os, std::list<T> const& list) {
    for(auto const& x: list) { os << x << " "; }
    return os;
}


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DEBUG_OUT_HPP_ */
