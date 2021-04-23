#include <ibis/color/detail/color.hpp>  // IWYU pragma: keep

#if BOOST_OS_WINDOWS && !IBIS_WITH_ANSI_COLOR_ON_WINDOWS

namespace ibis::color::detail {

const int win_printer::xindex = std::ios_base::xalloc();

}

#endif
