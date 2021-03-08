#!/usr/bin/env python3

import sys, re

def copy(file):
    for line in file:
        print(line.rstrip())

def isComment(line):
    comment_re = r'.*(//.*?|/\*.*)'
    return re.match(comment_re, line, flags=re.S)

def filter(file):
    fixme_re = r'(FIXME)(:)?'
    for line in file:
        if isComment(line):
            #print('# ' + line)
            x = re.sub(fixme_re, r'@todo (\\b FixMe)', line, flags=re.IGNORECASE)
            print(x.rstrip())
        else:
            print(line.rstrip())

if __name__ == "__main__":
    with open(sys.argv[1], 'r') as file:
        filter(file)
        #copy(file)
