#!/usr/bin/env python3


"""
Quick&Dirty script to gather the test case data and render them as Markdown
and reStructuredText for Doxygen/Sphinx.
"""


import os
import errno
from pathlib import Path
import argparse
import logging

from tabulate import tabulate

logger = logging.getLogger(os.path.basename(__file__))

# [tabulate](https://pypi.org/project/tabulate/)
tabulate.PRESERVE_WHITESPACE = True


class TestCaseFile_Object:
    """
    Object which collects all file data which belongs to single test case
    """

    def __init__(self, active=True):
        self._active = active

    @property
    def active(self):
        """Test cases can be set active or even not"""
        return self._active

    @property
    def file_name(self):
        """File name of test case"""
        return self._fname

    @file_name.setter
    def file_name(self, fname: str):
        self._fname = fname

    @property
    def input(self):
        """Test case contents, act as test input"""
        return self._input

    @input.setter
    def input(self, contents: str):
        self._input = contents

    @property
    def expected(self):
        """Test case expected result contents (gold data)"""
        return self._expected

    @expected.setter
    def expected(self, contents: str):
        self._expected = contents


class TestCaseGroup_Iterator:
    """
    Iterator class
    """

    def __init__(self, group):
        self._group = group
        # member variable to keep track of current index
        self._index = 0

    def __next__(self):
        """Returns the next value from team object's lists"""
        if self._index < len(self._group._entry):
            result = self._group._entry[self._index]
            self._index += 1
            return result
        # End of Iteration
        raise StopIteration


class TestCaseGroup_Object:
    """
    Grouping object for test case files
    """

    def __init__(self, rule_name='Unspecified TestCase'):
        self._name = rule_name
        self._entry = []  # empty list

    def __iter__(self):
        """Returns the Iterator object"""
        return TestCaseGroup_Iterator(self)

    def add(self, test_case: TestCaseFile_Object):
        """Add a test case object to the group"""
        self._entry.append(test_case)

    @property
    def name(self):
        """The name of the test case group"""
        return self._name


def make_label(base_id):
    """
    Generate a label as header attribute for Markdown and Rst

    :return: Label string in form of '{#label_id}'
    see [https://www.doxygen.nl/manual/markdown.html#markdown_extra](
            https://www.doxygen.nl/manual/markdown.html)
    """
    return f"{{#testcase_{base_id}}}"


class Tablemaker:
    """
    A simple table generator

    """

    def __init__(self, tablefmt):
        # see [tabulate](https://pypi.org/project/tabulate/) for table format
        self._tablefmt = tablefmt

    def data(self, test_case_group: TestCaseGroup_Object):
        """Transform test cases in the group into tabular form"""
        data = []  # empty list

        for test_case in test_case_group:
            filename = test_case.file_name
            if not test_case.active:
                filename = filename + '\n(deactivated)'
            data.append([
                filename,
                test_case.input,
                test_case.expected
            ])

        tbl = tabulate(data,
                       ['filename', 'input', 'expected'], colalign=("left", "left", "left"),
                       tablefmt=self._tablefmt,
                       disable_numparse=True
                       )

        return tbl


