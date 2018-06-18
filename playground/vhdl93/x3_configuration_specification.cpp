/*
 * x3_configuration_specification.cpp
 *
 *  Created on: 17.06.2018
 *      Author: olaf
 */

#define BOOST_SPIRIT_X3_DEBUG

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/optional.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    template <typename Out, typename T>
    inline void print_attribute(Out& os, boost::iterator_range<T> const& range) {
        os << range;
    }

}}}}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <boost/spirit/home/x3.hpp> // Boost.Spirit >= 1.67
#pragma GCC diagnostic pop


namespace x3 = boost::spirit::x3;

namespace parser {

typedef std::string::const_iterator   iterator_type;

}


namespace ast {

template <typename ...Types>
using variant = x3::variant<Types...>;

template <typename T>
using forward_ast = x3::forward_ast<T>;

template<typename T>
using optional = boost::optional<T>;

using string_span = boost::iterator_range<parser::iterator_type>;

struct nullary { };

enum class keyword_token { UNSPECIFIED, ALL, OTHERS, OPEN };

struct identifier {
    boost::iterator_range<parser::iterator_type>    name;
};

using label = ast::identifier;

struct name : variant<
    nullary,
    identifier
    // operator_symbol, selected_name, indexed_name, slice_name, attribute_name,
>
{
    name(name const&) = default;    // XXX
    name& operator=(name const&) = default; // XXX
    using base_type::base_type;
    using base_type::operator=;
};

//------------------------------------------------------------------------------
using instantiation_label_list = std::vector<ast::label>;


struct instantiation_list : variant<
    nullary,
    instantiation_label_list,
    keyword_token               // OTHERS | ALL
>
{
    using base_type::base_type;
    using base_type::operator=;
};

struct component_specification {
    ast::instantiation_list         instantiation_list;
    ast::name                       component_name;
};

//------------------------------------------------------------------------------
struct entity_aspect_entity {
    ast::name                       name;
    optional<ast::identifier>       architecture_identifier;
};

struct entity_aspect_configuration {
    ast::name                       name;
};


struct entity_aspect : variant<
    ast::nullary,
    ast::entity_aspect_entity,
    ast::entity_aspect_configuration,
    ast::keyword_token  // OPEN
>
{
    using base_type::base_type;
    using base_type::operator=;
};

struct formal_part {
    std::vector<ast::name>          context_tied_names;
};

struct actual_designator : variant<
    nullary,
    forward_ast<name>,
    ast::keyword_token      // OPEN
>
{
    using base_type::base_type;
    using base_type::operator=;
};

struct actual_part_chunk {
    forward_ast<ast::name>          context_tied_name; // function_name | type_mark(name)
    ast::actual_designator          actual_designator;
};


struct actual_part : variant<
    actual_designator,
    actual_part_chunk
>
{
    using base_type::base_type;
    using base_type::operator=;
};

struct association_element {
    association_element() = default;    // XXX
    association_element(association_element const&) = default; // XXX
    optional<ast::formal_part>      formal_part;
    ast::actual_part                actual_part;
};

struct association_list : std::vector<ast::association_element> { };

struct port_map_aspect {
    ast::association_list           association_list;
};

struct generic_map_aspect {
    ast::association_list           association_list;
};

struct binding_indication {
    optional<ast::entity_aspect>    entity_aspect;
    ast::generic_map_aspect         generic_map_aspect;
    ast::port_map_aspect            port_map_aspect;
};

struct configuration_specification {
    ast::component_specification    component_specification;
    ast::binding_indication         binding_indication;
};

}


BOOST_FUSION_ADAPT_STRUCT(ast::identifier,
    name
)
BOOST_FUSION_ADAPT_STRUCT(ast::component_specification,
    instantiation_list, component_name
)
BOOST_FUSION_ADAPT_STRUCT(ast::entity_aspect_entity,
    name, architecture_identifier
)
BOOST_FUSION_ADAPT_STRUCT(ast::entity_aspect_configuration,
    name
)
BOOST_FUSION_ADAPT_STRUCT(ast::formal_part,
    context_tied_names
)
BOOST_FUSION_ADAPT_STRUCT(ast::actual_part_chunk,
    context_tied_name, actual_designator
)
BOOST_FUSION_ADAPT_STRUCT(ast::association_element,
    formal_part, actual_part
)
BOOST_FUSION_ADAPT_STRUCT(ast::port_map_aspect,
    association_list
)
BOOST_FUSION_ADAPT_STRUCT(ast::generic_map_aspect,
    association_list
)
BOOST_FUSION_ADAPT_STRUCT(ast::binding_indication,
    entity_aspect, generic_map_aspect, port_map_aspect
)
BOOST_FUSION_ADAPT_STRUCT(ast::configuration_specification,
    component_specification, binding_indication
)



namespace parser {

    typedef x3::rule<struct _1,  ast::identifier> identifier_type;
    typedef x3::rule<struct _2,  ast::identifier> label_type;
    typedef x3::rule<struct _3,  ast::name> name_type;
    typedef x3::rule<struct _4,  ast::instantiation_list> instantiation_list_type;
    typedef x3::rule<struct _5,  ast::component_specification> component_specification_type;
    typedef x3::rule<struct _6,  ast::entity_aspect_entity> entity_aspect_entity_type;
    typedef x3::rule<struct _7,  ast::entity_aspect_configuration> entity_aspect_configuration_type;
    typedef x3::rule<struct _8,  ast::entity_aspect> entity_aspect_type;
    typedef x3::rule<struct _9,  ast::formal_part> formal_part_type;
    typedef x3::rule<struct _10, ast::actual_designator> actual_designator_type;
    typedef x3::rule<struct _11, ast::actual_part> actual_part_type;
    typedef x3::rule<struct _12, ast::association_element> association_element_type;
    typedef x3::rule<struct _13, ast::association_list> association_list_type;
    typedef x3::rule<struct _14, ast::port_map_aspect> port_map_aspect_type;
    typedef x3::rule<struct _15, ast::generic_map_aspect> generic_map_aspect_type;
    typedef x3::rule<struct _16, ast::binding_indication> binding_indication_type;
    typedef x3::rule<struct _17, ast::configuration_specification> configuration_specification_type;

