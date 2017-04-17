#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>
#include <list>


namespace ast
{
    struct identifer {
        int                     name;
    };
    struct expression {
        struct chunk {
            char                operator_;
            ast::identifer      identifer;
        };
        ast::identifer          identifer;
        std::list<chunk>        chunk_list;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::identifer,
    name
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression::chunk,
    operator_, identifer
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression,
    identifer, chunk_list
)


namespace boost { namespace spirit { namespace x3 { namespace traits {

void move_to(ast::expression::chunk&& chunk, std::list<ast::expression::chunk>& chunk_list,
        mpl::identity<container_attribute>)
{
    chunk_list.emplace(chunk_list.end(), std::move(chunk));
}

} } } }


namespace parser
{
    namespace x3 = boost::spirit::x3;

    auto const identifier = x3::rule<struct _, int> { "identifier" } =
        x3::int_;

    auto const operator_1 = x3::rule<struct _, char> { "operator" } =
        x3::char_("ABC");
    auto const operator_2 = x3::rule<struct _, char> { "operator" } =
        x3::char_("XYZ");

    auto const expression_chunk_1 = x3::rule<struct _, ast::expression::chunk> { "expression" } =
        operator_1 > identifier
        ;
    auto const expression_chunk_2 = x3::rule<struct _, ast::expression::chunk> { "expression" } =
        operator_2 > identifier
        ;
    auto const expression = x3::rule<struct _, ast::expression> { "expression" } =
          identifier >> *expression_chunk_1 // foo { and  foo }
        // rule below fails to compile, chunk_list contains only one value
        | identifier >>  expression_chunk_2 // foo [ nand foo ]
        ;
}


struct visitor {
    visitor(std::ostream& os) : os{ os } { }
    void operator()(ast::expression const& node) {
        os << "(";
        (*this)(node.identifer);
        for(auto const& chunk : node.chunk_list) {
            os << "(" << chunk.operator_ << " ";
            (*this)(chunk.identifer);
            os << ")";
        }
        os << ")\n";
    }
    void operator()(ast::identifer const& node) {
        os << "(" << node.name << ")";
    }
    std::ostream& os;
};


int main()
{
    namespace x3 = boost::spirit::x3;

    for(std::string const str: {
        "1 X 2",
        "3 A 4 A 5"
    }) {
      auto iter = str.begin(), end = str.end();

      ast::expression attr;
      bool r = x3::phrase_parse(iter, end, parser::expression, x3::space, attr);

      std::cout << "parse '" << str << "': ";
      if (r && iter == end) {
        std::cout << "succeeded:\n";
        visitor(std::cout)(attr);
      } else {
        std::cout << "*** failed ***\n";
      }
    }

    return 0;
}
