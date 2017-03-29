/*
 * testing_parser.hpp
 *
 *  Created on: 29.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_TEST_TESTING_PARSER_HPP_
#define SOURCES_VHDL93_TEST_TESTING_PARSER_HPP_

#include <eda/vhdl93/parser/grammar_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>

#include <eda/vhdl93/ast_printer.hpp>

#include <boost/test/output_test_stream.hpp>


namespace x3_test {

namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


template <typename AttrType = x3::unused_type, typename SkipperType = parser::skipper_type>
struct testing_parser
{
	typedef AttrType					attribute_type;
	typedef SkipperType					skipper_type;
	attribute_type						attr;
	skipper_type						skipper;


	template <typename ParserType>
	std::tuple<bool, std::string>
	operator()(
	    std::string const &input,
	    ParserType const &parser_rule,
	    bool full_match = true
	    )
	{
	    btt::output_test_stream output;

	    parser::iterator_type iter = input.begin();
	    parser::iterator_type const end = input.end();

	    parser::error_handler_type error_handler(iter, end, output);

	    auto const parser =
	        x3::with<x3::error_handler_tag>(std::ref(error_handler))
	        [
	              parser_rule
	        ];

	    bool success =
	      x3::phrase_parse(iter, end, parser, skipper, attr);

	    if (success) {
	        if (iter != end) {
	            error_handler(iter, "Error! Expecting end of input here: ");
	        }
	        else {
	            ast::printer print(output);
	            print.verbose_symbol = true;
	            print.verbose_variant = true;
	            print(attr);
	        }
	    }

	    // FixMe: C++17 Structured Bindings
	    return std::make_tuple(
	        success && (!full_match || (iter == end)),
	        output.str()
	    );
	}
};




//    class tester
//    {
//        fs::path prefix {
//        fs::path("/home/olaf/work/CXX/IBIS_SOURCE/sources/vhdl93/test/literal")
//        //fs::path(app_mock().argv[0]).filename()
//    }; // FixMe: extra cmd args
//
//    unsigned num_files_tested { 0 };
//
//};

} // namespace x3_test



#endif /* SOURCES_VHDL93_TEST_TESTING_PARSER_HPP_ */