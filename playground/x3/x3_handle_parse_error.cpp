/*
 * x3_handle_parse_error.cpp
 *
 *  Created on: 08.06.2018
 *      Author: olaf
 *
 *  see:
 *  - [Annotations - Decorating the ASTs](
 *     https://www.boost.org/doc/libs/develop/libs/spirit/doc/x3/html/spirit_x3/tutorials/annotation.html)
 *  - [Error Handling](
 *     https://www.boost.org/doc/libs/develop/libs/spirit/doc/x3/html/spirit_x3/tutorials/error_handling.html)
 *
 *  also useful with 'diagnostic' approach (even if shown using Qi)
 *  - [Dispatching on Expectation Point Failures](
 *     http://boost-spirit.com/home/2011/02/28/dispatching-on-expectation-point-failures/)
 */

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <map>

#include <boost/type_index.hpp>


namespace client { namespace ast
{
    namespace x3 = boost::spirit::x3;

    struct person : x3::position_tagged
    {
        person(
            std::string const& first_name = ""
          , std::string const& last_name = ""
        )
          : first_name(first_name)
          , last_name(last_name)
        {}

        std::string first_name, last_name;
    };

    struct employee : x3::position_tagged
    {
        int age;
        person who;
        double salary;
    };

    using employees = std::vector<client::ast::employee>;

    using boost::fusion::operator<<;
}}


BOOST_FUSION_ADAPT_STRUCT(client::ast::person,
    first_name, last_name
)

BOOST_FUSION_ADAPT_STRUCT(client::ast::employee,
    age, who, salary
)


namespace client
{
    namespace parser
    {
        namespace context {

            struct tag;

            struct foo
            {
                /* Since the parser rule names and lookup map are written by
                 * own it shouldn't necessary to case insensitive compare on
                 * keys, anyway see
                 * [Making map::find operation case insensitive](
                 *  https://stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive)
                 * recommended in Meyers, Effective STL when internationalization
                 * and embedded NULLs aren't an issue. */
                struct icase_strcmp {
                    bool operator()(std::string const& lhs, std::string const& rhs) const {
                            return ::strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
                        }
                };

                std::map<std::string, std::string, icase_strcmp> id_map;

                unsigned error_count;
                unsigned warning_count;

                foo()
                : error_count{ 0 }
                , warning_count{ 0 }
                {
                    id_map["quoted_string"] = "Quoted String";
                    id_map["person"]        = "Person";
                    id_map["employee"]      = "Employee";
                }

                std::string const& name(std::string const& name_)
                {
                    auto const iter = id_map.find(name_);

                    if(iter != id_map.end()) {
                        return iter->second;
                    }
                    else {
                        return name_;
                    }
                }
            };

        }


        namespace x3 = boost::spirit::x3;

        ///////////////////////////////////////////////////////////////////////
        // Our error handler
        // Note, error_handler's context is only of type:
        //
        // x3::context<
        //    x3::error_handler_tag,
        //    std::reference_wrapper<x3::error_handler<std::string::const_iterator>> const,
        //    x3::context<
        //        client::parser::context::tag,
        //        std::reference_wrapper<client::parser::context::foo> const,
        //    x3::context<
        //        x3::skipper_tag,
        //        x3::char_class<spirit::char_encoding::ascii, x3::space_tag> const,
        //        x3::unused_type>
        //    >
        // >
        //
        // while the parser rule context contains all of them!
        ///////////////////////////////////////////////////////////////////////
        struct error_handler_base
        {
            template <typename Iterator, typename Exception, typename Context>
            x3::error_handler_result
            on_error(Iterator& first, Iterator const& last,
                     Exception const& x, Context const& context)
            {
                auto& foo = x3::get<client::parser::context::tag>(context).get();

                std::string message{
                    "Oops! Expecting: " + foo.name(x.which()) + " here:"};

                auto& x3_error_handler = x3::get<x3::error_handler_tag>(context).get();
                x3_error_handler(x.where(), message);

                return x3::error_handler_result::fail;
            }
        };

        struct employee_error_handler
        {
            template <typename Iterator, typename Exception, typename Context>
            x3::error_handler_result
            on_error(Iterator& first, Iterator const& last,
                     Exception const& x, Context const& context)
            {
                auto& foo = x3::get<client::parser::context::tag>(context).get();

                std::string message{
                    "Employee Error: expecting: " + foo.name(x.which()) + " here:"};

                foo.error_count++;

                auto& x3_error_handler = x3::get<x3::error_handler_tag>(context).get();
                x3_error_handler(x.where(), message);

                // no way to force/clear the attribute, see note on top
                //std::cout << boost::typeindex::type_id<Context>().pretty_name() << "\n";

                // advance iterator to the end of employee block
                x3::parse(first, last, +~x3::char_('}') >> x3::char_('}'));

                return x3::error_handler_result::accept;
            }
        };

