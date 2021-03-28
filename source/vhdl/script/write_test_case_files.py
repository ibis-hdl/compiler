#! /usr/bin/env python3
# coding: utf-8


# THIS SCRIPT EXISTS ONLY FOR ARCHIVING AND IS NO LONGER FUNCTIONAL THESE DAYS.


'''
primary ::=
    name
    | literal
    | ( expression )

factor ::=
    primary [ ** primary ]
    | ABS primary
    | NOT primary

term ::=
    factor { multiplying_operator factor }

simple_expression ::=
    [ sign ] term { adding_operator term }

shift_expression ::=
    simple_expression [ shift_operator simple_expression ]

relation ::=
    shift_expression [ relational_operator shift_expression ]

expression ::=
      relation { AND relation }
    | relation { OR relation }
    | relation { XOR relation }
    | relation [ NAND relation ]
    | relation [ NOR relation ]
    | relation { XNOR relation }
'''
test_cases = [
'"0011" and "0010" and "1000"',
'"0011" or  "0010" or  "1000"',
'"0011" xor "0010" xor "1000"',
'"0011" xnor "0010" xnor "1000"',

'"0011" nand "0010"',

'"0011" nor "0010"',

'"0011" <= "0010" and "1000"',
'"0011" and "0010" >= "1000"',

'"0011" SRL "0010" and "1000"',
'"0011" and "0010" SRL "1000"',

'"0011" <= "0010" + "1000"',

'"0011" * "0010" and "1000"',

'-42 and 48 or 4711',

'7**3 or 42',

'42 - 5*2',
'42 - (5*2)',
'42 + 10 - 2**3',
'(42)*(42) + ((12 + 12)*(12-12))',

# http://insights.sigasi.com/tech/be-careful-vhdl-operator-precedence.html
'-5 mod (-3)',
'-(5 mod (-3))',
'(-5) mod (-3)',
'-16 ** 2',
'-(16 ** 2)',
'(-16) ** 2',
]


test_cases_fail = [
'''-- not valid VHDL
"0011" nand "0010" nand "1000"''',

'''-- not valid VHDL
"0011" nor "0010" nor "1000"''',

'''-- not valid VHDL.
-5 mod -3'''
]

import os
from pathlib import Path

class TestInputFileGenerator:
    """
    Quick & Dirty python script to generate predefined test cases into the
    current directory for tests, namely {root_name}.input and
    {root_name}.expected.
    """
    counter = None
    root_name = None
    path = None

    def __init__(self, root_name):
        self.counter = 1
        self.root_name = root_name
        self.path = os.path.dirname(os.path.realpath(__file__))

    def next(self):
        self.counter = self.counter + 1

    def filename(self, basename, extension):
        name = "{0}_{1:03d}.{2}".format(
            basename,
            self.counter,
            extension)
        return name

    def filename_input(self, basename):
        return self.filename(basename, 'input')

    def filename_expected(self, basename):
        return self.filename(basename, 'expected')

    def write(self, filename, contents):
        filepath = Path(self.path).joinpath(Path(filename))
        if not filepath.parent.exists():
            filepath.parent.mkdir(parents=True)
        if filepath.exists():
            print('Skipping already existing file "' + str(filepath) + '"')
            return
        with filepath.open(mode="w") as f:
            print('Write test case data to ' + filepath.name)
            f.write(contents)

    def generate(self, test_cases):
        for test_case in test_cases:
            filename = self.filename_input(self.root_name)
            self.write(filename, test_case)
            filename = self.filename_expected(self.root_name)
            self.write(filename, '')
            self.next()

if __name__ == "__main__":
    gen_success = TestInputFileGenerator('test_case/expression');
    gen_success.generate(test_cases)

    gen_success = TestInputFileGenerator('test_case/expression_failure');
    gen_success.generate(test_cases_fail)










