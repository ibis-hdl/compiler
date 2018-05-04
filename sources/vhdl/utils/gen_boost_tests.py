#!/usr/bin/env python3

import os
from pathlib import Path

import datetime
now = datetime.datetime.now()


class BoostTestGenerator:
    """
    Quick & Dirty python script to generate C++ skelets for Boost.Test
    based on the directories given below 'test_case'.
    Over the time there where changes on the macros used to generate
    the stuff, rewrting by hand isn#t suitable. 
    """
    path = None

    def __init__(self, root_name):
        self.root_name = root_name
        self.path = os.path.dirname(os.path.realpath(__file__))
        
    
    def getTestCases(self):
        # we assume the relative path to the test_case directory to this script
        path = os.path.join(self.path, '..', 'test', 'test_case')
        print('Search for test case in %s' % path)
        
        test_cases = []
        
        for dirname, dirnames, filenames in os.walk(path):
            for subdirname in dirnames:
                test_cases.append(subdirname)
        return test_cases
        
    def cxxHeader(self, title):
        return """
/*
 * {file}.cpp
 *
 *  Created on: {d}.{m}.{y}
 *      Author: olaf
 */
""".format(file=title, d=now.day, m=now.month, y=now.year)

    def cxxIncludes(self):
        return """
#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include <eda/vhdl/ast.hpp>
#include "data_set.hpp"
#include "testing_parser.hpp"
#include "generate_data_test_case.hpp"        
"""
        
    def cxxNamespaceAliases(self):
        return """
namespace btt = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;
"""
        
    def cxxDataSetLoader(self, name):
        return """
struct {name}_dataset : public ::x3_test::dataset_loader
{{
    {name}_dataset()
    : {name}_dataset{{ "test_case/{name}" }}
    {{ }}
}} const {name}_dataset;
""".format(name=name)
        
    def cxxTestCase(self, name, macro=True):
        if macro:
            return """
GENERATE_DATASET_TEST_CASE({name})            
""".format(name=name)
        else:
            return """
{dataset}            
FIXME
""".format(dataset=self.cxxDataSetLoader(test))


    def generate(self):
        """User function to generate the test case c++ code skelet"""
        test_cases = self.getTestCases()
        for test in test_cases:
            cxx = """
{header}
{includes}
BOOST_AUTO_TEST_SUITE( {basename} )
{ns_alias}
{testcase}
BOOST_AUTO_TEST_SUITE_END()
""".format(
    basename=test,
    header=self.cxxHeader(test),
    includes=self.cxxIncludes(),
    ns_alias=self.cxxNamespaceAliases(),
    
    testcase=self.cxxTestCase(test, True)
)
            print(cxx)
        

                
                            
                    
if __name__ == "__main__":
    generator = BoostTestGenerator('');
    generator.generate()
