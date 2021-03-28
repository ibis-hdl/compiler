#!/usr/bin/env python3

# THIS SCRIPT EXISTS ONLY FOR ARCHIVING AND IS NO LONGER FUNCTIONAL THESE DAYS.

import os
import re

from pathlib import Path


class ChangeAstVariant:
    """
    THIS SCRIPT EXISTS ONLY FOR ARCHIVING AND IS NO LONGER FUNCTIONAL THESE DAYS.

    Quick&Dirty script to replace all struct foo : variant<T...> derived classes
    to alias declarations.

    Background: To gain access to the BNF rules, the parser ID and types must be
                public to the testsuite. The types must be declared using X3's
                BOOST_SPIRIT_DECLARE macro. This doesn't seems to work work
                derived variants used as now (see below). Hence, aliases maybe
                a better solution, but also failes (see below).

    FixMe:
    Not related to the script, but to C++ AST nodes. How to declare this?
    E.g. template <typename ...Types> struct name; is correct, but failed with
    forward_ast to compile at e.g. primary.hpp with:
    error: 'name' was not declared in this scope .
    Otherwise: using derived variant types result into e.g.:
    note: 'choice(const choice&)' is implicitly declared as deleted because
    'choice' declares a move constructor or move assignment operator.
    """

    def __init__(self):
        self.path = os.path.dirname(os.path.realpath(__file__))
        self.include=os.path.join(self.path, '..', 'include', 'eda', 'vhdl')
        # test at https://pythex.org/
        self.re_variant_name=r"struct\s(\S+)\s:\svariant<"
        self.re_variant_bgn=r"(struct\s\S+\s:\svariant<)"
        self.str_variant_end=r""">
{
    using base_type::base_type;
    using base_type::operator=;
}"""

    def getAstVariantNodes(self):

        print('Search for ast nodes in %s' % self.include)

        ast_nodes=list()
        variant_nodes=list()

        is_variant=re.compile(self.re_variant_name)

        for dirname, dirnames, filenames in os.walk(self.include):
            #print('dirname ' + str(dirname))
            if 'ast' in dirname:
                for f in filenames:
                    ast_nodes.append(os.path.join(dirname, f))

        for filepath in sorted(ast_nodes):
            # Simply look into to find variant AST nodes
            with open(filepath, 'r') as fd:
                content=fd.read()
                if is_variant.search(content):
                    variant_nodes.append(filepath)
            fd.close()

        return variant_nodes


    def VariantToUsingAlias(self, content):

        variant_name = re.search(self.re_variant_name, content, re.M|re.I)
        variant_bgn  = re.search(self.re_variant_bgn,  content, re.M|re.I)

        if not variant_bgn or not variant_name:
            return 'N/A'    # something went wrong

        strong_variant=variant_bgn.group(1)
        alias_decl=r"using " + variant_name.group(1) + " = variant<"

        content = content.strip()
        content = content.replace(strong_variant, alias_decl)
        content = content.replace(self.str_variant_end, '>')

        return content


    def readFileToString(self, filepath):
        with open(filepath, 'r') as fd:
                content=fd.read()
        fd.close()
        return content


    def writeFileFromString(self, filepath, content):
        with open(filepath, 'w') as fd:
            content=fd.write(content)
        fd.close()


    def run(self):

        for header in self.getAstVariantNodes():
            print(header)
            content=self.readFileToString(header)
            new_content=self.VariantToUsingAlias(content)
            self.writeFileFromString(header, new_content)



if __name__ == "__main__":
    obj = ChangeAstVariant();
    obj.run()
