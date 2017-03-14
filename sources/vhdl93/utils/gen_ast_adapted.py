# https://github.com/CastXML/CastXML
# https://github.com/gccxml/pygccxml
# https://pygccxml.readthedocs.io/en/develop/examples.html
## special of interest
## https://pygccxml.readthedocs.io/en/develop/examples/artificial/example.html
## https://pygccxml.readthedocs.io/en/develop/examples/caching/example.html
## https://pygccxml.readthedocs.io/en/develop/examples/print-example/example.html

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser


# Find out the c++ parser
generator_path, generator_name = utils.find_xml_generator()

# Configure the xml generator
xml_generator_config = parser.xml_generator_configuration_t(
    xml_generator_path=generator_path,
    xml_generator=generator_name)

# The c++ file we want to parse
filename = "../include/eda/vhdl93/ast/based_literal.hpp"

file_config = parser.file_configuration_t(
    data=filename,
    content_type=parser.CONTENT_TYPE.CACHED_SOURCE_FILE)

project_reader = parser.project_reader_t(xml_generator_config)
decls = project_reader.read_files(
    [file_config],
    compilation_mode=parser.COMPILATION_MODE.FILE_BY_FILE)


global_namespace = declarations.get_global_namespace(decls)

ns_ast = global_namespace.namespace("ast")


#print(ns_ast.name)
#query = declarations.custom_matcher_t(lambda n: n.name.endswith( 'literal'))
#y=global_namespace.member_functions( function=query)
#print(y)

#declarations.print_declarations(ns_ast)

#for decl in ns_ast.declarations:
#    print(decl)


## https://media.readthedocs.org/pdf/pygccxml/latest/pygccxml.pdf
## pg. 28

class AstFusionAdapter:
    width = 20
    #def __init__(self):
        
    
    def fusionize(self, cls):
        text = ""
        if not cls.class_type == 'struct':
            return "<error> not a struct"
        text += str(cls.decl_string) + ',\n'
        members = [m for m in cls.get_members() if m.is_artificial == False]
        for m in members:
            text += "    ({0:<{2}}, {1:>{2}})\n".format(m.decl_type, m.name, self.width)
        return "BOOST_FUSION_ADAPT_STRUCT(\n{0}\n)\n".format(text)

    
    def inspect(self, ns):
        text = ""
        cls_list = [cls for cls in ns_ast.classes() if cls.class_type == 'struct']
        for cls in cls_list:
            text += self.fusionize(cls)
        return text
            
    
if __name__ == "__main__":
    adapter = AstFusionAdapter()
    print(adapter.inspect(ns_ast))
