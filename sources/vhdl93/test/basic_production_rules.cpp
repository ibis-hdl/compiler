/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>


#include "grammar_api.hpp"


BOOST_AUTO_TEST_SUITE( test_basic_productions )



BOOST_AUTO_TEST_CASE( test_identifier )
{
  BOOST_TEST_WARN( sizeof(int) < 4U );
}

#if 0
BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_REQUIRE( 1 == 2 );
  BOOST_FAIL( "Should never reach this line" );
}
#endif



BOOST_AUTO_TEST_SUITE_END()




#if 0
#include "grammar_api.hpp"


BOOST_AUTO_TEST_SUITE( test_suite1 )

BOOST_AUTO_TEST_CASE( test_case1 )
{
  BOOST_TEST_WARN( sizeof(int) < 4U );
}

BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_REQUIRE( 1 == 2 );
  BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( test_suite2 )

BOOST_AUTO_TEST_CASE( test_case3 )
{
  BOOST_TEST( true );
}

BOOST_AUTO_TEST_CASE( test_case4 )
{
  BOOST_TEST( false );
}

BOOST_AUTO_TEST_SUITE_END()
#endif
