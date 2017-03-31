/*
 * app_mock.cpp
 *
 *  Created on: 31.03.2017
 *      Author: olaf
 */

#include "app_mock.hpp"

app_mock::app_mock()
: argc(boost::unit_test::framework::master_test_suite().argc)
, argv(boost::unit_test::framework::master_test_suite().argv)
{ }

