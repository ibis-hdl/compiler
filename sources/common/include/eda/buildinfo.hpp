#ifndef SOURCES_COMMON_INCLUDE_EDA_BUILDINFO_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_BUILDINFO_HPP_

#include <iosfwd>

namespace eda {

class buildinfo 
{
public:
    static std::ostream& print_on(std::ostream& os);
};

static inline
std::ostream& operator<< (std::ostream& os, buildinfo const& info) {
    return info.print_on(os);
}

} // namespace eda

#endif // SOURCES_COMMON_INCLUDE_EDA_BUILDINFO_HPP_
