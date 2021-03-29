#pragma once

// forward Boost.Orgs's namespace used
namespace boost::spirit::x3::iso8859_1 {
}
namespace boost::filesystem {
}

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std::filesystem {
}

namespace eda {

namespace x3 = boost::spirit::x3;

namespace vhdl::ast {
}

namespace vhdl::parser {
// VHDL char set is iso8859:1
namespace iso8859_1 = boost::spirit::x3::iso8859_1;
}  // namespace vhdl::parser

namespace vhdl::analyze {
}

namespace fs = std::filesystem;
}  // namespace eda
