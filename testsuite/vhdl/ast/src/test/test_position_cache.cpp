//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <filesystem>
#include <string_view>

#include <testsuite/namespace_alias.hpp>

namespace valid_data {

using namespace std::literals;

// https://www.loremipsum.de/
constexpr auto const lorem_ipsum = R"(
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut 
labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo 
dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit 
amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor 
invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et 
justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum 
dolor sit amet.)"sv;

// https://baconipsum.com/
constexpr auto const bacon_ipsum = R"(
Bacon ipsum dolor amet flank ham brisket, sirloin rump tail doner swine sausage beef pig drumstick 
leberkas landjaeger. Ground round tongue fatback, sausage ball tip salami turducken biltong pork 
belly tenderloin. Tongue filet mignon brisket, pork loin turkey venison kielbasa cow drumstick 
ball tip turducken boudin. Shankle jerky bacon brisket tongue turducken flank ground round.
)"sv;

///
/// helper to gather iterator pair inside the contents for "tagging"
///
/// for concept, see [coliru](https://coliru.stacked-crooked.com/a/571ed8baf4265f8c)
using find_pos_type =
    std::tuple<std::string_view::size_type, std::string_view::iterator, std::string_view::iterator>;
auto find(std::string_view contents, std::string_view search_str,
          std::string_view::size_type pos_ = 0) -> find_pos_type
{
    auto pos = contents.find(search_str, pos_);
    // ensure correct found
    assert(pos != std::string::npos);
    assert(contents.substr(pos, search_str.size()).compare(search_str) == 0);

    auto view = contents.substr(pos, search_str.size());
    return { pos, begin(view), end(view) };
}

}  // namespace valid_data

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(position_cache)

using valid_data::find;
using namespace std::literals;

///
/// Test the correct function for multiple string searches for a pair of iterators
///
BOOST_AUTO_TEST_CASE(test_requirements)
{
    auto const search_str{ "elitr"sv };

    auto const verbose = [](auto pos, auto first, auto last) {
        std::cout << std::format("pos = {:3d}: {}\n", pos, std::string_view{ first, last });
    };

    // find 1st
    auto const [pos1, first1, last1] = find(valid_data::lorem_ipsum, search_str);
    verbose(pos1, first1, last1);

    // find 2nd
    auto const [pos2, first2, last2] = find(valid_data::lorem_ipsum, search_str, pos1 + 1);
    verbose(pos2, first2, last2);

    BOOST_REQUIRE(search_str == std::string_view(first1, last1));
    BOOST_REQUIRE(search_str == std::string_view(first2, last2));
}

using iterator_type = std::string_view::iterator;
using ibis::vhdl::ast::position_tagged;

///
/// Check basic functionality with position_cache "proxy"
///
// clang-format off
BOOST_AUTO_TEST_CASE(position_cache_basic,
                     *utf::label("ast")
                     *utf::label("parser"))
