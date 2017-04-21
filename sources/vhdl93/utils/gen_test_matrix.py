#!/usr/bin/env python3

import os
from prettytable import PrettyTable
import prettytable


class RstMaker:
    '''A simple StructuredText generator'''
    adornment = {
        1 : '=',    # title, chapter
        2 : '-',    # title, section
        3 : '~'     # subtitle, subsection
    }

    def title_header(self, title, depth = 1):
        adornment = self.adornment.get(depth, '')
        width=len(title)
        text='''\n{0}\n{1:<{2}}\n{0}\n'''.format(adornment*width, title, width)
        return text

    def section_header(self, header, depth = 1):
        adornment = self.adornment.get(depth, '')
        width=len(header)
        text='''\n{0:<{1}}\n{2}\n'''.format(header, width, adornment*width)
        return text
    
    def simple_table(self, header_list, subject_list):
        tbl = PrettyTable(header_list)
        for row in subject_list:
            tbl.add_row(row)
        tbl.align="l"
        tbl.hrules=prettytable.ALL
        print(tbl)


class TestMatrixGenerator:
    rst = RstMaker()

    def contents(self):
        for root, dirs, files in sorted(os.walk('test_case')):
            #print("root=" + str(root) + ", dirs=" + str(dirs) + ", files=" + str(files))
            if files and not dirs:
                subject_list = []
                subject = os.path.basename(root)
                for file in files:
                    (base, ext) = os.path.splitext(file)
                    if ext == '.input':
                        input    = self.read_content(os.path.join(root, base + '.input'))
                        expected = self.read_content(os.path.join(root, base + '.expected'))
                        test_case = (base, input, expected)
                        subject_list.append(test_case)

                print(self.rst.title_header(subject, 1))
                headers = ("File", "Input", "Expected")
                self.rst.simple_table(headers, subject_list)


    def read_content(self, file):
        fd = open(file, "r")
        content = fd.read()
        return content


if __name__ == "__main__":
    table = TestMatrixGenerator()
    table.contents()
