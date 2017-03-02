#!/usr/bin/env python
from pyxb.utils.utility import _XMLIdentifierToPython


# copy&paste reserved keywords
# https://www.csee.umbc.edu/portal/help/VHDL/reserved.html
vhdl93_words = """
abs           operator, absolute value of right operand. No () needed.
access        used to define an access type, pointer
after         specifies a time after NOW
alias         create another name for an existing identifier
all           dereferences what precedes the .all
and           operator, logical "and" of left and right operands
architecture  a secondary design unit
array         used to define an array, vector or matrix
assert        used to have a program check on itself
attribute     used to declare attribute functions
begin         start of a  begin  end  pair
block         start of a block structure
body          designates a procedure body rather than declaration
buffer        a mode of a signal, holds a value
bus           a mode of a signal, can have multiple drivers
case          part of a case statement
component     starts the definition of a component
configuration a primary design unit
constant      declares an identifier to be read only
disconnect    signal driver condition
downto        middle of a range  31 downto 0
else          part of "if" statement, if cond then ... else ... end if;
elsif         part of "if" statement, if cond then ... elsif cond ...
end           part of many statements, may be followed by word and id
entity        a primary design unit
exit          sequential statement, used in loops
file          used to declare a file type
for           start of a for type loop statement
function      starts declaration and body of a function
generate      make copies, possibly using a parameter
generic       introduces generic part of a declaration
group         collection of types that can get an attribute
guarded       causes a wait until a signal changes from False to True
if            used in "if" statements
impure        an impure function is assumed to have side effects
in            indicates a parameter in only input, not changed
inertial      signal characteristic, holds a value
inout         indicates a parameter is used and computed in and out
is            used as a connective in various statements
label         used in attribute statement as entity specification
library       context clause, designates a simple library name
linkage       a mode for a port, used like buffer and inout
literal       used in attribute statement as entity specification
loop          sequential statement, loop ... end loop;
map           used to map actual parameters, as in  port map
mod           operator, left operand modulo right operand
nand          operator, "nand" of left and right operands
new           allocates memory and returns access pointer
next          sequential statement, used in loops
nor           operator, "nor" of left and right operands
not           operator, complement of right operand
null          sequential statement and a value
of            used in type declarations, of Real ;
on            used as a connective in various statements
open          initial file characteristic
or            operator, logical "or" of left and right operands
others        fill in missing, possibly all, data
out           indicates a parameter is computed and output
package       a design unit, also  package body
port          interface definition, also  port map
postponed     make process wait for all non postponed process to suspend
procedure     typical programming procedure
process       sequential or concurrent code to be executed
pure          a pure function may not have side effects
range         used in type definitions, range 1 to 10;
record        used to define a new record type
register      signal parameter modifier
reject        clause in delay mechanism, followed be a time
rem           operator, remainder of left operand divided by right op
report        statement and clause in assert statement, string output
return        statement in procedure or function
rol           operator, left operand rotated left by right operand
ror           operator, left operand rotated right by right operand
select        used in selected signal assignment statement
severity      used in assertion and reporting, followed by a severity
signal        declaration that an object is a signal
shared        used to declare shared objects
sla           operator, left operand shifted left arithmetic by right op
sll           operator, left operand shifted left logical by right op
sra           operator, left operand shifted right arithmetic by right
srl           operator, left operand shifted right logical by right op
subtype       declaration to restrict an existing type
then          part of  if condition then ...
to            middle of a range  1 to 10
transport     signal characteristic
type          declaration to create a new type
unaffected    used in signal waveform
units         used to define new types of units
until         used in wait statement
use           make a package available to this design unit
variable      declaration that an object is a variable
wait          sequential statement, also used in case statement
when          used for choices in case and other statements
while         kind of loop statement
with          used in selected signal assignment statement          
xnor          operator, exclusive "nor" of left and right operands
xor           operator, exclusive "or" of left and right operands
"""

