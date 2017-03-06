## from ML boost.spirit
##  [Spirit-general] splitted source (decl, def) gives compile errors byy use for test suite

SchematicFileGrammer_def.hpp http://pastebin.com/SUP0WAq3
SchematicFileGrammer.hpp http://pastebin.com/t5hwymCe
SchematicFileParserConfig.hpp http://pastebin.com/VgyrrAVQ
SchematicFileGrammer.cpp http://pastebin.com/sNkQtXuS
error_handler.hpp http://pastebin.com/4HJHTkSS

--------8<--------- SchematicFileGrammer_def.hpp http://pastebin.com/SUP0WAq3
#pragma once
#include <Parse/BoostSpiritConfig.h>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include "SchematicFileParserConfig.hpp"

#include <boost/fusion/adapted.hpp>
// #include <boost/fusion/include/io.hpp>
// #include <boost/fusion/include/vector.hpp>

#include "SchematicFileAST.hpp"
#include "SchematicFileAST_Adapted.hpp"
#include "SchematicFileGrammar.hpp"
#include "SchematicFileGrammarTypes.hpp"

#include <vector>
#include "error_handler.hpp"

#include <boost/optional/optional_io.hpp>

namespace client {
namespace KicadFileParser_grammar {

namespace x3    = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

    using x3::uint_;
    using x3::char_;
    using x3::float_;
    using x3::lit;

    using x3::int_;
    using x3::lit;
    using x3::double_;
    using x3::lexeme;
    using x3::no_skip;
    using x3::omit;
    using x3::repeat;
    using x3::with;
    using x3::eps;
    using x3::get;
    using x3::_attr;
    using x3::_pass;
    using x3::_val;
    using x3::hex;

    boost::spirit::x3::int_parser<unsigned, 16, 2, 2> hex_; // This allows for a hex doublet

    // Visit 3
    schematic_type const                    schematic                    = "schematic";
    bitmapImage_type const                  bitmapImage                  = "bitmapImage";
    busEntry_type const                     busEntry                     = "busEntry";
    wireSegment_type const                  wireSegment                  = "wireSegment";
    textNote_type const                     textNote                     = "textNote";
    schematicHeader_type const              schematicHeader              = "schematicHeader";
    schematicDescription_type const         schematicDescription         = "schematicDescription";
    globalLabel_type const                  globalLabel                  = "globalLabel";
    busSegment_type const                   busSegment                   = "busSegment";
    label_type const                        label                        = "label";
    componentAlternateReference_type const  componentAlternateReference  = "componentAlternateReference";
    componentField_type const               componentField               = "componentField";
    component_type const                    component                    = "component";
    dottedLineSegment_type const            dottedLineSegment            = "dottedLineSegment";
    heirarchicalSheetSymbolLabel_type const heirarchicalSheetSymbolLabel = "heirarchicalSheetSymbolLabel";
    heirarchicalSheetSymbol_type const      heirarchicalSheetSymbol      = "heirarchicalSheetSymbol";
    heirarchicalLabel_type const            heirarchicalLabel            = "heirarchicalLabel";
    junction_type const                     junction                     = "junction";
    noConnect_type const                    noConnect                    = "noConnect";
    nonQuotedString_type const              nonQuotedString              = "nonQuotedString";
    nonQuotedStringMultiWord_type const     nonQuotedStringMultiWord     = "nonQuotedStringMultiWord";
    optionalChar_type const                 optionalChar                 = "optionalChar";
    quotedString_type const                 quotedString                 = "quotedString";

    // Small generic parsers
    const auto nonQuotedString_def          = lexeme[*(char_ - lit(" ")) > lit(" ")];
    const auto nonQuotedStringMultiWord_def = lexeme[*(char_ - lit("\n")) > lit("\n")];
    const auto quotedString_def             = lexeme[lit('"') > *(char_ - lit('"')) > lit('"')];
    const auto optionalChar_def             = no_skip[lit(' ') > (char_ - (lit(' ') | lit("\n")))];

    const auto bitmapImage_def =
        lit("$Bitmap")
        > lit("Pos") > uint_ > uint_
        > lit("Scale") > float_
        > lit("Data")
        > *(hex_)            // The Data itself
        > lit("EndData")
        > lit("$EndBitmap"); // x and y

