/*
 * abstract_literal.cpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/abstract_literal.hpp>
#include <eda/vhdl93/ast_printer.hpp>


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, abstract_literal const& node)
{
	ast::printer print(os);
	print(node);

    return os;
}


} } } // namespace eda.vhdl93.ast








