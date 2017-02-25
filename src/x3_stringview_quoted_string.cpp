
// c++14 experimental
#include <experimental/string_view>

namespace boost { namespace spirit { namespace x3 { namespace traits {

template <typename It>
void move_to(It b, It e, std::experimental::string_view& v)
{
	// FixMe: storage is contiguous as a concept check for input range
    v = std::experimental::string_view(&*b, std::size_t(std::distance(b,e)));
}

} } } }


#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>


namespace client { namespace ast
{
	using std::experimental::string_view;

    ///////////////////////////////////////////////////////////////////////////
    //  Our employee struct
    ///////////////////////////////////////////////////////////////////////////
    struct employee
    {
        int age;
        string_view surname;
        std::string forename;
        double salary;
    };

    using boost::fusion::operator<<;
}}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

BOOST_FUSION_ADAPT_STRUCT(client::ast::employee,
    age, surname, forename, salary
)

namespace client
{
    ///////////////////////////////////////////////////////////////////////////////
    //  Our employee parser
    ///////////////////////////////////////////////////////////////////////////////
    namespace parser
    {
        namespace x3 = boost::spirit::x3;
        namespace ascii = boost::spirit::x3::ascii;

        using x3::int_;
        using x3::lit;
        using x3::double_;
        using x3::lexeme;
        using ascii::char_;
        using x3::raw;

        x3::rule<class employee, ast::employee> const employee = "employee";

        auto const quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

        auto const employee_def =
            lit("employee")
            >> '{'
            >>  int_ >> ','
            >>  '"' >> lexeme[ raw[ +(char_ - '"') ] ] >> '"' >> ','
            >>  quoted_string >> ','
            >>  double_
            >>  '}'
            ;

        BOOST_SPIRIT_DEFINE(employee);
    }
}

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int
main()
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an employee of the form :"
        << "employee{age, \"surname\", \"forename\", salary } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    using boost::spirit::x3::ascii::space;
    typedef std::string::const_iterator iterator_type;
    using client::parser::employee;

    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        client::ast::employee emp;
        iterator_type iter = str.begin();
        iterator_type const end = str.end();
        bool r = phrase_parse(iter, end, employee, space, emp);

        if (r && iter == end)
        {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "got: " << emp << std::endl;
            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
