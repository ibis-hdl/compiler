#!/usr/bin/env python3

import os, sys
import re


class TestCaseEnumerationFixer:
    """Fix the enumeration of test_case files used.
    
    Boost.Test data driven tests enumerate the tests starting with index 0,
    where the files used here starts with 1. This make its difficult to determine
    the correct file input which rises the TEST error.
    This script fixes the enumeration of the test case files;
    the test case number embedded into the filename equals to the Boost.Test
    dataset driven test number scheme than.
    
    e.g. rename:
    my_test_003.{input, expected, ...} => my_test_002.{input, expected, ...}
    
    Usage:
    python sources/vhdl/utils/fix_test_case_enumeration.py sources/vhdl/test
    """ 
    
    def __init__(self):
        self.testcase_path = sys.argv[1]
        self.int_pattern=re.compile(r'\d\d\d')
        
    
    def get_integer(self, name):
        number=re.findall(self.int_pattern, name)
        if len(number) > 1:
            print('WARNING: found more than 1 integer in ' + str(name))
        if len(number): return int(number[0])
        else:           return None
        
    
    def iterate_dir(self, prefix_path):
        for root, dirs, files in sorted(os.walk(prefix_path + '/' + 'test_case')):
            #print("root=" + str(root) + ", dirs=" + str(dirs) + ", files=" + str(files))
            for origin in files:
                n=self.get_integer(origin)
                if not n: continue
                assert n > 0 # multiple runs? Prevent negative file numbers
                new_name=origin.replace(str(n), str(n-1))
                print(origin + ' => ' + new_name)
                os.rename(
                    os.path.join(root, origin),
                    os.path.join(root, new_name)
                )
                        
    
    def fix(self):
        self.iterate_dir(self.testcase_path)

if __name__ == "__main__":
    util = TestCaseEnumerationFixer()
    util.fix()
    #n=util.get_integer('foo_.bar')
    #print(n)
    