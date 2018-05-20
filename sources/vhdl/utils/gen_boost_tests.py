#!/usr/bin/env python3

import os, errno
from pathlib import Path

import datetime
now = datetime.datetime.now()


class BoostTestGenerator:
    """
    Quick & Dirty python script to generate C++ skelets for Boost.Test
    based on the directories given below 'test_case' to test the VHDL
    parser grammar.
    
    Over the time there where changes on the macros used to generate
    the stuff, rewriting by hand isn't suitable. 
    """
    path = None

    def __init__(self, root_name):
        self.root_name = root_name
        self.path = os.path.dirname(os.path.realpath(__file__))
        
    
    def isFailuretest(self, name):
        """Check if there is a '_failure' into given name.
        
        This identifies a parser fail test. If True, it returns the clean 
        ('_failure' pruned) name, otherwise the given name.
        """
        
        if '_failure' in name:
            return [True, name[:-8]]
        else:
            return [False, name]
        
        
    def getTestCases(self):
        """Iterate over the path to gather test test_cases
        
        We assume the relative path to the test_case directory to this script
        """
        
        path = os.path.join(self.path, '..', 'test', 'test_case')
        print('Search for test case in %s' % path)
        
        test_cases = []
        
        for dirname, dirnames, filenames in os.walk(path):
            for subdirname in dirnames:
                test_cases.append(subdirname)
        return test_cases
        
        
    def cxxHeader(self, filename):
        """Create a common C++ header
        
        the \arg filename is used for the filename title documented into the
        header.
        """
        
        return """
/*
 * {file}
 *
 *  Created on: {d}.{m}.{y}
 *      Author: olaf
 */
""".format(
        file=filename, 
        d=now.day,
        m=now.month, 
        y=now.year
    )

    def cxxIncludes(self):
        """Generate the headers required to compile.
        
        """
        return """
#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser_def.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"
#include "testing_util.hpp"
"""
        
    def cxxNamespaceAliases(self):
        return """
namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;"""
        
        
    def cxxDataSetLoader(self, name):
        return """
struct {name}_dataset : public ::x3_test::dataset_loader
{{
    {name}_dataset()
    : dataset_loader{{ "test_case/{name}" }}
    {{ }}
}} const {name}_dataset;
""".format(name=name)
        
        
    def cxxDataTestCase(self, test_name, name):
        test_case = test_name
        attribute_name=name
        parser_name=name
        [failure_test, _] = self.isFailuretest(test_name)
       
        return """
BOOST_DATA_TEST_CASE( {test_case},
      {test_case}_dataset.input()
    ^ {test_case}_dataset.expect()
    ^ {test_case}_dataset.test_case_name(),
    input, expected, test_case_name)
{{
    using attribute_type = ast::{attr_name};
    auto const parser = parser::{parser_name};

    boost::ignore_unused(test_case_name);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser);

    BOOST_TEST({F}parse_ok);
    BOOST_REQUIRE_MESSAGE({F}parse_ok,
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
        x3_test::report_diagnostic(test_case_name, input, parse_result)
    );
}}
""".format(
        test_case=test_case,
        attr_name=attribute_name,
        parser_name=parser_name,
        F='!' if failure_test else ''
    )

    
    def writeFile(self, path, filename, dataset_loader, datatest_case, testsuite_name='parser'):
        contents="""{header}
{includes}

BOOST_AUTO_TEST_SUITE( {testsuite_name} )

{namespace_alias}


{dataset_loader}


{datatest_case}

BOOST_AUTO_TEST_SUITE_END()

""".format(
    header=self.cxxHeader(filename)[1:],
    includes=self.cxxIncludes(),
    testsuite_name=testsuite_name,
    namespace_alias=self.cxxNamespaceAliases(),
    dataset_loader='\n'.join(dataset_loader),
    datatest_case='\n'.join(datatest_case)
)

        pathname=os.path.join(path, filename)
        
        if not os.path.exists(os.path.dirname(pathname)):
            try:
                os.makedirs(os.path.dirname(pathname))
            except OSError as exc: # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise

        with open(pathname, "w") as f:
            f.write(contents)
        
        
    
    def generate(self, path):
        test_cases = sorted(self.getTestCases())
        cmake_sources=list()
        
        # generate the files required
        for test in test_cases:
            [failure_test, _] = self.isFailuretest(test)
            
            if failure_test:
                continue

            dataset_loader = list()
            datatest_case  = list()

            dataset_loader.append(self.cxxDataSetLoader(test))
            datatest_case.append( self.cxxDataTestCase(test, test))
            
            test_failure = test + '_failure'
            if test_failure in test_cases:
                dataset_loader.append(self.cxxDataSetLoader(test_failure))
                datatest_case.append(self.cxxDataTestCase(test_failure, test))
                
            test_filename = test + '_parsertest.cpp'

            self.writeFile(path, test_filename, dataset_loader, datatest_case) 
        
            cmake_sources.append("{cxx}".format(
                    cxx=path + '/' + test_filename))
                    
        for src in cmake_sources:
            print(src)
                                        
                    
if __name__ == "__main__":
    generator = BoostTestGenerator('');
    generator.generate('parser_test')
