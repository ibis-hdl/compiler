/*
 * x3_debug.cpp
 *
 *  Created on: 26.03.2017
 *      Author: olaf
 */

#include <iostream>
#define BOOST_SPIRIT_X3_DEBUG_OUT std::cout
//#define BOOST_SPIRIT_X3_DEBUG

#include <eda/vhdl93/parser/grammar_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>
#include <eda/vhdl93/ast_printer.hpp>



int main()
{
   namespace x3 = boost::spirit::x3;

   namespace ast = eda::vhdl93::ast;
   namespace parser = eda::vhdl93::parser;

   for(std::string const str: {
       "VHDL",
       "\\BoBus\\",                // expected '\Bus\'
       "\\Foo\\\\oh\\",         // expected '\Foo\\oh\'
       "\\Foo\\\\Bar\\\\Baz\\", // expected '\Foo\\Bar\\Baz\'
    })
    {
     parser::iterator_type iter = str.begin(), end = str.end();

     ast::expression attr;

     std::cout << "parse `" << str << "`:\n";

     bool r = x3::phrase_parse(iter, end, parser::expression, x3::space, attr);

     if (r && iter == end) {
       std::cout << "succeeded: ";
       ast::printer print(std::cout);
       print(attr);
       std::cout << '\n';
     } else {
       std::cout << "*** failed ***\n";
     }
   }

   return 0;
}



