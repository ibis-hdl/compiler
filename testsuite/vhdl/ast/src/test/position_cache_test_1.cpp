#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <testsuite/vhdl/ast/position_cache_fixture.hpp>

#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <filesystem>

#include <testsuite/namespace_alias.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(position_cache)

//
// Test File #1 (Lorem Ipsum)
//
// ----8<----8<----8<----8<----8<----8<----
// Lorem ipsum dolor sit amet, consetetur
// sadipscing elitr, sed diam nonumy eirmod
// tempor invidunt ut labore et dolore magna
// aliquyam erat, sed diam voluptua. At vero eos
// et accusam et justo duo dolores et ea rebum.
// Stet clita kasd gubergren, no sea takimata
// sanctus est Lorem ipsum dolor sit amet.
// Lorem ipsum dolor sit amet, consetetur
// sadipscing elitr, sed diam nonumy eirmod
// tempor invidunt ut labore et dolore magna
// aliquyam erat, sed diam voluptua. At vero eos
// et accusam et justo duo dolores et ea rebum.
// Stet clita kasd gubergren, no sea takimata
// sanctus est Lorem ipsum dolor sit amet.
// ---->8---->8---->8---->8---->8---->8----

using namespace testsuite;
using testsuite::vhdl::ast::position_cache_fixture;

//
// Test of basic embedding the filename and contents into, using test input file #1.
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(contents_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;  // under test

    fs::path const path = fixture.test_case_source_dir();
    auto const file_name = path / "LoremIpsum.txt";
    std::size_t const id_ref = fixture.load_reference(file_name);
    std::string const file_contents = fixture.reference_contents(id_ref);

    // add file name with contents to position cache.
    auto position_proxy = position_cache_ut.add_file(file_name.string(), file_contents);
    auto const id = position_proxy.id();

    // ID and file_name with contents shall be the same.
    BOOST_TEST(value_of(id) == id_ref);
    BOOST_TEST(position_cache_ut.file_name(id) == file_name);
    BOOST_TEST(position_cache_ut.file_contents(id) == file_contents);

    // check the range functionality by creating a temporary string from this range.
    auto const [first, last] = position_cache_ut.range(id);
    std::string const range_contents{ first, last };

    // the contents created from cache's range shall be equal to origin.
    BOOST_TEST(range_contents == position_cache_ut.file_contents(id));
    BOOST_TEST(range_contents == fixture.reference_contents(id_ref));
}

//
// Check basic annotation capabilities *without* proxy/handle using string #1.
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(basic_annotate_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

   // position/string to find
    std::string const tagging_str{ "elitr" };

    // reuse ID from last test 'contents_1_txt'
    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);

    // emulate the parser, return pair of iterator to search string 'tagging_str' ...
    auto const [first, last] = fixture.contents_range(id, tagging_str);

    // ... and pseudo 'tag' them, basically initialize the AST node.
    ast::position_tagged node;
    position_cache_ut.annotate(id, node, first, last);

    auto const range = position_cache_ut.position_of(node);

    BOOST_TEST(range.has_value());
    // dereference iterator and compare address of object.
    BOOST_TEST(&*first == &*range.value().begin());
    BOOST_TEST(&*last == &*range.value().end());

    // store tagged node by key into fixture's internal memory for later use.
    fixture.addNode(make_key(id_ref, tagging_str), node);
}

//
// Check basic annotation capabilities *with* proxy/handle using string #2.
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_annotate_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // position/string to find
    std::string const tagging_str{ "voluptua" };

    // reuse ID from last test 'contents_1_txt'
    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);

    auto proxy = position_cache_ut.get_proxy(id);

    auto const [first, last] = fixture.contents_range(id, tagging_str);
    ast::position_tagged node;
    proxy.annotate(node, first, last);
    auto const range = proxy.position_of(node);

    BOOST_TEST(range.has_value());
    // dereference iterator and compare address of object.
    BOOST_TEST(&*first == &*range.value().begin());
    BOOST_TEST(&*last == &*range.value().end());

    // store tagged node by key into fixture's internal memory for later use.
    fixture.addNode(make_key(id_ref, tagging_str), node);
}

//
// Check node handling using the proxy with test string #1.
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_position1_of_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // position/string to find
    std::string const tagged_str{ "elitr" };

    // get the tagged node from test before
    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);
    auto tagged_node = fixture.getNode(make_key(id_ref, tagged_str));

    auto proxy = position_cache_ut.get_proxy(id);
    auto const range = proxy.position_of(tagged_node);
    BOOST_TEST(range.has_value());

    std::string const node_str{ range.value().begin(), range.value().end() };

    BOOST_TEST(node_str == tagged_str);
}

//
// Check node handling using the proxy with test string #2.
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_position2_of_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    // position/string to find
    std::string const tagged_str{ "voluptua" };

    // get the tagged node from test before
    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);
    auto tagged_node = fixture.getNode(make_key(id_ref, tagged_str));

    auto proxy = position_cache_ut.get_proxy(id);
    auto const range = proxy.position_of(tagged_node);
    BOOST_TEST(range.has_value());

    std::string const node_str{ range.value().begin(), range.value().end() };

    BOOST_TEST(node_str == tagged_str);
}

//
// Check for correct line numbers of tagged nodes
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_lineno_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);
    auto proxy = position_cache_ut.get_proxy(id);

    {
        // test string #1
        auto node = fixture.getNode(make_key(id_ref, "elitr"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::size_t const line_no = proxy.line_number(range.value().begin());
        BOOST_TEST(line_no == 2);
    }

    {
        // test string #2
        auto node = fixture.getNode(make_key(id_ref, "voluptua"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        std::size_t const line_no = proxy.line_number(range.value().begin());
        BOOST_TEST(line_no == 4);
    }
}

//
// Check for correct line of tagged nodes
//
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_CASE(proxy_line_1_txt)
{
    // short-hands for convenience
    auto& fixture = position_cache_fixture::instance();
    auto& position_cache_ut = fixture.position_cache;

    // helper
    auto const make_key = [](std::size_t id, auto name) { return std::to_string(id) + name; };

    std::size_t const id_ref = fixture.current_FileID();
    auto const id = position_cache_fixture::file_id_type(id_ref);
    auto proxy = position_cache_ut.get_proxy(id);

    {
        auto node = fixture.getNode(make_key(id_ref, "elitr"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        // expect line #2 of LoremIpsum.txt
        std::string const expected{ "sadipscing elitr, sed diam nonumy eirmod" };

        parser::iterator_type first = range.value().begin();
        parser::iterator_type const iter = proxy.get_line_start(first);
        auto const current_line = proxy.current_line(iter);

        BOOST_TEST(expected == current_line);
    }

    {
        auto node = fixture.getNode(make_key(id_ref, "voluptua"));
        auto const range = proxy.position_of(node);
        BOOST_TEST(range.has_value());

        // expect line #4 of LoremIpsum.txt
        std::string expected{ "aliquyam erat, sed diam voluptua. At vero eos" };

        parser::iterator_type first = range.value().begin();
        parser::iterator_type const iter = proxy.get_line_start(first);
        auto const current_line = proxy.current_line(iter);

        BOOST_TEST(expected == current_line);
    }
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
