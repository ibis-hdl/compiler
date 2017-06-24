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


static inline
std::ostream& operator<<(std::ostream& os,delay_mechanism::delay_type type) {
    switch(type) {
        case delay_mechanism::delay_type::TRANSPORT_DELAY: {
            os << "TRANSPORT_DELAY"; break;
        }
        case delay_mechanism::delay_type::INERTIAL_DELAY: {
            os << "INERTIAL_DELAY"; break;
        }
        default: {
            os << "INVALID";
        }
    }
    return os;
}


static inline
std::ostream& operator<<(std::ostream& os, sensitivity_list const& list) {
    for(auto const& name: list) { os << name << " "; }
    return os;
}

static inline
std::ostream& operator<<(std::ostream& os, signature_parameter_type_list const& list) {
    for(auto const& type_mark: list) { os << type_mark << " "; }
    return os;
}

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