    const auto busEntry_def =
        lit("Entry")
        > nonQuotedString
        > nonQuotedString
        > uint_ > uint_
        > uint_ > uint_;

    const auto busSegment_def =
        lit("Wire") >> lit("Bus") >> lit("Line")
        > uint_ > uint_
        > uint_ > uint_;

    const auto wireSegment_def =
        lit("Wire") >> lit("Wire") >> lit("Line")
        > uint_ > uint_  // Start X and y
        > uint_ > uint_; // End X and Y

    const auto textNote_def =
        lit("Text")
        >> lit("Notes")
        > uint_ > uint_
        > char_ > uint_
        > nonQuotedString > uint_
        >  nonQuotedStringMultiWord;

    const auto componentAlternateReference_def =
        lit("AR")
        > lit("Path=") > quotedString
        > lit("Ref=") > quotedString
        > lit("Part=") > quotedString

        > lit("AR")
        > lit("Path=") > quotedString
        > lit("Ref=") > quotedString
        > lit("Part=") > quotedString;

    const auto label_def =
        lit("Text")
        >> lit("Label")
        > uint_ > uint_
        > char_ > uint_
        > lit("~")
        > uint_
        > nonQuotedStringMultiWord;

    const auto schematicDescription_def =
        lit("$Descr") > char_ > int_ > int_  > int_
        > lit("encoding") > lexeme[+(char_ - "\n") > "\n"]
        > lit("Sheet") > int_ > int_
        > lit("Title") > quotedString
        > lit("Date") > quotedString
        > lit("Rev") > quotedString
        > lit("Comp") > quotedString
        > lit("Comment1") > quotedString
        > lit("Comment2") > quotedString
        > lit("Comment3") > quotedString
        > lit("Comment4") > quotedString
        > lit("$EndDescr");
    const auto schematicHeader_def =

        lit("EESchema Schematic File Version")
        > int_
        > +lexeme[(lit("LIBS:") > *(char_ - lit("\n ")) > lit("\n "))] // Dump the libs
        > lit("EELAYER")
        > int_
        > int_
        > lit("EELAYER")
        > lit("END")
        > schematicDescription;

    const auto componentField_def =
        lit("F")
        > uint_
        > quotedString
        > char_
        > int_
        > int_
        > uint_
        > uint_
        > char_
        > nonQuotedString
        > -quotedString;
    const auto dottedLineSegment_def =
        lit("Wire") >> lit("Notes") >> lit("Line")
        > uint_ > uint_
        > uint_ > uint_;

    const auto heirarchicalLabel_def =
        lit("Text")
        >> lit("HLabel")
        > uint_ > uint_
        > char_
        > uint_
        > nonQuotedString
        > lit("~")
        > uint_
        > nonQuotedStringMultiWord;

    // #TODO rename this to symbol fields
    const auto heirarchicalSheetSymbolLabel_def=
        lexeme[lit("F") > uint_]
        > quotedString
        > -(char_ - int_)
        > -(char_ - int_)
        > uint_
        > -uint_
        > -uint_;

    const auto heirarchicalSheetSymbol_def =
        lit("$Sheet")
        > lit("S")
        > uint_
        > uint_
        > uint_
        > uint_
        > lit("U")
        > hex
        > *(heirarchicalSheetSymbolLabel)
        > lit("$EndSheet");

    const auto component_def =
        lit("$Comp")
        > lit("L") > nonQuotedString > nonQuotedString
        > lit("U") > uint_ > uint_ > hex
        > lit("P") > uint_ > uint_
        > -componentAlternateReference
        > *componentField
        > uint_ > uint_ > uint_
        > int_ > int_ > int_ > int_
        > lit("$EndComp");

    const auto junction_def =
        lit("Connection")
        > lit("~")
        > uint_ > uint_; // x and ye

    const auto noConnect_def =
        lit("NoConn") > lit("~")
        > uint_ > uint_; // x and y

    const auto globalLabel_def =
        lit("Text")
        >> lit("GLabel")
        > uint_ > uint_
        > char_ > uint_ > nonQuotedString > nonQuotedString;