        ///////////////////////////////////////////////////////////////////////
        //  Our employee parser
        ///////////////////////////////////////////////////////////////////////
        namespace ascii = boost::spirit::x3::ascii;

        using x3::int_;
        using x3::double_;
        using x3::lexeme;
        using ascii::char_;

        struct quoted_string_class;
        struct person_class;
        struct employee_class;
        struct employees_class;

        x3::rule<quoted_string_class, std::string> const quoted_string = "quoted_string";
        x3::rule<person_class, ast::person> const person = "person";
        x3::rule<employee_class, ast::employee> const employee = "employee";
        x3::rule<employees_class, ast::employees> const employees = "employees";

        auto const show_ctx = [](auto const& ctx) {
            std::cout << boost::typeindex::type_id<decltype(ctx)>().pretty_name() << "\n";
        };

        auto const quoted_string_def = lexeme['"' >> +(char_ - '"') >> '"'];
        auto const person_def = quoted_string > ',' > quoted_string;

        auto const employee_def =
                '{'
            >   int_ > ','
            >   person > ','
            >   double_
            >   '}'
            ;

        auto const employees_def = employee >> *(',' > employee);

        BOOST_SPIRIT_DEFINE(quoted_string, person, employee, employees);

        struct quoted_string_class : x3::annotate_on_success {};
        struct person_class : x3::annotate_on_success {};
        struct employee_class : x3::annotate_on_success, employee_error_handler {};
        struct employees_class : x3::annotate_on_success, error_handler_base {};
    }
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Our main parse entry point
///////////////////////////////////////////////////////////////////////////////
namespace fs = boost::filesystem;
namespace x3 = boost::spirit::x3;


client::ast::employees
parse(std::string const& input, fs::path source_path)
{
    typedef std::string::const_iterator iterator_type;

    iterator_type iter = input.begin();
    iterator_type const end = input.end();

    client::ast::employees ast;

    typedef boost::spirit::x3::error_handler<iterator_type> error_handler_type;
    error_handler_type error_handler{iter, end, std::cout, source_path.string()};

    auto foo = client::parser::context::foo{};

    auto const employees = client::parser::employees;

    auto const parser =
        x3::with<client::parser::context::tag>(std::ref(foo))[
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                 employees
            ]
        ];

    using x3::ascii::space;

    bool parse_ok = phrase_parse(iter, end, parser, space, ast);

    if (parse_ok)
    {
        std::cout << boost::fusion::tuple_open('[');
        std::cout << boost::fusion::tuple_close(']');
        std::cout << boost::fusion::tuple_delimiter(", ");

        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded";
        if(foo.error_count > 0) {
            std::cout << " with "<< foo.error_count << " error(s)";
        }
        std::cout << "\n";

        for (auto const& emp : ast)
        {
            std::cout << "got: " << emp << std::endl;
        }
        std::cout << "\n-------------------------\n";

        if(iter != end) {
            std::cout << "-------------------------\n";
            std::cout << "But some input has been left:\n";
            std::cout << std::string(iter, end) << "\n";
            std::cout << "-------------------------\n";
        }

    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed completely\n";
        std::cout << "-------------------------\n";
        ast.clear();
    }
    return ast;
}

// Good sample:

std::string good_input = R"(
{
    23,
    "Amanda",
    "Stefanski",
    1000.99
},
{
    35,
    "Angie",
    "Chilcote",
    2000.99
},
{
    43,
    "Dannie",
    "Dillinger",
    3000.99
},
{
    22,
    "Dorene",
    "Dole",
    2500.99
},
{
    38,
    "Rossana",
    "Rafferty",
    5000.99
}
)";

// Input sample with error:

std::string bad_input = R"(
{
    23,
    "Amanda",
    "Stefanski",
    1000.99
},
{
    35,
    "Angie",
    "Chilcote",
    2000.99
},
{
    43,
    'I am not a person!'    <--- this should be a person
    3000.99
},
{
    22,
    'I am also not a person!' <--- this should be a person too
    "Sparrow",
    2500.99
},
{
    22,
    "Dorene",
    "Dole",
    2500.99
},
{
    38,
    "Rossana",
    "Rafferty",
    5000.99
}
)";

int main()
{
    // Good input
    parse(good_input, "string@good_input");

   // Bad input
    std::cout << "Now we have some errors" << std::endl;
    parse(bad_input, "string@bad_input");
    return 0;
}


// Get the source of the 2nd employee and print it
//    auto pos = positions.position_of(ast[1]); // zero based of course!
//    std::cout << "Here's the 2nd employee:" << std::endl;
//    std::cout << std::string(pos.begin(), pos.end()) << std::endl;
//    std::cout << "-------------------------\n";




