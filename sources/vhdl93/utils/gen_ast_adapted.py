#!/usr/bin/env python

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser

import os
import sys


class AstFusionAdapter:
    global_namespace = None
    ns_ast = None
    width = 40
    indent = "    "
    
    def __init__(self):
        generator_path, generator_name = utils.find_xml_generator()
        xml_generator_config = parser.xml_generator_configuration_t(
            xml_generator_path=generator_path,
            xml_generator=generator_name,
            cflags='-std=c++11')
        header_list = [self.include_prefix() + hpp for hpp in self.find_ast_hpp()]
        decls = parser.parse(header_list, xml_generator_config)
        self.global_namespace = declarations.get_global_namespace(decls)
        self.ns_ast = self.global_namespace.namespace("ast")
        
    def find_ast_hpp(self):
        ast_include_path = self.include_prefix()
        file_ext = ['hpp']
        header_list = [hxx for hxx in os.listdir(ast_include_path)
                      if any(hxx.endswith(ext) for ext in file_ext)]
        return header_list

    def include_prefix(self):
        """
        This script assumed the file layout of:
        $project_root/utils/__this_file__
        $project_root/include/...
        """ 
        selfy = os.path.abspath(
            os.path.dirname(sys.modules[__name__].__file__))
        prefix = selfy + "/../include/eda/vhdl93" + '/ast' + '/'
        return prefix
        
    def fusion_adapt(self, cls):
        alist = []
        alist.append(str(cls.decl_string).lstrip('::') + ',')
        members = [m for m in cls.get_members(access='public') if m.is_artificial == False]
        for member in members:
            if declarations.is_enum(member):
                continue
            alist.append("({0:<{1}}, {2:>{3}})".format(
                member.decl_type, self.width, member.name, self.width/2))
        text = "\n".join(self.indent + line for line in alist)
        return "BOOST_FUSION_ADAPT_STRUCT(\n{0}\n)\n".format(text)

    
    def inspect(self):
        text = ""
        cls_list = [cls for cls in self.ns_ast.classes() if cls.class_type == 'struct']
        for cls in cls_list:
            text += self.fusion_adapt(cls) + '\n'
        return text
    
    def print_all(self):
        declarations.print_declarations(self.ns_ast)
            
    
if __name__ == "__main__":
    adapter = AstFusionAdapter()
    print(adapter.inspect())
    
    #adapter.print_all()

    
    