// clang-format on
{
    ibis::util::file_mapper file_mapper;
    ibis::vhdl::parser::position_cache<iterator_type> position_cache;
    auto const filename{ "Lorem Ipsum" };
    auto current_file = file_mapper.add_file(filename, valid_data::lorem_ipsum);
    auto annotator = position_cache.annotator_for(current_file.id());

    // store all found pos and iterators for this test for later/final evaluation. The test sequence
    // order index equals to the position added into the vector. If more complex test cases are
    // created, make sure that the vector index can be clearly assigned to a test in order to avoid
    // mistakes during the check.
    std::vector<valid_data::find_pos_type> find_pos;

    {  // #0
        auto const search_str{ "elitr"sv };
        auto [pos, first, last] = find(valid_data::lorem_ipsum, search_str);
        find_pos.emplace_back(pos, first, last);

        position_tagged ast_node;
        annotator.annotate(ast_node, first, last);

        BOOST_TEST(position_cache.position_count() == 1U);
        BOOST_TEST(ast_node.file_id == current_file.id());
        BOOST_TEST(ast_node.position_id == 0U);
        // getting iterators back (annotated by x3 on_success error_handler)
        auto iter_range = position_cache.position_of(ast_node);
        BOOST_TEST(std::begin(iter_range) == first);
        BOOST_TEST(std::end(iter_range) == last);
    }
    {  // #1
        auto const search_str{ "voluptua"sv };
        auto [pos, first, last] = find(valid_data::lorem_ipsum, search_str);
        find_pos.emplace_back(pos, first, last);

        position_tagged ast_node;
        annotator.annotate(ast_node, first, last);

        BOOST_TEST(position_cache.position_count() == 2U);
        BOOST_TEST(ast_node.file_id == current_file.id());
        BOOST_TEST(ast_node.position_id == 1U);
        // getting iterators back (annotated by x3 on_success error_handler)
        auto iter_range = position_cache.position_of(ast_node);
        BOOST_TEST(std::begin(iter_range) == first);
        BOOST_TEST(std::end(iter_range) == last);
    }
    {  // #2
        auto const search_str{ "elitr"sv };
        [[maybe_unused]] auto [pos_prev, f, l] = find_pos[0];  // previous find pass
        auto [pos, first, last] = find(valid_data::lorem_ipsum, search_str, pos_prev + 1);
        BOOST_REQUIRE(pos_prev != pos);
        find_pos.emplace_back(pos, first, last);

        position_tagged ast_node;
        annotator.annotate(ast_node, first, last);
    }
    {  // #3
        auto const search_str{ "voluptua"sv };
        [[maybe_unused]] auto [pos_prev, f, l] = find_pos[1];  // previous find pass
        auto [pos, first, last] = find(valid_data::lorem_ipsum, search_str, pos_prev + 1);
        BOOST_REQUIRE(pos_prev != pos);
        find_pos.emplace_back(pos, first, last);

        position_tagged ast_node;
        annotator.annotate(ast_node, first, last);
    }
    BOOST_TEST(position_cache.position_count() == 4U);
    BOOST_TEST(find_pos.size() == position_cache.position_count());

    // TBD more tests
}

///
/// Check with 2 files on correct position tags
///
// clang-format off
BOOST_AUTO_TEST_CASE(position_cache_annotate,
                     *utf::label("ast")
                     *utf::label("parser"))
// clang-format on
{
    ibis::util::file_mapper file_mapper;
    ibis::vhdl::parser::position_cache<iterator_type> position_cache;

    // two input files
    auto lorem_ipsum_file = file_mapper.add_file("Lorem Ipsum", valid_data::lorem_ipsum);
    auto bacon_ipsum_file = file_mapper.add_file("Bacon Ipsum", valid_data::bacon_ipsum);

    std::vector<position_tagged> tagged_nodes;

    // prepare
    struct {
        ibis::util::file_mapper::file_id_type file_id;
        std::string_view search_str;
    } const file_data[] = {
        { lorem_ipsum_file.id(), "ipsum" },  // --
        { bacon_ipsum_file.id(), "beef" }    // --
    };

    for (auto [file_id, search_str] : file_data) {
        auto annotator = position_cache.annotator_for(file_id);
        auto [pos, first, last] = find(file_mapper.file_contents(file_id), search_str);

        position_tagged ast_node;
        annotator.annotate(ast_node, first, last);
        // position represents order of ast_nodes inserted, hence order of file_data
        tagged_nodes.emplace_back(std::move(ast_node));
    }

    // test
    {
        for (auto index{ 0U }; auto const& ast_node : tagged_nodes) {
            BOOST_TEST_CONTEXT(">>> Test index at " << index << " <<<")
            {
                auto gold_data = file_data[index];
                BOOST_TEST(ast_node.file_id == gold_data.file_id);
                BOOST_TEST(ast_node.position_id == index);
                auto iter_range = position_cache.position_of(ast_node);
                BOOST_TEST(std::string_view{ iter_range } == gold_data.search_str,
                           btt::per_element());
            }
            ++index;
        }
    }
}

///
/// Pessimistic test
///
// clang-format off
BOOST_AUTO_TEST_CASE(position_cache_failure_handling,
                     *utf::label("ast")
                     *utf::label("parser"))
// clang-format on
{
    // TBD
    // Thoughts on this: It would be possible that the position would *not* be tagged (for whatever
    // reason). However, this test does not make sense here, only for the caller.
    // Nevertheless, this test is here as a reminder.
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
