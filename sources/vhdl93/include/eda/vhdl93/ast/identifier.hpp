/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_


#include <string>


namespace eda { namespace vhdl93 { namespace ast {


/* Note, simply deriving from std::string like
 *
 *    struct identifier : public std::string
 *    {
 *        using std::string::string;
 *    };
 *
 * breaks BOOST_SPIRIT_X3_DEBUG compilation.
 */
struct identifier
{
    std::string        name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_ */
