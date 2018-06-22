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

#include <eda/support/boost/locale.hpp>

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

    auto const make_exception_description = [](fs::path const &filename, auto const& e)
    {
        using boost::locale::format;
        using boost::locale::translate;

        // [IIFE idiom](https://www.bfilipek.com/2016/11/iife-for-complex-initialization.html)
        std::string const what = [&] {
            if constexpr(std::is_base_of<decltype(e), std::exception>::value) {
                return e.what();
            }
            else {
                return translate("ExceptionDescription", "unknown");
            }
        }();

        std::string const str{(format(translate("ExceptionDescription",
            "Caught exception '{1}' during parsing file '{2}'"
            ))
            % what
            % filename.string()
            ).str()};

        return str;
    };

    try {
        bool const parse_ok = x3::phrase_parse(
            iter, end,
            parser >> x3::eoi, parser::skipper,
            design_file
        );

        if (!parse_ok) {

            using boost::locale::format;
            using boost::locale::translate;

            std::string const message{
                (format(translate("Source file '{1}' failed to parse!"))
                 % filename.string()).str()};

            error_handler(iter, message);
        }

        return parse_ok;
    }
    catch(std::bad_alloc const& e) {
        /* ToDo: Re-throw using C++11 exception_ptr, see 2nd answer
         * [How do I make a call to what() on std::exception_ptr](
         * https://stackoverflow.com/questions/14232814/how-do-i-make-a-call-to-what-on-stdexception-ptr)  */
        os << make_exception_description(filename, e);
    }
    catch(std::exception const& e) {
        os << make_exception_description(filename, e);
    }
    catch(...) {
        typedef struct { } unknown;
        os << make_exception_description(filename, unknown{});
    }

    return false;
}


} } } // namespace eda.vhdl.parser