# copy&paste VHDL93 rule 
# from https://tams.informatik.uni-hamburg.de/vhdl/tools/grammar/vhdl93-bnf.txt
## TopUnit => design_file ???
# see https://tams-www.informatik.uni-hamburg.de/vhdl/doc/cookbook/VHDL-Cookbook.pdf
# 5.1 "Design Units and Libraries"
vhdl93_ebnf = """
abstract_literal ::= decimal_literal | based_literal

access_type_definition ::= access subtype_indication

actual_designator ::=
    expression
    | signal_name
    | variable_name
    | file_name
    | open

actual_parameter_part ::= parameter_association_list

actual_part ::=
    actual_designator
    | function_name ( actual_designator )
    | type_mark ( actual_designator )

adding_operator ::= + | -  | &

aggregate ::=
    ( element_association { , element_association } )

alias_declaration ::=
    alias alias_designator [ : subtype_indication ] is name [ signature ] ;

alias_designator ::= identifier | character_literal | operator_symbol

allocator ::=
    new subtype_indication
    | new qualified_expression

architecture_body ::=
    architecture identifier of entity_name is
        architecture_declarative_part
    begin
        architecture_statement_part
    end [ architecture ] [ architecture_simple_name ] ;

architecture_declarative_part ::=
    { block_declarative_item }

architecture_statement_part ::=
    { concurrent_statement }

array_type_definition ::=
    unconstrained_array_definition    |   constrained_array_definition

assertion ::=
    assert condition
        [ report expression ]
        [ severity expression ]

assertion_statement ::=     [ label : ] assertion ;

association_element ::=
    [ formal_part => ] actual_part

association_list ::=
    association_element { , association_element }

attribute_declaration ::=
    attribute identifier : type_mark ;

attribute_designator ::= attribute_simple_name

attribute_name ::=
    prefix [ signature ] ' attribute_designator [ ( expression ) ]

attribute_specification ::=
    attribute attribute_designator of entity_specification is expression ;

base ::= integer

base_specifier ::=  B | O | X

base_unit_declaration ::= identifier ;

based_integer ::=
    extended_digit { [ underline ] extended_digit }

based_literal ::=
    base # based_integer [ . based_integer ] # [ exponent ]

basic_character ::=
    basic_graphic_character | format_effector

basic_graphic_character ::=
    upper_case_letter | digit | special_character| space_character

basic_identifier ::=
    letter { [ underline ] letter_or_digit }

binding_indication ::=
    [ use entity_aspect ]
    [ generic_map_aspect ]
    [ port_map_aspect ]

bit_string_literal ::=    base_specifier " bit_value "

bit_value ::= extended_digit { [ underline ] extended_digit }

block_configuration ::=
    for block_specification
        { use_clause }
        { configuration_item }
    end for ;

block_declarative_item ::=
    subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | component_declaration
    | attribute_declaration
    | attribute_specification
    | configuration_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

block_declarative_part ::=
    { block_declarative_item }

block_header ::=
    [ generic_clause
    [ generic_map_aspect ; ] ]
    [ port_clause
    [ port_map_aspect ; ] ]

block_specification ::=
    architecture_name
    | block_statement_label
    | generate_statement_label [ ( index_specification ) ]

block_statement ::=
    block_label :
        block [ ( guard_expression ) ] [ is ]
            block_header
            block_declarative_part
        begin
            block_statement_part
        end block [ block_label ] ;

block_statement_part ::=
    { concurrent_statement }

case_statement ::=
    [ case_label : ]
        case expression is
            case_statement_alternative
            { case_statement_alternative }
        end case [ case_label ] ;

case_statement_alternative ::=
    when choices =>
        sequence_of_statements

character_literal ::= ' graphic_character '

choice ::=
    simple_expression
    | discrete_range
    | element_simple_name
    | others

choices ::= choice { | choice }

component_configuration ::=
    for component_specification
        [ binding_indication ; ]
        [ block_configuration ]
    end for ;

component_declaration ::=
    component identifier [ is ]
        [ local_generic_clause ]
        [ local_port_clause ]
    end component [ component_simple_name ] ;

component_instantiation_statement ::=
    instantiation_label :
        instantiated_unit
            [ generic_map_aspect ]
            [ port_map_aspect ] ;

component_specification ::=
    instantiation_list : component_name

composite_type_definition ::=
    array_type_definition
    | record_type_definition

concurrent_assertion_statement ::=
    [ label : ] [ postponed ] assertion ;

concurrent_procedure_call_statement ::=
    [ label : ] [ postponed ] procedure_call ;

concurrent_signal_assignment_statement ::=
      [ label : ] [ postponed ] conditional_signal_assignment
    | [ label : ] [ postponed ] selected_signal_assignment

concurrent_statement ::=
    block_statement
    | process_statement
    | concurrent_procedure_call_statement
    | concurrent_assertion_statement
    | concurrent_signal_assignment_statement
    | component_instantiation_statement
    | generate_statement

condition ::= boolean_expression

condition_clause ::= until condition

conditional_signal_assignment ::=
    target    <= options conditional_waveforms ;

conditional_waveforms ::=
    { waveform when condition else }
    waveform [ when condition ]

configuration_declaration ::=
    configuration identifier of entity_name is
        configuration_declarative_part
        block_configuration
    end [ configuration ] [ configuration_simple_name ] ;

configuration_declarative_item ::=
    use_clause
    | attribute_specification
    | group_declaration

configuration_declarative_part ::=
    { configuration_declarative_item }

configuration_item ::=
    block_configuration
    | component_configuration

configuration_specification ::=
    for component_specification binding_indication ;

constant_declaration ::=
    constant identifier_list : subtype_indication [ := expression ] ;

constrained_array_definition ::=
    array index_constraint of element_subtype_indication

constraint ::=
    range_constraint
    | index_constraint

context_clause ::= { context_item }

context_item ::=
    library_clause
    | use_clause

decimal_literal ::= integer [ . integer ] [ exponent ]

declaration ::=
    type_declaration
    | subtype_declaration
    | object_declaration
    | interface_declaration
    | alias_declaration
    | attribute_declaration
    | component_declaration
    | group_template_declaration
    | group_declaration
    | entity_declaration
    | configuration_declaration
    | subprogram_declaration
    | package_declaration

delay_mechanism ::=
    transport
    | [ reject time_expression ] inertial

design_file ::= design_unit { design_unit }

design_unit ::= context_clause library_unit

designator ::= identifier  |  operator_symbol

direction ::= to | downto

disconnection_specification ::=
    disconnect guarded_signal_specification after time_expression ;

discrete_range ::= discrete_subtype_indication | range

element_association ::=
    [ choices => ] expression

element_declaration ::=
    identifier_list : element_subtype_definition ;

element_subtype_definition ::= subtype_indication

entity_aspect ::=
      entity entity_name [ ( architecture_identifier) ]
    | configuration configuration_name
    | open

entity_class ::=
    entity         | architecture  | configuration
    | procedure  | function         | package
    | type         | subtype         | constant
    | signal     | variable         | component
    | label         | literal         | units
    | group         | file

entity_class_entry ::=    entity_class [ <> ]

entity_class_entry_list ::=
    entity_class_entry { , entity_class_entry }

entity_declaration ::=
    entity identifier is
        entity_header
        entity_declarative_part
      [ begin
        entity_statement_part ]
    end [ entity ] [ entity_simple_name ] ;

entity_declarative_item ::=
    subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

entity_declarative_part ::=
    { entity_declarative_item }

entity_designator ::= entity_tag [ signature ]

entity_header ::=
    [ formal_generic_clause ]
    [ formal_port_clause ]

entity_name_list ::=
    entity_designator { , entity_designator }
    | others
    | all

entity_specification ::=
    entity_name_list : entity_class

entity_statement ::=
    concurrent_assertion_statement
    | passive_concurrent_procedure_call_statement
    | passive_process_statement

entity_statement_part ::=
    { entity_statement }

entity_tag ::=    simple_name | character_literal | operator_symbol

enumeration_literal ::= identifier | character_literal

enumeration_type_definition ::=
    ( enumeration_literal { , enumeration_literal } )

exit_statement ::=
    [ label : ] exit [ loop_label ] [ when condition ] ;

exponent ::= E [ + ] integer | E - integer

expression ::=
      relation { and relation }
    | relation { or relation }
    | relation { xor relation }
    | relation [ nand relation ]
    | relation [ nor relation ]
    | relation { xnor relation }

extended_digit ::= digit | letter

extended_identifier ::=
    \ graphic_character { graphic_character } \

factor ::=
    primary [ ** primary ]
    | abs primary
    | not primary

file_declaration ::=
    file identifier_list : subtype_indication file_open_information ] ;

file_logical_name ::= string_expression

file_open_information ::=
    [ open file_open_kind_expression ] is file_logical_name

file_type_definition ::=
    file  of type_mark

floating_type_definition  :=  range_constraint

formal_designator ::=
    generic_name
    | port_name
    | parameter_name

formal_parameter_list ::= parameter_interface_list

formal_part ::=
    formal_designator
    | function_name ( formal_designator )
    | type_mark ( formal_designator )

full_type_declaration ::=
    type identifier is type_definition ;

function_call ::=
    function_name [ ( actual_parameter_part ) ]

generate_statement ::=
    generate_label :
        generation_scheme generate
            [ { block_declarative_item }
        begin ]
            { concurrent_statement }
        end generate [ generate_label ] ;

generation_scheme ::=
    for generate_parameter_specification
    | if condition

generic_clause ::=
    generic ( generic_list ) ;

generic_list ::= generic_interface_list

generic_map_aspect ::=
    generic map ( generic_association_list )

graphic_character ::=
    basic_graphic_character     | lower_case_letter | other_special_character

group_constituent ::= name | character_literal

group_constituent_list ::= group_constituent { , group_constituent }

group_template_declaration ::=
    group identifier is ( entity_class_entry_list ) ;

group_declaration ::=
    group identifier : group_template_name ( group_constituent_list ) ;

guarded_signal_specification ::=
    guarded_signal_list : type_mark

identifier ::=
    basic_identifier | extended_identifier

identifier_list ::= identifier { , identifier }

if_statement ::=
    [ if_label : ]
        if condition then
            sequence_of_statements
        { elsif condition then
            sequence_of_statements }
        [ else
            sequence_of_statements ]
        end if [ if_label ] ;

incomplete_type_declaration ::=     type identifier ;

index_constraint ::= ( discrete_range { , discrete_range } )

index_specification ::=
    discrete_range
    | static_expression

index_subtype_definition ::= type_mark range <>

indexed_name ::= prefix ( expression { , expression } )

instantiated_unit ::=
    [ component ] component_name
    | entity entity_name [ ( architecture_identifier ) ]
    | configuration configuration_name

instantiation_list ::=
    instantiation_label { , instantiation_label }
    | others
    | all

integer ::= digit { [ underline ] digit }

integer_type_definition ::= range_constraint

interface_constant_declaration ::=
    [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]

interface_declaration ::=
    interface_constant_declaration
    | interface_signal_declaration
    | interface_variable_declaration
    | interface_file_declaration

interface_element ::= interface_declaration

interface_file_declaration ::=
    file identifier_list : subtype_indication

interface_list ::=
    interface_element { ; interface_element }

interface_signal_declaration ::=
    [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]

interface_variable_declaration ::=
    [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]

iteration_scheme ::=
    while condition
    | for loop_parameter_specification

label ::= identifier

letter ::= upper_case_letter | lower_case_letter

letter_or_digit ::= letter | digit

library_clause ::= library logical_name_list ;

library_unit ::=
    primary_unit
    | secondary_unit

literal ::=
    numeric_literal
    | enumeration_literal
    | string_literal
    | bit_string_literal
    | null

logical_name ::= identifier

logical_name_list ::= logical_name { , logical_name }

logical_operator ::= and | or | nand | nor | xor | xnor

loop_statement ::=
    [ loop_label : ]
        [ iteration_scheme ] loop
            sequence_of_statements
        end loop [ loop_label ] ;

miscellaneous_operator ::= ** | abs | not

mode ::= in | out | inout | buffer | linkage

multiplying_operator ::= * | / | mod | rem

name ::=
    simple_name
    | operator_symbol
    | selected_name
    | indexed_name
    | slice_name
    | attribute_name

next_statement ::=
    [ label : ] next [ loop_label ] [ when condition ] ;

null_statement ::= [ label : ] null ;

numeric_literal ::=
    abstract_literal
    | physical_literal

object_declaration ::=
    constant_declaration
    | signal_declaration
    | variable_declaration
    | file_declaration

operator_symbol ::= string_literal

options ::= [ guarded ] [ delay_mechanism ]

package_body ::=
    package body package_simple_name is
        package_body_declarative_part
    end [ package body ] [ package_simple_name ] ;

package_body_declarative_item ::=
    subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | use_clause
    | group_template_declaration
    | group_declaration

package_body_declarative_part ::=
    { package_body_declarative_item }

package_declaration ::=
    package identifier is
        package_declarative_part
    end [ package ] [ package_simple_name ] ;

package_declarative_item ::=
    subprogram_declaration
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | signal_declaration
    | shared_variable_declaration
    | file_declaration
    | alias_declaration
    | component_declaration
    | attribute_declaration
    | attribute_specification
    | disconnection_specification
    | use_clause
    | group_template_declaration
    | group_declaration

package_declarative_part ::=
    { package_declarative_item }

parameter_specification ::=
    identifier in discrete_range

physical_literal ::= [ abstract_literal ] unit_name

physical_type_definition ::=
    range_constraint
        units
            base_unit_declaration
            { secondary_unit_declaration }
        end units [ physical_type_simple_name ]

port_clause ::=
    port ( port_list ) ;

port_list ::= port_interface_list

port_map_aspect ::=
    port map ( port_association_list )

prefix ::=
    name
    | function_call

primary ::=
    name
    | literal
    | aggregate
    | function_call
    | qualified_expression
    | type_conversion
    | allocator
    | ( expression )

primary_unit ::=
    entity_declaration
    | configuration_declaration
    | package_declaration

procedure_call ::= procedure_name [ ( actual_parameter_part ) ]

procedure_call_statement ::=
    [ label : ] procedure_call ;

process_declarative_item ::=
    subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | use_clause
    | group_template_declaration
    | group_declaration

process_declarative_part ::=
    { process_declarative_item }

process_statement ::=
    [ process_label : ]
        [ postponed ] process [ ( sensitivity_list ) ] [ is ]
            process_declarative_part
        begin
            process_statement_part
        end [ postponed ] process [ process_label ] ;

process_statement_part ::=
    { sequential_statement }

qualified_expression ::=
    type_mark ' ( expression )
    | type_mark ' aggregate

range ::=
    range_attribute_name
    | simple_expression direction simple_expression

range_constraint ::= range range

record_type_definition ::=
    record
        element_declaration
        { element_declaration }
    end record [ record_type_simple_name ]

relation ::=
    shift_expression [ relational_operator shift_expression ]

relational_operator ::=      =  |    /=  |  <  |  <=     |  >  |  >=

report_statement ::=
    [ label : ]
        report expression
            [ severity expression ] ;

return_statement ::=
    [ label : ] return [ expression ] ;

scalar_type_definition ::=
    enumeration_type_definition   | integer_type_definition
    | floating_type_definition      | physical_type_definition

secondary_unit ::=
    architecture_body
    | package_body

secondary_unit_declaration ::=    identifier = physical_literal ;

selected_name ::= prefix . suffix

selected_signal_assignment ::=
    with expression select
        target    <= options selected_waveforms ;

selected_waveforms ::=
    { waveform when choices , }
    waveform when choices

sensitivity_clause ::=    on sensitivity_list

sensitivity_list ::= signal_name { , signal_name }

sequence_of_statements ::=
    { sequential_statement }

sequential_statement ::=
    wait_statement
    | assertion_statement
    | report_statement
    | signal_assignment_statement
    | variable_assignment_statement
    | procedure_call_statement
    | if_statement
    | case_statement
    | loop_statement
    | next_statement
    | exit_statement
    | return_statement
    | null_statement

shift_expression ::=
    simple_expression [ shift_operator simple_expression ]

shift_operator ::= sll | srl | sla | sra | rol | ror

sign ::= + | -

signal_assignment_statement ::=
    [ label : ] target <= [ delay_mechanism ] waveform ;

signal_declaration ::=
    signal identifier_list : subtype_indication [ signal_kind ] [ := expression ] ;

signal_kind ::=     register  |  bus

signal_list ::=
    signal_name { , signal_name }
    | others
    | all

signature ::= [ [ type_mark { , type_mark } ] [ return type_mark ] ]

simple_expression ::=
    [ sign ] term { adding_operator term }

simple_name ::=     identifier

slice_name ::=    prefix ( discrete_range )

string_literal ::= " { graphic_character } "

subprogram_body ::=
    subprogram_specification is
        subprogram_declarative_part
    begin
        subprogram_statement_part
    end [ subprogram_kind ] [ designator ] ;

subprogram_declaration ::=
    subprogram_specification ;

subprogram_declarative_item ::=
    subprogram_declaration
    | subprogram_body
    | type_declaration
    | subtype_declaration
    | constant_declaration
    | variable_declaration
    | file_declaration
    | alias_declaration
    | attribute_declaration
    | attribute_specification
    | use_clause
    | group_template_declaration
    | group_declaration

subprogram_declarative_part ::=
    { subprogram_declarative_item }

subprogram_kind ::= procedure | function

subprogram_specification ::=
    procedure designator [ ( formal_parameter_list ) ]
    | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
        return type_mark

subprogram_statement_part ::=
    { sequential_statement }

subtype_declaration ::=
    subtype identifier is subtype_indication ;

subtype_indication ::=
    [ resolution_function_name ] type_mark [ constraint ]

suffix ::=
    simple_name
    | character_literal
    | operator_symbol
    | all

target ::=
    name
    | aggregate

term ::=
    factor { multiplying_operator factor }

timeout_clause ::= for time_expression

type_conversion ::= type_mark ( expression )

type_declaration ::=
    full_type_declaration
    | incomplete_type_declaration

type_definition ::=
    scalar_type_definition
    | composite_type_definition
    | access_type_definition
    | file_type_definition

type_mark ::=
    type_name
    | subtype_name

unconstrained_array_definition ::=
    array ( index_subtype_definition { , index_subtype_definition } )
        of element_subtype_indication

use_clause ::=
    use selected_name { , selected_name } ;

variable_assignment_statement ::=
    [ label : ] target  := expression ;

variable_declaration ::=
    [ shared ] variable identifier_list : subtype_indication [ := expression ] ;

wait_statement ::=
    [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ] ;

waveform ::=
    waveform_element { , waveform_element }
    | unaffected

waveform_element ::=
    value_expression [ after time_expression ]
    | null [ after time_expression ]
"""

