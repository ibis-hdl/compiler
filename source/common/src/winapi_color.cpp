#include <eda/color/detail/color.hpp>  // IWYU pragma: keep

#if BOOST_OS_WINDOWS && !EDA_ON_WINDOWS_USE_ANSII_COLOR

namespace eda::color::detail {

const int win_printer::xindex = std::ios_base::xalloc();

}

#endif
