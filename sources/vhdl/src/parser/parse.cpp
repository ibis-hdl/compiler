/*
 * parse.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */


#include <eda/vhdl/parser/parse.hpp>
#include <eda/vhdl/parser/skipper.hpp>
#include <eda/vhdl/parser/grammar.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

#include <iostream>


namespace eda { namespace vhdl { namespace parser {


parse::parse(std::iostream& os_)
: os{ os_ }
{ }


bool parse::operator()(std::string const &input, ast::design_file& design_file,
                        fs::path const &filename)
{
    using iterator_type = vhdl::parser::iterator_type;

    iterator_type iter = input.begin();
    iterator_type end  = input.end();

    /* using different iterator_types causes linker errors, see e.g.
     * [linking errors while separate parser using boost spirit x3](
     *  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3) */
    static_assert(std::is_same<decltype(iter), iterator_type>::value
               && std::is_same<decltype(end),  iterator_type>::value,
                  "iterator types must be the same"
    );

    parser::error_handler_type error_handler(iter, end,
                                             os, filename.string());

    auto const parser =
        x3::with<x3::error_handler_tag>(std::ref(error_handler)) [
            parser::grammar()
    ];

    try {
        bool const parse_ok = x3::phrase_parse(
            iter, end,
            parser >> x3::eoi, parser::skipper,
            design_file
        );

        if (!parse_ok) {
            error_handler(iter, "Source file '"
                    + filename.string()
                    + "' failed to parse!");
        }

        return parse_ok;

    }
    catch(std::bad_alloc const& e) {
        // ToDo: Rethrow using C++11 exception_ptr
        os << "Memory exhausted: '"
           << e.what()
           << "'\n"
        ;
    }
    catch(std::exception const& e) {
        os << "Caught unexpected exception '"
                << e.what()
                << "'\n";
    }
    catch(...) {
        os << "Caught unexpected exception '<unknown>'\n";
    }

    return false;
}


} } } // namespace eda.vhdl.parser




