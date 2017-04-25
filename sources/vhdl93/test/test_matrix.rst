
================
abstract_literal
================

+---------------------+----------------+-----------------------------------------------------------------+
| File                | Input          | Expected                                                        |
+---------------------+----------------+-----------------------------------------------------------------+
| decimal_literal_001 | 1              | (v:abstract_literal=(decimal_literal={l=1, tag=int}))           |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| decimal_literal_002 | 1_000          | (v:abstract_literal=(decimal_literal={l=1_000, tag=int}))       |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| decimal_literal_003 | 1e3            | (v:abstract_literal=(decimal_literal={l=1e3, tag=int}))         |
|                     |                |                                                                 |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| decimal_literal_004 | 42.42          | (v:abstract_literal=(decimal_literal={l=42.42, tag=double}))    |
|                     |                |                                                                 |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| decimal_literal_005 | 42.42e42       | (v:abstract_literal=(decimal_literal={l=42.42e42, tag=double})) |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| based_literal_002   | 016#00_FF#e-42 | (v:abstract_literal=(based_literal={b=016, n=00_FF, e=e-42}))   |
|                     |                |                                                                 |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+
| based_literal_001   | 16#00_FF#      | (v:abstract_literal=(based_literal={b=16, n=00_FF}))            |
|                     |                |                                                                 |
|                     |                |                                                                 |
+---------------------+----------------+-----------------------------------------------------------------+

=============
based_literal
=============

+-------------------+---------------------------------+-------------------------------------------------+
| File              | Input                           | Expected                                        |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_005 | -- Integer literal of value 224 | (based_literal={b=2, n=1110_0000})              |
|                   | 2#1110_0000#                    |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_007 | -- Real literal of value 4095.0 | (based_literal={b=2, n=1.1111_1111_111, e=E11}) |
|                   | 2#1.1111_1111_111#E11           |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_003 | -- Integer literal of value 255 | (based_literal={b=016, n=0_FF})                 |
|                   | 016#0_FF#                       |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_002 | -- Integer literal of value 255 | (based_literal={b=16, n=FF})                    |
|                   | 16#FF#                          |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_001 | -- Integer literal of value 255 | (based_literal={b=2, n=1111_1111})              |
|                   | 2#1111_1111#                    |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_006 | -- Real literal of value 4095.0 | (based_literal={b=16, n=F.FF, e=E+2})           |
|                   | 16#F.FF#E+2                     |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+
| based_literal_004 | -- Integer literal of value 224 | (based_literal={b=16, n=E, e=E1})               |
|                   | 16#E#E1                         |                                                 |
|                   |                                 |                                                 |
|                   |                                 |                                                 |
+-------------------+---------------------------------+-------------------------------------------------+

==================
bit_string_literal
==================

+------------------------+-------------------+--------------------------------------------------+
| File                   | Input             | Expected                                         |
+------------------------+-------------------+--------------------------------------------------+
| bit_string_literal_001 | B"1111_1111_1111" | (bit_string_literal={l=1111_1111_1111, tag=bin}) |
|                        |                   |                                                  |
|                        |                   |                                                  |
+------------------------+-------------------+--------------------------------------------------+
| bit_string_literal_003 | O"777"            | (bit_string_literal={l=777, tag=oct})            |
|                        |                   |                                                  |
+------------------------+-------------------+--------------------------------------------------+
| bit_string_literal_002 | X"FFF"            | (bit_string_literal={l=FFF, tag=hex})            |
|                        |                   |                                                  |
|                        |                   |                                                  |
+------------------------+-------------------+--------------------------------------------------+

=================
character_literal
=================

+-----------------------+-------+-----------------------+
| File                  | Input | Expected              |
+-----------------------+-------+-----------------------+
| character_literal_001 | 'X'   | (character_literal=X) |
|                       |       |                       |
|                       |       |                       |
+-----------------------+-------+-----------------------+
| character_literal_002 | '*'   | (character_literal=*) |
|                       |       |                       |
|                       |       |                       |
+-----------------------+-------+-----------------------+
| character_literal_003 | '\'   | (character_literal=\) |
|                       |       |                       |
|                       |       |                       |
+-----------------------+-------+-----------------------+
| character_literal_004 | ' '   | (character_literal= ) |
|                       |       |                       |
|                       |       |                       |
+-----------------------+-------+-----------------------+

===============
decimal_literal
===============

