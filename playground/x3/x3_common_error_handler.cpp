/*
 * x3_error_handler.cpp
 *
 *  Created on: 07.06.2018
 *      Author: olaf
 *
 * https://www.boost.org/doc/libs/develop/libs/spirit/example/x3/annotation.cpp
 * https://www.boost.org/doc/libs/develop/libs/spirit/example/x3/error_handling.cpp
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

//#include <boost/spirit/home/x3/support/context.hpp>
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


#if 1 // eclipse syntax checker sucks here
BOOST_FUSION_ADAPT_STRUCT(client::ast::person,
    first_name, last_name
)

BOOST_FUSION_ADAPT_STRUCT(client::ast::employee,
    age, who, salary
)
#endif

namespace client
{
    namespace parser
    {
        namespace x3 = boost::spirit::x3;

        // the x3 parser context
        typedef std::string::const_iterator                         iterator_type;
        typedef x3::error_handler<iterator_type>                    error_handler_type;
        typedef x3::phrase_parse_context<x3::ascii::space_type>::type phrase_context_type;

        typedef x3::context<
          x3::error_handler_tag, std::reference_wrapper<error_handler_type> /* const */,
          phrase_context_type
        >
        context_type;


        ///////////////////////////////////////////////////////////////////////
        //  Our error handler
        ///////////////////////////////////////////////////////////////////////
        struct error_handler_base
        {
            std::map<std::string, std::string> id_map;

            error_handler_base()
            {
                id_map["quoted_string"] = "Quoted String";
                id_map["person"]        = "Person";
                id_map["employee"]      = "Employee";
            }

            template <typename Iterator, typename Exception, typename Context>
            x3::error_handler_result
            on_error(Iterator& first, Iterator const& last,
                     Exception const& x, Context const& context)
            {
#if 1
                static_assert(
                    std::is_same<Context, parser::context_type>::value,
                    "The Spirit.X3 Context must be equal"
                );

                //x3::context<
                //  x3::error_handler_tag, std::reference_wrapper<x3::error_handler<std::string::const_iterator > >,
                //  x3::context<x3::skipper_tag, x3::char_class<char_encoding::ascii, x3::space_tag> const, x3::unused_type>
                //>
                std::cout << "context_type:\n" << boost::typeindex::type_id<context_type>().pretty_name() << "\n";
                std::cout << "Context Tmpl:\n" << boost::typeindex::type_id<Context>().pretty_name() << "\n";
#endif

                std::string which = x.which();
                auto iter = id_map.find(which);

                if (iter != id_map.end()) {
//                    std::cout << "Lookup for \'" << which
//                              << "' -> '" << iter->second << "'\n";
                    which = iter->second;
                }
                else {
//                    std::cout << "Lookup for \'" << which
//                              << "' failed\n";
                }

                std::string message{
                    "Oops! Expecting: " + which + " here:"};

                auto& x3_error_handler = x3::get<x3::error_handler_tag>(context).get();
                x3_error_handler(x.where(), message);

                return x3::error_handler_result::fail;
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
        struct employee_class : x3::annotate_on_success {};
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

    auto const employees = client::parser::employees;

    auto const parser =
        // we pass our position_cache to the parser so we can access
        // it later in our on_sucess handlers
        x3::with<x3::error_handler_tag>(std::ref(error_handler))
        [
             employees
        ];

    using x3::ascii::space;

    bool r = phrase_parse(iter, end, parser, space, ast);

    if (r && iter == end)
    {
        std::cout << boost::fusion::tuple_open('[');
        std::cout << boost::fusion::tuple_close(']');
        std::cout << boost::fusion::tuple_delimiter(", ");

        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";

        for (auto const& emp : ast)
        {
            std::cout << "got: " << emp << std::endl;
        }
        std::cout << "\n-------------------------\n";

    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
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
