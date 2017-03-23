/*
 * based_literal.cpp
 *
 *  Created on: 13.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/based_literal.hpp>

#include <boost/spirit/home/x3.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


namespace detail { }




std::ostream& operator<<(std::ostream& os, based_literal const& node)
{
    os << "{b=" << node.base << ", n=" << node.literal << "}";

    return os;
}


} } } // namespace eda.vhdl93.ast





