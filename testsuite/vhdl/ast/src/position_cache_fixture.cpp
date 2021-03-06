//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/ast/position_cache_fixture.hpp>
#include <testsuite/vhdl/ast/compile_builtin.hpp>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace testsuite::vhdl::ast {

position_cache_fixture& position_cache_fixture::instance()
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static position_cache_fixture static_position_cache_fixture;
    return static_position_cache_fixture;
}

position_cache_fixture::position_cache_fixture() = default;
position_cache_fixture::~position_cache_fixture() = default;

std::string position_cache_fixture::test_case_source_dir() const
{
    // use cached input path if any
    if (input_path) {
        return *input_path;
    }

    // try to parse for '--source-dir=' at boost.UTF

    auto const parse_for = [](std::string_view key, std::string_view argv) {
        auto const pos = argv.find(key);
        if (pos == std::string_view::npos) {
            return std::optional<std::string>{};
        }
        return std::optional<std::string>{ argv.substr(pos + key.size()) };
    };

    int const argc = boost::unit_test::framework::master_test_suite().argc;
    char** const argv = boost::unit_test::framework::master_test_suite().argv;

    assert(argc > 0 && "unexpected argc value from master_test_suite");

    // check command line args
    for (int i = 0; i != argc; i++) {
        // FixMe: Clang-Tidy [cppcoreguidelines-pro-bounds-pointer-arithmetic]
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        std::string_view const argv_sv{ argv[i] };
        auto source_dir = parse_for("--source-dir=", argv_sv);
        if (source_dir) {
            input_path.swap(source_dir);
            BOOST_TEST_MESSAGE(
                "INFO(testsuite::position_cache_fixture) using given 'source-dir' path \""
                << *input_path << "\"");
        }
    }

    // fall back: use hard coded from CMake build
    if (!input_path) {
        BOOST_TEST_REQUIRE(!compile_builtin::default_source_dir.empty());
        std::optional<std::string> source_dir{ compile_builtin::default_source_dir };
        input_path.swap(source_dir);
        BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) using builtin/compiled path \""
                           << *input_path << "\"");
    }

    return *input_path;
}

std::size_t position_cache_fixture::load_reference(fs::path const& file_name)
{
    std::size_t const id = inputs.size();

    BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) emplace "  // --
                       << file_name << " with ID = " << id);
    inputs.emplace_back(read_file(file_name));

    current_file_id = id;  // update
    return id;
}

std::string position_cache_fixture::read_file(fs::path const& file_name)
{
    BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) load " << file_name);

    std::ifstream file{ file_name, std::ios::in | std::ios::binary };

    BOOST_TEST_REQUIRE((!file.fail() && !file.bad()));

    std::ostringstream ss{};
    file.unsetf(std::ios::skipws);
    ss << file.rdbuf();

    return ss.str();
}

std::tuple<parser::iterator_type, parser::iterator_type> position_cache_fixture::contents_range(
    file_id_type id, std::string_view str) const
{
    auto const pos = position_cache.file_contents(id).find(str);
    BOOST_TEST_REQUIRE(pos != std::string::npos);

    parser::iterator_type begin =  // --
        position_cache.file_contents(id).begin() +
        static_cast<std::string_view::difference_type>(pos);

    parser::iterator_type end =  // --
        begin + static_cast<std::string_view::difference_type>(str.length());

    return std::tuple{ begin, end };
}

ibis::vhdl::ast::position_tagged& position_cache_fixture::addNode(
    std::string const& key, ibis::vhdl::ast::position_tagged const& node)
{
    BOOST_TEST_MESSAGE("INFO(position_cache_fixture) add Node: " << key);
    // this key doesn't have to be mapped before
    BOOST_TEST_REQUIRE(node_map.count(key) == 0);
    return node_map[key] = node;
}

ibis::vhdl::ast::position_tagged const& position_cache_fixture::getNode(
    std::string const& key) const
{
    BOOST_TEST_MESSAGE("INFO(position_cache_fixture) lookup Node: " << key);
    // this key has to be mapped before
    BOOST_TEST_REQUIRE(node_map.count(key) > 0);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<node_map_type&>(node_map)[key];
}

}  // namespace testsuite::vhdl::ast

///
/// Global Boost.Test Fixture Instance
///
using position_cache_fixture = testsuite::vhdl::ast::position_cache_fixture;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_GLOBAL_FIXTURE(position_cache_fixture);