import collections


## BNF keywords
class vhdl93Keywords:
    'extracts the VHDL93 keywords from given copy&paste arg'
    kw_list = []
    x3_words = []
    
    def __init__(self, snippet):
        self.kw_list = [l.split()[0] for l in snippet.splitlines() if l.strip()]
        self.x3_words.append("""
auto kw = [](auto xx) {
    return x3::lexeme [ x3::no_case[ xx ] >> !(ascii::alnum | '_') ];
};
""")

    def keywords(self):
        return self.kw_list

    def x3_name(self, kw):
        return kw.lower() + '_'

    def x3(self):
        for line in self.keywords():
            kw = line.lower()
            def_ = """auto const {0} = kw(\"{1}\");""".format(self.x3_name(kw), kw)
            self.x3_words.append(def_)
        return self.x3_words


## global helper class
def cxx_ify(identier):
    cpp_reserved = [ # C++ reserved words
            'and', 'or', 'xor', 'not'
            ]
    if identier in cpp_reserved: identier += '_'
    return identier    

## BNF operator symbol production rules
class Operatorsymbols:
    
    operators = {    # hand selected operators from BNF
        'adding_operator'        : ['+', '-', '&'],
        'logical_operator'       : ['and', 'or', 'nand', 'nor', 'xor', 'xnor'],
        'miscellaneous_operator' : ['**', 'abs', 'not'],
        'multiplying_operator'   : ['*', '/', 'mod', 'rem'],
        'relational_operator'    : ['=', '/=', '<', '<=', '>', '>='],
        'shift_operator'         : ['sll', 'srl', 'sla', 'sra', 'rol', 'ror']
    }
    
    
    
    def is_operator(self, op):
        for name in self.operators:
            if name == op.split(): return True
            else:                  return False

    def as_name(self, symbol):
        subs_dic = {
            '+'  : 'add',
            '-'  : 'sub',
            '*'  : 'mul',
            '/'  : 'div',
            '**' : 'exponent',
            '&'  : 'concat',
            '='  : 'equal',
            '/=' : 'not_equals',
            '<'  : 'less',
            '<=' : 'less_equals',
            '>'  : 'greater',
            '>=' : 'greater_equals'
        }
        return cxx_ify(subs_dic.get(symbol, symbol))

    def as_enums(self, operator_name):
        text = ""
        ops = self.operators.get(operator_name)
        for n, o in enumerate(ops):
            text += '    {0},\n'.format(self.as_name(o))
        return text

    def enum_class(self):
        text = "// operator symbol enums\n"
        text += "enum class operator_type {\n"
        ops_list = list(self.operators.keys())
        for n, o in enumerate(ops_list):
            text += "    // {0}\n".format(o)
            text += self.as_enums(o)
        text.rstrip(',') # fails
        text += "};\n"
        return text

    def x3_operator_declare(self, ast_node):
        text = ""
        ops_list = list(self.operators.keys())
        for n, o in enumerate(ops_list):
            text += 'x3::symbols<{0}> {1};\n'.format(
                ast_node,
                o
            )
        return text

    def x3_op_define(self, operator_name, ast_node):
        text = "{0}.add\n".format(operator_name)
        ops = self.operators.get(operator_name)
        for n, o in enumerate(ops):
            text += '    ("{0}", {1}::{2})\n'.format(
                o,
                ast_node,
                self.as_name(o)
            )
        text += '    ;\n'
        return text
        
    def x3_operator_defines(self, ast_node):
        text = "// operator symbol definition\n"
        ops_list = list(self.operators.keys())
        for n, o in enumerate(ops_list):
            text += self.x3_op_define(o, ast_node)
        return text


