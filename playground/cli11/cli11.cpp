#include <CLI/CLI11.hpp>
#include <iostream>
#include <string>

#include <boost/locale/generator.hpp>
#include <boost/locale/localization_backend.hpp>
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

int main(int argc, char **argv) 
{
    using boost::locale::translate;

    CLI::App app("CLI11 1.6.1");

    try {
        std::string file;
        CLI::Option *opt = app.add_option("-f,--file,file", file, translate("File name"));

        int v{0};
        CLI::Option *flag = app.add_flag("--flag", v, translate("Some flag that can be passed multiple times"));

        CLI11_PARSE(app, argc, argv);

        std::cout << "Working on file: " << file << ", direct count: " << app.count("--file")
                << ", opt count: " << opt->count() << std::endl;
        std::cout << "Received flag: " << v << " (" << flag->count() << ") times\n";
    }
    catch(...) { }

    return 0;
}
