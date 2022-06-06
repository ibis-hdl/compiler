#!/usr/bin/env python3
#
# Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
# SPDX-License-Identifier: GPL-3.0-only
#

"""
Filter for doxygen's Doxygen config file
"""

import sys
import os
import re


def doxy_filter(contents: str, filename: str):
    """
    Replace all ToDo, FixMe comments into Doxygen's '@todo' format.

    Note that the todo items have to be part of the documentation of something,
    comments within the code are ignored!
    See [doxygen todo list is losing/missing some todo comments](
    https://stackoverflow.com/questions/11458423/doxygen-todo-list-is-losing-missing-some-todo-comments)
    """
    for line_no, line in enumerate(contents):
        # [@|\\]?(todo|fixme):?
        fixme_re = r'(@|\\)?fixme:?'
        todo_re = r'(@|\\)?todo:?'
        line = re.sub(fixme_re, r'@todo (\\b FixMe)', line, flags=re.IGNORECASE)
        line = re.sub(todo_re, r'@todo', line, flags=re.IGNORECASE)
        try:
            # expect some codecs.charmap_encode errors (especially on Windows cp1252) by
            # copy & paste artifacts
            print(line.rstrip())
        except UnicodeEncodeError as ex:
            print("caught exception {e}\n  in {filename}:{n}".format( #pylint: disable=consider-using-f-string
                e=ex,
                filename=filename,
                n=line_no + 1),
                file=sys.stderr)


def main(file: str, verbose: bool = True):
    """
    Filter procedure for Doxygen. Intended to be used with Doxygen's INPUT_FILTER tag.

    Output is written to standard output stream.
    Error messages are written to standard error stream.
    """
    if file == '-':
        doxy_filter(sys.stdin, verbose)
    else:
        try:
            if verbose:
                print("-> {py_name}: filter('{filename}')".format( #pylint: disable=consider-using-f-string
                    py_name=os.path.basename(__file__),
                    filename=file),
                    file=sys.stderr
                )
            with open(file, 'r', encoding='utf-8') as file_contents:
                doxy_filter(file_contents, file)
        except OSError as ex:
            print("ERROR: unable to open File '{filename}': {err_str} (errno={err_no})".format( #pylint: disable=consider-using-f-string
                filename=ex.filename,
                err_str=ex.strerror,
                err_no=ex.errno),
                file=sys.stderr
            )


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("{bin}\nUsage: {py_name} input_file".format( #pylint: disable=consider-using-f-string
            bin=sys.argv[0],
            py_name=os.path.basename(__file__)),
            file=sys.stderr
        )
    else:
        main(sys.argv[1], False)
