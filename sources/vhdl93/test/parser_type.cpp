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

namespace eda { namespace vhdl93 { namespace ast {

    using integer_type_definition = ast::range_constraint;
    using floating_type_definition = ast::range_constraint;

} } } // namespace eda.vhdl93.ast



BOOST_AUTO_TEST_SUITE( parser_type )

// array_type_definition
GENERATE_DATASET_TEST_CASE(constrained_array_definition)
GENERATE_DATASET_TEST_CASE(index_subtype_definition)
GENERATE_DATASET_TEST_CASE(unconstrained_array_definition)

// composite_type_definition
GENERATE_DATASET_TEST_CASE(element_declaration)
GENERATE_DATASET_TEST_CASE(record_type_definition)

// scalar_type_definition
GENERATE_DATASET_TEST_CASE(enumeration_type_definition)
GENERATE_DATASET_TEST_CASE_RULE(integer_type_definition, range_constraint)
GENERATE_DATASET_TEST_CASE_RULE(floating_type_definition, range_constraint)
GENERATE_DATASET_TEST_CASE(primary_unit_declaration)    // physical_type_definition
GENERATE_DATASET_TEST_CASE(secondary_unit_declaration)  // physical_type_definition
GENERATE_DATASET_TEST_CASE(physical_type_definition)

GENERATE_DATASET_TEST_CASE(type_declaration)
GENERATE_DATASET_TEST_CASE(type_definition)

GENERATE_DATASET_TEST_CASE(subtype_declaration)

GENERATE_DATASET_TEST_CASE(type_conversion)


// alias
GENERATE_DATASET_TEST_CASE(alias_declaration)


BOOST_AUTO_TEST_SUITE_END()

