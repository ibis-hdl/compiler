/*
 * parser_type.cpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */



#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl93/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"

#include "generate_data_test_case.hpp"


BOOST_AUTO_TEST_SUITE( parser_type )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


/*
 * test cases for type_declaration
 */

// array_type_definition
GENERATE_DATASET_TEST_CASE(constrained_array_definition)
GENERATE_DATASET_TEST_CASE(index_subtype_definition)
GENERATE_DATASET_TEST_CASE(unconstrained_array_definition)

// composite_type_definition
GENERATE_DATASET_TEST_CASE(element_declaration)
GENERATE_DATASET_TEST_CASE(record_type_definition)

// scalar_type_definition
GENERATE_DATASET_TEST_CASE(enumeration_type_definition)
GENERATE_DATASET_TEST_CASE(integer_type_definition)
GENERATE_DATASET_TEST_CASE(floating_type_definition)
GENERATE_DATASET_TEST_CASE(primary_unit_declaration)    // physical_type_definition
GENERATE_DATASET_TEST_CASE(secondary_unit_declaration)  // physical_type_definition
GENERATE_DATASET_TEST_CASE(physical_type_definition)

// type_definition
GENERATE_DATASET_TEST_CASE(full_type_declaration)
GENERATE_DATASET_TEST_CASE(incomplete_type_declaration)
GENERATE_DATASET_TEST_CASE(type_definition)


BOOST_AUTO_TEST_SUITE_END()

