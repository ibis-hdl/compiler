/*
 * testing_parser.hpp
 *
 *  Created on: 29.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_TESTING_PARSER_HPP_
#define SOURCES_VHDL_TEST_TESTING_PARSER_HPP_

#include <boost/test/output_test_stream.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>


namespace x3_test {


namespace x3 = boost::spirit::x3;


template <
    typename AttrType = x3::unused_type
>
struct testing_parser
{
    typedef AttrType                    attribute_type;

    template <typename ParserType>
    std::tuple<bool, std::string>
    operator()(
        std::string const &input,
        ParserType const &parser_rule,
        bool full_match = true
    );
};


} // namespace x3_test



#endif /* SOURCES_VHDL_TEST_TESTING_PARSER_HPP_ */