+---------------------+---------------------------------+----------------------------------------------+
| File                | Input                           | Expected                                     |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_009 | -- Real literals with exponents | (decimal_literal={l=1.34E-12, tag=double})   |
|                     | 1.34E-12                        |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_010 | -- Real literals with exponents | (decimal_literal={l=1.0E+6, tag=double})     |
|                     | 1.0E+6                          |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_001 | -- Integer literals             | (decimal_literal={l=12, tag=int})            |
|                     | 12                              |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_002 | -- Integer literals             | (decimal_literal={l=0, tag=int})             |
|                     | 0                               |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_006 | -- Real literals                | (decimal_literal={l=0.0, tag=double})        |
|                     | 0.0                             |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_003 | -- Integer literals             | (decimal_literal={l=1e6, tag=int})           |
|                     | 1e6                             |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_004 | -- Integer literals             | (decimal_literal={l=1234_5678, tag=int})     |
|                     | 1234_5678                       |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_008 | -- Real literals                | (decimal_literal={l=3.14159_26, tag=double}) |
|                     | 3.14159_26                      |                                              |
|                     |                                 |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_005 | -- Real literals                | (decimal_literal={l=12.0, tag=double})       |
|                     | 12.0                            |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_007 | -- Real literals                | (decimal_literal={l=0.456, tag=double})      |
|                     | 0.456                           |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+
| decimal_literal_011 | -- Real literals with exponents | (decimal_literal={l=6.023E+24, tag=double})  |
|                     | 6.023E+24                       |                                              |
|                     |                                 |                                              |
+---------------------+---------------------------------+----------------------------------------------+

===========================
enumeration_type_definition
===========================

+---------------------------------+---------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| File                            | Input                                 | Expected                                                                                                                                                                                                                                             |
+---------------------------------+---------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| enumeration_type_definition_001 | LOW, HIGH, RISING, FALLING, AMBIGUOUS | (enumeration_type_definition=(v:enumeration_literal=(identifier=LOW))(v:enumeration_literal=(identifier=HIGH))(v:enumeration_literal=(identifier=RISING))(v:enumeration_literal=(identifier=FALLING))(v:enumeration_literal=(identifier=AMBIGUOUS))) |
|                                 |                                       |                                                                                                                                                                                                                                                      |
|                                 |                                       |                                                                                                                                                                                                                                                      |
+---------------------------------+---------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| enumeration_type_definition_002 | '0','1','X'                           | (enumeration_type_definition=(v:enumeration_literal=(character_literal=0))(v:enumeration_literal=(character_literal=1))(v:enumeration_literal=(character_literal=X)))                                                                                |
|                                 |                                       |                                                                                                                                                                                                                                                      |
|                                 |                                       |                                                                                                                                                                                                                                                      |
+---------------------------------+---------------------------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

==========
expression
==========