    const auto schematic_def =
        schematicHeader
        > *(
            label
            | textNote
            | noConnect
            | wireSegment
            | busSegment
            | dottedLineSegment
            | busEntry
            | heirarchicalLabel
            | globalLabel
            | junction
            | heirarchicalSheetSymbol
            | bitmapImage
            | component
            )
        > lit("$EndSCHEMATC");

    BOOST_SPIRIT_DEFINE
    (
        schematic,
        bitmapImage,
        busEntry,
        wireSegment,
        textNote,
        schematicHeader,
        schematicDescription,
        busSegment,
        componentAlternateReference,
        componentField,
        globalLabel,
        junction,
        heirarchicalSheetSymbol,
        heirarchicalSheetSymbolLabel,
        heirarchicalLabel,
        component,
        label,
        noConnect,
        dottedLineSegment,
        quotedString,
        nonQuotedString,
        nonQuotedStringMultiWord,
        optionalChar

    )

    struct schematic_class : error_handler_base, x3::annotate_on_success {};
    struct bitmapImage_class : x3::annotate_on_success {};
    struct busEntry_class : x3::annotate_on_success {};
    struct wireSegment_class : x3::annotate_on_success {};
    struct textNote_class : x3::annotate_on_success {};
    struct schematicDescription_class : x3::annotate_on_success {};
    struct schematicHeader_class : x3::annotate_on_success {}; // #TODO add rectshape to lib
    struct globalLabel_class : x3::annotate_on_success {};
    struct busSegment_class : x3::annotate_on_success {};
    struct componentField_class : x3::annotate_on_success {};
    struct componentAlternateReference_class : x3::annotate_on_success {};

    struct component_class : x3::annotate_on_success {};
    struct heirarchicalSheetSymbol_class : x3::annotate_on_success {};
    struct heirarchicalSheetSymbolLabel_class : x3::annotate_on_success {};
    struct heirarchicalLabel_class : x3::annotate_on_success {};
    struct noConnect_class : x3::annotate_on_success {};
    struct label_class : x3::annotate_on_success {};

    struct dottedLineSegment_class : x3::annotate_on_success {};
    struct junction_class : x3::annotate_on_success {};
    struct quotedString_class : x3::annotate_on_success {};
    struct nonQuotedString_class : x3::annotate_on_success {};
    struct nonQuotedStringMultiWord_class : x3::annotate_on_success {};
    struct optionalChar_class : x3::annotate_on_success {};
}
}

namespace client {
    const KicadFileParser_grammar::schematic_type&schematicFile()
    {
        return KicadFileParser_grammar::schematic;
    }
}
-------->8---------

--------8<--------- SchematicFileGrammer.hpp http://pastebin.com/t5hwymCe
#pragma once

#include "SchematicFileAST.hpp"
#include "SchematicFileGrammarTypes.hpp"
#include <boost/spirit/home/x3.hpp>

namespace client {
    namespace x3 = boost::spirit::x3;

    namespace KicadFileParser_grammar {

        BOOST_SPIRIT_DECLARE
        (
            schematic_type
        )
    }

    const KicadFileParser_grammar::schematic_type & schematicFile();
}
-------->8---------

--------8<--------- SchematicFileParserConfig.hpp http://pastebin.com/VgyrrAVQ
#pragma once

#include <string>
#include <boost/spirit/home/x3.hpp>
#include "error_handler.hpp"

namespace client {
    namespace KicadFileParser_grammar {

        namespace x3 = boost::spirit::x3;

//        using iterator_type = std::string::const_iterator ;
//        //using context_type = x3::unused_type; //x3::phrase_parse_context<x3::ascii::space_type>::type ;
//        using context_type = x3::phrase_parse_context<x3::ascii::space_type>::type;

        // CONFIG_VISIT_BEGIN
        // Our Iterator Type
        typedef std::string::const_iterator iterator_type;

        // The Phrase Parse Context
        typedef
            x3::phrase_parse_context<x3::ascii::space_type>::type
        phrase_context_type;

        // Our Error Handler
        typedef error_handler<iterator_type> error_handler_type;

