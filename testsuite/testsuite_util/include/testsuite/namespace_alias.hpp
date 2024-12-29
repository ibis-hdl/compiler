//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

// clang-format off
namespace boost::spirit::x3 {}
namespace boost::test_tools {}
namespace boost::unit_test::framework {}
namespace boost::unit_test::data {}

namespace ibis::vhdl::ast {}
namespace ibis::vhdl::parser {}
namespace ibis::vhdl::analyze {}
// clang-format on

namespace testsuite {
// namespace fs = std::filesystem;  // can't fwd with libc++
namespace x3 = boost::spirit::x3;
// ToDo: Check for correct and intuitive aliases!
namespace btt = boost::test_tools;
namespace utf = boost::unit_test;
namespace utf_data = boost::unit_test::data;
namespace butf = boost::unit_test::framework;
namespace parser = ibis::vhdl::parser;
namespace ast = ibis::vhdl::ast;
namespace analyze = ibis::vhdl::analyze;
}  // namespace testsuite

// global for BOOST_DATA_TEST_CASE()
namespace btt = boost::test_tools;
namespace utf = boost::unit_test;
namespace utf_data = boost::unit_test::data;
namespace parser = ibis::vhdl::parser;
namespace ast = ibis::vhdl::ast;
namespace vhdl = ibis::vhdl;