+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| File           | Input                           | Expected                                                                                                               |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_004 | "0011" xnor "0010" xnor "1000"  | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=XNOR                                                                                                          |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=XNOR                                                                                                          |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_022 | -16 ** 2                        | (expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                             |
|                |                                 | (factor_binary_operation={                                                                                             |
|                |                                 | operator=**                                                                                                            |
|                |                                 | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=16, tag=int}))))                     |
|                |                                 | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int}))))                      |
|                |                                 | })})))))                                                                                                               |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_023 | -(16 ** 2)                      | (expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                             |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (factor_binary_operation={                                                                                             |
|                |                                 | operator=**                                                                                                            |
|                |                                 | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=16, tag=int}))))                     |
|                |                                 | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int}))))                      |
|                |                                 | })}))))))})))))                                                                                                        |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_001 | "0011" and "0010" and "1000"    | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_014 | 7**3 or 42                      | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (factor_binary_operation={                                                                                             |
|                |                                 | operator=**                                                                                                            |
|                |                                 | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=7, tag=int}))))                      |
|                |                                 | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=3, tag=int}))))                      |
|                |                                 | })}))))                                                                                                                |
|                |                                 | operator=OR                                                                                                            |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))})))))               |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_002 | "0011" or  "0010" or  "1000"    | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=OR                                                                                                            |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=OR                                                                                                            |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_008 | "0011" and "0010" >= "1000"     | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))})))                                                                      |
|                |                                 | operator=>=                                                                                                            |
|                |                                 | (shift_expression=(simple_expression=(term={                                                                           |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_005 | "0011" nand "0010"              | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=NAND                                                                                                          |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_007 | "0011" <= "0010" and "1000"     | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))})))                                                                      |
|                |                                 | operator=<=                                                                                                            |
|                |                                 | (shift_expression=(simple_expression=(term={                                                                           |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_006 | "0011" nor "0010"               | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=NOR                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_013 | -42 and 48 or 4711              | (expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                             |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))}))))                |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=48, tag=int})))))}))))                |
|                |                                 | operator=OR                                                                                                            |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=4711, tag=int})))))})))))             |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_024 | (-16) ** 2                      | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (factor_binary_operation={                                                                                             |
|                |                                 | operator=**                                                                                                            |
|                |                                 | primary_lhs=(expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                 |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=16, tag=int})))))})))))               |
|                |                                 | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int}))))                      |
|                |                                 | })})))))                                                                                                               |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_009 | "0011" SRL "0010" and "1000"    | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))                                                                       |
|                |                                 | operator=SRL                                                                                                           |
|                |                                 | (simple_expression=(term={                                                                                             |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_017 | 42 + 10 - 2**3                  | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))})                   |
|                |                                 | operator=+(term={                                                                                                      |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=10, tag=int})))))})                   |
|                |                                 | operator=-(term={                                                                                                      |
|                |                                 | (factor_binary_operation={                                                                                             |
|                |                                 | operator=**                                                                                                            |
|                |                                 | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int}))))                      |
|                |                                 | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=3, tag=int}))))                      |
|                |                                 | })})))))                                                                                                               |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_016 | 42 - (5*2)                      | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))})                   |
|                |                                 | operator=-(term={                                                                                                      |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=5, tag=int})))))                      |
|                |                                 | operator=*                                                                                                             |
|                |                                 | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int})))))}))))))})))))  |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_010 | "0011" and "0010" SRL "1000"    | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))                                                                       |
|                |                                 | operator=SRL                                                                                                           |
|                |                                 | (simple_expression=(term={                                                                                             |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_003 | "0011" xor "0010" xor "1000"    | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))}))))                                                                     |
|                |                                 | operator=XOR                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))}))))                                                                     |
|                |                                 | operator=XOR                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_018 | (42)*(42) + ((12 + 12)*(12-12)) | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))}))))))              |
|                |                                 | operator=*                                                                                                             |
|                |                                 | factor=(v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                   |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))}))))))})            |
|                |                                 | operator=+(term={                                                                                                      |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=12, tag=int})))))})                   |
|                |                                 | operator=+(term={                                                                                                      |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=12, tag=int})))))}))))))              |
|                |                                 | operator=*                                                                                                             |
|                |                                 | factor=(v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                   |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=12, tag=int})))))})                   |
|                |                                 | operator=-(term={                                                                                                      |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=12, tag=int})))))}))))))}))))))}))))) |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_011 | "0011" <= "0010" + "1000"       | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))})))                                                                      |
|                |                                 | operator=<=                                                                                                            |
|                |                                 | (shift_expression=(simple_expression=(term={                                                                           |
|                |                                 | (v:primary=(v:literal=(string_literal=0010)))})                                                                        |
|                |                                 | operator=+(term={                                                                                                      |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_012 | "0011" * "0010" and "1000"      | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(string_literal=0011)))                                                                          |
|                |                                 | operator=*                                                                                                             |
|                |                                 | factor=(v:primary=(v:literal=(string_literal=0010)))}))))                                                              |
|                |                                 | operator=AND                                                                                                           |
|                |                                 | (relation=(shift_expression=(simple_expression=(term={                                                                 |
|                |                                 | (v:primary=(v:literal=(string_literal=1000)))})))))                                                                    |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_020 | -(5 mod (-3))                   | (expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                             |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=(term={                                          |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=5, tag=int})))))                      |
|                |                                 | operator=MOD                                                                                                           |
|                |                                 | factor=(v:primary=(expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                           |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=3, tag=int})))))}))))))}))))))})))))  |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_021 | (-5) mod (-3)                   | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                  |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=5, tag=int})))))}))))))               |
|                |                                 | operator=MOD                                                                                                           |
|                |                                 | factor=(v:primary=(expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                           |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=3, tag=int})))))}))))))})))))         |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_019 | -5 mod (-3)                     | (expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                                             |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=5, tag=int})))))                      |
|                |                                 | operator=MOD                                                                                                           |
|                |                                 | factor=(v:primary=(expression=(relation=(shift_expression=(simple_expression=sign=-, (term={                           |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=3, tag=int})))))}))))))})))))         |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+
| expression_015 | 42 - 5*2                        | (expression=(relation=(shift_expression=(simple_expression=(term={                                                     |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))})                   |
|                |                                 | operator=-(term={                                                                                                      |
|                |                                 | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=5, tag=int})))))                      |
|                |                                 | operator=*                                                                                                             |
|                |                                 | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=2, tag=int})))))})))))         |
+----------------+---------------------------------+------------------------------------------------------------------------------------------------------------------------+

==================
expression_failure
==================

