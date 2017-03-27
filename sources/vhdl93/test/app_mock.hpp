/*
 * app_mock.hpp
 *
 *  Created on: 27.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_TEST_APP_MOCK_HPP_
#define SOURCES_VHDL93_TEST_APP_MOCK_HPP_


#include <boost/test/unit_test.hpp>


/**
 * A shortcut for boost::unit_test::framework::master_test_suite().{argc, argv}
 * to access boost.test command line arguments access interface. argc and argv
 * do not include parameters handled by the boost unit test framework, such as
 * e.g. --log_level etc.
 *
 * @example
 *
 *  app_mock app_mock;
 *  std::cout << "ARGC = " << app_mock.argc << '\n';
 *  for(int n = 0; n != app_mock.argc; n++) {
 *  	std::cout << app_mock.argv[n] << '\n';
 *  }
 */
struct app_mock
{
	app_mock();

	int const 			argc;
	char** const 		argv;
};


BOOST_GLOBAL_FIXTURE(app_mock);


#endif /* SOURCES_VHDL93_TEST_APP_MOCK_HPP_ */
