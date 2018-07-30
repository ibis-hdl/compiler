/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <ibis/parse_cli.hpp>
#include <ibis/global_options.hpp>
#include <eda/util/infix_ostream_iterator.hpp>

#include <iterator>
#include <iostream>


int main(int argc, const char *argv[])
{
    parse_cli(argc, argv);

    std::cout << "processing:\n";

    auto const& sources{ ibis::global_options.source_files };

    std::copy(sources.begin(), sources.end(),
              eda::util::infix_ostream_iterator<std::string>(std::cout, ", "));
    std::cout << "\n";

    return 0;
}