+------------------------+--------------------------------+----------+
| File                   | Input                          | Expected |
+------------------------+--------------------------------+----------+
| expression_failure_002 | -- not valid VHDL              |          |
|                        | "0011" nor "0010" nor "1000"   |          |
+------------------------+--------------------------------+----------+
| expression_failure_001 | -- not valid VHDL              |          |
|                        | "0011" nand "0010" nand "1000" |          |
+------------------------+--------------------------------+----------+
| expression_failure_003 | -- not valid VHDL.             |          |
|                        | -5 mod -3                      |          |
+------------------------+--------------------------------+----------+

======
factor
======

+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| File                    | Input               | Expected                                                                                                |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| extended_identifier_001 | \BUS\               | (v:factor=(v:primary=(v:name=(simple_name=\BUS\))))                                                     |
|                         |                     |                                                                                                         |
|                         |                     |                                                                                                         |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| basic_identifier_001    | FooBar              | (v:factor=(v:primary=(v:name=(simple_name=FooBar))))                                                    |
|                         |                     |                                                                                                         |
|                         |                     |                                                                                                         |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| abs_001                 | abs 42              | (v:factor=(factor_unary_operation={                                                                     |
|                         |                     | operator=ABS                                                                                            |
|                         |                     | primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))          |
|                         |                     | }))                                                                                                     |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| based_literal_001       | 8#42#               | (v:factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=8, n=42})))))) |
|                         |                     |                                                                                                         |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| not_001                 | not '0'             | (v:factor=(factor_unary_operation={                                                                     |
|                         |                     | operator=NOT                                                                                            |
|                         |                     | primary=(v:literal=(v:enumeration_literal=(character_literal=0)))                                       |
|                         |                     | }))                                                                                                     |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+
| exponentiation_001      | X"42_FF" ** B"0111" | (v:factor=(factor_binary_operation={                                                                    |
|                         |                     | operator=**                                                                                             |
|                         |                     | primary_lhs=(v:literal=(bit_string_literal={l=42_FF, tag=hex}))                                         |
|                         |                     | primary_rhs=(v:literal=(bit_string_literal={l=0111, tag=bin}))                                          |
|                         |                     | }))                                                                                                     |
+-------------------------+---------------------+---------------------------------------------------------------------------------------------------------+

==========
identifier
==========

+-------------------------+-----------------+------------------------------+
| File                    | Input           | Expected                     |
+-------------------------+-----------------+------------------------------+
| keyword_null_002        | nullify         | (identifier=nullify)         |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| extended_identifier_001 | \Bus\           | (identifier=\Bus\)           |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| extended_identifier_003 | \Foo\\Bar\\Baz\ | (identifier=\Foo\\Bar\\Baz\) |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| basic_identifier_003    | COUNT           | (identifier=COUNT)           |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| basic_identifier_001    | X               | (identifier=X)               |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| keyword_null_003        | initiallynull   | (identifier=initiallynull)   |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| keyword_null_001        | null_server     | (identifier=null_server)     |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| basic_identifier_004    | STORE_NEXT_ITEM | (identifier=STORE_NEXT_ITEM) |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| extended_identifier_004 | \a\\b\          | (identifier=\a\\b\)          |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| basic_identifier_005    | c_out           | (identifier=c_out)           |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| basic_identifier_002    | X1              | (identifier=X1)              |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+
| extended_identifier_002 | \Foo\\Bar\      | (identifier=\Foo\\Bar\)      |
|                         |                 |                              |
|                         |                 |                              |
+-------------------------+-----------------+------------------------------+

==================
identifier_failure
==================

+----------+-------+----------+
| File     | Input | Expected |
+----------+-------+----------+
| null_003 | Null  |          |
|          |       |          |
+----------+-------+----------+
| null_002 | NULL  |          |
|          |       |          |
+----------+-------+----------+
| null_001 | null  |          |
|          |       |          |
|          |       |          |
+----------+-------+----------+

===============
identifier_list
===============

+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+
| File                | Input                                 | Expected                                                                                              |
+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+
| identifier_list_001 | foo, bar, baz                         | (identifier_list=(identifier=foo)(identifier=bar)(identifier=baz))                                    |
|                     |                                       |                                                                                                       |
|                     |                                       |                                                                                                       |
+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+
| identifier_list_004 | Foo, \Foo\\Bar\, \Foo\\Bar\\Baz\, \X\ | (identifier_list=(identifier=Foo)(identifier=\Foo\\Bar\)(identifier=\Foo\\Bar\\Baz\)(identifier=\X\)) |
|                     |                                       |                                                                                                       |
|                     |                                       |                                                                                                       |
+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+
| identifier_list_003 | foo, \bar\, baz, \Bus\                | (identifier_list=(identifier=foo)(identifier=\bar\)(identifier=baz)(identifier=\Bus\))                |
|                     |                                       |                                                                                                       |
|                     |                                       |                                                                                                       |
+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+
| identifier_list_002 | \foo\, \bar\, \baz\                   | (identifier_list=(identifier=\foo\)(identifier=\bar\)(identifier=\baz\))                              |
|                     |                                       |                                                                                                       |
|                     |                                       |                                                                                                       |
+---------------------+---------------------------------------+-------------------------------------------------------------------------------------------------------+

