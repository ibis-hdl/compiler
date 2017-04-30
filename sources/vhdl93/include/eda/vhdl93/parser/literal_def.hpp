/*
 * literal_def.hpp
 *
 *  Created on: 21.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_DEF_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_DEF_HPP_


#include <eda/vhdl93/parser/spirit_x3.hpp>

#include <eda/vhdl93/parser/literal.hpp>
#include <eda/vhdl93/ast_adapted.hpp>



/*
 * VHDL common literals
 */
namespace eda { namespace vhdl93 { namespace parser {

/*
 * Rule IDs
 */
struct upper_case_letter_class;
struct lower_case_letter_class;
struct digit_class;
struct special_character_class;
struct other_special_character_class;
struct space_character_class;
struct basic_graphic_character_class;
struct graphic_character_class;
struct string_literal_class;

/*
 * Rule Instances
 */
string_literal_type const string_literal { "string_literal" };


using iso8859_1::char_;
using iso8859_1::lit;
using x3::lexeme;
using x3::raw;


/*
 * Parser Rule Definition
 */

/*
 * Character Sets                                                       [§ 13.1]
 */

auto const upper_case_letter =
    x3::rule<struct upper_case_letter_class, char> { "upper_case_letter" } =
            char_("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ");
auto const lower_case_letter =
    x3::rule<struct lower_case_letter_class, char> { "lower_case_letter" } =
        char_("abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ");
auto const digit =
    x3::rule<struct digit_class, char> { "digit" } =
        char_("0-9");
auto const special_character =
    x3::rule<struct special_character_class, char> { "special_character" } =
        char_("\"#&'()*+,-./:;<=>[]_|");
auto const other_special_character =
    x3::rule<struct other_special_character_class, char> { "other_special_character" } =
        char_("!$%?@\\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷");
auto const space_character =
    x3::rule<struct space_character_class, char> { "space_character" } =
        iso8859_1::space;


// basic_graphic_character ::=                                          [§ 13.1]
// upper_case_letter | digit | special_character| space_character
auto const basic_graphic_character = x3::rule<basic_graphic_character_class, char> { "basic_graphic_character" }
    =
      upper_case_letter
    | digit
    | special_character
    | space_character
    ;

// graphic_character ::=                                                [§ 13.1]
// basic_graphic_character | lower_case_letter | other_special_character
auto const graphic_character = x3::rule<graphic_character_class, char> { "graphic_character" }
    =
      basic_graphic_character
    | lower_case_letter
    | other_special_character
    ;

// string_literal ::=                                                   [§ 13.6]
// " { graphic_character } "
/* Note, std::using string_view and hence x3::raw directive, the complete
 * contents including '""' (or even '%%') will be included into the parsed
 * string! If changed to this, the test cases will be fail. Using this will
 * require some post processing. */
namespace detail
{
    auto const string_literal_1 = x3::rule<struct _, std::string> { "string_literal" } =
       *( ( graphic_character - '"'  )
        | ( char_('"') >> char_('"') )
        )
        ;

    auto const string_literal_2 = x3::rule<struct _, std::string> { "string_literal" } =
       *( ( graphic_character - '%'  )
        | ( char_('%') >> char_('%') )
        )
        ;

    auto const string_literal = x3::rule<struct _, std::string> { "string_literal" } =
        lexeme [
              ('"' >> string_literal_1 >> '"')
            | ('%' >> string_literal_2 >> '%')
        ]
        ;
}
auto const string_literal_def =
    // FixMe: direct embedding the rule results into twice concatenated attributes!
    detail::string_literal
    ;


/* get rid off the annoying unused parameter warnings from x3 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

BOOST_SPIRIT_DEFINE(
    string_literal
)

#pragma GCC diagnostic pop

} } } // namespace eda.vhdl93.parser


/*
 * VHDL common literals API
 */
namespace eda { namespace vhdl93 { namespace parser_api {

parser::string_literal_type const& string_literal()
{
    return parser::string_literal;
}


} } } // namespace eda.vhdl93.parser_api


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_LITERAL_DEF_HPP_ */
