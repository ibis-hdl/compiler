#pragma once

namespace boost::spirit::x3 {
}
namespace boost::filesystem {
}
namespace boost::test_tools {
}
namespace boost::unit_test::data {
}

// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std::filesystem {
}

namespace eda::vhdl::ast {
}
namespace eda::vhdl::parser {
}
namespace eda::vhdl::analyze {
}

namespace testsuite {

namespace x3 = boost::spirit::x3;
namespace fs = std::filesystem;

namespace btt = boost::test_tools;
namespace utf = boost::unit_test;
namespace utf_data = boost::unit_test::data;

namespace parser = eda::vhdl::parser;
namespace ast = eda::vhdl::ast;
namespace analyze = eda::vhdl::analyze;

}  // namespace testsuite

// global for BOOST_DATA_TEST_CASE()
namespace btt = testsuite::btt;
namespace utf_data = testsuite::utf_data;

namespace parser = eda::vhdl::parser;
namespace ast = eda::vhdl::ast;
namespace vhdl = eda::vhdl;