=======
integer
=======

+-------------+--------------------+-----------------------------------+
| File        | Input              | Expected                          |
+-------------+--------------------+-----------------------------------+
| integer_007 | -- overflows int32 | (std::string_view=2_147_483_647)  |
|             | 2_147_483_647      |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_001 | 0                  | (std::string_view=0)              |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_004 | 00_1_000           | (std::string_view=00_1_000)       |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_003 | 1_000              | (std::string_view=1_000)          |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_002 | 1                  | (std::string_view=1)              |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_005 | 023                | (std::string_view=023)            |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+
| integer_006 | -- int32 max       | (std::string_view=21_47_48_36_46) |
|             | 21_47_48_36_46     |                                   |
|             |                    |                                   |
|             |                    |                                   |
+-------------+--------------------+-----------------------------------+

===============
integer_failure
===============

+---------------------+-------+--------------------------------------+
| File                | Input | Expected                             |
+---------------------+-------+--------------------------------------+
| integer_failure_002 | 42_   | In line 1:                           |
|                     |       | Error! Expecting end of input here:  |
|                     |       | 42_                                  |
|                     |       | __^_                                 |
|                     |       |                                      |
+---------------------+-------+--------------------------------------+
| integer_failure_001 | _42   |                                      |
|                     |       |                                      |
|                     |       |                                      |
+---------------------+-------+--------------------------------------+

=======
literal
=======

+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| File                    | Input         | Expected                                                                                                            |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| extended_identifier_001 | \Foo\         | (v:literal=(v:enumeration_literal=(identifier=\Foo\)))                                                              |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| decimal_literal_001     | 42            | (v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))                              |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| decimal_literal_002     | 42e6          | (v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42e6, tag=int}))))                            |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| physical_literal_001    | 42 fs         | (v:literal=(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(decimal_literal={l=42, tag=int})), u=fs}))) |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| bit_string_literal_001  | B"1111"       | (v:literal=(bit_string_literal={l=1111, tag=bin}))                                                                  |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| basic_identifier_003    | Bar           | (v:literal=(v:enumeration_literal=(identifier=Bar)))                                                                |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| basic_identifier_001    | X             | (v:literal=(v:enumeration_literal=(identifier=X)))                                                                  |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| decimal_literal_003     | 42.42e-3      | (v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42.42e-3, tag=double}))))                     |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| character_literal_001   | 'A'           | (v:literal=(v:enumeration_literal=(character_literal=A)))                                                           |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| based_literal_003       | 16#00_FF#     | (v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=00_FF}))))                                |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| based_literal_002       | 16#42#E4      | (v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=42, e=E4}))))                             |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| basic_identifier_002    | X2            | (v:literal=(v:enumeration_literal=(identifier=X2)))                                                                 |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| keyword_null            | NULL          | (v:literal=(keyword=NULL))                                                                                          |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| based_literal_001       | 8#42#         | (v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=8, n=42}))))                                    |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| string_literal_001      | "FooBar"      | (v:literal=(string_literal=FooBar))                                                                                 |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| physical_literal_002    | 10#42# ms     | (v:literal=(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=10, n=42})), u=ms})))      |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+
| based_literal_004       | 016#0_FF#e-23 | (v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=016, n=0_FF, e=e-23}))))                        |
|                         |               |                                                                                                                     |
+-------------------------+---------------+---------------------------------------------------------------------------------------------------------------------+

====
name
====

+-------------------------+--------+-------------------------------+
| File                    | Input  | Expected                      |
+-------------------------+--------+-------------------------------+
| extended_identifier_001 | \BUS\  | (v:name=(simple_name=\BUS\))  |
|                         |        |                               |
|                         |        |                               |
+-------------------------+--------+-------------------------------+
| basic_identifier_001    | FooBar | (v:name=(simple_name=FooBar)) |
|                         |        |                               |
|                         |        |                               |
+-------------------------+--------+-------------------------------+

===============
numeric_literal
===============

