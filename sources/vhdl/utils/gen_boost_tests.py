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
    .
    Over the time there where changes on the macros used to generate
    the stuff, rewriting by hand isn't suitable. 
    
    ToDo:
        - embbed 'failure' test cases into the approbiate test self
        - 'failure' test case on same CMAKE line 
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
#include "testing_parser.hpp"
#include "testing_parser_grammar_hack.hpp"
#include "generate_data_test_case.hpp"
#include "testing_util.hpp"
"""
        
    def cxxNamespaceAliases(self, macro):
        """Namespace alias used. 
        
        If \arg macro=True they are not generated, otherwise they are.
        This is useful by use of the macros defined at header 
        <sources/vhdl/test/generate_data_test_case.hpp> where no namespace
        aliases are used/required. 
        """
        
        if macro:
            return ""
        else:
            return """
namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;"""
        
        
    def cxxDataSetLoader(self, name, macro):
        """Test file data set loader.
        
        Generate the required C++ code to load {input, expected} test vectors.
        The \arg name is required for the instance name and the test_case
        directory name.
        If \arg macro=True no extra C++ code for the dataset loader instance
        is generated since it's embedded into the macro defined at 
        <sources/vhdl/test/generate_data_test_case.hpp>.
        """
        
        if macro:
            return ""
        else:
            return """
struct {name}_dataset : public ::x3_test::dataset_loader
{{
    {name}_dataset()
    : dataset_loader{{ "test_case/{name}" }}
    {{ }}
}} const {name}_dataset;
""".format(name=name)
        
        
    def cxxTestCase(self, name, macro):
        """Generate the C++ code for the parser test self. 
        
        The \arg name is required for the instance name and the test_case used.
        If \arg macro=True the macro class is used defined at 
        <sources/vhdl/test/generate_data_test_case.hpp>. Otherwise the C++ code 
        skelet is generated.
        """
        
        [failure_test, clean_name]=self.isFailuretest(name) 
        test_case = name
        attribute_name=clean_name
        parser_name=clean_name
        
        if macro:
            return """
GENERATE_DATASET_TEST_CASE( {test_case} )            
""".format(test_case=name)
        else:
            return """
BOOST_DATA_TEST_CASE( {test_case},
      {test_case}_dataset.input()
    ^ {test_case}_dataset.expect()
    ^ {test_case}_dataset.test_case_name(),
    VHDL_code, expect_AST, test_case)
{{
    using attribute_type = ast::{attr_name};
    auto const parser = parser::{parser_name};

    boost::ignore_unused(test_case);

    x3_test::testing_parser<attribute_type> parse;
    auto [parse_ok, parsed_AST] = parse(VHDL_code, parser);

    BOOST_TEST({F}parse_ok);
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\\n    PARSED AST = '\\n" << parsed_AST << "'");

    BOOST_TEST(parsed_AST == expect_AST, btt::per_element());
    BOOST_REQUIRE_MESSAGE(x3_test::current_test_passing(),
                          "\\n    PARSED AST = '\\n" << parsed_AST << "'");
}}
""".format(
        test_case=name,
        attr_name=attribute_name,
        parser_name=parser_name,
        F='!' if failure_test else ''
    )


    def CxxTestCaseFile(self, name, macro):
        """Create a complete C++ Boost.Test implementation file ready to save
        
        Returns a filename and file contents.
        """
        
        [failure_test, _]=self.isFailuretest(name)
        # The macro doesn't support failure test yet.
        if failure_test: macro_ = False
        else:            macro_ = macro
        
        test_filename=''.join([name, '_parsertest', '.cpp'])
        cxx_test = """
{header}
{includes}
BOOST_AUTO_TEST_SUITE( {suite_name} )
{ns_alias}
{dataset}
{testcase}
BOOST_AUTO_TEST_SUITE_END()
""".format(
        header=self.cxxHeader(test_filename),
        includes=self.cxxIncludes(),
        suite_name=name,
        ns_alias=self.cxxNamespaceAliases(macro_),
        dataset=self.cxxDataSetLoader(name, macro_),
        testcase=self.cxxTestCase(name, macro_)
    )
        return [test_filename, cxx_test]
    

    def cxxParserInstance(self, name):
        """Spirit.X3 Explicit Template Instantiation

        """
        
        [failure_test, clean_name] = self.isFailuretest(name) 
        test_case = name
        attribute_name = clean_name
        parser_name = clean_name
        return """
#include <eda/vhdl/ast.hpp>
#include "testing_parser_def.hpp"
#include "testing_parser_grammar_hack.hpp"

namespace x3_test {{

    using attribute_type = ast::{attr_name};
    using parser_type = parser::{parser_name}_type;

    // Explicit Template Instantiation
    template
    std::tuple<bool, std::string>
    testing_parser<attribute_type>::operator()(std::string const &, parser_type const&, bool);
}}
        
""".format(
        attr_name = attribute_name,
        parser_name = parser_name
    )
    
    
    def cxxParserInstanceFile(self, test):
        """Create a complete C++ VHDL rule grammar instance file ready to save
        
        Returns a filename and file contents.
        """

        grammar_filename=''.join([test, '_grammar', '.cpp'])            
        cxx_grammar="""
{header}
{instance}
""".format(
        header=self.cxxHeader(grammar_filename),
        instance=self.cxxParserInstance(test)
    )
        return [grammar_filename, cxx_grammar]

    
    def writeFile(self, path, filename, contents):
        """Write the filename with the given contents into path.
        
        If the path isn't exist it will be created.
        """

        pathname=os.path.join(path, filename)
        
        if not os.path.exists(os.path.dirname(pathname)):
            try:
                os.makedirs(os.path.dirname(pathname))
            except OSError as exc: # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise

        with open(pathname, "w") as f:
            f.write(contents)
        
        
    
    def generate(self, path, macro=True):
        """User function to generate the test case c++ code skelet
        
        """
        
        test_cases = sorted(self.getTestCases())
        cmake_sources=[]
        
        # generate the files required
        for test in test_cases:
            
            [failure_test, _] = self.isFailuretest(test)

            [test_filename, cxx_test] = self.CxxTestCaseFile(test, macro)
            self.writeFile(path, test_filename, cxx_test[2:]) # skip first 2 empty lines
        
            [grammar_filename, cxx_grammar] = self.cxxParserInstanceFile(test)
            self.writeFile(path, grammar_filename, cxx_grammar[2:]) # skip first 2 empty lines   
            
            # failure test use same grammar instance, no extra generation required
            if failure_test:
                cmake_sources.append("{test}".format(
                    test=os.path.join(path, test_filename)))
            else:
                cmake_sources.append("{test} {grammar}".format(
                    test=os.path.join(path, test_filename),
                    grammar=os.path.join(path, grammar_filename)))
            
            
        # print files for CMake sources to compile
        for src in cmake_sources:
            print(src)
                                        
                    
if __name__ == "__main__":
    generator = BoostTestGenerator('');
    generator.generate('parser_test', True)
