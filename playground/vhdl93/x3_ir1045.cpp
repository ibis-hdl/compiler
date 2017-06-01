/*
 * x3_ir1045.cpp
 *
 *  Created on: 31.05.2017
 *      Author: olaf
 */

#define BOOST_SPIRIT_X3_DEBUG

#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>
#include <list>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace x3 = boost::spirit::x3;

namespace ast
{
    struct identifier {
        std::string              name;
    };
    struct character_literal {
        char                     literal;
    };

    struct enumeration_literal : x3::variant<
        identifier,
        character_literal
    >
    {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct enumeration_type_definition {
        std::vector<enumeration_literal>    list;
    };

    struct attribute_name {
        identifier                  id;
        enumeration_type_definition data;
    };

    enum class token {
        unspecified,
        r_bracket,      // ']'
        r_brace,        // ')'
        kw_all,         // keyword "ALL"
        identifier
    };
}



BOOST_FUSION_ADAPT_STRUCT(ast::identifier,
    name
)

BOOST_FUSION_ADAPT_STRUCT(ast::character_literal,
    literal
)

BOOST_FUSION_ADAPT_STRUCT(ast::enumeration_type_definition,
    list
)

BOOST_FUSION_ADAPT_STRUCT(ast::attribute_name,
    id, data
)




namespace parser {

    namespace x3 = boost::spirit::x3;
    using x3::char_;

    struct ir1045_tag {};

    auto preceding_token = [](auto& ctx) {
        std::cout << "attr " << (unsigned)x3::_attr(ctx) << "\n";
        ast::token& ir1045 = x3::get<ir1045_tag>(ctx);
        ir1045 = x3::_attr(ctx);
    };

    auto const is_character_literal = [](auto& ctx) {
        /* for details see
         * [VHDL Issue Number 1045](http://www.eda-twiki.org/isac/IRs-VHDL-93/IR1045.txt)
         * The set of tokens that may precede a character literal is disjoint
         * from that which may precede a single tick token.  */
        auto& pass = x3::_pass(ctx);
        ast::token ir1045_token = x3::get<ir1045_tag>(ctx);
        switch(ir1045_token) {
            case ast::token::r_bracket:
                [[falltrough]]
            case ast::token::r_brace:
                [[falltrough]]
            case ast::token::kw_all:
                [[falltrough]]
            case ast::token::identifier: {
                pass = false;
                ir1045_token = ast::token::unspecified; // clear
                std::cout << "is_character_literal = false\n";
                break;
            }
            default: {
                // must be a character literal
                pass = true;
                ir1045_token = ast::token::unspecified; // clear
                std::cout << "is_character_literal = true\n";
            }
        }
    };

    auto const r_bracket = x3::rule<struct _> { "]" } =
        ']' >> x3::attr(ast::token::r_bracket)[preceding_token];

    auto const r_brace = x3::rule<struct _> { ")" } =
        ')' >> x3::attr(ast::token::r_brace)[preceding_token];

    auto const ALL = x3::rule<struct _> { "ALL" } =
        "ALL" >> x3::attr(ast::token::kw_all)[preceding_token];



    auto const identifier = x3::rule<struct _, ast::identifier> { "identifier" } =
        x3::lexeme [ *char_("A-Za-z") - char_( R"('")" ) ]; // note the excluding char set inside lexeme

    auto const character_literal_char = x3::rule<struct _, char, true> { "character_literal(char)" } =
        x3::lexeme [
               ("\'" >> x3::eps[is_character_literal])
            >> char_
            >> "\'"
        ];

    auto const character_literal = x3::rule<struct _, ast::character_literal> { "character_literal" } =
        character_literal_char;

    auto const enumeration_literal = x3::rule<struct _, ast::enumeration_literal> { "enumeration_literal" } =
        identifier | character_literal;

    auto const enumeration_type_definition = x3::rule<struct _, ast::enumeration_type_definition> { "enumeration_type_definition" } =
        '(' >> (enumeration_literal % ',') >> r_brace;



    auto const attribute_name = x3::rule<struct _, ast::attribute_name> { "attribute_name" } =
        identifier >> "'" >> enumeration_type_definition;

}


struct visitor {
    visitor(std::ostream& os) : os{ os } { }
    void operator()(ast::identifier const& node) {
        os << "(" << node.name << ")\n";
    }
    void operator()(ast::character_literal const& node) {
        os << "('" << node.literal << "')\n";
    }

    void operator()(ast::enumeration_literal const& node) {
        boost::apply_visitor(*this, node);
    }

    void operator()(ast::enumeration_type_definition const& node) {
        for(auto const& e : node.list)
            (*this)(e);
    }

    void operator()(ast::attribute_name const& node) {
        (*this)(node.id);
        (*this)(node.data);
    }

    std::ostream& os;
};


int main()
{
    namespace x3 = boost::spirit::x3;

    for(std::string const str: {
        "Id'('A', 'B')",
        "('Id')'foo"
    }) {
      auto iter = str.begin(), end = str.end();

      ast::attribute_name attr;
#if 0
      ast::token ir1045_token = ast::token::r_bracket;
#else
      ast::token ir1045_token = ast::token::unspecified;
#endif

      std::cout << "parse '" << str << "': ";
      bool r = x3::phrase_parse(iter, end,
                  x3::with<parser::ir1045_tag>(std::ref(ir1045_token))[parser::attribute_name],
                  x3::space, attr
              );

      if (r && iter == end) {
        std::cout << "succeeded:\n";
        visitor(std::cout)(attr);
      } else {
        std::cout << "*** failed ***\n";
      }
    }

    return 0;
}