## BNF production rules
class vhdl93Bnf:
    bnf_rules = []
    bnf_operators = None

    # initialize private tuple with 'parsed' data
    def __init__(self, snipet):
        name = ""
        rest = ""
        bnf_tuple = collections.namedtuple("BNF_Rule", ["name", "rule"])
        for line in [l for l in snipet.splitlines() if l.strip()]:
            #print(line)
            if "::=" in line:
                # avoid inserting empty (name, rest) tuple
                if name: self.bnf_rules.append(bnf_tuple(name, rest))
                p = line.split("::=", 1)
                name = p[0].strip()
                rest = p[1].strip().rstrip(';')
            else:
                rest += "    " + line.strip().rstrip(';') + '\n'
        self.bnf_operators = Operatorsymbols()

    def x3_rule_id_name(self, name):
        return name + '_class'

    def x3_rule_type_name(self, name):
        return name + '_type'

    def x3_rule_ids(self):
        """
        Create a list over for all X3/BNF rules ID.
        The name scheme is: struct <rule>_class;
        """
        id_list = []
        for t in self.bnf_rules:
            id_list.append(
                """struct {0};""".format(self.x3_rule_id_name(t.name))
            )
        return id_list

    def x3_rule_typedefs(self):
        """
        Create a list over for all X3/BNF rules types.
        The name scheme is: typedef x3::rule<rule_id> rule_type;
        """
        type_list = []
        for p in self.bnf_rules:
            if self.bnf_operators.is_operator(p.name): continue
            type_list.append(
                """typedef x3::rule<{0}> {1};""".format(
                    self.x3_rule_id_name(p.name),
                    self.x3_rule_type_name(p.name))
            )
        return type_list

    def x3_rules(self):
        instance_list = []
        for p in self.bnf_rules:
            if self.bnf_operators.is_operator(p.name): continue
            instance_list.append(
                """{0} const {1} {{ "{2}" }};""".format(
                    self.x3_rule_type_name(p.name),
                    p.name,
                    p.name)
            )
        return instance_list

    def x3_substitute(self, txt):
        sub_dict = {
            " ' "  : " char_('\\'') ", 
            " \" " : " char_('\"') ",
            " # "  : " char_('#') ",
            " . "  : " char_('.') ",
            " , "  : " char_(',') ",
            " ; "  : " char_(';') ",
            " : "  : " char_(':') ",
            " <= " : ' lit("<=") '
        }
        res = ""
        for s in txt.splitlines(True): # preserve newlines
            for i,j in sub_dict.items():
                s = s.replace(i,j)
            res += s
        return res

    def x3_definition(self):
        definitions = []
        for d in self.bnf_rules:
            if self.bnf_operators.is_operator(d.name): continue
            comment = """// {0} ::= \n""".format(d.name)
            for r in d.rule.splitlines():
                comment += """// {0}\n""".format(r)
            comment = comment[0:-1] # skip last '\n'
            definition = """
#if 0
{0}
auto const {1}_def = 
    {2}
    ;
#endif""".format(
            comment,
            d.name, 
            self.x3_substitute(d.rule))
            
            definitions.append(definition)
        return definitions

    def x3_declare_macro(self):
        decl_macro = []
        for r in self.bnf_rules:
            if self.bnf_operators.is_operator(r.name): continue
            decl_macro.append("""BOOST_SPIRIT_DECLARE({0});""".format(
                self.x3_rule_type_name(r.name))
            )
        return decl_macro

    def x3_define_macro(self):
        def_macro = ['BOOST_SPIRIT_DEFINE(']
        for n, p in enumerate(self.bnf_rules):
            if self.bnf_operators.is_operator(p.name): continue
            if n != len(self.bnf_rules) - 1:
                def_macro.append("""//    {0},""".format(p.name))
            else:
                def_macro.append("""//    {0}""".format(p.name))
        def_macro.append(");")
        return def_macro


