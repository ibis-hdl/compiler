#pragma once

#include <iosfwd>

namespace eda {

class buildinfo {
public:
    static std::ostream& print_on(std::ostream& os);
};

static inline std::ostream& operator<<(std::ostream& os, buildinfo const& info)
{
    return info.print_on(os);
}

}  // namespace eda