        // Combined Error Handler and Phrase Parse Context
        typedef x3::with_context<
            error_handler_tag
          , std::reference_wrapper<error_handler_type> const
          , phrase_context_type>::type
        context_type;
        // CONFIG_VISIT_END
    }
}
-------->8---------

--------8<--------- SchematicFileGrammer.cpp http://pastebin.com/sNkQtXuS
#include "SchematicFileGrammar_def.hpp"
#include "SchematicFileParserConfig.hpp"

namespace client {
namespace KicadFileParser_grammar {

    BOOST_SPIRIT_INSTANTIATE(schematic_type, iterator_type, context_type)

}
}
-------->8---------

--------8<--------- error_handler.hpp http://pastebin.com/4HJHTkSS
#pragma once

#include <iostream>
#include <string>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include "SchematicLibraryGrammar.hpp"
#include <map>

namespace client { namespace KicadParser_grammar
{
    namespace x3 = boost::spirit::x3;

//    struct error_handler
//        {
//            //  Our error handler
//            template <typename Iterator, typename Exception, typename Context>
//            x3::error_handler_result
//            on_error(Iterator&, Iterator const& last, Exception const& x, Context const& context)
//            {
//                std::cout
//                    << "Error! Expecting: "
//                    << x.which()
//                    << " here: \""
//                    << std::string(x.where(), last)
//                    << "\""
//                    << std::endl
//                    ;
//                return x3::error_handler_result::fail;
//            }
//        };
    ////////////////////////////////////////////////////////////////////////////
    //  Our error handler
    ////////////////////////////////////////////////////////////////////////////
    // ERROR_HANDLER1_VISIT_BEGIN
    // X3 Error Handler Utility
    template <typename Iterator>
    using error_handler = x3::error_handler<Iterator>;

    // tag used to get our error handler from the context
    using x3::error_handler_tag;

    struct error_handler_base
    {
        error_handler_base();

        template <typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator& first, Iterator const& last
          , Exception const& x, Context const& context);

        std::map<std::string, std::string> id_map;
    };
    // ERROR_HANDLER1_VISIT_END

    ////////////////////////////////////////////////////////////////////////////
    // Implementation
    ////////////////////////////////////////////////////////////////////////////

    // ERROR_HANDLER2_VISIT_BEGIN
    inline error_handler_base::error_handler_base()
    {
                id_map["schematicLibrary"] = "schematicLibrary";
                id_map["schematicSymbolDefinition"] = "schematicSymbolDefinition";
                id_map["arcShape"]                  = "arcShape";
                id_map["circleShape"]               = "circleShape";
                id_map["symbolAlias"]               = "symbolAlias";
                id_map["rectangleShape"]            = "rectangleShape";
                id_map["symbolField"]               = "symbolField";
                id_map["textShape"]                 = "textShape";
                id_map["footprintFilterList"]       = "footprintFilterList";
                id_map["polygonShape"]              = "polygonShape";
                id_map["pinShape"]                  = "pinShape";
                id_map["bezierShape"]               = "bezierShape";
                id_map["schematicSymbol"]           = "schematicSymbol";
                id_map["symbolShape"]               = "symbolShape";
                id_map["nonQuotedString"]           = "nonQuotedString";
                id_map["nonQuotedStringMultiWord"]  = "nonQuotedStringMultiWord";
                id_map["optionalChar"]              = "optionalChar";
                id_map["quotedString"]              = "quotedString";
    }
    // ERROR_HANDLER2_VISIT_END

    // ERROR_HANDLER3_VISIT_BEGIN
    template <typename Iterator, typename Exception, typename Context>
    inline x3::error_handler_result
    error_handler_base::on_error(
        Iterator& first, Iterator const& last
      , Exception const& x, Context const& context)
    {
        std::string which = x.which();
        auto iter = id_map.find(which);
        if (iter != id_map.end())
            which = iter->second;

        std::string message = "Error! Expecting: " + which + " here:";
        auto& error_handler = x3::get<error_handler_tag>(context).get();
        error_handler(x.where(), message);
        return x3::error_handler_result::fail;
    }
    // ERROR_HANDLER3_VISIT_END
}}
-------->8---------