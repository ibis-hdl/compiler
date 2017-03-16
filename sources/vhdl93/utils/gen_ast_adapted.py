#!/usr/bin/env python

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser

import os
import sys

from collections import OrderedDict


class AstFusionAdapter:
    global_namespace = None
    ns_ast = None
    node_list = []
    l_width = 0
    r_width = 0
    indent = "    "
    
    def __init__(self):
        generator_path, generator_name = utils.find_xml_generator()
        xml_generator_config = parser.xml_generator_configuration_t(
            xml_generator_path=generator_path,
            xml_generator=generator_name,
            cflags='-std=c++11')
        header_list = [self.include_prefix() + hpp for hpp in self.find_hpp()]
        decls = parser.parse(header_list, xml_generator_config)
        self.global_namespace = declarations.get_global_namespace(decls)
        self.ns_ast = self.global_namespace.namespace("ast")
        self.update_db()
        
    def find_hpp(self):
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
        
    def nod_signature(self, cls):
        '''
        Extract the name of the ast node self and member variables. The order of
        structure members matters here for BOOST_FUSION_ADAPT_STRUCT macro!
        '''
        member_dict = OrderedDict()
        members = [m for m in cls.get_members(access='public') if m.is_artificial == False]
        for member in members:
            if declarations.is_enum(member):
                continue
            else:
                member_dict.update({ str(member.decl_type) : member.name })
                self.l_width = max(self.l_width, len(str(member.decl_type)))
                self.r_width = max(self.r_width, len(member.name))
        return (cls.decl_string, member_dict)
        
    def update_db(self):
        cls_list = [cls for cls in self.ns_ast.classes() if cls.class_type == 'struct']
        for cls in cls_list:
            self.node_list.append(self.nod_signature(cls))
            
    def fusion_adapt(self, node):
        node_name = node[0]
        attr_dict = node[1]
        alist = [node_name.lstrip('::') + ',']
        for attr in attr_dict.items():
            alist.append("({0:<{1}}, {2:>{3}})".format(
                attr[0], self.l_width, attr[1], self.r_width))
        text = "\n".join(self.indent + line for line in alist)
        return "BOOST_FUSION_ADAPT_STRUCT(\n{0}\n)\n".format(text)   
            
    def fusionize(self):
        text = ""
        for node in sorted(self.node_list, key=lambda tpl: tpl[0]):
            text += self.fusion_adapt(node) + '\n'
        return text
    
    def print_all(self):
        declarations.print_declarations(self.ns_ast)
            
    
if __name__ == "__main__":
    adapter = AstFusionAdapter()
    print(adapter.fusionize())
    
    
    #adapter.print_all()

    
    