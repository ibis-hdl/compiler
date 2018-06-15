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


using integer = boost::iterator_range<parser::iterator_type>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_GRAMMAR_HACK_HPP_ */
