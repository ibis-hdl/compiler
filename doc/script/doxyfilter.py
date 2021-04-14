#!/usr/bin/env python3
import sys, os, re


def doxy_filter(contents: str, verbose: bool):
    """
    Replace all ToDo, FixMe comments into Doxygen's '@todo' format.

    Note that the todo items have to be part of the documentation of something,
    comments within the code are ignored!
    See [doxygen todo list is losing/missing some todo comments](
    https://stackoverflow.com/questions/11458423/doxygen-todo-list-is-losing-missing-some-todo-comments)
    """
    for line in contents:
        # [@|\\]?(todo|fixme):?
        fixme_re = r'(@|\\)?fixme:?'
        todo_re  = r'(@|\\)?todo:?'
        line = re.sub(fixme_re, r'@todo (\\b FixMe)', line, flags=re.IGNORECASE)
        line = re.sub(todo_re,  r'@todo', line, flags=re.IGNORECASE)
        print(line.rstrip())


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
                print("-> {py_name}: filter('{filename}')".format(
                    py_name=os.path.basename(__file__),
                    filename=file),
                    file=sys.stderr
                )
            with open(file, 'r') as f:
                doxy_filter(f, verbose)
        except OSError as e:
            print("ERROR: unable to open File '{filename}': {err_str} (errno={err_no})".format(
                filename=e.filename,
                err_str=e.strerror,
                err_no=e.errno),
                file=sys.stderr
            )


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("{bin}\nUsage: {py_name} input_file".format(
            bin=sys.argv[0],
            py_name=os.path.basename(__file__)),
            file=sys.stderr
        )
    else:
        main(sys.argv[1], False)

