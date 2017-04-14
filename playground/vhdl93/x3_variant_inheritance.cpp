/*
 * x3_variant_inheritance.cpp
 *
 *  Created on: 14.04.2017
 *      Author: olaf
 */

/*
 * use case for signal_list
 * where signal_name is a name (variant)
 */
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <string>
#include <iostream>

namespace x3 = boost::spirit::x3;

namespace ast {
struct name : x3::variant<double, std::string>
{
    using base_type::base_type;
    using base_type::operator=;

    //name(base&& b) : base_type(std::move(static_cast<base_type&>(b)))  { }
};


struct signal_name : name
{
    using base_type::base_type;
    using base_type::operator=;

};
}

namespace parser {

    auto const name = x3::rule<struct _, ast::name> {} = +x3::char_;
    //auto const signal_name = x3::rule<struct _, ast::signal_name> {} = name;
}

int main()
{
   for(std::string const str: {
       "Bar",
       }
   ) {
     auto iter = str.begin();
     auto const end = str.end();

     ast::name attr;

     std::cout << "parse `" << str << "`:\n";

     bool r = x3::phrase_parse(iter, end, parser::name , x3::space, attr);

     if (r && iter == end) {
       std::cout << "SUCCEEDED: '" << attr << "'\n\n";
     } else {
       std::cout << "*** FAILED ***\n";
     }
     std::cout << "-----------------------------------------------------------\n";
   }

   return 0;
}



