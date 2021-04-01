#!/usr/bin/env python3


"""
Quick&Dirty script to gather the test case data and render them as Markdown
and reStructuredText for Doxygen.
"""


import os, sys
from pathlib import Path
import argparse
import logging

# [tabulate](https://pypi.org/project/tabulate/)
from tabulate import tabulate


class TestCaseFile_Object:
    """Object which collects all file data which belongs to single test case

    """
    def __init__(self, active = True):
        self._active = active

    @property
    def active(self):
        return self._active

    @property
    def fileName(self):
        return self._fname

    @fileName.setter
    def fileName(self, fname: str):
        self._fname = fname

    @property
    def input(self):
        return self._input

    @input.setter
    def input(self, contents: str):
        self._input = contents

    @property
    def expected(self):
        return self._expected

    @expected.setter
    def expected(self, contents: str):
        self._expected = contents


class TestCaseGroup_Iterator:
    """Iterator class

    """
    def __init__(self, group):
        self._group = group
        # member variable to keep track of current index
        self._index = 0

    def __next__(self):
        """Returns the next value from team object's lists"""
        if self._index < len(self._group._entry):
            result = self._group._entry[self._index]
            self._index +=1
            return result
        # End of Iteration
        raise StopIteration


class TestCaseGroup_Object:
    """Grouping object for test case files

    """
    def __init__(self, rule_name = 'Unspecified TestCase'):
        self._name = rule_name
        self._entry = list()

    def __iter__(self):
       """Returns the Iterator object"""
       return TestCaseGroup_Iterator(self)

    def add(self, test_case : TestCaseFile_Object):
        self._entry.append(test_case)

    @property
    def name(self):
        return self._name


def mkLabel(base_id):
    """Generate a lable as header attribute for Markdown and Rst

    see [https://www.doxygen.nl/manual/markdown.html#markdown_extra](
            https://www.doxygen.nl/manual/markdown.html)
    """
    return "{{#testcase_{id}}}".format(id=base_id)


class TableMaker:
    """
    A simple table generator

    """
    def __init__(self):
        self._tablefmt = "grid"
        self._adornment = {
            1 : '=',    # title, chapter
            2 : '-',    # title, section
            3 : '~'     # subtitle, subsection
        }



    def title_header(self, title, depth = 1):
        adornment = self._adornment.get(depth, '')
        width = len(title)
        text="\n{ruler}\n{title:<{w}} {label}\n{ruler}\n".format(
            ruler=adornment*width,
            title=title,
            w=width,
            label=mkLabel(title)
        )
        return text

    def data(self, test_case_group : TestCaseGroup_Object):

        data = list()

        title = self.title_header(test_case_group.name, 1)

        for test_case in test_case_group:
            filename = test_case.fileName
            if not test_case.active:
                filename = filename + '\n(deactivated)'
            data.append([
                filename,
                test_case.input,
                test_case.expected
            ])

        headers = ['filename', 'input', 'expected']
        tbl = tabulate(data, headers, self._tablefmt)

        contents = title + '\n' + tbl
        return contents


