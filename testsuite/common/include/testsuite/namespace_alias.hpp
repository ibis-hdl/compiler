/*
 * namespace_alias.hpp
 *
 *  Created on: 26.06.2018
 *      Author: olpetzol
 */

#ifndef TESTSUITE_COMMON_INCLUDE_TESTSUITE_NAMESPACE_ALIAS_HPP_
#define TESTSUITE_COMMON_INCLUDE_TESTSUITE_NAMESPACE_ALIAS_HPP_


// forward Boost.Orgs's namespace used
namespace boost {

    namespace spirit { namespace x3 { } }

    namespace filesystem { }

    namespace test_tools { }
    namespace unit_test { namespace data { } }

} // namespace boost


namespace eda {

    namespace vhdl {
        namespace ast { }
        namespace parser { }
        namespace analyze { }
    } // namespace vhdl

} // namespace eda


namespace testsuite {


namespace x3 = boost::spirit::x3;
namespace fs = boost::filesystem;

namespace btt      = boost::test_tools;
namespace utf      = boost::unit_test;
namespace utf_data = boost::unit_test::data;

namespace parser  = eda::vhdl::parser;
namespace ast     = eda::vhdl::ast;
namespace analyze = eda::vhdl::analyze;

} // namespace testsuite


// global for BOOST_DATA_TEST_CASE()
namespace btt      = testsuite::btt;
namespace utf_data = testsuite::utf_data;

namespace parser  = eda::vhdl::parser;
namespace ast     = eda::vhdl::ast;
namespace vhdl    = eda::vhdl;


#endif /* TESTSUITE_COMMON_INCLUDE_TESTSUITE_NAMESPACE_ALIAS_HPP_ */
