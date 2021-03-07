#include <iostream>

#include <eda/buildinfo.hpp>
#include <eda/buildinfo_static.hpp>

namespace eda {

std::ostream& buildinfo::print_on(std::ostream& os) {
    os << "platform: " << build_info::platform << '\n'
       << "type:     " << build_info::type << '\n'
       << "system:   " << build_info::system << '\n'
    ;
    os << "compiler: " << build_info::compiler << '\n'
       << "stdlib:   " << build_info::stdlib << '\n'
       << "libboost: " << build_info::libboost << '\n'
    ;
    return os;
}

} // namespace eda
