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

#include <eda/vhdl/ast/node/design_file.hpp>
#include <eda/vhdl/ast/position_cache.hpp>
#include <eda/vhdl/parser/error_handler.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>

#include <eda/support/boost/locale.hpp>             // IWYU pragma: keep

#include <iterator>
#include <new>                                      // for bad_alloc
#include <type_traits>
#include <iostream>


namespace eda { namespace vhdl { namespace parser {


bool parse::operator()(std::string const &input, ast::design_file& design_file)
{
    using vhdl::parser::iterator_type;

    iterator_type iter = input.begin();
    iterator_type end  = input.end();

    static_assert(std::is_base_of_v<
            std::forward_iterator_tag,
            typename std::iterator_traits<parser::iterator_type>::iterator_category
        >, "iterator type must be of multipass iterator");

    /* using different iterator_types causes linker errors, see e.g.
     * [linking errors while separate parser using boost spirit x3](
     *  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3) */
    static_assert(std::is_same_v<decltype(iter), iterator_type>,
                  "iterator types must be the same"
    );

    auto const parser =
        x3::with<parser::error_handler_tag>(std::ref(error_handler)) [
            parser::grammar()
    ];


    auto filename = error_handler.current_file().file_name();

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
                 % filename).str()};

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
        using unknown = struct { };
        os << make_exception_description(filename, unknown{});
    }

    return false;
}


template<typename ExceptionT>
std::string parse::make_exception_description(std::string const &filename,
                                              ExceptionT const& exception) const
{
    using boost::locale::format;
    using boost::locale::translate;

    std::string const what = [&] {
#ifndef __clang_analyzer__
        if constexpr(std::is_base_of_v<std::remove_reference_t<ExceptionT>, std::exception>) {
            return std::string{ exception.what() };
        }
#endif // __clang_analyzer__

        // make GGC quiet
        boost::ignore_unused(exception);

        /* An exception was caught which hasn't been derived from
         * std::exception, hence no what() is available - simple unknown. */
         return translate("ExceptionDescription", "unknown").str();
    }();

    return (format(translate("ExceptionDescription",
        "Caught exception '{1}' during parsing file '{2}'"
        ))
        % what
        % filename
        ).str();
};

} } } // namespace eda.vhdl.parser




