#include <ibis/vhdl/parser/parse.hpp>

#include <ibis/vhdl/parser/grammar.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/parser/skipper.hpp>

#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/context.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <iostream>
#include <iterator>
#include <new>  // for bad_alloc
#include <type_traits>

namespace ibis::vhdl::parser {

// required to successfully compile Spirit X3 rules, since we don't include
// 'grammar_decl.hpp' and hence all it's declarations.
#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_DECLARE(design_file_type)
#endif

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

bool parse::operator()(position_cache<parser::iterator_type>::proxy& position_cache_proxy,
                       parser::context& ctx, ast::design_file& design_file)
{
    using vhdl::parser::iterator_type;

    static_assert(
        std::is_base_of_v<std::forward_iterator_tag,
                          typename std::iterator_traits<parser::iterator_type>::iterator_category>,
        "iterator type must be of multi-pass iterator");

    parser::diagnostic_handler_type diagnostic_handler{ os, ctx, position_cache_proxy };

    // clang-format off
    auto const parser =
        x3::with<parser::position_cache_tag>(std::ref(position_cache_proxy))[
            x3::with<parser::diagnostic_handler_tag>(std::ref(diagnostic_handler))[
                parser::grammar()
            ]
        ];
    // clang-format on

    auto [iter, end] = position_cache_proxy.range();

    // using different iterator_types causes linker errors, see e.g.
    // [linking errors while separate parser using boost spirit x3](
    //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
    //
    static_assert(std::is_same_v<decltype(iter), iterator_type>, "iterator types must be the same");

    auto const filename = position_cache_proxy.file_name();

    try {
        bool const parse_ok =
            x3::phrase_parse(iter, end, parser >> x3::eoi, parser::skipper, design_file);

        if (!parse_ok) {
            using boost::locale::format;
            using boost::locale::translate;

            using error_type = typename vhdl::diagnostic_handler<parser::iterator_type>::error_type;
            auto constexpr parser_error = error_type::parser;

            std::string const error_message{
                (format(translate("Source file '{1}' failed to parse!")) % filename).str()
            };

            diagnostic_handler(iter, error_message, parser_error);
        }

        return parse_ok;
    }
    catch (std::bad_alloc const& e) {
        // @todo Re-throw using C++11 exception_ptr, see 2nd answer
        // [How do I make a call to what() on std::exception_ptr](
        // https://stackoverflow.com/questions/14232814/how-do-i-make-a-call-to-what-on-stdexception-ptr)
        //
        os << make_exception_description(e, filename);
    }
    catch (std::exception const& e) {
        os << make_exception_description(e, filename);
    }
    catch (...) {
        os << make_exception_description(filename);
    }

    return false;
}

std::string parse::make_exception_description(std::exception const& exception,
                                              std::string_view filename)
{
    using boost::locale::format;
    using boost::locale::translate;

    return (format(translate("ExceptionDescription",
                             "Caught exception '{1}' during parsing file '{2}'"))  // --
            % exception.what()                                                     // {1}
            % filename                                                             // {2}
            )
        .str();
}

std::string parse::make_exception_description(std::string_view filename)
{
    using boost::locale::format;
    using boost::locale::translate;

    return (format(translate("ExceptionDescription",
                             "Caught unexpected exception during parsing file '{1}'"))  // --
            % filename                                                                  // {1}
            )
        .str();
}

}  // namespace ibis::vhdl::parser
