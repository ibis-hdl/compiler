//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/file_mapper.hpp>

#include <boost/test/tools/assertion.hpp>                    // for binary_expr, value_expr, EQ
#include <boost/test/tools/cstring_comparison_op.hpp>        // for EQ, NE
#include <boost/test/tools/detail/indirections.hpp>          // for assertion_type
#include <boost/test/tools/detail/per_element_manip.hpp>     // for per_element
#include <boost/test/tools/interface.hpp>                    // for BOOST_TEST
#include <boost/test/tree/decorator.hpp>                     // for label, collector_t, base
#include <boost/test/unit_test.hpp>                          // for BOOST_PP...
#include <boost/test/utils/basic_cstring/basic_cstring.hpp>  // for basic_cstring
#include <boost/test/utils/lazy_ostream.hpp>                 // for operator<<

#include <string_view>
#include <string>

#include <testsuite/namespace_alias.hpp>  // for btt, utf

using namespace std::literals::string_view_literals;

namespace valid_data {

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

}  // namespace valid_data
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(file_mapper)

///
/// Check basic functionality with current_file "proxy"
///
// clang-format off
BOOST_AUTO_TEST_CASE(file_mapper_basic,
                     *utf::label("ast")
                     *utf::label("parser")
                     *utf::label("tagging"))
// clang-format on
{
    ibis::util::file_mapper file_mapper;
    auto const filename{ "Lorem Ipsum"sv };

    // use overload @fn add_file(std::string_view filename, std::string_view contents)
    auto current_file = file_mapper.add_file(filename, valid_data::lorem_ipsum);

    BOOST_TEST(file_mapper.file_count() == 1U);
    BOOST_TEST((file_mapper.file_count() - 1) == current_file.file_id().get());
    BOOST_TEST(file_mapper.valid_id(current_file.file_id()) == true);
    BOOST_TEST(file_mapper.file_name(current_file.file_id()) == filename);
    BOOST_TEST(file_mapper.file_contents(current_file.file_id()) == valid_data::lorem_ipsum,
               btt::per_element());
    // check correctness of current_file proxy
    BOOST_TEST(current_file.file_name() == file_mapper.file_name(current_file.file_id()),
               btt::per_element());
    BOOST_TEST(current_file.file_contents() == file_mapper.file_contents(current_file.file_id()),
               btt::per_element());

    // use move-sematic overload @fn add_file(std::string&& filename, std::string&& contents)
    // with same filename and contents (for convenience)
    current_file =
        file_mapper.add_file(std::string{ filename }, std::string{ valid_data::lorem_ipsum });

    BOOST_TEST(file_mapper.file_count() == 2U);
    BOOST_TEST((file_mapper.file_count() - 1) == current_file.file_id().get());
    BOOST_TEST(file_mapper.valid_id(current_file.file_id()) == true);
    BOOST_TEST(file_mapper.file_name(current_file.file_id()) == filename);
    BOOST_TEST(file_mapper.file_contents(current_file.file_id()) == valid_data::lorem_ipsum,
               btt::per_element());
    // check correctness of current_file proxy
    BOOST_TEST(current_file.file_name() == file_mapper.file_name(current_file.file_id()),
               btt::per_element());
    BOOST_TEST(current_file.file_contents() == file_mapper.file_contents(current_file.file_id()),
               btt::per_element());
}

///
/// Check functionality with two files
///
// clang-format off
BOOST_AUTO_TEST_CASE(file_mapper_api,
                     *utf::label("ast")
                     *utf::label("parser")
                     *utf::label("tagging"))
// clang-format on
{
    ibis::util::file_mapper file_mapper;
    auto const filename_lorem{ "Lorem Ipsum"sv };
    auto const filename_bacon{ "Bacon Ipsum"sv };

    // use overload @fn add_file(std::string_view filename, std::string_view contents)
    auto lorem_ipsum = file_mapper.add_file(filename_lorem, valid_data::lorem_ipsum);
    auto bacon_ipsum = file_mapper.add_file(filename_bacon, valid_data::bacon_ipsum);

    BOOST_TEST(file_mapper.file_count() == 2U);

    BOOST_TEST(file_mapper.valid_id(lorem_ipsum.file_id()) == true);
    BOOST_TEST(file_mapper.file_name(lorem_ipsum.file_id()) == filename_lorem);
    BOOST_TEST(file_mapper.file_contents(lorem_ipsum.file_id()) == valid_data::lorem_ipsum,
               btt::per_element());

    BOOST_TEST(file_mapper.valid_id(bacon_ipsum.file_id()) == true);
    BOOST_TEST(file_mapper.file_name(bacon_ipsum.file_id()) == filename_bacon);
    BOOST_TEST(file_mapper.file_contents(bacon_ipsum.file_id()) == valid_data::bacon_ipsum,
               btt::per_element());

    // check correctness of proxy
    BOOST_TEST(lorem_ipsum.file_name() == file_mapper.file_name(lorem_ipsum.file_id()),
               btt::per_element());
    BOOST_TEST(bacon_ipsum.file_name() == file_mapper.file_name(bacon_ipsum.file_id()),
               btt::per_element());

    // paranoid
    BOOST_TEST(lorem_ipsum.file_contents() != bacon_ipsum.file_contents());
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
