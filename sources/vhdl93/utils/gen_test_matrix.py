#!/usr/bin/env python

import os
from collections import namedtuple

class RstMaker:
    '''A simple StructuredText generator'''
    adornment = {
        1 : '=',    # title, chapter
        2 : '-',    # title, section
        3 : '~'     # subtitle, subsection
    }

    def title_header(self, title, depth = 1):
        adornment = ''
        for n in title:
            adornment += self.adornment.get(depth, '')
        text='''\n{0}\n{1}\n{0}\n'''.format(adornment, title)
        return text

    def section_header(self, header, depth = 1):
        adornment = ''
        for n in header:
            adornment += self.adornment.get(depth, '')
        text='''\n{0}\n{1}\n'''.format(header, adornment)
        return text

    def simple_table_header(self, header, length):
        adornment = ''
        for n in range(0, length):
            adornment += self.adornment.get(1, '')
        h = "{:^{width}}".format(header, width=length)
        text='''\n{0}\n{1}\n{0}\n'''.format(adornment, h)
        return text

    def simple_table_body(self, body, length):
        text = ''
        text += '''{0}\n'''.format(body)
        return text

    def simple_table_old(self, headers, col_list, col_selector):
        width0 = max(self.get_row_length(headers, col_list, 0))
        width1 = max(self.get_row_length(headers, col_list, 1))
        print(str(width0) + ' ' + str(width1))
        tbl  = self.simple_table_header(headers[0], width0)
        for tpl in col_list:
            tbl += self.simple_table_body(tpl[0], width0)
        print(tbl)


    def get_row_length(self, headers, col_list, index):
        width_header  = len(max(headers[index], key=len))
        width_content =  0
        for item in col_list:
            width_content = max(width_content, len(item[index]))
        return (width_header, width_content)

    def simple_table(self, headers, col_list, col_selector):
        print(len(headers), len(col_list), len(col_selector))
        if not max(col_selector) <= len(headers): raise AssertionError
        if not max(col_selector) <= len(col_list[col_selector[0]]): raise AssertionError
        index = col_selector[0]
        width0 = self.get_width(headers, col_list[index], index)
        print(width0)
        h = self.simple_table_header(headers[0], width0)
        print(h)

    def get_width(self, headers, col_list, index):
        hdr_max = len(headers[index])
        col_max = 0
        for n in col_list:
            #print("width of " + col_list[index])
            col_max = max(col_max, len(max(col_list[index], key=len)))
        width = max(hdr_max, col_max)
        #print(hdr_max, col_max)
        return width


    def get_column_width(self, col_list, idx):
        col_max = 0;
        for n in col_list:
            col_max = max(col_max, len(max(col_list[idx], key=len)))
        return col_max


class TestMatrixGenerator:
    rst = RstMaker()

    def bar(self):
        for root, dirs, files in sorted(os.walk('test')):
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
                self.rst.simple_table(headers, subject_list, (0,1))
                for test in subject_list:
                    print(test)

    def read_content(self, file):
        fd = open(file, "r")
        content = fd.read()
        return content


if __name__ == "__main__":
    gen = TestMatrixGenerator()
    gen.bar()