class TestMatrixGenerator:

    def __init__(self, args):
        self.testcase_path = args.input_dir
        self._output_path = args.output_dir

    def read_content(self, file_pathname):
        """Read the file contents

        :arg file_pathname: The input file to be read
        :return: The contents of the file on success, an empty str on failure
        :rtype: str
        """
        try:
            with open(file_pathname) as f:
                content = f.read()
                return content
        except Exception as e:
            #logging.exception("read_content() message")
            return str()

    def getTestCases(self):
        """Iterate over the input path to gather test_cases.

        :return list: List of TestCase_Object gathered from directory listing.

        It is assumed that the directory structure is:
        input_dir + test_case_a
                  + test_case_b
                  :
                  + test_case_n

        where each 'test_case' address a grammar rule and contains the real test data
        below this directory.

        FixMe: Group all test case, even failure test cases!
        """

        print('Search for test cases in %s' % self.testcase_path)

        test_cases_dirlist = list()

        # iterate over directory structure to gather the test cases
        for dirname, dirnames, filenames in os.walk(self.testcase_path):
            for subdirname in dirnames:
                test_cases_dirlist.append(subdirname)

        #print('=> found: ', end=''); print(*sorted(test_cases_dirlist))

        test_case_list = list()

        # iterate over sorted test case data top level dir
        for test_case in sorted(test_cases_dirlist):

            # and pickup the concrete test input/expected file contents
            test_case_path = os.path.join(self.testcase_path, test_case)

            # The test case top level directory / group
            test_case_groupobj = TestCaseGroup_Object(test_case)

            for dirname, dirnames, test_case_files in os.walk(test_case_path):

                #print('test_case <{}> with data files: {}'.format(test_case, test_case_files))

                # lookup the files of concrete test case below test_data's directory
                for test_case_fname in test_case_files:

                    test_case_filepath = os.path.join(self.testcase_path, test_case, test_case_fname)
                    basename = Path(test_case_filepath).stem

                    if False: # debug
                        print('process test_case_filepath: {}, test_case_file: {}, basename: {}'.format(
                            test_case_filepath,
                            test_case_fname,
                            basename
                        ))

                    # check on disabled test case
                    if basename.endswith('.input'):
                        #print('read disabled input: {}'.format(test_case_filepath))
                        input = self.read_content(test_case_filepath)
                        # anyway check if there is a expected file
                        expected_filename = os.path.join(
                            self.testcase_path, test_case, Path(basename).stem + '.expected'
                        )
                        #print('read expected: {}'.format(expected_filename))
                        expected = self.read_content(expected_filename)

                        # Fill the file object for test case ...
                        test_case_obj = TestCaseFile_Object()
                        test_case_obj.fileName = test_case_fname
                        test_case_obj.input = input
                        test_case_obj.expected = expected
                        # ... and add it to the group it belongs to
                        test_case_groupobj.add(test_case_obj)

                        continue

                    # read regular input test case
                    if test_case_filepath.endswith('.input'):
                        # regular test case input
                        #print('read disabled input: {}'.format(test_case_filepath))
                        input = self.read_content(test_case_filepath)
                        expected_filename = os.path.join(
                            self.testcase_path, test_case, basename + '.expected'
                        )
                        #print('read expected: {}'.format(expected_filename))
                        expected = self.read_content(expected_filename)

                        # Fill the file object for test case ...
                        test_case_obj = TestCaseFile_Object()
                        test_case_obj.fileName = test_case_fname
                        test_case_obj.input = input
                        test_case_obj.expected = expected
                        # ... and add it to the group it belongs to
                        test_case_groupobj.add(test_case_obj)

                        continue

                    # other stuff is '*.expected' or other files

            test_case_list.append(test_case_groupobj)

        return test_case_list


    def generate(self, file_ext = '.md'):
        """Generate the test case

        """
        table = TableMaker()
        toc_entry = list()

        # iterate over all test cases
        for test_case_group in self.getTestCases():

            name = test_case_group.name
            tab = table.data(test_case_group)

            fname = os.path.join(self._output_path, name + file_ext)
            self.writeTableFile(fname, tab)
            toc_entry.append(name)

        # FixMe: This path is hard coded!
        for test_case in toc_entry:
            print('- [{entry}]({test_case_md})'.format(
                entry=test_case,
                test_case_md='parser_test_data/' + test_case + '.md',
                label=mkLabel(test_case)
            ))


    def writeTableFile(self, filepath_name, contents):
        """
        Write the test case file.

        :param str filepath_name: The full file path be written into.
        :param contents: The contens of the file.
        """

        if not os.path.exists(os.path.dirname(filepath_name)):
            try:
                os.makedirs(os.path.dirname(filepath_name))
            except OSError as exc: # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise

        with open(filepath_name, "w") as f:
            f.write(contents)



if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Generate Testsuite test files matrix.')
    parser.add_argument('--input-dir', '-I',
        dest='input_dir',
        default=os.path.join(os.getcwd(), 'test_case'),
        help='top level input directory of test case files, separated in subdirectories for each grammar rule.')
    parser.add_argument('--output-dir', '-O',
        dest='output_dir',
        default='parser_test_data',
        help='output directory where the resulting files are written into.')
    args = parser.parse_args()
    #print('input: ' + args.input_dir)
    #print('output: ' + args.output_dir)
    table = TestMatrixGenerator(args)
    table.generate()