    identifier_type const identifier {"identifier"};
    label_type const label {"label"};
    name_type const name {"name"};
    instantiation_list_type const instantiation_list {"instantiation_list"};
    component_specification_type const component_specification {"component_specification"};
    entity_aspect_entity_type const entity_aspect_entity {"entity_aspect::entity"};
    entity_aspect_configuration_type const entity_aspect_configuration {"entity_aspect::configuration"};
    entity_aspect_type const entity_aspect {"entity_aspect"};
    formal_part_type const formal_part {"formal_part"};
    actual_designator_type const actual_designator {"actual_designator"};
    actual_part_type const actual_part {"actual_part"};
    association_element_type const association_element  {"association_element"};
    association_list_type const association_list {"association_list"};
    port_map_aspect_type const port_map_aspect  {"port_map_aspect"};
    generic_map_aspect_type const generic_map_aspect {"generic_map_aspect"};
    binding_indication_type const binding_indication {"binding_indication"};
    configuration_specification_type const configuration_specification {"configuration_specification"};

    auto const distinct = [](auto const& parser) {
        return
            x3::lexeme[
                   x3::no_case[ parser ]
                >> !(x3::iso8859_1::alnum | '_')
            ];
    };

    template<typename T>
    auto const as = [](auto const& expr) {
        return x3::rule<struct _, T> { "as" } = x3::as_parser(expr);
    };

    auto const ALL = distinct("all") >> x3::attr(ast::keyword_token::ALL);
    auto const CONFIGURATION = distinct("configuration");
    auto const ENTITY = distinct("entity");
    auto const FOR = distinct("for");
    auto const GENERIC = distinct("generic");
    auto const OPEN = distinct("open") >> x3::attr(ast::keyword_token::OPEN);
    auto const OTHERS = distinct("others") >> x3::attr(ast::keyword_token::OTHERS);
    auto const PORT = distinct("port");
    auto const MAP = distinct("map");
    auto const USE = distinct("use");

    using x3::char_;

    auto const identifier_def =
        x3::raw[ x3::lexeme[
             char_("a-zA-Z")
          >> *( char_("a-zA-Z0-9") | char_("_") )
        ]];

    auto const label_def = identifier;

    auto const name_def = identifier;

    auto const instantiation_list_def =
        (label % ',') | OTHERS | ALL;

    auto const component_specification_def =
        instantiation_list >> ':'  >> name;

    //--------------------------------------------------------------------------

    auto const entity_aspect_entity_def =
        ENTITY >> name >> -( '(' >> identifier >> ')' );

    auto const entity_aspect_configuration_def =
        CONFIGURATION >> name;

    auto const entity_aspect_def =
          entity_aspect_entity
        | entity_aspect_configuration
        | OPEN
        ;

    //--------------------------------------------------------------------------
    auto const formal_part_def =
        as<std::vector<ast::name>>(
            name >> -( '(' >> name /* formal_designator */>> ')' ) );

    auto const actual_designator_def =
          name | OPEN
        ;

    auto const actual_part_chunk = x3::rule<struct _, ast::actual_part_chunk>{ "actual_part" } =
         name >> '(' >> name /* actual_designator */ >> ')';

    auto const actual_part_def = /* order matters */
          actual_part_chunk
        | actual_designator
        ;

    auto const association_element_def =
           -as<ast::formal_part>( formal_part >> "=>" )
        >> actual_part
        ;

    auto const association_list_def =
        association_element % ',' ;

    auto const port_map_aspect_def =
        PORT >> MAP >> '(' >> association_list >> ')';

    auto const generic_map_aspect_def =
        GENERIC >> MAP >> '(' >> association_list >> ')';

    auto const binding_indication_def =
           -( USE >> entity_aspect )
        >> -generic_map_aspect   // XXX optional by association_list vector<>
        >> -port_map_aspect      // XXX optional by association_list vector<>
        ;

    auto const configuration_specification_def = ( // operator precedence
        FOR >> component_specification >> binding_indication ) >> ';'
        ;

    //--------------------------------------------------------------------------
    BOOST_SPIRIT_DEFINE(
        identifier, label, name,
        instantiation_list,
        component_specification,
        entity_aspect_entity, entity_aspect_configuration, entity_aspect,
        formal_part, actual_designator, actual_part,
        association_element, association_list,
        port_map_aspect, generic_map_aspect,
        binding_indication,
        configuration_specification
    );
}


int main()
{
    auto const parser = parser::configuration_specification;
    using attr_type   = ast::configuration_specification;

    for(std::string str : {
        "FOR ALL : nand_socket;",
        "FOR ALL : nand_socket USE ENTITY foo;",
        "FOR ALL : nand_socket USE ENTITY foo(arch);",
        "FOR ALL : nand_socket USE ENTITY foo GENERIC MAP ( N => n );",
        "FOR ALL : nand_socket USE ENTITY foo GENERIC MAP ( N => n ) PORT MAP (b => b);"
    }) {
        parser::iterator_type iter = str.begin(), end = str.end();
        attr_type attr;
        std::cout << "parse '" << str << "'\n";
        bool const parse_ok = x3::phrase_parse(iter, end, parser >> x3::eoi, x3::ascii::space, attr);
        std::cout << "parse_ok = " << std::boolalpha << parse_ok << "\n";
    }
}