## main
class x3_vhdl93:
    keywords = None
    grammar  = None
    def_ns   = []

    def __init__(self):
        self.keywords = vhdl93Keywords(vhdl93_words)
        self.grammar  = vhdl93Bnf(vhdl93_ebnf)
        #self.operators = Operatorsymbols()
        self.def_ns   = ['eda', 'vhdl93']

    def embrace_ns(self, contents, ns):
        """
        embrace the given (string) contents with the given namespace 'ns'
        """
        top = ""
        for n in ns: top += "namespace {0} {{ ".format(n)
        btm = ""
        for n in ns: btm += "} "
        btm += "// namespace "
        # add ns path comment
        for n in ns: btm += "{0}.".format(n)
        return top.strip() + '\n' + contents + btm.rstrip('.') + '\n'

    def generate_keywords(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.keywords.x3(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_rule_ids(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_rule_ids(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_typedefs(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_rule_typedefs(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_rules(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_rules(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_definitions(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_definition(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_define_macros(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_define_macro(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_declare_macros(self, in_ns=True):
        contents = ""
        ns = self.def_ns + ["parser"]
        for k in self.grammar.x3_declare_macro(): contents += k + '\n'
        if in_ns: return self.embrace_ns(contents, ns)
        else:     return contents

    def generate_call_declaration(self, in_ns=True):
        contents = ""
        ns = "parser"
        for t in self.grammar.bnf_rules:
            contents += "{0}::{1} const& {2}();\n".format(
                ns,
                self.grammar.x3_rule_type_name(t.name),
                t.name
            )
        if in_ns: return self.embrace_ns(contents, self.def_ns)
        else:     return contents

    def generate_keywords(self, in_ns=True):
        contents = ""
        ns = "parser"
        for k in self.keywords.x3():
            contents += "{0}\n".format(k)
        if in_ns: return self.embrace_ns(contents, self.def_ns)
        else:     return contents
    
    def generate_call_definition(self, in_ns=True):
        contents = ""
        ns = "parser"
        for t in self.grammar.bnf_rules:
            contents += """
#if 0
{0}::{1} const& {2}() {{
    return {0}::{2};
}}
#endif
""".format(
                ns,
                self.grammar.x3_rule_type_name(t.name),
                t.name
            )
        if in_ns: return self.embrace_ns(contents, self.def_ns)
        else:     return contents

    def generate_x3(self):
        ast_operator_enums = """
/*
 * VHDL93 AST
 */
 {0}
""".format(
            self.embrace_ns(
                self.grammar.bnf_operators.enum_class(), 
                self.def_ns + ['ast']
            )
        )
        
        header = """
/*
 * VHDL93 Grammar {0}
 */
"""
        decls = '\n'
        decls += 'namespace x3 = boost::spirit::x3;\n\n'
        decls += '// Parser Rule IDs\n'
        decls += self.generate_rule_ids(False) + '\n'
        decls += '// Parser Rule Types\n'
        decls += self.generate_typedefs(False) + '\n'
        decls = header.format('Declaration') + self.embrace_ns(decls, self.def_ns + ['parser'])
        
        defs = '\n'
        defs += 'namespace x3 = boost::spirit::x3;\n'
        defs += 'namespace ascii = boost::spirit::x3::ascii;\n\n'
        defs += '// Parser Declarations\n'
        defs += self.generate_rules(False) + '\n'
        defs += '// Keywords'
        defs += self.generate_keywords(False) + '\n'
        defs += '//Parser Operator Symbol Declaration\n'
        defs += self.grammar.bnf_operators.x3_operator_declare('ast::operator') + '\n'
        defs += '//Parser Operator Symbol Definition'
        defs += """
void add_keywords() {
static bool once = false;
if(once) { return; }
once = true;
"""
        defs += self.grammar.bnf_operators.x3_operator_defines('ast::operator') + '}\n\n'
        defs += '// Parser Definitions\n'
        defs += self.generate_definitions(False) + '\n'
        defs += '// Parser Defines\n'
        defs += self.generate_define_macros(False) + '\n'
        defs = header.format('Definition') + self.embrace_ns(defs, self.def_ns + ['parser'])
        
        return ast_operator_enums + decls + defs
        
    def generate_x3_api(self):
        header = """
/*
 * VHDL93 Grammar Test Bench API {0}
 */
"""
        # declaration has nested namespaces
        decls = '\n'
        decls += self.generate_declare_macros(False) # ns eda.vhdl.parser
        decls = self.embrace_ns(decls, ['parser'])
        decls += '\n'
        decls += self.generate_call_declaration(False) # ns eda.vhdl
        decls = header.format('Declaration') + self.embrace_ns(decls, self.def_ns)
        # definitions hasn't nested namespaces
        defs = '\n'
        defs += self.generate_call_definition() 
        defs = header.format('Definition') + defs
        
        return decls + defs
    
    def generate(self):
        # grammar decl/def
        print(self.generate_x3())
        
        # test bench related stuff
        print(self.generate_x3_api())

if __name__ == "__main__":
    x3 = x3_vhdl93()
    x3.generate()