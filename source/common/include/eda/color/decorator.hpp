#pragma once

#include <iosfwd>
#include <string>

namespace eda::color {

template <typename Tag>
class message_decorator {
public:
    explicit message_decorator(std::string const& contents_)
        : contents{ contents_ }
    {
    }

    std::ostream& print(std::ostream& os) const
    {
        os << contents;
        return os;
    }

private:
    std::string const& contents;
};

}  // namespace eda::color
