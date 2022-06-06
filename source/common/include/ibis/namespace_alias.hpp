//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

// forward Boost.Orgs's namespace used
namespace boost::spirit::x3::iso8859_1 {
}
namespace boost::filesystem {
}
namespace boost::property_tree {
}

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std::filesystem {
}

namespace ibis {

namespace x3 = boost::spirit::x3;

namespace pt = boost::property_tree;

namespace vhdl::ast {
}

namespace vhdl::parser {
// VHDL char set is iso8859:1
namespace iso8859_1 = boost::spirit::x3::iso8859_1;
}  // namespace vhdl::parser

namespace vhdl::analyze {
}

namespace fs = std::filesystem;
}  // namespace ibis
