/*
 * winapi_color.cpp
 *
 *  Created on: 09.08.2018
 *      Author: olaf
 */

#include <eda/color/detail/color.hpp>


#if BOOST_OS_WINDOWS && !EDA_ON_WINDOWS_USE_ANSII_COLOR

namespace eda { namespace color { namespace detail {

    const int win_printer::xindex = std::ios_base::xalloc();

} } }

#endif
