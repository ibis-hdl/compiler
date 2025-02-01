//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

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
#include <ibis/util/get_iterator_pair.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <iostream>
#include <iterator>
#include <new>  // for bad_alloc
#include <ranges>
#include <type_traits>

namespace ibis::vhdl::parser {

// required to successfully compile Spirit X3 rules, since we don't include
// 'grammar_decl.hpp' and hence all it's declarations.
#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_DECLARE(design_file_type)
#endif

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

bool parse::operator()(current_file_type&& current_file, position_cache_type& position_cache,
                       vhdl_context_type& vhdl_ctx, ast::design_file& design_file)
{
    using ibis::util::get_iterator_pair;

    static_assert(
        std::is_base_of_v<std::forward_iterator_tag,
                          typename std::iterator_traits<iterator_type>::iterator_category>,
        "iterator type must be of multi-pass iterator");  // ToDo realize this as concept

    // clang-format off
    parser::diagnostic_handler_type diagnostic_handler{
        os, std::move(current_file), std::ref(position_cache), std::ref(vhdl_ctx)
    };
    // clang-format on

    auto ast_annotator = position_cache.annotator_for(current_file.id());

    // clang-format off
    auto const parser =
        x3::with<parser::annotator_tag>(std::ref(ast_annotator))[
            x3::with<parser::diagnostic_handler_tag>(std::ref(diagnostic_handler))[
                parser::grammar()
            ]
        ];
    // clang-format on

    auto [iter, end] = get_iterator_pair(current_file.file_contents());

    // using different iterator_types causes linker errors, see e.g.
    // [linking errors while separate parser using boost spirit x3](
    //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
    //
    static_assert(std::is_same_v<decltype(iter), iterator_type>, "iterator types must be the same");

    auto const filename = current_file.file_name();
    bool parse_ok = false;

    try {
        parse_ok = x3::phrase_parse(iter, end, parser >> x3::eoi, parser::skipper, design_file);

        if (!parse_ok) {
            using boost::locale::format;
            using boost::locale::translate;

            std::string const error_message{
                (format(translate("Source file '{1}' failed to parse!")) % filename).str()
            };

            diagnostic_handler.parser_error(iter, error_message);
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

    return parse_ok;
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
