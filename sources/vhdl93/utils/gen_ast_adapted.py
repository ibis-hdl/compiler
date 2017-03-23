#!/usr/bin/env python3

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser

import os
import sys


class AstFusionAdapter:
    global_namespace = None
    ns_ast = None
    node_list = []
    l_width = 0
    r_width = 0
    max_width=60
    indent = "    "
    parse_blacklist = []
    
    def __init__(self):
        # problem headers with boost::variant
        self.parse_blacklist = self.find_x3_variant()
        print("blacklisted <x3::variant> headers = " 
            + ", ".join("{0}".format(x) for x in self.parse_blacklist))
        generator_path, generator_name = utils.find_xml_generator()
        xml_generator_config = parser.xml_generator_configuration_t(
            xml_generator_path=generator_path,
            xml_generator=generator_name,
            cflags='-std=c++14')
        hxx_list = list(filter(lambda hxx: hxx not in self.parse_blacklist, self.find_hpp()))
        header_list = [self.include_prefix() + hpp for hpp in hxx_list]
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
        
    def find_x3_variant(self):
        '''
        pygccxml has problems to parse / build AST by boost's variant headers.
        Until this getn't solved, we use a black list here. In real world it
        doesn't matter since the variants doesn't have any attributes which 
        needs to be adapted to fusion sequences.
        '''
        hxx_list = []
        for hpp in sorted(self.find_hpp()):
            #print("inspect " + self.include_prefix() + hpp + ' for x3::variant')
            with open(self.include_prefix() + hpp, 'r') as f:
                contents = f.read()
                if contents.find('x3::variant') > 0:
                    hxx_list.append(hpp)
        return hxx_list

    def include_prefix(self):
        '''
        This script assumed the file layout of:
        $project_root/utils/__this_file__
        $project_root/include/...
        ''' 
        selfy = os.path.abspath(
            os.path.dirname(sys.modules[__name__].__file__))
        prefix = selfy + "/../include/eda/vhdl93" + '/ast' + '/'
        return prefix
        
    def nod_signature(self, cls):
        '''
        Extract the name of the ast node self and member variables. The order of
        structure members matters here for BOOST_FUSION_ADAPT_STRUCT macro!
        '''
        member_list = []
        members = [m for m in cls.get_members(access='public') if m.is_artificial == False]
        for member in members:
            if declarations.is_enum(member):
                continue
            else:
                member_list.append((str(member.decl_type) , member.name ))
                self.l_width = max(self.l_width, len(str(member.decl_type)))
                # there are some long types to be limited
                self.l_width = min(self.l_width, self.max_width) 
                self.r_width = max(self.r_width, len(member.name))
        return (cls.decl_string, member_list)
        
    def update_db(self):
        cls_list = [cls for cls in self.ns_ast.classes() if cls.class_type == 'struct']
        for cls in cls_list:
            self.node_list.append(self.nod_signature(cls))
            
    def fusion_adapt(self, node):
        node_name = node[0]
        attr_dict = node[1]
        alist = [node_name.lstrip('::') + ',']
        for attr in attr_dict:
            alist.append("({0:<{1}} {2:>{3}})".format(
                attr[0] + ',', self.l_width, attr[1], self.r_width))
        text = "\n".join(self.indent + line for line in alist)
        return "BOOST_FUSION_ADAPT_STRUCT(\n{0}\n)\n".format(text)   
            
    def fusion_adapt_ligth(self, node):
        '''
        X3 example Calc9 shows an alternative way to fusionize ast structures 
        which provides this function.
        '''
        node_name = node[0]
        attr_dict = node[1]
        if not attr_dict:  # skip empty classes used for strong types
            return ""
        member_list = [] 
        for attr in attr_dict:
            member_list.append("{0}".format(attr[1]))
        ast_type = node_name.lstrip('::') + ','
        text = ", ".join(line for line in member_list)
        text = "".join(self.indent + line for line in text.splitlines(True))
        return "BOOST_FUSION_ADAPT_STRUCT({0}\n{1}\n)\n".format(
            ast_type, text)   
            
    def fusionize(self, compact=True):
        text = ""
        for node in sorted(self.node_list, key=lambda tpl: tpl[0]):
            if compact:
                text += self.fusion_adapt_ligth(node) + '\n'
            else:
                text += self.fusion_adapt(node) + '\n'
        return text
    
    def ast_header_collector(self):
        hxx_list = []
        for hpp in sorted(self.find_hpp()):
            hxx_list.append("#include <eda/vhdl93/ast/{0}>".format(hpp))
        return "\n".join(hxx_list)
    
    def print_all(self):
        declarations.print_declarations(self.ns_ast)
        
    def dump_db(self):
        for node in self.node_list:
            print(node)
            
    
if __name__ == "__main__":
    adapter = AstFusionAdapter()
    print(adapter.ast_header_collector())
    print(adapter.fusionize())    
    #adapter.dump_db()

    
    