class TestMatrixGenerator:
    """
    The Class for generating Test Case matrix
    """

    def __init__(self, args):
        self.testcase_path = args.input_dir
        self._output_path = args.output_dir
        self._dataset_page = args.dataset_page
        self._ext_dict = {
            'rst': '.rst',
            'html': '.html',
            'latex': '.tex',
            'latex_raw': '.tex',
            'latex_booktabs': '.tex'
        }
        self._adornment = {
            1: '=',    # title, chapter
            2: '-',    # title, section
            3: '~'     # subtitle, subsection
        }

    def get_file_ext(self, tablefmt: str):
        """
        Lookup the internal dictionary for file extensions according the
        table format.
        """
        return self._ext_dict.get(tablefmt, '.txt')

    def read_content(self, file_pathname):
        """
        Read the file contents

        :arg file_pathname: The input file to be read
        :return: The contents of the file on success, an empty str on failure
        :rtype: str
        """
        try:
            with open(file_pathname) as f:
                #content = escape(f.read())
                content = f.read()
                return content
        except IOError as ex:  # pylint: disable=unused-variable
            #logging.exception("read_content() message")
            return str()

    def get_test_cases(self):
        """
        Iterate over the input path to gather test_cases.

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

        logger.debug('Search for test cases in %s', self.testcase_path)

        test_cases_dirlist = []  # empty list

        # iterate over directory structure to gather the test cases
        for dirname, dirnames, filenames in os.walk(
                self.testcase_path):  # pylint: disable=unused-variable
            for subdirname in dirnames:
                test_cases_dirlist.append(subdirname)

        logger.debug('found: {}'.format(" ".join(sorted(test_cases_dirlist)))
                     )  # pylint: disable=consider-using-f-string,logging-format-interpolation

        test_case_list = []  # empty list

        # iterate over sorted test case data top level dir
        for test_case in sorted(test_cases_dirlist):

            # and pickup the concrete test input/expected file contents
            test_case_path = os.path.join(self.testcase_path, test_case)

            # The test case top level directory / group
            test_case_groupobj = TestCaseGroup_Object(test_case)

            for dirname, dirnames, test_case_files in os.walk(test_case_path):

                logger.debug('enter test_case <%s> with data files: %s',
                             test_case, test_case_files)

                # lookup the files of concrete test case below test_data's
                # directory
                for test_case_fname in test_case_files:

                    test_case_filepath = os.path.join(
                        self.testcase_path, test_case, test_case_fname)
                    basename = Path(test_case_filepath).stem

                    if False:  # debug
                        print('process test_case_filepath: {}, test_case_file: {}, basename: {}'.format(
                            test_case_filepath,
                            test_case_fname,
                            basename
                        ))

                    # check on disabled test case
                    if basename.endswith('.input'):
                        logger.debug(
                            'read disabled input: %s',
                            test_case_filepath)
                        input = self.read_content(test_case_filepath)
                        # anyway check if there is a expected file
                        expected_filename = os.path.join(
                            self.testcase_path, test_case, Path(
                                basename).stem + '.expected'
                        )
                        logger.debug('read expected: %s', expected_filename)
                        expected = self.read_content(expected_filename)

                        # Fill the file object for test case ...
                        test_case_obj = TestCaseFile_Object()
                        test_case_obj.file_name = test_case_fname
                        test_case_obj.input = input
                        test_case_obj.expected = expected
                        # ... and add it to the group it belongs to
                        test_case_groupobj.add(test_case_obj)

                        continue

                    # read regular input test case
                    if test_case_filepath.endswith('.input'):
                        # regular test case input
                        logger.debug(
                            'read disabled input: %s',
                            test_case_filepath)
                        input = self.read_content(test_case_filepath)
                        expected_filename = os.path.join(
                            self.testcase_path, test_case, basename + '.expected'
                        )
                        logger.debug('read expected: %s', expected_filename)
                        expected = self.read_content(expected_filename)

                        # Fill the file object for test case ...
                        test_case_obj = TestCaseFile_Object()
                        test_case_obj.file_name = test_case_fname
                        test_case_obj.input = input
                        test_case_obj.expected = expected
                        # ... and add it to the group it belongs to
                        test_case_groupobj.add(test_case_obj)

                        continue

                    # other stuff is '*.expected' or other files

            test_case_list.append(test_case_groupobj)

        return test_case_list

    def title_header(self, title, label='', depth=1):
        """
        Generate the page header
        """
        adornment = self._adornment.get(depth, '')
        width = len(title)
        text = "{ruler}\n{title:<{w}} {label}\n{ruler}\n".format(
            ruler=adornment * width,
            title=title,
            w=width,
            label=label
        )
        return text

    def create_test_page(self, title, table, fmt):
        """
        Generate the page self
        """
        if fmt in ['rst']:
            pg_contents = f"""{title}
.. code-block:: none

