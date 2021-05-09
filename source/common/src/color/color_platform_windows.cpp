#include <ibis/color/detail/color.hpp>  // IWYU pragma: keep

namespace ibis::color::detail {

template <>
const int32_t winapi_printer<color::attribute, 4>::xindex = std::ios_base::xalloc();

}
