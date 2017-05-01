Tales of boost.spirit X3
========================

Nasty linker error
------------------

During development of the VHDL parser the rules increases and hence the compiler
time. The obvious way is to split the rules into separate compile units. And
starting with this the linker problem arise. I took several attemts to get the
origin of this. Boost.spirit has X3 examples of splitting the rules, e.g. the x3
`calc9`_ example and shows the way to go by using the macros
BOOST_SPIRIT_{DEFINE, DECLARE, INSTANTIATE}.

After reducing the problem and concentrating to the spirit x3 part I came
finally to to these redux:

- The AST (`ast.hpp`)

.. code-block:: c++
   :linenos:
    #ifndef AST_HPP_
    #define AST_HPP_

    #include <string>
    #include <boost/fusion/include/adapt_struct.hpp>

    namespace ast {
       struct string_literal {
            std::string literal;
        };
    }

    BOOST_FUSION_ADAPT_STRUCT(ast::string_literal,
        literal
    )

    #endif // AST_HPP_

- Grammar definition (`grammar_def.hpp`) to be used by the main aka client:

.. code-block:: c++
   :linenos:
    #include "ast.hpp"
    #include <boost/spirit/home/x3.hpp>
    #if defined(LINKER_ERROR)
    #include "literal.hpp"
    #endif

    namespace parser {

       namespace x3 = boost::spirit::x3;

    #if !defined(LINKER_ERROR)
        struct string_literal_class;
        typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;
        string_literal_type const string_literal{ "string_literal" };
    #endif

    #if defined(LINKER_ERROR)
        namespace {
            auto const& string_literal = grammar::string_literal();
        }
    #endif

    #if !defined(LINKER_ERROR)
        auto const string_literal_def =
            x3::lexeme ['"' >> *x3::char_ >> '"' ]
            ;
    #endif

    #if !defined(LINKER_ERROR)
        BOOST_SPIRIT_DEFINE(string_literal)
    #endif
    }

- The string_literal rule definition (`literal_def.hpp`) by seperated as compile unit:

.. code-block:: c++
   :linenos:
    #ifndef PARSER_LITERAL_DEF_HPP_
    #define PARSER_LITERAL_DEF_HPP_

    #include "literal.hpp"

    namespace parser {

        namespace x3 = boost::spirit::x3;

        string_literal_type const string_literal { "string_literal" };

        auto const string_literal_def =
            x3::lexeme ['"' >> *x3::char_ >> '"' ]
            ;

        BOOST_SPIRIT_DEFINE(
            string_literal
        )
    }

    namespace grammar {
        parser::string_literal_type const& string_literal()
        {
            return parser::string_literal;
        }
    }


    #endif /* PARSER_LITERAL_DEF_HPP_ */

- there declaration (`literal.hpp`):

.. code-block:: c++
   :linenos:
    #ifndef PARSER_LITERAL_HPP_
    #define PARSER_LITERAL_HPP_

    #include "ast.hpp"
    #include <boost/spirit/home/x3.hpp>

    namespace parser {

        namespace x3 = boost::spirit::x3;

        struct string_literal_class;
        typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;

        BOOST_SPIRIT_DECLARE(string_literal_type);
    }

    namespace grammar {
        parser::string_literal_type const& string_literal();
    }

    #endif /* PARSER_LITERAL_HPP_ */

- ... and instance (`literal.cpp`):

.. code-block:: c++
   :linenos:
    #include "literal_def.hpp"
    #include "parser_config.hpp"

    namespace parser {
        BOOST_SPIRIT_INSTANTIATE(
            string_literal_type,
            iterator_type,
            context_type
        );
    }

- configuration of parser (`parser_config.hpp`):

.. code-block:: c++
   :linenos:
    #ifndef PARSER_CONFIG_HPP_
    #define PARSER_CONFIG_HPP_

    #include <boost/spirit/home/x3.hpp>
    #include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

    namespace parser {
        namespace x3 = boost::spirit::x3;

        template <typename Iterator>
        using error_handler = x3::error_handler<Iterator>;
        using error_handler_tag = x3::error_handler_tag;


        typedef std::string::const_iterator                 iterator_type;

        typedef error_handler<iterator_type>                error_handler_type;

        typedef x3::phrase_parse_context<
                x3::iso8859_1::space_type>::type            phrase_context_type;

        typedef x3::with_context<
            error_handler_tag
            , std::reference_wrapper<error_handler_type> const
            , phrase_context_type
        >::type                                             context_type;
    }

    #endif /* PARSER_CONFIG_HPP_ */

- the main program (`main.cpp`) resp. client:

.. code-block:: c++
   :linenos:
    #include "grammar_def.hpp"
    #include "parser_config.hpp"
    #include <iostream>

    int main()
    {
        namespace x3 = boost::spirit::x3;

        ast::string_literal  attr;

        std::string input{ " Hello " };

        using parser::iterator_type;
        iterator_type iter = input.begin();
        iterator_type end = input.end();

        parser::error_handler_type error_handler(iter, end, std::cerr);

        auto const parser =
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                  parser::string_literal
            ];

        bool success = x3::phrase_parse(iter, end, parser, x3::iso8859_1::space, attr);

        return 0;
    }

- and finally, to be complete, the CMake file used; allowing per option to
  compile the sources with and without the linker error:

