/*
 * physical_literal.cpp
 *
 *  Created on: 18.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/physical_literal.hpp>

#include <boost/spirit/home/x3.hpp>


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, physical_literal const& literal)
{
    return os;
}


} } } // namespace eda.vhdl93.ast





