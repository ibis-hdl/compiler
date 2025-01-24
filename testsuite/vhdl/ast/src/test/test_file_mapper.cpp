//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <ibis/util/file_mapper.hpp>

#include <filesystem>
#include <string_view>

#include <testsuite/namespace_alias.hpp>

namespace valid_data {

using namespace std::literals;

// https://www.loremipsum.de/
auto constexpr lorem_ipsum = R"(
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut 
labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo 
dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit 
amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor 
invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et 
justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum 
dolor sit amet.)"sv;

// https://baconipsum.com/
auto constexpr bacon_ipsum = R"(
Bacon ipsum dolor amet flank ham brisket, sirloin rump tail doner swine sausage beef pig drumstick 
leberkas landjaeger. Ground round tongue fatback, sausage ball tip salami turducken biltong pork 
belly tenderloin. Tongue filet mignon brisket, pork loin turkey venison kielbasa cow drumstick 
ball tip turducken boudin. Shankle jerky bacon brisket tongue turducken flank ground round.
)"sv;

}  // namespace valid_data
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE(file_mapper)

// clang-format off
BOOST_AUTO_TEST_CASE(file_mapper,
                     *utf::label("parser")
                     *utf::label("tagging"))
// clang-format on
{
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_AUTO_TEST_SUITE_END()