.. code-block:: c++
   :linenos:
    cmake_minimum_required(VERSION 3.6)

    project(x3_linker_error LANGUAGES CXX)
    find_package(Boost REQUIRED COMPONENTS system)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    # lib
    add_library(${PROJECT_NAME}_x3 STATIC
        literal.cpp
    )
    # exe
    add_executable(${PROJECT_NAME}
        main.cpp
    )
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_x3
        ${Boost_SYSTEM_LIBRARY}
    )

    set(CMAKE_VERBOSE_MAKEFILE ON)
    option(LINKER_ERROR "Enforce the linker error" ON)
    if(LINKER_ERROR)
    message("## Build to show linker errors")
    target_compile_definitions(${PROJECT_NAME}_x3 PRIVATE LINKER_ERROR)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINKER_ERROR)
    endif()


And here we are with the linker error:
::
    In function `bool boost::spirit::x3::rule<parser::string_literal_class, ast::string_literal, false>::parse<__gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, boost::spirit::x3::context<boost::spirit::x3::error_handler_tag, std::reference_wrapper<boost::spirit::x3::error_handler<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > const, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::iso8859_1, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> >, ast::string_literal>(__gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >&, __gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > const&, boost::spirit::x3::context<boost::spirit::x3::error_handler_tag, std::reference_wrapper<boost::spirit::x3::error_handler<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > const, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::iso8859_1, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> > const&, boost::spirit::x3::unused_type, ast::string_literal&) const':
    main.cpp:(.text._ZNK5boost6spirit2x34ruleIN6parser20string_literal_classEN3ast14string_literalELb0EE5parseIN9__gnu_cxx17__normal_iteratorIPcNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEENS1_7contextINS1_17error_handler_tagEKSt17reference_wrapperINS1_13error_handlerINSA_IPKcSH_EEEEENSJ_INS1_11skipper_tagEKNS1_10char_classINS0_13char_encoding9iso8859_1ENS1_9space_tagEEENS1_11unused_typeEEEEES6_EEbRT_RKS13_RKT0_S10_RT1_[_ZNK5boost6spirit2x34ruleIN6parser20string_literal_classEN3ast14string_literalELb0EE5parseIN9__gnu_cxx17__normal_iteratorIPcNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEENS1_7contextINS1_17error_handler_tagEKSt17reference_wrapperINS1_13error_handlerINSA_IPKcSH_EEEEENSJ_INS1_11skipper_tagEKNS1_10char_classINS0_13char_encoding9iso8859_1ENS1_9space_tagEEENS1_11unused_typeEEEEES6_EEbRT_RKS13_RKT0_S10_RT1_]+0x37): undefined reference to `bool parser::parse_rule<__gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, boost::spirit::x3::context<boost::spirit::x3::error_handler_tag, std::reference_wrapper<boost::spirit::x3::error_handler<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > const, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::iso8859_1, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> >, ast::string_literal>(boost::spirit::x3::rule<parser::string_literal_class, ast::string_literal, false>, __gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >&, __gnu_cxx::__normal_iterator<char*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > const&, boost::spirit::x3::context<boost::spirit::x3::error_handler_tag, std::reference_wrapper<boost::spirit::x3::error_handler<__gnu_cxx::__normal_iterator<char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > const, boost::spirit::x3::context<boost::spirit::x3::skipper_tag, boost::spirit::x3::char_class<boost::spirit::char_encoding::iso8859_1, boost::spirit::x3::space_tag> const, boost::spirit::x3::unused_type> > const&, ast::string_literal&)'

At time of writing (April 2017) at StackOverflow there is one linker error
listed: `x3_link_err_space`_ where two different space types are used. Verified,
it doesn't cover my problem. Further, that the Iterator type is getting deduced
as ``std::string::iterator``, not ``std::string::const_iterator``. Not understood
and hence ignored.


The linker error is not very readable, but by using an online GNU C++ symbol
demangler like `demangler.com`_ the demangled symbols are human readable.
After applying some substitutes the result is:

::
    In function `bool x3::rule<parser::string_literal_class, ast::string_literal, false>::parse<string::iterator, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> >, ast::string_literal>(string::iterator&, string::iterator const&, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> > const&, x3::unused_type, ast::string_literal&) const':
    main.cpp:(.text.bool x3::rule<parser::string_literal_class, ast::string_literal, false>::parse<string::iterator, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> >, ast::string_literal>(string::iterator&, string::iterator const&, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> > const&, x3::unused_type, ast::string_literal&) const[bool x3::rule<parser::string_literal_class, ast::string_literal, false>::parse<string::iterator, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> >, ast::string_literal>(string::iterator&, string::iterator const&, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> > const&, x3::unused_type, ast::string_literal&) const] 0x37): undefined reference to `bool parser::parse_rule<string::iterator, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> >, ast::string_literal>(x3::rule<parser::string_literal_class, ast::string_literal, false>, string::iterator&, string::iterator const&, x3::context<x3::error_handler_tag, std::reference_wrapper<x3::error_handler<string::const_iterator > > const, x3::context<x3::skipper_tag, x3::char_class<char_encoding::iso8859_1, x3::space_tag> const, x3::unused_type> > const&, ast::string_literal&)'

Maybe some wonder by doing this that there are two iterator types which I never
used by spirit's x3 source! After some looking over the code and comparing again
with the calc9 example I found a conceptional difference by the iterator
instances in the main.cpp. calc9 used explicit ``parser::iterator_type``.
Gotcha! By fixing it it compiles without linker errors. At the time of writing
I found again the `x3_link_err_space`_ answer and now understand what was the
meaning of the different iterators...


.. URI
.. _x3_link_err_space: https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3
.. _calc9: https://github.com/boostorg/spirit/tree/develop/example/x3/calc/calc9
.. _demangler.com: demangler.com
