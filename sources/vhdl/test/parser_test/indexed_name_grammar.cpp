/*
 * indexed_name_grammar.cpp
 *
 *  Created on: 6.5.2018
 *      Author: olaf
 */


#include <eda/vhdl/ast.hpp>
#include "testing_parser_def.hpp"
#include "testing_parser_grammar_hack.hpp"

namespace x3_test {

    using attribute_type = ast::indexed_name;
    using parser_type = parser::indexed_name_type;

    // Explicit Template Instantiation
    template
    std::tuple<bool, std::string>
    testing_parser<attribute_type>::operator()(std::string const &, parser_type const&, bool);
}
        

