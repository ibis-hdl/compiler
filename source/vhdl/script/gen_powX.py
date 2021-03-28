#!/usr/bin/env python3

# THIS SCRIPT EXISTS ONLY FOR ARCHIVING AND IS NO LONGER FUNCTIONAL THESE DAYS.

from math import log2, log10, log, ceil
from itertools import cycle


class pow_LUT:

    def __init__(self, radix):
        self.nMax = 308   #  std::numeric_limits<double>::max()
        self.N = int(log(10**self.nMax, radix)) +1
        #self.N = 94
        self.radix = radix
        self.step = int(log2(self.radix))
        self.bit_stride = range(0, 64, self.step)

    def get(self):
        if self.radix == 10:
            pow_list = self.decimal_radix()
        else:
            pow_list = self.binary_radix()
        # due to limit range of unsigned long long the table is splitted
        if self.radix == 10:
            lut_table = self.format(pow_list)
            text = self.embrace('', lut_table.rstrip('\n, '))
            return text
        else:
            decl      = self.format(pow_list[0])
            lut_table = self.format(pow_list[1])
            text = self.embrace(decl, lut_table.rstrip('\n, '))
            return text

    def embrace(self, decl_table, lut_table):
        tab = "    "
        indent = tab * 2
        decl_table = indent + decl_table # hack to get the first line with indent
        decl = indent.join(line for line in decl_table.splitlines(True))
        indent = tab * 3
        lut_table = indent + lut_table # hack to get the first line with indent
        lut = indent.join(line for line in lut_table.splitlines(True))
        text = """
namespace pow{radix}_helper
{{
    /* max exponent must be less than max_exponent() */
    constexpr std::size_t upper_bound() {{ return {N}; }}

    static inline const double call(unsigned dim) {{

{decl}
        static const double exponents[/* {N} */] = {{
{table}
        }};
        assert(dim < sizeof(exponents)/sizeof(double) && "exponent out of range (condition < {N})");
        return exponents[dim];
    }}
}}
""".format(N=self.N, radix=self.radix, decl=decl, table=lut)
        return text

    def format(self, pow_list, border_width=65):
        # textwraps isn't a solution here since it breaks at spaces
        text = ""
        # determine the numer of elements on one line without excededing line width
        for width_cnt, val in enumerate(reversed(pow_list)):
            text += val
            if len(text) > border_width:
                #print("|" + text + "|")
                break
        # now join the list into LUT
        text = ""
        for idx, val in enumerate(pow_list):
            #text += val + "\t/* {idx} */\n".format(idx=idx)
            text += val
            if not (idx+1) % width_cnt: text += '\n'

        return text

    def decimal_radix(self):
        step = 1
        idx = range(0, self.N, step)
        pow_list = []
        for n in idx:
            pow_list.append(
                "1e{0:<3}, ".format(n)
            )
        return pow_list

    def make_constexpr_name(self, n):
        width_predef = {
            2   :   4,
            8   :   4,
            16  :   3
        }
        width = width_predef.get(self.radix)
        return "pow2_{n:0{w}}".format(n=n, w=width)
        #return "pow2_{n:<3}".format(n=n)

    def make_constexpr(self, n):
        name = self.make_constexpr_name(n)
        if n < self.bit_stride[-1] + 1:
            return "constexpr double {name} = (1uLL << {n:>3});".format(name=name, n=n)
        else:
            stride_max = self.bit_stride[-1]
            lhs_name = self.make_constexpr_name(n - stride_max)
            rhs_name = self.make_constexpr_name(stride_max)
            return "constexpr double {name} = {lhs_name} * {rhs_name};".format(
                name=name, lhs_name=lhs_name, rhs_name=rhs_name)

    def binary_radix(self):
        # unsigned long long can only be shifted to less than 64 bit

        bit_stride = cycle(self.bit_stride)
        stride_max = self.bit_stride[-1]
        pow_constexpr = []
        pow_k_constexpr = []
        pow_list = []
        exp_k = self.bit_stride[-1]

        stride_is_zero = False;
        k = 0
        for exp_n in range(0, self.N):
            stride = next(bit_stride)
            step = self.step
            if exp_n > 1 and stride == 0: # skip stride=0 at bitshift higher 64
                stride_is_zero = True;
                stride = next(bit_stride)
            else:
                stride_is_zero = False;

            # generate constexpr for less than 64 bit
            if exp_n < 64 / step:
                constexpr = self.make_constexpr(stride)
                pow_constexpr.append(constexpr)

            # special case for base**0
            if exp_n == 0:
                constexpr_name = self.make_constexpr_name(stride)
                pow_list.append("{expr}, ".format(expr=constexpr_name))
                continue

            # common case for base**n where n < 64
            if exp_n < 64 / step:
                constexpr_name = self.make_constexpr_name(stride)
                pow_list.append("{expr}, ".format(expr=constexpr_name))
                continue

            # higher 64 bit
            #k = int(exp_n * step / (stride_max + 1))
            if stride_is_zero:
                k = k + 1
            exp_k = k * stride_max
            #else:
            #    exp_k = (k + 0) * stride_max
            pow_k_constexpr.append(self.make_constexpr(exp_k)) # nevertheless added
            lhs_name = self.make_constexpr_name(exp_k)
            rhs_name = self.make_constexpr_name(stride)
            pow_list.append("{lhs} * {rhs}, ".format(lhs=lhs_name, rhs=rhs_name))

        # cleanup duplicated from constexpr list
        pow_constexpr = pow_constexpr + pow_k_constexpr
        pow_constexpr = sorted(set(pow_constexpr))

        return [pow_constexpr, pow_list]

