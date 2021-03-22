/*
 * position_cache_fixture.cpp
 *
 *  Created on: 06.09.2018
 *      Author: olaf
 */

#include <testsuite/ast/position_cache_fixture.hpp>
#include <testsuite/ast/compile_builtin.hpp>

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace testsuite {

position_cache_fixture*& position_cache_fixture::instance()
{
    static position_cache_fixture* self = nullptr; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    return self;
}

position_cache_fixture::position_cache_fixture()
: current_FileID{ 0 }
{
    //std::cout << "INFO(testsuite::position_cache_fixture) Setup\n";
    instance() = this;
}

position_cache_fixture::~position_cache_fixture() // NOLINT(modernize-use-equals-default)
{
    //std::cout << "INFO(testsuite::position_cache_fixture) Teardown\n";
}


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

    unsigned const argc = boost::unit_test::framework::master_test_suite().argc;
    char** const   argv = boost::unit_test::framework::master_test_suite().argv;

    // check command line args
    for (unsigned i = 0; i != argc; i++) {
        std::string_view const argv_sv{ argv[i] }; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto source_dir = parse_for("--source-dir=", argv_sv);
        if (source_dir) {
            input_path.swap(source_dir);
            BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) using given 'source-dir' path \""
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


std::size_t position_cache_fixture::load_reference(std::string const& file_name)
{
    std::size_t const id = inputs.size();
    BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) emplace "
                        << file_name << " with ID = " << id);
    inputs.emplace_back(read_file(file_name));
    return id;
}

std::string position_cache_fixture::read_file(std::string const& file_name)
{
    BOOST_TEST_MESSAGE("INFO(testsuite::position_cache_fixture) load " << file_name);

    std::ifstream file{ file_name, std::ios::in | std::ios::binary };

    BOOST_TEST_REQUIRE((!file.fail() && !file.bad()));

    std::ostringstream ss{};
    file.unsetf(std::ios::skipws);
    ss << file.rdbuf();

    return ss.str();
}

std::tuple<parser::iterator_type, parser::iterator_type>
position_cache_fixture::contents_range(std::size_t id, std::string_view str)
{
    auto const pos = position_cache.file_contents(id).find(str);
    BOOST_TEST_REQUIRE(pos != std::string::npos);

    parser::iterator_type begin = position_cache.file_contents(id).begin() + pos;
    parser::iterator_type end   = begin + str.length();

    return std::tuple{ begin, end };
}

ast::position_tagged& position_cache_fixture::addNode(std::string const& key, ast::position_tagged const& node)
{
    BOOST_TEST_MESSAGE("INFO(position_cache_fixture) add Node: " << key);
    BOOST_TEST_REQUIRE(node_map.count(key) == 0);
    return node_map[key] = node;
}

ast::position_tagged const& position_cache_fixture::getNode(std::string const& key) const
{
    BOOST_TEST_MESSAGE("INFO(position_cache_fixture) lookup Node: " << key);
    BOOST_TEST_REQUIRE(node_map.count(key) > 0);
    // FixMe: Clang-Tidy: warning: do not use const_cast [cppcoreguidelines-pro-type-const-cast]
    //        but it's required here
    return const_cast<node_map_type&>(node_map)[key];
}

} // namespace testsuite
