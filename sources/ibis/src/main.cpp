/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <ibis/parse_cli.hpp>
#include <ibis/global_options.hpp>
#include <eda/util/infix_ostream_iterator.hpp>
#include <eda/util/file/file_reader.hpp>

#include <iostream>


int main(int argc, const char *argv[])
{
    parse_cli(argc, argv);

    std::cout << "processing:\n";

    auto const& sources { ibis::global_options.source_files };

    std::copy(sources.begin(), sources.end(),
              eda::util::infix_ostream_iterator<std::string>(std::cout, ", "));
    std::cout << "\n";

    eda::util::file_loader ld { std::cerr };

    //std::cout << std::boolalpha << ld.exist_files(sources)<< "\n";
    std::cout << std::boolalpha << ld.unique_files(sources) << "\n";

    try {
        for (auto const filename : sources) {
            auto const contents = ld.read_file(filename);
            std::cout << "\n------------------------------------------------\n";
            std::cout << contents;
            std::cout << "\n------------------------------------------------\n";
            std::time_t t = ld.timesstamp(filename);
            std::cout << "timestamp: " << t << "\n";
            std::cout << "------------------------------------------------\n";
        }
    }
    catch(std::exception const& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
    return 0;
}

