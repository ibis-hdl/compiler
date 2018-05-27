/*
 * based_literal.hpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/parser/common_types.hpp>
#include <boost/range/iterator_range.hpp>


namespace eda { namespace vhdl { namespace ast {


struct based_literal : position_tagged
{
    enum class kind_specifier { integer, real };

    struct number_chunk {
        boost::iterator_range<parser::iterator_type>    integer_part;
        boost::iterator_range<parser::iterator_type>    fractional_part;
        boost::iterator_range<parser::iterator_type>    exponent;
        kind_specifier                                  kind_type;
    };

    boost::iterator_range<parser::iterator_type>    base;
    number_chunk                                    number;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BASED_LITERAL_HPP_ */
