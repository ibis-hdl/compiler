#!/usr/bin/env python3

import sys, re

def copy():
    for line in sys.stdin:
        print(line.rstrip())

def isComment(line):
    comment_re = r'.*(//.*?|/\*.*)'
    return re.match(comment_re, line, flags=re.S)

def filter():
    fixme_re = r'(FIXME)(:)?'
    # [How do you read from stdin?](
    #  https://stackoverflow.com/questions/1450393/how-do-you-read-from-stdin)
    for line in sys.stdin:
        if isComment(line):
            #print('# ' + line)
            x = re.sub(fixme_re, r'\\TODO FixMe', line, flags=re.IGNORECASE)
            print(x.rstrip())
        else:
            print(line.rstrip())


if __name__ == "__main__":
    #filter()
    copy()
