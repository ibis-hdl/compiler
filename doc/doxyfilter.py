#!/usr/bin/env python3

import sys, re
from pathlib import Path

# unused, but it serves as a reminder:
# The intention was to speed up RE-ing the input from 
# doxygen since 'FixMe' strings shall only be replaced
# inside comments. Currently the problem is related
# to the C multi line comments used here, hence it's 
# unused.
def isComment(line):
    comment_re = r'.*(//.*?|/\*.*)'
    return re.match(comment_re, line, flags=re.S)

def doxy_fixes(lines):
    # [@|\\]?(todo|fixme):?
    fixme_re = r'(@|\\)?fixme:?'
    todo_re  = r'(@|\\)?todo:?'
    for line in lines:
        line = re.sub(fixme_re, r'@todo (\\b FixMe)', line, flags=re.IGNORECASE)
        line = re.sub(todo_re,  r'@todo', line, flags=re.IGNORECASE)
        print(line.rstrip())

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {} input_file".format(sys.argv[0]), file=sys.stderr)
    else:    
        try:
            lines = Path(sys.argv[1]).read_text().splitlines()
            doxy_fixes(lines)
        except FileNotFoundError as e:
            print("File {} Is not exist!".format(e.filename), file=sys.stderr)
