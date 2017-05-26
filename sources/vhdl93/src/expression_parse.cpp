/*
 * expression_parse.cpp
 *
 *  Created on: 26.05.2017
 *      Author: olaf
 */


#include <eda/vhdl93/parser/expression_parse.hpp>

#include <eda/vhdl93/parser/parser_config.hpp>
#include <eda/vhdl93/parser/grammar_def.hpp>

#include <iostream>


namespace eda { namespace vhdl93 { namespace parser {


bool parse(const std::string& input, ast::expression& expression_)
{
    parser::iterator_type iter = input.begin();
    parser::iterator_type const end = input.end();

    parser::error_handler_type error_handler(iter, end, std::cout);

    auto const parser =
        x3::with<x3::error_handler_tag>(std::ref(error_handler))
        [
              parser::expression
        ];

    bool success = false;

    try {
        success = x3::phrase_parse(iter, end, parser, parser::skipper, expression_);

        if (success) {
            if (iter != end) {
                error_handler(iter, "Error! Expecting end of input here: ");
            }
            else {
                /* nothing */;
            }
        }
    } catch(x3::expectation_failure<parser::iterator_type> const& e) {
        error_handler(e.where(), "Error! Expecting " + e.which() + " here: ");
    }

    return success;
}


} } } // namespace eda.vhdl93.parser

