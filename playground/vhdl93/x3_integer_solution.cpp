/*
 * x3_integer_solution.cpp
 *
 *  Created on: 21.05.2018
 *      Author: olaf
 */

/*
 * Concept Check for VHDL digit separator
 *
 * VHDL uses for numeric literals a '_' as separator. Spirit.X3 doesn't
 * support explicit separators by his parsers, e.g. ()int_, double_).
 * As of C++14 (sesp.
 * [n3781](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3781.pdf))
 * this is a C++ language feature. Anyway, there are several approaches
 * to realize parsing digit separator, e.g. Stackoverflow
 * [Using boost::spirit::qi to parse numbers with separators](
 * https://stackoverflow.com/questions/29132809/using-boostspiritqi-to-parse-numbers-with-separators?answertab=active#tab-top).
 * Here an alternative approach is used - filtering iterator which allows
 * to use Spirit.X3 supplied numeric parser.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>

//#define BOOST_SPIRIT_X3_DEBUG
#include <boost/spirit/home/x3.hpp>


int main()
{
    namespace x3 = boost::spirit::x3;

    std::vector<std::string> const test_cases {
        "0",
        "1",
        "01",
        "1_000",
        "42_666_4711",
        "4_294_967_295", // uint32::max
        // below must fail to parse
        "4_294_967_296",
        "4_294_967_295_0" };

    for (auto str : test_cases) {

        // fake x3::raw[] directive
        auto const str_view = boost::make_iterator_range(str.begin(),
                str.end());

        struct separator_predicate {
            bool operator()(char x) {
                return '_' != x;
            }
        };

        auto str_view_f = boost::make_iterator_range(
                boost::make_filter_iterator(separator_predicate{},
                        str_view.begin(), str_view.end()),
                boost::make_filter_iterator(separator_predicate{},
                        str_view.end())
        );

        auto iter = str_view_f.begin();
        auto last = str_view_f.end();

        auto str_filt = std::string(iter, last);

        uint32_t attribute;
        auto const integer = x3::rule<struct _, uint32_t> { "integer" } = x3::uint_;

        bool parse_ok = x3::phrase_parse(iter, last, integer, x3::space, attribute);

        if (parse_ok && iter == last) {
            std::cout << "succeeded: \"" << str_view << "\" -> \"" << str_filt
                    << "\" -> " << attribute << "\n";
        } else {
            std::cout << "failed: \"" << str_view << "\" -> \"" << str_filt
                    << "\" -> " << "N/A" << "\n";
        }
    }

    return 0;
}

/* ----8<----
 output:
 succeeded: "0" -> "0" -> 0
 succeeded: "1" -> "1" -> 1
 succeeded: "01" -> "01" -> 1
 succeeded: "1_000" -> "1000" -> 1000
 succeeded: "42_666_4711" -> "426664711" -> 426664711
 succeeded: "4_294_967_295" -> "4294967295" -> 4294967295
 failed: "4_294_967_296" -> "4294967296"
 failed: "4_294_967_295_0" -> "42949672950"
 ----->8----- */