{''.join(f'    {line}' for line in table.splitlines(True))}
"""
        else:
            pg_contents = title + '\n' + table

        return pg_contents

    def create_toc_page(self, toc_entries, table_format: str):
        """
        Create the main page for Test Matrix

        FixMe: This paths, names, file extensions (.txt etc) are hard coded!
        """
        rst_like = ['rst']

        def rst_entry(test_case: str, path: str):
            return f"{path}/{test_case}"

        def dox_entry(test_case: str, path: str):
            file_ext = '.txt'
            return "- [{entry}]({test_case_pg})".format(
                entry=test_case,
                test_case_pg='../' + path + '/' + test_case + file_ext,
                label=make_label(test_case)
            )

        label = make_label('mainpage')
        if table_format in rst_like:
            label = ''

        title = self.title_header(
            'TestSuite VHDL Parser Grammar Rules', label, 1)

        entry_list = []  # empty list

        for test_case in toc_entries:
            if table_format in rst_like:
                line = rst_entry(test_case, 'parser_test_data')
            else:
                line = dox_entry(test_case, 'parser_test_data')
            entry_list.append(line)

        body = '\n'.join(f"   {line}" for line in entry_list)

        if table_format in rst_like:
            # rST page
            page = f"""{title}
.. toctree::

{body}
"""

        else:
            # Doxy page
            page = f"""{title}
[TOC]

{body}
"""
        return page

    def generate(self, table_format: str):
        """
        Generate the test case.

        FixMe: The table created for reStructuredText is generated verbatim to avoid
        'warnings: Definition list ends without a blank line; unexpected unindent'
        and other.
        """
        # Quick&Dirty fix for rST tables for better 'user experience'
        if table_format in ['rst']:
            table_format = 'grid'

        table = Tablemaker(table_format)
        toc_entry = []  # empty list
        file_ext = self.get_file_ext(table_format)

        # iterate over all test cases
        for test_case_group in self.get_test_cases():

            name = test_case_group.name
            title_label = ''
            title = self.title_header(test_case_group.name, title_label, 1)
            tab = table.data(test_case_group)

            pg_contents = self.create_test_page(title, tab, table_format)

            fname = os.path.join(self._output_path, name + file_ext)
            self.write_file(fname, pg_contents)
            toc_entry.append(name)

        # testsuite dataset main page
        pg_contents = self.create_toc_page(toc_entry, table_format)

        if self._dataset_page:
            #fname = os.path.join(self._output_path, self._dataset_page)
            fname = os.path.join(os.getcwd(), self._dataset_page)
            self.write_file(fname, pg_contents)
        else:
            print(pg_contents)

    def write_file(self, filepath_name, contents):
        """
        Write the test case file.

        :param str filepath_name: The full file path be written into.
        :param contents: The contens of the file.
        """

        if not os.path.exists(os.path.dirname(filepath_name)):
            try:
                os.makedirs(os.path.dirname(filepath_name))
            except OSError as ex:  # Guard against race condition
                if ex.errno != errno.EEXIST:
                    raise

        with open(filepath_name, "w") as f:
            f.write(contents)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Generate Testsuite test files matrix.')
    parser.add_argument('--verbose', '-v',
                        action='store_true',
                        help='print debug information.')
    parser.add_argument('--input-dir', '-i',
                        dest='input_dir',
                        default=os.path.join(os.getcwd(), 'test_case'),
                        help='top level input directory of test case files, separated in subdirectories for each grammar rule.')
    parser.add_argument('--output-dir', '-o',
                        dest='output_dir',
                        default='parser_test_data',
                        help='output directory where the resulting files are written into.')
    parser.add_argument('--format', '-f',
                        dest='tablefmt',
                        default='pretty',
                        help='''set output table format, format name must be given without hyphens; supported formats:
            plain, simple, github, grid, fancy_grid, pipe, orgtbl, rst, mediawiki, html, latex, latex_raw,
            latex_booktabs, latex_longtable, tsv (default: pretty)''')
    parser.add_argument('--dataset-page', '-p',
                        dest='dataset_page',
                        help='path/name to output page with references to the test cases, stored relative to current dir.')

    args = parser.parse_args()

    # [Logging setLevel is being ignored](
    #  https://stackoverflow.com/questions/43109355/logging-setlevel-is-being-ignored)
    handler = logging.StreamHandler()
    formatter = logging.Formatter('%(name)s(%(levelname)s): %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    if args.verbose:
        logger.setLevel(logging.DEBUG)

    table = TestMatrixGenerator(args)
    table.generate(args.tablefmt)
