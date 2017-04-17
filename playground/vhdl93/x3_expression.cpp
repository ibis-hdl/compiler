/*
 * x3_expression.cpp
 *
 *  Created on: 17.04.2017
 *      Author: olaf
 */

#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>
#include <list>


namespace ast
{
    enum class operator_token {
        and_, or_, xor_, nand, nor, xnor
    };

    std::ostream& operator<<(std::ostream& os, operator_token token) {
        static std::string const lut[] = {
            "and", "or" , "xor", "nand", "nor", "xnor"
        };
        os << lut[static_cast<unsigned>(token)];
        return os;
    }

    struct relation {
        std::string             foo;
    };
    struct expression {
        struct chunk {
            operator_token      operator_;
            ast::relation       relation;
        };
        ast::relation           relation;
        std::list<chunk>        chunk_list;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::relation,
    foo
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression::chunk,
    operator_, relation
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression,
    relation, chunk_list
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
    using x3::char_;
    using x3::alpha;
    using x3::alnum;

    struct keyword : x3::symbols<> {
        keyword() {
            add("and")("nor");
        }
    } const keyword;

    struct logical_operator : x3::symbols<ast::operator_token> {
        logical_operator() {
            add("and", ast::operator_token::and_)
               ("nor", ast::operator_token::nor);
            }
    } const logical_operator;

    auto const identifier = x3::rule<struct _, std::string> { "identifier" } =
        x3::lexeme[((alpha | char_('_')) >> *(alnum | char_('_'))) - keyword];

    auto const relation = x3::rule<struct _, ast::relation> { "relation" } =
        identifier;


/*
    expression ::=
             relation { and relation }
           | relation { or relation }
           | relation { xor relation }
           | relation [ nand relation ]
           | relation [ nor relation ]
           | relation { xnor relation }
*/
    auto const expression_chunk = x3::rule<struct _, ast::expression::chunk> { "expression" } =
        logical_operator > relation;

    auto const append = [](auto& ctx) {
        auto& list = x3::_val(ctx).chunk_list;
        list.push_back(list.end(), std::move(x3::_attr(ctx)));
    };
    auto const expression = x3::rule<struct _, ast::expression> { "expression" } =
        relation >> expression_chunk;
}


struct visitor {
    visitor(std::ostream& os) : os{ os } { }
    void operator()(ast::expression const& node) {
        os << "(";
        (*this)(node.relation);
        for(auto const& chunk : node.chunk_list) {
            os << "(" << chunk.operator_ << " ";
            (*this)(chunk.relation);
            os << ")";
        }
        os << ")\n";
    }
    void operator()(ast::relation const& node) {
        os << "(" << node.foo << ")";
    }
    std::ostream& os;
};


int main()
{
    namespace x3 = boost::spirit::x3;

    for(std::string const str: {
        "Hello and Bello",
        "Hello and Bello and Trello"
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



