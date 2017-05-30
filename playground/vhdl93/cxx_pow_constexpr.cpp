
#include <boost/hana/assert.hpp>
#include <boost/hana/at_key.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>

#include <iostream>
#include <cmath>
#include <cassert>
#include <limits>       // std::numeric_limits

namespace hana = boost::hana;

constexpr auto m = hana::make_map(
    hana::make_pair(hana::int_c<2>,  hana::int_c<1024>),
    hana::make_pair(hana::int_c<8>,  hana::int_c<342>),
    hana::make_pair(hana::int_c<10>, hana::int_c<309>),
    hana::make_pair(hana::int_c<16>, hana::int_c<256>)
);


namespace detail {

constexpr double power(double x, unsigned n)
{
    double acc{0};

    if (n == 0) {
        return 1;
    }

    if (n % 2 == 0) {
        acc = power(x, n / 2);
        return acc * acc;
    }
    else {
        return x * power(x, n - 1);
    }
}

} // namespace detail


template <unsigned Radix, std::size_t N> struct pow_table
{
    static const std::size_t size = N;

    constexpr pow_table() : value{}
    {
        for(unsigned i = 0; i != N; ++i) {
            value[i] = detail::power(Radix, i);
        }
    }

    double value[N];
};


static_assert(std::numeric_limits<double>::max_exponent10 == 308,
              "IEEE-754 double type is required");

constexpr auto log_radix_map = hana::make_map(
    // log(Radix, 10e308)
    hana::make_pair(hana::int_c<2>,  hana::int_c<1024>),
    hana::make_pair(hana::int_c<8>,  hana::int_c<342>),
    hana::make_pair(hana::int_c<10>, hana::int_c<309>),
    hana::make_pair(hana::int_c<16>, hana::int_c<256>)
);


template <unsigned Radix>
static inline
double pow(unsigned n)
{
    constexpr auto N = log_radix_map[hana::int_c<Radix>];
    assert( n < (unsigned)N && "pow exponent 'n' out of range");

    static constexpr auto lut = pow_table<Radix, N>{};

    return lut.value[n];
}


int main()
{
    // test fail with radix = 10
    constexpr unsigned Radix = 10;
    constexpr unsigned N = log_radix_map[hana::int_c<Radix>];

    std::cout << "Radix = " << Radix << "\n";
    for (unsigned n = 0; n != N; ++n)
    {
        std::cout << (std::pow(Radix, n) - pow<Radix>(n)) << " ";
    }
    std::cout << "\n";

  return 0;
}
