/*
 * Boost Spirit X3: “Attribute does not have the expected size,” but why does it care?
 * https://stackoverflow.com/questions/41101915/boost-spirit-x3-attribute-does-not-have-the-expected-size-but-why-does-it-ca
 *
 */
#define BOOST_SPIRIT_X3_DEBUG

#include <iostream>
#include <boost/spirit/home/x3.hpp>

using namespace std;
namespace x3 = boost::spirit::x3;

namespace lang {

    using namespace x3;

    struct Constant {
    };

    rule<class constant_id, Constant> const constant = "constant";

    auto const integer_literal = -char_('-') >> +digit;
    auto const float_literal = -char_('-') >> +digit >> -(char_('.') >> *digit);

    auto const constant_def = (integer_literal)[([](auto &ctx) { _val(ctx) = Constant(); })];

    BOOST_SPIRIT_DEFINE(constant);
}

int main(int argc, char *argv[]) {

    string s("3.14159");
    if (x3::phrase_parse(s.begin(), s.end(), lang::constant, x3::space)) {
        cout << "Ok!";
    } else {
        cout << "Error!";
    }

    return 0;
}
