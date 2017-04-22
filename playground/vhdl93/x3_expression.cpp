/*
 * x3_expression.cpp
 *
 *  Created on: 17.04.2017
 *      Author: olaf
 */

#include <iostream>
//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <list>


namespace ast
{
    enum class operator_token {
        and_, or_, xor_, nand, nor, xnor,
        equal, not_equals, less, less_equals, greater, greater_equals,
    };

    std::ostream& operator<<(std::ostream& os, operator_token token) {
        static std::string const lut[] = {
            "and", "or" , "xor", "nand", "nor", "xnor",
            "equal", "not_equals", "less", "less_equals", "greater", "greater_equals",
        };
        os << lut[static_cast<unsigned>(token)];
        return os;
    }

    struct shift_expression {
        std::string                 foo;
    };
    struct relation {
        struct chunk {
            operator_token          operator_;
            ast::shift_expression   shift_expression;
        };
        ast::shift_expression       shift_expression;
        boost::optional<chunk>      rest;
    };
    struct expression {
        struct chunk {
            operator_token          operator_;
            ast::relation           relation;
        };
        ast::relation               relation;
        std::list<chunk>            rest_list;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::shift_expression,
    foo
)

BOOST_FUSION_ADAPT_STRUCT(ast::relation::chunk,
    operator_, shift_expression
)

BOOST_FUSION_ADAPT_STRUCT(ast::relation,
    shift_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression::chunk,
    operator_, relation
)

BOOST_FUSION_ADAPT_STRUCT(ast::expression,
    relation, rest_list
)

struct visitor {
    visitor(std::ostream& os) : os{ os } { }
    void operator()(ast::expression::chunk const& chunk) {
        os << "(" << chunk.operator_ << " ";
        (*this)(chunk.relation);
        os << ")";
    }
    void operator()(ast::expression const& node) {
        os << "(";
        (*this)(node.relation);
        for(auto const& chunk : node.rest_list) {
            (*this)(chunk);
        }
        os << ")\n";
    }
    void operator()(ast::relation::chunk const& chunk) {
        os << "(" << chunk.operator_ << " ";
        (*this)(chunk.shift_expression);
        os << ")";
    }
    void operator()(ast::relation const& node) {
        os << "(";
        (*this)(node.shift_expression);
        if(node.rest.is_initialized()) {
            (*this)(node.rest.get().shift_expression);
        }
        os << ")";
    }
    void operator()(ast::shift_expression const& node) {
        os << "(" << node.foo << ")";
    }
    std::ostream& os;
};

namespace ast {
    std::ostream& operator<<(std::ostream& os, ast::expression const& node) {
        visitor{os}(node);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ast::expression::chunk const& chunk) {
        visitor{os}(chunk);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ast::relation const& node) {
        visitor{os}(node);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ast::relation::chunk const& chunk) {
        visitor{os}(chunk);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ast::shift_expression const& node) {
        visitor{os}(node);
        return os;
    }
}

//namespace boost { namespace spirit { namespace x3 { namespace traits {
//// DOESN'T WORK
//void move_to(ast::expression::chunk&& chunk, std::list<ast::expression::chunk>& chunk_list,
//        mpl::true_)
//{
//    chunk_list.emplace(chunk_list.end(), std::move(chunk));
//}
//} } } }


namespace parser
{
    namespace x3 = boost::spirit::x3;
    using x3::char_;
    using x3::alpha;
    using x3::alnum;

    template<typename T>
    auto as = [](auto p) { return x3::rule<struct _, T>{ "as" } = x3::as_parser(p); };

    struct keyword : x3::symbols<> {
        keyword() {
            add("and")("nor");
        }
    } const keyword;

    auto const identifier = x3::rule<struct _, std::string> { "identifier" } =
        x3::lexeme[((alpha | char_('_')) >> *(alnum | char_('_'))) - keyword];

    struct relational_operator_symbols : x3::symbols<ast::operator_token> {
        relational_operator_symbols() {
            add("=",  ast::operator_token::equal)
               ("/=", ast::operator_token::not_equals)
               ("<",  ast::operator_token::less)
               ("<=", ast::operator_token::less_equals)
               (">",  ast::operator_token::greater)
               (">=", ast::operator_token::greater_equals)
               ;
        }
    } const relational_operator;

    struct logical_operator_1 : x3::symbols<ast::operator_token> {
        logical_operator_1() {
            add("and",  ast::operator_token::and_)
               ("or",   ast::operator_token::or_);
               ("xor",  ast::operator_token::xor_);
               ("xnor", ast::operator_token::xnor);
            }
    } const logical_operator_1;

    struct logical_operator_2 : x3::symbols<ast::operator_token> {
        logical_operator_2() {
            add("nand", ast::operator_token::nand)
               ("nor",  ast::operator_token::nor);
            }
    } const logical_operator_2;


    auto const shift_expression = x3::rule<struct _, ast::shift_expression> { "shift_expression" } =
        identifier;

/*
    relation ::=
        shift_expression [ relational_operator shift_expression ]
 */
    auto const relation = x3::rule<struct _, ast::relation> { "relation" } =
        shift_expression >> -as<ast::relation::chunk>(relational_operator > shift_expression)
        ;


/*
    expression ::=
             relation { and relation }
           | relation { or relation }
           | relation { xor relation }
           | relation [ nand relation ]
           | relation [ nor relation ]
           | relation { xnor relation }
 */
    auto const expression_chunk_1 = x3::rule<struct _, ast::expression::chunk> { "expression" } =
        logical_operator_1 > relation;
    auto const expression_chunk_2 = x3::rule<struct _, ast::expression::chunk> { "expression" } =
        logical_operator_2 > relation;
    auto const expression = x3::rule<struct _, ast::expression> { "expression" } =
#if 1
           relation
        >> ( x3::repeat(1)[ expression_chunk_2 ] // artificially vector<T>
           | *expression_chunk_1
           )
#else      // doesn't compile :(
           relation
        >> (  expression_chunk_2
           | *expression_chunk_1
           )

#endif
        ;
}


int main()
{
    namespace x3 = boost::spirit::x3;

    for(std::string const str: {
//        "Foo",
//        "Hello and Bello",
//        "Hello and Bello and Trello",
//        "Foo nand Bar",
//        "Foo nand Bar nand Baz", // has to fail
        "Foo and Bar != Buu and Buz"
    }) {
      auto iter = str.begin(), end = str.end();

      ast::expression attr;
      bool r = x3::phrase_parse(iter, end, parser::expression, x3::space, attr);

      std::cout << "parse '" << str << "': ";
      if (r && iter == end) {
        std::cout << "succeeded:\n";
        visitor(std::cout)(attr);
        std::cout << "\n";
      } else {
        std::cout << "*** failed ***\n";
      }
    }


    return 0;
}



