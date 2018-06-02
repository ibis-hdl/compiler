/*
 * locale.hpp
 *
 *  Created on: 01.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_LOCALE_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_LOCALE_HPP_


/* special boost.locale header to get rid off compiler warning:
 *  'template<class> class std::auto_ptr' is deprecated */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <boost/locale.hpp>

#pragma GCC diagnostic pop


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_LOCALE_HPP_ */
