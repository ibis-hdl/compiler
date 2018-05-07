/*
 * constant_declaration_grammar.cpp
 *
 *  Created on: 7.5.2018
 *      Author: olaf
 */


#include <eda/vhdl/ast.hpp>
#include "testing_parser_def.hpp"
#include "testing_parser_grammar_hack.hpp"

namespace x3_test {

    using attribute_type = ast::constant_declaration;
    using parser_type = parser::constant_declaration_type;

    // Explicit Template Instantiation
    template
    std::tuple<bool, std::string>
    testing_parser<attribute_type>::operator()(std::string const &, parser_type const&, bool);
}
        

