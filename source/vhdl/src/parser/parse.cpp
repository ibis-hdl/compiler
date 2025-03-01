//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/parser/parse.hpp>

#include <ibis/util/get_iterator_pair.hpp>
#include <ibis/vhdl/ast/node/design_file.hpp>
#include <ibis/vhdl/parser/grammar.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>
#include <ibis/vhdl/parser/skipper.hpp>
#include <ibis/vhdl/ast/ast_context.hpp>

// #include <boost/spirit/home/x3.hpp>                    // IWYU pragma: keep
#include <boost/spirit/home/x3/auxiliary/eoi.hpp>      // for eoi_parser, eoi
#include <boost/spirit/home/x3/core/parse.hpp>         // for phrase_parse
#include <boost/spirit/home/x3/directive/with.hpp>     // for with_directive, with, with_gen
#include <boost/spirit/home/x3/nonterminal/rule.hpp>   // for rule, BOOST_SPIRIT_DECLARE
#include <boost/spirit/home/x3/operator/sequence.hpp>  // for sequence, operator>>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <exception>
#include <functional>
#include <iterator>
#include <new>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include <ibis/namespace_alias.hpp>

namespace ibis::vhdl::parser {

// required to successfully compile Spirit X3 rules, since we don't include
// 'grammar_decl.hpp' and hence all it's declarations.
#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_DECLARE(design_file_type)
#endif

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

template <std::random_access_iterator IteratorT>
bool parse<IteratorT>::operator()(current_file_type& current_file,
                                  position_cache_type& position_cache, vhdl_context_type& vhdl_ctx,
                                  ast::design_file& design_file) const
{
    using ibis::util::get_iterator_pair;

    ast::ast_context<iterator_type> ast_context{ current_file, std::ref(position_cache) };

    // clang-format off
    diagnostic_handler_type diagnostic_handler{
        os, std::ref(ast_context), std::ref(vhdl_ctx)
    };
    // clang-format on

    // ToDo Check idea, approach used in
    // [Cleanest way to handle both quoted and unquoted strings in Spirit.X3](
    // https://stackoverflow.com/questions/74031183/cleanest-way-to-handle-both-quoted-and-unquoted-strings-in-spirit-x3)

    // clang-format off
    auto const parser =
        x3::with<parser::annotator_tag>(std::ref(ast_context))[
            x3::with<parser::diagnostic_handler_tag>(std::ref(diagnostic_handler))[
                parser::grammar()
            ]
        ];
    // clang-format on

    auto [iter, end] = get_iterator_pair(ast_context.file_contents());

    // using different iterator_types causes linker errors, see e.g.
    // [linking errors while separate parser using boost spirit x3](
    //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
    //
    static_assert(std::is_same_v<decltype(iter), iterator_type>, "iterator types must be the same");

    auto const filename = ast_context.file_name();
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

template <std::random_access_iterator IteratorT>
std::string parse<IteratorT>::make_exception_description(std::exception const& exception,
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

template <std::random_access_iterator IteratorT>
std::string parse<IteratorT>::make_exception_description(std::string_view filename)
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

// ----------------------------------------------------------------------------
// Explicit template instantiation
// ----------------------------------------------------------------------------
namespace ibis::vhdl::parser {

template class parse<vhdl::parser::iterator_type>;

}  // namespace ibis::vhdl::parser
