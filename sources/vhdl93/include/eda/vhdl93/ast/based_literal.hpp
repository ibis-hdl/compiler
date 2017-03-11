/*
 * based_literal.hpp
 *
 *  Created on: 11.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/optional.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct based_literal {
    int32_t                         base;
    std::string                     integer_part;
    boost::optional<std::string>    fractional_part;
    int32_t                         exponent;
};


using boost::fusion::operator<<;


} } } // namespace eda.vhdl93.ast



BOOST_FUSION_ADAPT_STRUCT(
    eda::vhdl93::ast::based_literal,
    (int32_t,                       base)
    (std::string,                   integer_part)
    (boost::optional<std::string>,  fractional_part)
    (int32_t,                       exponent)
)


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BASED_LITERAL_HPP_ */
