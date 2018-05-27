#!/usr/bin/env python3

import os, sys
import re


class TestCaseEnumerationFixer:
    """Quick & Dirty python script to fix the enumeration of test_case files used.
    
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
        """Return the integer value of the strring \a name
        """
          
        number=re.findall(self.int_pattern, name)
        if len(number) > 1:
            print('WARNING: found more than 1 integer in ' + str(name))
        if len(number): return int(number[0])
        else:           return None
        
        
    def prepend(self, root, filename, contents, dry_run):
        """Add additional contents on top of the given file.
        
        This is useful to get clear diagnostic using Boost.Test
        """
        n=self.get_integer(filename)
        if not n: return # not a test case file by convention
        print(filename + ' <= ' + contents)
        if not dry_run:
            with open(os.path.join(root, filename), 'r') as original:
                 data = original.read()
            with open(os.path.join(root, filename), 'w') as modified:
                 modified.write(contents + '\n' + data)


    def rename(self, root, origin, dry_run):
        """Rename the origin name to the new enumeration scheme
        
        If there is no integer in the file name encoding, the file is skipped. 
        This is for common files, e.g. readme.txt
        """
        
        n=self.get_integer(origin)
        if not n: return # not a test case file by convention
        assert n > 0     # multiple runs? Prevent negative file numbers
        src=os.path.join(root, origin)
        ## FIXME: use format string, e.g. '{num:03d}'.format(num=i) here,
        ##        otherwise you get a 'wide' problem on width changes in the
        ##        file name, e.g. file_010 => file_09 !
        ##        Actually 3 cases are concerned, fix by hand.
        dst=os.path.join(root, origin.replace(str(n), str(n-1)))
        if os.name == 'nt':
            print('ren ' + src + ' ' + dst)
        elif os.name == 'posix':
            print('mv ' + src + ' ' + dst)
        else:
            print('# rename ' + src + ' => ' + dst)
        if not dry_run:
            os.rename(src, dst)


    def iterate_dir(self, prefix_path, dry_run):
        """Iterate of the given path and renames the approbiate test case
        files.
        """
        
        prepend_txt="-- VHDL test case input code --"
        
        # walk before renaming
        dir_walk=sorted(os.walk(prefix_path + '/' + 'test_case'))
        
        for root, dirs, files in dir_walk:
            #print("root=" + str(root) + ", dirs=" + str(dirs) + ", files=" + str(files))
            for origin in files:
#                 if origin.endswith('.input'):
#                     self.prepend(root, origin, prepend_txt, dry_run)
                self.rename(root, origin, dry_run)
                        
    
    def fix(self, dry_run=False):
        self.iterate_dir(self.testcase_path, dry_run)



if __name__ == "__main__":
    util = TestCaseEnumerationFixer()
    util.fix()

    