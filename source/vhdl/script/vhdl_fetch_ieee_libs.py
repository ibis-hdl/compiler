#!/usr/bin/env python3
#
# Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
# SPDX-License-Identifier: GPL-3.0-or-later
#

"""
Fetch VHDL libraries
"""
import urllib.request


class VhdlLib:
    """
    Class for fetching misc. VHDL libraries.
    """
    # IEEE-SA Supplemental Material
    ieee_url = 'https://standards.ieee.org/downloads/1076/1076.2-1996'
    ieee_libs = [
        'math_complex-body.vhdl',
        'math_complex.vhdl',
        'math_real-body.vhdl',
        'math_real.vhdl',
        'numeric_bit-body.vhdl',
        'numeric_bit.vhdl',
        'numeric_std-body.vhdl',
        'numeric_std.vhdl',
        'std_logic_1164-body.vhdl',
        'std_logic_1164.vhdl'
    ]
    vital2k_url = "http://svn.gna.org/svn/ghdl/trunk/libraries/vital2000"
    vital2k_libs = [
        'timing_p.vhdl',
        'timing_b.vhdl',
        'prmtvs_p.vhdl',
        'prmtvs_b.vhdl',
        'memory_p.vhdl',
        'memory_b.vhdl',
    ]

    def fetch_ieee(self):
        """Fetch IEEE libraries"""
        for lib in self.ieee_libs:
            url = "".join(self.ieee_url + '/' + lib)
            print('fetch IEEE lib ' + lib)
            urllib.request.urlretrieve(url, lib)

    def fetch_vital2k(self):
        """"Fetcj VITAL libraries"""
        for lib in self.vital2k_libs:
            url = "".join(self.vital2k_url + '/' + lib)
            print('fetch IEEE Vital 2000 lib ' + lib)
            urllib.request.urlretrieve(url, lib)


if __name__ == '__main__':
    vhdl = VhdlLib()
    vhdl.fetch_ieee()
    vhdl.fetch_vital2k()