+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| File                 | Input           | Expected                                                                                                 |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| decimal_literal_001  | 1               | (v:numeric_literal=(v:abstract_literal=(decimal_literal={l=1, tag=int})))                                |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| decimal_literal_002  | 42e6            | (v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42e6, tag=int})))                             |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| physical_literal_003 | 2#1111_1111# ms | (v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=2, n=1111_1111})), u=ms})) |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| physical_literal_001 | 42 fs           | (v:numeric_literal=(physical_literal={l=(v:abstract_literal=(decimal_literal={l=42, tag=int})), u=fs}))  |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| decimal_literal_003  | 42.42e-3        | (v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42.42e-3, tag=double})))                      |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| decimal_literal_004  | 42.42e-3        | (v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42.42e-3, tag=double})))                      |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| based_literal_003    | 16#00_FF#       | (v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=00_FF})))                                 |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| based_literal_002    | 16#42#E4        | (v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=42, e=E4})))                              |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| based_literal_001    | 8#42#           | (v:numeric_literal=(v:abstract_literal=(based_literal={b=8, n=42})))                                     |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| physical_literal_002 | 10#42# ms       | (v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=10, n=42})), u=ms}))       |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+
| based_literal_004    | 016#0_FF#e-23   | (v:numeric_literal=(v:abstract_literal=(based_literal={b=016, n=0_FF, e=e-23})))                         |
|                      |                 |                                                                                                          |
+----------------------+-----------------+----------------------------------------------------------------------------------------------------------+

================
physical_literal
================

+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| File                | Input              | Expected                                                                                    |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| decimal_literal_001 | 100 fs             | (physical_literal={l=(v:abstract_literal=(decimal_literal={l=100, tag=int})), u=fs})        |
|                     |                    |                                                                                             |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| based_literal_003   | 10#42# ms          | (physical_literal={l=(v:abstract_literal=(based_literal={b=10, n=42})), u=ms})              |
|                     |                    |                                                                                             |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| based_literal_002   | 2#1111_1111# d     | (physical_literal={l=(v:abstract_literal=(based_literal={b=2, n=1111_1111})), u=d})         |
|                     |                    |                                                                                             |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| based_literal_001   | 16#FF# ns          | (physical_literal={l=(v:abstract_literal=(based_literal={b=16, n=FF})), u=ns})              |
|                     |                    |                                                                                             |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+
| based_literal_004   | 016#AFFE.42#E+69 h | (physical_literal={l=(v:abstract_literal=(based_literal={b=016, n=AFFE.42, e=E+69})), u=h}) |
|                     |                    |                                                                                             |
+---------------------+--------------------+---------------------------------------------------------------------------------------------+

========================
physical_literal_failure
========================

+----------------------+--------------------+----------+
| File                 | Input              | Expected |
+----------------------+--------------------+----------+
| physical_literal_001 | -- unit is keyword |          |
|                      | abs                |          |
|                      |                    |          |
|                      |                    |          |
+----------------------+--------------------+----------+

=======
primary
=======

+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| File                    | Input    | Expected                                                                                           |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| extended_identifier_001 | \BUS\    | (v:primary=(v:name=(simple_name=\BUS\)))                                                           |
|                         |          |                                                                                                    |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| decimal_literal_001     | 42       | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))) |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| bit_string_literal_001  | B"1111"  | (v:primary=(v:literal=(bit_string_literal={l=1111, tag=bin})))                                     |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| basic_identifier_001    | FooBar   | (v:primary=(v:name=(simple_name=FooBar)))                                                          |
|                         |          |                                                                                                    |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| character_literal_001   | 'A'      | (v:primary=(v:literal=(v:enumeration_literal=(character_literal=A))))                              |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| keyword_null            | NULL     | (v:primary=(v:literal=(keyword=NULL)))                                                             |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| based_literal_001       | 8#42#    | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=8, n=42})))))       |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+
| string_literal_001      | "FooBar" | (v:primary=(v:literal=(string_literal=FooBar)))                                                    |
|                         |          |                                                                                                    |
+-------------------------+----------+----------------------------------------------------------------------------------------------------+

========
relation
========

+--------------+-----------------------+---------------------------------------------------------------------------------------------------------------+
| File         | Input                 | Expected                                                                                                      |
+--------------+-----------------------+---------------------------------------------------------------------------------------------------------------+
| relation_001 | "0111" * 42 < '1'     | (relation=(shift_expression=(simple_expression=(term={                                                        |
|              |                       | (v:primary=(v:literal=(string_literal=0111)))                                                                 |
|              |                       | operator=*                                                                                                    |
|              |                       | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))}))) |
|              |                       | operator=<                                                                                                    |
|              |                       | (shift_expression=(simple_expression=(term={                                                                  |
|              |                       | (v:primary=(v:literal=(v:enumeration_literal=(character_literal=1))))}))))                                    |
+--------------+-----------------------+---------------------------------------------------------------------------------------------------------------+
| relation_002 | a + b > c - not "101" | (relation=(shift_expression=(simple_expression=(term={                                                        |
|              |                       | (v:primary=(v:name=(simple_name=a)))})                                                                        |
|              |                       | operator=+(term={                                                                                             |
|              |                       | (v:primary=(v:name=(simple_name=b)))})))                                                                      |
|              |                       | operator=>                                                                                                    |
|              |                       | (shift_expression=(simple_expression=(term={                                                                  |
|              |                       | (v:primary=(v:name=(simple_name=c)))})                                                                        |
|              |                       | operator=-(term={                                                                                             |
|              |                       | (factor_unary_operation={                                                                                     |
|              |                       | operator=NOT                                                                                                  |
|              |                       | primary=(v:literal=(string_literal=101))                                                                      |
|              |                       | })}))))                                                                                                       |
+--------------+-----------------------+---------------------------------------------------------------------------------------------------------------+

