//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <boost/test/included/unit_test.hpp>                 // for BOOST_PP...
#include <boost/test/tools/assertion.hpp>                    // for EQ, binary_expr, value_expr
#include <boost/test/tools/interface.hpp>                    // for BOOST_TEST
#include <boost/test/tree/decorator.hpp>                     // for label, collector_t, base
#include <boost/test/utils/basic_cstring/basic_cstring.hpp>  // for basic_cstring
#include <boost/test/utils/lazy_ostream.hpp>                 // for operator<<
#include <ibis/util/strong_type.hpp>                         // for strong_type, operator==

#include <testsuite/namespace_alias.hpp>  // for utf

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(position_tagged)

///
/// Test position_tagged functionality
///
/// This checks here can't be tested useful with file_mapper or position_cache due to numeric range
/// of types used. Testing util::strong_type<> alone doesn't give new information/tests
///
// clang-format off
BOOST_AUTO_TEST_CASE(position_tagged,
                     *utf::label("ast")
                     *utf::label("parser")
                     *utf::label("tagging"))
// clang-format on
{
    using namespace ibis::vhdl;

    {
        // test case: empty/default constructed, MAX_ID as marker
        ast::position_tagged position_tagged{};
        BOOST_TEST(position_tagged.file_id == ast::position_tagged::MAX_FILE_ID);
        BOOST_TEST(position_tagged.position_id == ast::position_tagged::MAX_POSITION_ID);
        BOOST_TEST(position_tagged.is_tagged() == false);
    }
    {
        // test case: wrong constructed - file tag only
        // NOLINTNEXTLINE(modernize-use-designated-initializers)
        ast::position_tagged position_tagged{
            ast::position_tagged::file_id_type{ 0UL },
            ast::position_tagged::MAX_POSITION_ID  // -- default
        };
        BOOST_TEST(position_tagged.file_id == 0U);
        BOOST_TEST(position_tagged.position_id == ast::position_tagged::MAX_POSITION_ID);
        BOOST_TEST(position_tagged.is_tagged() == false);
    }
    {
        // test case: wrong constructed - position tag only
        // clang-format off
        ast::position_tagged position_tagged{   // NOLINT(modernize-use-designated-initializers)
            ast::position_tagged::MAX_FILE_ID,  // -- default
            ast::position_tagged::position_id_type{ 0UL }
        };
        // clang-format on
        BOOST_TEST(position_tagged.file_id == ast::position_tagged::MAX_FILE_ID);
        BOOST_TEST(position_tagged.position_id == 0U);
        BOOST_TEST(position_tagged.is_tagged() == false);
    }
    {
        // correct tagged
        auto const id = 42U;
        // clang-format off
        ast::position_tagged position_tagged{ // NOLINT(modernize-use-designated-initializers)
            ast::position_tagged::file_id_type{ id },
            ast::position_tagged::position_id_type{ id }
        };
        // clang-format on
        BOOST_TEST(position_tagged.file_id == id);
        BOOST_TEST(position_tagged.position_id == id);
        BOOST_TEST(position_tagged.is_tagged() == true);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
