/*
 * testing_parser_grammar_hack.hpp
 *
 *  Created on: 06.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_GRAMMAR_HACK_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_GRAMMAR_HACK_HPP_


/**
 * Some rules of the VHDL Spirit.X3 grammar are directly embedded into the
 * grammar self, hence no AST nodes or grammar symbols exist, but there are
 * test case files with address this rules for simplicity of testing.
 *
 * To get these and not to pollute the grammar with testing code they are
 * collected in this header file.
 */

namespace eda { namespace vhdl { namespace ast {


// This aren't AST members

using floating_type_definition = range;
using integer_type_definition  = range;

using integer = std::string;


} } } // namespace eda.vhdl.ast


namespace eda { namespace vhdl { namespace parser {


// This aren't grammar rules declared/defined in the grammar

using floating_type_definition_type = range_constraint_type;
auto const floating_type_definition = range_constraint;

using integer_type_definition_type = range_constraint_type;
auto const integer_type_definition = range_constraint;


} } } // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_GRAMMAR_HACK_HPP_ */
