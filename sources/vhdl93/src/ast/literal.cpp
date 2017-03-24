/*
 * literal.cpp
 *
 *  Created on: 23.03.2017
 *      Author: olaf
 */

#include <eda/vhdl93/ast/literal.hpp>
#include <eda/vhdl93/ast_printer.hpp>


namespace eda { namespace vhdl93 { namespace ast {


std::ostream& operator<<(std::ostream& os, literal const& node)
{
	ast::printer print(os);
	print(node);

    return os;
}


} } } // namespace eda.vhdl93.ast




