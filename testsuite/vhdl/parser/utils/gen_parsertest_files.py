#!/usr/bin/env python3

import os, errno
from pathlib import Path

import datetime
now = datetime.datetime.now()


class BoostTestGenerator:
    """
    Quick & Dirty python script to generate C++ skeletons for Boost.Test
    based on the directories given below 'test_case' to test the VHDL
    parser grammar.
    
    Over the time there where changes on the AST printer output format and 
    macros used to generate the stuff, rewriting by hand isn't suitable. 
    """
    def __init__(self, root_name):
        self.root_name = root_name
        self.path = os.path.dirname(os.path.realpath(__file__))
        self.testfile_postfix = '_test.cpp'
        self.skiplist = ['_failure', 'xxx',
                         # no parsers, embedded into grammar
                         'floating_type_definition',
                         'full_type_declaration',
                         'incomplete_type_declaration',
                         'integer_type_definition'
                         ]
        
    
    def skip(self, name):
        """returns true if name is inside the skip list.
        
        This is only usefull for the API header/source file generation!
        """
        for s in self.skiplist:
            if s in name:
                return True
        return False
        
        
    def namespace_open(self, namespaces):
        """Helper for opening namespace from namespace list.
        
        """
        
        txt=' '.join('namespace {name} {{'.format(name=name) for name in namespaces)
        return txt
    
    
    def namespace_close(self, namespaces):
        """Helper for closing namespace from namespace list.
        
        """
        
        braces=' '.join('}' for name in namespaces) 
        comment='.'.join('{name}'.format(name=name) for name in namespaces)
        txt=braces + ' // namespace ' + comment
        return txt
        

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
        
        path = os.path.join(self.path, '..', 'test_case')
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

#include <testsuite/vhdl_parser/data_set.hpp>
#include <testsuite/vhdl_parser/rules.hpp>
#include <testsuite/vhdl_parser/testing_parser.hpp>
#include <testsuite/vhdl_parser/generate_data_test_case.hpp>
#include <testsuite/vhdl_parser/testing_util.hpp>
#include <testsuite/vhdl_parser/testing_parser_grammar_hack.hpp>
"""
        
    def cxxNamespaceAliases(self):
        return """
namespace btt    = boost::test_tools;
namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;"""
        
        
    def cxxDataSetLoader(self, name):
        return """
struct {name}_dataset : public testsuite::vhdl_parser::util::dataset_loader
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
    auto const& parser = testsuite::vhdl_parser::{parser_name}();

    using testsuite::vhdl_parser::util::testing_parser;
    using testsuite::vhdl_parser::util::current_test_passing;
    using testsuite::vhdl_parser::util::report_diagnostic;

    testing_parser<attribute_type> parse;
    auto [parse_ok, parse_result] = parse(input, parser, test_case_name);

    BOOST_TEST({F}parse_ok);
    BOOST_REQUIRE_MESSAGE({F}parse_ok,
        report_diagnostic(test_case_name, input, parse_result)
    );

    BOOST_TEST(parse_result == expected, btt::per_element());
    BOOST_REQUIRE_MESSAGE(current_test_passing(),
        report_diagnostic(test_case_name, input, parse_result)
    );
}}
""".format(
        test_case=test_case,
        attr_name=attribute_name,
        parser_name=parser_name,
        F='!' if failure_test else ''
    )

    
    def writeParserTestFile(self, path, filename, dataset_loader, datatest_case, testsuite_name='parser'):
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
        
     
    def cxxBnfDecl(self, parser_list, api_namespace):
        """ Generate the API to access the BNF parsers
        
        """    
        
        api_list=list()
        
        for p in parser_list:
            if self.skip(p):
                continue
            
            api_list.append("{name}_type const& {name}();".format(name=p))
        
        contents="""
#include <eda/vhdl/parser/grammar_decl.hpp>

{namespace_api_bgn}

namespace parser = eda::vhdl::parser;

{fcn}

{namespace_api_end}
""".format(
    namespace_api_bgn=self.namespace_open(api_namespace),
    fcn='\n'.join(f"parser::{x}" for x in api_list),
    namespace_api_end=self.namespace_close(api_namespace)
)

        return contents
        
    
    def cxxBnfInst(self, parser_list, api_namespace):
        """ Generate the API instances to access the BNF parsers
        
        """    
        
        inst_list=list()
        fcn_list=list()

        for p in parser_list:
            if self.skip(p):
                continue
            
            inst_list.append(
                "BOOST_SPIRIT_INSTANTIATE({name}_type, iterator_type, context_type);"
                .format(name=p))
            
            fcn_list.append(
                """parser::{name}_type const& {name}() {{
    return eda::vhdl::parser::{name}; 
}}
"""
                .format(name=p))       
        
        contents="""
#include <testsuite/vhdl_parser/rules.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>


namespace eda {{ namespace vhdl {{ namespace parser {{

{inst}

}} }} }} // namespace eda.vhdl.parser


{namespace_api_bgn}

{fcn}

{namespace_api_end}
""".format(
    namespace_api_bgn=self.namespace_open(api_namespace),
    inst='\n'.join(f"{x}" for x in inst_list),
    fcn='\n'.join(f"{x}" for x in fcn_list),
    namespace_api_end=self.namespace_close(api_namespace)
)
        
        return contents 
    
    
    def writeBnfFile(self, path, filebase_name, parser_list):
        
        pathname=os.path.join(path, filebase_name)
        api_namespace=['testsuite', 'vhdl_parser']

        with open(pathname + '.hpp', "w") as f:
            f.write(self.cxxBnfDecl(parser_list, api_namespace))
        
        
        with open(pathname + '.cpp', "w") as f:
            f.write(self.cxxBnfInst(parser_list, api_namespace))
        
        
    
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
                
            test_filename = test + self.testfile_postfix

            self.writeParserTestFile(path, test_filename, dataset_loader, datatest_case) 
        
            cmake_sources.append("{cxx}".format(
                    cxx=path + '/' + test_filename))
                    
        # generate parser rule access API files, leading '0' for dir-sort on top
        self.writeBnfFile(path , '0_rules', test_cases)
        
        
        # print CMakeFiles
        print('set(PARSERTEST_SOURCES\n${PARSERTEST_COMMON_SOURCES}')
        for src in cmake_sources:
            print(src)
        print(')')

                    
if __name__ == "__main__":
    generator = BoostTestGenerator('');
    generator.generate('parser_test')