class CXX_Driver:
    def __init__(self):
        self.cxx_main = """
#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

{0}

int main() {{

{1}

    return 0;
}}
"""

    def cxx_test_driver(self, radix):
        loop = """
    for(unsigned n = 0; n != pow{radix}_helper::upper_bound(); ++n) {{
        std::cout <<  n << ": "
            << std::pow({radix}, n) << " - " << pow{radix}_helper::call(n)
            << " = "
            << ( std::pow({radix}, n) - pow{radix}_helper::call(n))
            << "\\n";
    }}
""".format(radix=radix)
        return loop

    def gen(self):
        body = ""
        decl = "/* test driver */"
        N = [2, 8, 10, 16]
        #N=[10]
        for radix in N:
            pow_gen = pow_LUT(radix)
            decl += pow_gen.get()
            body += self.cxx_test_driver(radix)
        text = self.cxx_main.format(decl, body)
        return text

if __name__ == "__main__":
    drv = CXX_Driver();
    print(drv.gen())

################################################################################
"""
// doesn't compile with real types in templates:
// 'double' is not a valid type for a template non-type parameter
// The ISO C++ standard forbit this
#include <iostream>

constexpr double ipow(double base, unsigned exp, double result = 1)
{
    return exp < 1 ? result : ipow(base*base, exp/2, (exp % 2) ? result*base : result);
}

template < typename T, T base, unsigned exponent >
using pow_ = std::integral_constant < T, ipow(base, exponent) >;


int main()
{
    constexpr double pow_16_3 = pow_<double, 16, 3>::value;
    std::cout << ipow(16, 0) << "\n";
    std::cout << ipow(16, 1) << "\n";
    std::cout << ipow(16, 2) << "\n";
    std::cout <<  pow_16_3 << "\n";
}

"""
################################################################################
"""
#include <type_traits>

template <unsigned int N, std::enable_if_t<N == 2>* = nullptr>
double pow(unsigned n) {
    return pow2_helper::call(n);
}

template <unsigned int N, typename std::enable_if<N == 8>::type* = nullptr>
double pow(unsigned n) {
   return pow8_helper::call(n);
}


template <unsigned int N, typename std::enable_if<N == 16>::type* = nullptr>
double pow(unsigned n) {
   return pow16_helper::call(n);
}


follow:
https://stackoverflow.com/questions/30440483/execute-different-functions-depending-on-template-parameter-disequation

"""