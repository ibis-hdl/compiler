#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/vhdl/ast/position_cache_fixture.hpp>

#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <filesystem>

#include <testsuite/namespace_alias.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(position_cache)

using namespace testsuite;

///
/// Test File #2 (Bacon ipsum)
///

///
/// Test of basic embedding the filename and contents into with test input file #1.
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(contents_2_txt)
{
    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();

    fs::path const path = fixture->test_case_source_dir();
    auto const file_name = path / "BaconIpsum.txt";

    std::size_t const id_ref = fixture->load_reference(file_name.string());
    fixture->current_FileID = id_ref;

    std::size_t const id = position_cache.add_file(file_name.string());
    BOOST_TEST(id == id_ref);

    position_cache.file_contents(id) = fixture->reference_contents(id_ref);

    BOOST_TEST(position_cache.file_name(id) == file_name);
    BOOST_TEST(position_cache.file_contents(id) == fixture->reference_contents(id_ref));

    auto const [first, last] = position_cache.range(id);
    std::string const range_contents{ first, last };
    BOOST_TEST(range_contents == position_cache.file_contents(id));
    BOOST_TEST(range_contents == fixture->reference_contents(id_ref));
    BOOST_TEST(position_cache.file_contents(id) == fixture->reference_contents(id_ref));
}

///
/// Check basic annotation capabilities *without* proxy/handle using string #1.
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(basic_annotate_2_txt)
{
    std::string const tagging_str{ "Bacon" };

    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    ast::position_tagged node;
    auto const [first, last] = fixture->contents_range(id, tagging_str);
    position_cache.annotate(id, node, first, last);
    auto const range = position_cache.position_of(node);
    fixture->addNode(node_name(id, tagging_str), node);

    BOOST_TEST(range.has_value());
    // dereference iterator and compare address of object.
    BOOST_TEST(&*first == &*range.value().begin());
    BOOST_TEST(&*last == &*range.value().end());
}

///
/// Check basic annotation capabilities *with* proxy/handle using string #2.
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_annotate_2_txt)
{
    std::string const tagging_str{ "porchetta" };

    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    auto proxy = position_cache.handle(id);

    ast::position_tagged node;
    auto const [first, last] = fixture->contents_range(id, tagging_str);
    proxy.annotate(node, first, last);
    auto const range = proxy.position_of(node);
    fixture->addNode(node_name(id, tagging_str), node);

    BOOST_TEST(range.has_value());
    // dereference iterator and compare address of object.
    BOOST_TEST(&*first == &*range.value().begin());
    BOOST_TEST(&*last == &*range.value().end());
}

///
/// Check node handling using the proxy with test string #1.
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_position1_of_2_txt)
{
    std::string const tagged_str{ "Bacon" };

    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    auto proxy = position_cache.handle(id);
    auto node = fixture->getNode(node_name(id, tagged_str));

    auto const range = proxy.position_of(node);
    BOOST_TEST(range.has_value());

    std::string const node_str{ range.value().begin(), range.value().end() };

    BOOST_TEST(node_str == tagged_str);
}

///
/// Check node handling using the proxy with test string #2.
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_position2_of_2_txt)
{
    std::string const tagged_str{ "porchetta" };

    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    auto proxy = position_cache.handle(id);
    auto node = fixture->getNode(node_name(id, tagged_str));

    auto const range = proxy.position_of(node);
    BOOST_TEST(range.has_value());

    std::string const node_str{ range.value().begin(), range.value().end() };

    BOOST_TEST(node_str == tagged_str);
}

///
/// Check for correct line numbers of tagged nodes
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_lineno_2_txt)
{
    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    auto proxy = position_cache.handle(id);

    {
        auto node = fixture->getNode(node_name(id, "Bacon"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::size_t const line_no = proxy.line_number(range.value().begin());
        BOOST_TEST(line_no == 1);
    }

    {
        auto node = fixture->getNode(node_name(id, "porchetta"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::size_t const line_no = proxy.line_number(range.value().begin());
        BOOST_TEST(line_no == 3);
    }
}

///
/// Check for correct line of tagged nodes
///
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_line_2_txt)
{
    auto const node_name = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // short-hands for convenience
    using testsuite::vhdl::ast::position_cache_fixture;

    auto& position_cache = position_cache_fixture::instance()->position_cache;
    auto* fixture = position_cache_fixture::instance();
    std::size_t const id = fixture->current_FileID;

    auto proxy = position_cache.handle(id);

    {
        auto node = fixture->getNode(node_name(id, "Bacon"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::string expected{ "Bacon ipsum dolor amet spare ribs tail" };

        parser::iterator_type first = range.value().begin();
        parser::iterator_type const iter = proxy.get_line_start(first);
        std::string current_line = proxy.current_line(iter);

        BOOST_TEST(expected == current_line);
    }

    {
        auto node = fixture->getNode(node_name(id, "porchetta"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::string expected{ "porchetta tenderloin kevin hamburger" };

        parser::iterator_type first = range.value().begin();
        parser::iterator_type const iter = proxy.get_line_start(first);
        std::string current_line = proxy.current_line(iter);

        BOOST_TEST(expected == current_line);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