================
shift_expression
================

+----------------------------+-------------------+-------------------------------------------------------------------------------------------------------+
| File                       | Input             | Expected                                                                                              |
+----------------------------+-------------------+-------------------------------------------------------------------------------------------------------+
| shift_expression_names_001 | "1110_1110" sll 1 | (shift_expression=(simple_expression=(term={                                                          |
|                            |                   | (v:primary=(v:literal=(string_literal=1110_1110)))}))                                                 |
|                            |                   | operator=SLL                                                                                          |
|                            |                   | (simple_expression=(term={                                                                            |
|                            |                   | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=1, tag=int})))))}))) |
+----------------------------+-------------------+-------------------------------------------------------------------------------------------------------+
| shift_expression_names_002 | 66**42 ror abs 66 | (shift_expression=(simple_expression=(term={                                                          |
|                            |                   | (factor_binary_operation={                                                                            |
|                            |                   | operator=**                                                                                           |
|                            |                   | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int}))))    |
|                            |                   | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))    |
|                            |                   | })}))                                                                                                 |
|                            |                   | operator=ROR                                                                                          |
|                            |                   | (simple_expression=(term={                                                                            |
|                            |                   | (factor_unary_operation={                                                                             |
|                            |                   | operator=ABS                                                                                          |
|                            |                   | primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int}))))        |
|                            |                   | })})))                                                                                                |
+----------------------------+-------------------+-------------------------------------------------------------------------------------------------------+

===========
signal_list
===========

+------------------+-----------------+-------------------------------------------------------------------------------------------+
| File             | Input           | Expected                                                                                  |
+------------------+-----------------+-------------------------------------------------------------------------------------------+
| keyword_002      | ALL             | (v:signal_list=(keyword=ALL))                                                             |
|                  |                 |                                                                                           |
|                  |                 |                                                                                           |
+------------------+-----------------+-------------------------------------------------------------------------------------------+
| signal_names_002 | Foo, Bar, \BUS\ | (v:signal_list=(signal_list.names=(simple_name=Foo)(simple_name=Bar)(simple_name=\BUS\))) |
|                  |                 |                                                                                           |
+------------------+-----------------+-------------------------------------------------------------------------------------------+
| keyword_001      | others          | (v:signal_list=(keyword=OTHERS))                                                          |
|                  |                 |                                                                                           |
|                  |                 |                                                                                           |
+------------------+-----------------+-------------------------------------------------------------------------------------------+
| signal_names_001 | FooBar          | (v:signal_list=(signal_list.names=(simple_name=FooBar)))                                  |
|                  |                 |                                                                                           |
|                  |                 |                                                                                           |
+------------------+-----------------+-------------------------------------------------------------------------------------------+

=================
simple_expression
=================

+-----------------------+-------------------+--------------------------------------------------------------------------------------------------------------+
| File                  | Input             | Expected                                                                                                     |
+-----------------------+-------------------+--------------------------------------------------------------------------------------------------------------+
| simple_expression_001 | not '1'           | (simple_expression=(term={                                                                                   |
|                       |                   | (factor_unary_operation={                                                                                    |
|                       |                   | operator=NOT                                                                                                 |
|                       |                   | primary=(v:literal=(v:enumeration_literal=(character_literal=1)))                                            |
|                       |                   | })}))                                                                                                        |
+-----------------------+-------------------+--------------------------------------------------------------------------------------------------------------+
| simple_expression_002 | 66**42 * 16#AFFE# | (simple_expression=(term={                                                                                   |
|                       |                   | (factor_binary_operation={                                                                                   |
|                       |                   | operator=**                                                                                                  |
|                       |                   | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int}))))           |
|                       |                   | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))           |
|                       |                   | })                                                                                                           |
|                       |                   | operator=*                                                                                                   |
|                       |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=AFFE})))))}))    |
+-----------------------+-------------------+--------------------------------------------------------------------------------------------------------------+
| simple_expression_003 | -42 * 66          | (simple_expression=sign=-, (term={                                                                           |
|                       | +18 * 88          | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))           |
|                       |                   | operator=*                                                                                                   |
|                       |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int})))))})  |
|                       |                   | operator=+(term={                                                                                            |
|                       |                   | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=18, tag=int})))))           |
|                       |                   | operator=*                                                                                                   |
|                       |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=88, tag=int})))))})) |
+-----------------------+-------------------+--------------------------------------------------------------------------------------------------------------+

