/*
 * vhdl_string_literal_print.cpp
 *
 *  Created on: 20.06.2018
 *      Author: olaf
 */
#include <iostream>
#include <cstdlib>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>


#if 0

struct predicate {
  predicate()
  : prev_char{ 0 }
  , dbl_quote_printed{ false }
  { }

  bool operator()(char chr) {

    auto const check = [this](char chr, char quote) {
        if((prev_char != quote) || (prev_char != chr) || dbl_quote_printed) {
          dbl_quote_printed = false;
          return true;
        } else {
          dbl_quote_printed = true;
          return false;
        }
    };

    bool flag = false;

    switch(chr) {
      case '"': flag = check(chr, '"'); break;
      case '%': flag = check(chr, '%'); break;
      default:  flag = true;
    }

    prev_char = chr;
    return flag;
  }

  char prev_char;
  bool dbl_quote_printed;
};


int main()
{
    for(std::string const str : {    // expected print:
        R"("""")",                   // ""
        R"(%%%%)",                   // %%
        R"(""Hello"")",              // "Hello"
        R"(Quotation: ""REPORT..."")", // Quotation: "REPORT..."
        R"("%"%")",                  // "%"%" (as is)
        R"(%"%"")",                  // %"%"
    }) {

        auto const range = boost::make_iterator_range(str);

        auto p = predicate{};
        auto const range_f = boost::make_iterator_range(
            boost::make_filter_iterator(p,
                    range.begin(), range.end()),
            boost::make_filter_iterator(p,
                    range.end())
        );

        std::cout << range_f << "\n";
    }
}

#else

#include <iostream>
#include <cstdlib>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>


struct predicate {

    typedef struct {
        char prev_char;
        bool quote_may_start;
    } state_type;

    predicate(predicate::state_type& state_)
    : state{ state_ }
    { }

    bool operator()(char chr) const {

        auto const check = [this](char chr, char quote)
        {
            if((state.prev_char != quote)
            || (state.prev_char != chr)
            ||  state.quote_may_start
            ) {
                state.quote_may_start = false;
                return true;
            } else {
                state.quote_may_start = true;
                return false;
            }
        };

        bool flag = false;

        switch(chr) {
            case '"': flag = check(chr, '"'); break;
            case '%': flag = check(chr, '%'); break;
            default:  flag = true;
        }

        state.prev_char = chr;
        return flag;
    }

    predicate::state_type& state;
};


int main()
{
    for(std::string const str : {    // expected print:
        R"("""")",                   // ""
        R"(%%%%)",                   // %%
        R"(""Hello"")",              // "Hello"
        R"(Quotation: ""REPORT..."")", // Quotation: "REPORT..."
        R"("%"%")",                  // "%"%" (as is)
        R"(%"%"")",                  // %"%"
    }) {

        auto const range = boost::make_iterator_range(str);

        using boost::adaptors::filtered;

        auto state = predicate::state_type{};

        /* a const predicate is required, hence the state are on external
         * storage, this prevents further copying the data inside the
         * algorithm. */
        boost::copy(
            range | filtered(predicate{state}),
            std::ostream_iterator<std::string::value_type>(std::cout, ""));

        std::cout << "\n";
    }
}

#endif
