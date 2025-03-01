//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/literals.hpp>

namespace testsuite::util {

///
/// @brief Test case fixture for file_mapp, position_cache and diagnostic_handler
///
/// In the UT, the same sequences of instances are used again and again to carry out tests.
/// Small changes in the API entail changes in the UT in several places. The fixture is intended
/// for each individual test so that only one place needs to be changed when changes are made.
///
/// @tparam IteratorT iterator_type
///
/// @see [Single test case fixture](
///       https://www.boost.org/doc/libs/1_87_0/libs/test/doc/html/boost_test/tests_organization/fixtures/case.html)
///
template <typename IteratorT>
struct diagnostic_handler_fixture {
    using iterator_type = IteratorT;
    using file_id_type = ibis::util::file_mapper::file_id_type;
    using position_cache_type = parser::position_cache<iterator_type>;
    using diagnostic_handler_type = parser::diagnostic_handler<iterator_type>;
    using vhdl_context = parser::context;

    static constexpr vhdl_context::value_type const error_limit{ 10 };

    diagnostic_handler_fixture() { BOOST_TEST_MESSAGE("setup diagnostic_handler_fixture"); }

    diagnostic_handler_fixture(std::size_t position_cache_reserve, std::uint32_t error_limit_)
        : position_cache{ position_cache_reserve }
        , ctx{ error_limit_ }
    {
        BOOST_TEST_MESSAGE("setup diagnostic_handler_fixture");
    }

    ~diagnostic_handler_fixture() { BOOST_TEST_MESSAGE("teardown diagnostic_handler_fixture"); }

    ///
    /// Add file name with contents to file mapper, returning diagnostic_handler
    /// related to file mapper's file_id and position_cache's proxy. The output
    /// can be read by member function @fn output() and VHDL context.
    /// @param filename
    /// @param contents
    /// @return diagnostic_handler_type
    ///
    auto diagnostic_handler(std::string_view filename, std::string&& contents)
    {
        BOOST_TEST_MESSAGE("diagnostic_handler_fixture add file " << filename);

        auto const current_file_id = file_mapper.add_file(filename, contents);
        auto position_proxy = position_cache.get_proxy(current_file_id);
        return diagnostic_handler_type{ os, ctx, std::move(position_proxy) };
    }

    /// The output generated from diagnostic_handler
    std::string output() const { return os.str(); }

    /// The VHDL context
    vhdl_context& context() { return ctx; }

private:
    ibis::util::file_mapper file_mapper{};
    position_cache_type position_cache{ 4096 };
    btt::output_test_stream os{};
    vhdl_context ctx{ error_limit };
};

}  // namespace testsuite::util