===========
simple_name
===========

+-------------------------+-----------------+-------------------------------+
| File                    | Input           | Expected                      |
+-------------------------+-----------------+-------------------------------+
| extended_identifier_001 | \Bus\           | (simple_name=\Bus\)           |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| extended_identifier_003 | \Foo\\Bar\\Baz\ | (simple_name=\Foo\\Bar\\Baz\) |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| basic_identifier_003    | COUNT           | (simple_name=COUNT)           |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| basic_identifier_001    | X               | (simple_name=X)               |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| basic_identifier_004    | STORE_NEXT_ITEM | (simple_name=STORE_NEXT_ITEM) |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| extended_identifier_004 | \a\\b\          | (simple_name=\a\\b\)          |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| basic_identifier_005    | c_out           | (simple_name=c_out)           |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| basic_identifier_002    | X1              | (simple_name=X1)              |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+
| extended_identifier_002 | \Foo\\Bar\      | (simple_name=\Foo\\Bar\)      |
|                         |                 |                               |
|                         |                 |                               |
+-------------------------+-----------------+-------------------------------+

==============
string_literal
==============

+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| File               | Input                                                            | Expected                                                                        |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_009 | --  string literals of length 1                                  | (string_literal=A)                                                              |
|                    | "A"                                                              |                                                                                 |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_007 | -- empty string literal                                          | (string_literal=)                                                               |
|                    | ""                                                               |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_002 | "Characters such as $, %, and } are allowed in string literals." | (string_literal=Characters such as $, %, and } are allowed in string literals.) |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_008 | -- string literals of length 1                                   | (string_literal= )                                                              |
|                    | " "                                                              |                                                                                 |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_006 | %Quotation: %%REPORT...%% is also allowed%                       | (string_literal=Quotation: %REPORT...% is also allowed)                         |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_004 | "Quotation: ""REPORT..."" is also allowed"                       | (string_literal=Quotation: "REPORT..." is also allowed)                         |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_003 | "& ' ( ) * + , - . / : ; < = > | [ ]"                            | (string_literal=& ' ( ) * + , - . / : ; < = > | [ ])                            |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_010 | --  string literals of length 1                                  | (string_literal=")                                                              |
|                    | """"                                                             |                                                                                 |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_005 | %see \"LRM 13.10\", it's legal VHDL%                             | (string_literal=see \"LRM 13.10\", it's legal VHDL)                             |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+
| string_literal_001 | "Both S and Q equal to 1"                                        | (string_literal=Both S and Q equal to 1)                                        |
|                    |                                                                  |                                                                                 |
|                    |                                                                  |                                                                                 |
+--------------------+------------------------------------------------------------------+---------------------------------------------------------------------------------+

====
term
====

+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
| File       | Input             | Expected                                                                                                    |
+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
| term_001   | 42 * 42           | (term={                                                                                                     |
|            |                   | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))          |
|            |                   | operator=*                                                                                                  |
|            |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))}) |
+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
| term_002   | 42 * 66 * 99      | (term={                                                                                                     |
|            |                   | (v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int})))))          |
|            |                   | operator=*                                                                                                  |
|            |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int})))))   |
|            |                   | operator=*                                                                                                  |
|            |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=99, tag=int})))))}) |
+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
| factor_001 | abs 42            | (term={                                                                                                     |
|            |                   | (factor_unary_operation={                                                                                   |
|            |                   | operator=ABS                                                                                                |
|            |                   | primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))              |
|            |                   | })})                                                                                                        |
+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
| term_003   | 66**42 * 16#AFFE# | (term={                                                                                                     |
|            |                   | (factor_binary_operation={                                                                                  |
|            |                   | operator=**                                                                                                 |
|            |                   | primary_lhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=66, tag=int}))))          |
|            |                   | primary_rhs=(v:literal=(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42, tag=int}))))          |
|            |                   | })                                                                                                          |
|            |                   | operator=*                                                                                                  |
|            |                   | factor=(v:primary=(v:literal=(v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=AFFE})))))})    |
+------------+-------------------+-------------------------------------------------------------------------------------------------------------+
