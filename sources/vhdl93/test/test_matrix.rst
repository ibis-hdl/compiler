
================
abstract_literal
================

+---------------------+----------------+-----------------------------------------+
| File                | Input          | Expected                                |
+---------------------+----------------+-----------------------------------------+
| based_literal_001   | 16#00_FF#      | (abstract_literal<v>                    |
|                     |                |   (based_literal                        |
|                     |                |     base: 16, number: 00_FF             |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| based_literal_002   | 016#00_FF#e-42 | (abstract_literal<v>                    |
|                     |                |   (based_literal                        |
|                     |                |     base: 016, number: 00_FF, exp: e-42 |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| decimal_literal_001 | 1              | (abstract_literal<v>                    |
|                     |                |   (decimal_literal                      |
|                     |                |     literal: 1, hint: int               |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| decimal_literal_002 | 1_000          | (abstract_literal<v>                    |
|                     |                |   (decimal_literal                      |
|                     |                |     literal: 1_000, hint: int           |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| decimal_literal_003 | 1e3            | (abstract_literal<v>                    |
|                     |                |   (decimal_literal                      |
|                     |                |     literal: 1e3, hint: int             |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| decimal_literal_004 | 42.42          | (abstract_literal<v>                    |
|                     |                |   (decimal_literal                      |
|                     |                |     literal: 42.42, hint: double        |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+
| decimal_literal_005 | 42.42e42       | (abstract_literal<v>                    |
|                     |                |   (decimal_literal                      |
|                     |                |     literal: 42.42e42, hint: double     |
|                     |                |   )                                     |
|                     |                | )                                       |
|                     |                |                                         |
+---------------------+----------------+-----------------------------------------+

=============
based_literal
=============

+-------------------+---------------------------------+----------------------------------------------+
| File              | Input                           | Expected                                     |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_001 | -- Integer literal of value 255 | (based_literal                               |
|                   | 2#1111_1111#                    |   base: 2, number: 1111_1111                 |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_002 | -- Integer literal of value 255 | (based_literal                               |
|                   | 16#FF#                          |   base: 16, number: FF                       |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_003 | -- Integer literal of value 255 | (based_literal                               |
|                   | 016#0_FF#                       |   base: 016, number: 0_FF                    |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_004 | -- Integer literal of value 224 | (based_literal                               |
|                   | 16#E#E1                         |   base: 16, number: E, exp: E1               |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_005 | -- Integer literal of value 224 | (based_literal                               |
|                   | 2#1110_0000#                    |   base: 2, number: 1110_0000                 |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_006 | -- Real literal of value 4095.0 | (based_literal                               |
|                   | 16#F.FF#E+2                     |   base: 16, number: F.FF, exp: E+2           |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+
| based_literal_007 | -- Real literal of value 4095.0 | (based_literal                               |
|                   | 2#1.1111_1111_111#E11           |   base: 2, number: 1.1111_1111_111, exp: E11 |
|                   |                                 | )                                            |
|                   |                                 |                                              |
+-------------------+---------------------------------+----------------------------------------------+

==================
bit_string_literal
==================

+------------------------+-------------------+--------------------------------------+
| File                   | Input             | Expected                             |
+------------------------+-------------------+--------------------------------------+
| bit_string_literal_001 | B"1111_1111_1111" | (bit_string_literal                  |
|                        |                   |   base: BIN, literal: 1111_1111_1111 |
|                        |                   | )                                    |
|                        |                   |                                      |
+------------------------+-------------------+--------------------------------------+
| bit_string_literal_002 | X"FFF"            | (bit_string_literal                  |
|                        |                   |   base: HEX, literal: FFF            |
|                        |                   | )                                    |
|                        |                   |                                      |
+------------------------+-------------------+--------------------------------------+
| bit_string_literal_003 | O"777"            | (bit_string_literal                  |
|                        |                   |   base: OCT, literal: 777            |
|                        |                   | )                                    |
|                        |                   |                                      |
+------------------------+-------------------+--------------------------------------+

=================
character_literal
=================

+-----------------------+-------+--------------------+
| File                  | Input | Expected           |
+-----------------------+-------+--------------------+
| character_literal_001 | 'X'   | (character_literal |
|                       |       |   'X'              |
|                       |       | )                  |
|                       |       |                    |
+-----------------------+-------+--------------------+
| character_literal_002 | '*'   | (character_literal |
|                       |       |   '*'              |
|                       |       | )                  |
|                       |       |                    |
+-----------------------+-------+--------------------+
| character_literal_003 | '\'   | (character_literal |
|                       |       |   '\'              |
|                       |       | )                  |
|                       |       |                    |
+-----------------------+-------+--------------------+
| character_literal_004 | ' '   | (character_literal |
|                       |       |   ' '              |
|                       |       | )                  |
|                       |       |                    |
+-----------------------+-------+--------------------+

===============
decimal_literal
===============

+---------------------+---------------------------------+-------------------------------------+
| File                | Input                           | Expected                            |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_001 | -- Integer literals             | (decimal_literal                    |
|                     | 12                              |   literal: 12, hint: int            |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_002 | -- Integer literals             | (decimal_literal                    |
|                     | 0                               |   literal: 0, hint: int             |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_003 | -- Integer literals             | (decimal_literal                    |
|                     | 1e6                             |   literal: 1e6, hint: int           |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_004 | -- Integer literals             | (decimal_literal                    |
|                     | 1234_5678                       |   literal: 1234_5678, hint: int     |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_005 | -- Real literals                | (decimal_literal                    |
|                     | 12.0                            |   literal: 12.0, hint: double       |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_006 | -- Real literals                | (decimal_literal                    |
|                     | 0.0                             |   literal: 0.0, hint: double        |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_007 | -- Real literals                | (decimal_literal                    |
|                     | 0.456                           |   literal: 0.456, hint: double      |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_008 | -- Real literals                | (decimal_literal                    |
|                     | 3.14159_26                      |   literal: 3.14159_26, hint: double |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_009 | -- Real literals with exponents | (decimal_literal                    |
|                     | 1.34E-12                        |   literal: 1.34E-12, hint: double   |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_010 | -- Real literals with exponents | (decimal_literal                    |
|                     | 1.0E+6                          |   literal: 1.0E+6, hint: double     |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+
| decimal_literal_011 | -- Real literals with exponents | (decimal_literal                    |
|                     | 6.023E+24                       |   literal: 6.023E+24, hint: double  |
|                     |                                 | )                                   |
|                     |                                 |                                     |
+---------------------+---------------------------------+-------------------------------------+

===========================
enumeration_type_definition
===========================

+---------------------------------+---------------------------------------+------------------------------+
| File                            | Input                                 | Expected                     |
+---------------------------------+---------------------------------------+------------------------------+
| enumeration_type_definition_001 | LOW, HIGH, RISING, FALLING, AMBIGUOUS | (enumeration_type_definition |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (identifier              |
|                                 |                                       |       LOW                    |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (identifier              |
|                                 |                                       |       HIGH                   |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (identifier              |
|                                 |                                       |       RISING                 |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (identifier              |
|                                 |                                       |       FALLING                |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (identifier              |
|                                 |                                       |       AMBIGUOUS              |
|                                 |                                       |     )                        |
|                                 |                                       |   )                          |
|                                 |                                       | )                            |
|                                 |                                       |                              |
+---------------------------------+---------------------------------------+------------------------------+
| enumeration_type_definition_002 | '0','1','X'                           | (enumeration_type_definition |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (character_literal       |
|                                 |                                       |       '0'                    |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (character_literal       |
|                                 |                                       |       '1'                    |
|                                 |                                       |     )                        |
|                                 |                                       |   ),                         |
|                                 |                                       |   (enumeration_literal<v>    |
|                                 |                                       |     (character_literal       |
|                                 |                                       |       'X'                    |
|                                 |                                       |     )                        |
|                                 |                                       |   )                          |
|                                 |                                       | )                            |
|                                 |                                       |                              |
+---------------------------------+---------------------------------------+------------------------------+

==========
expression
==========

+----------------+---------------------------------+--------------------------------------------------------------------+
| File           | Input                           | Expected                                                           |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_001 | "0011" and "0010" and "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   ,                                                                |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_002 | "0011" or  "0010" or  "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: OR,                                                    |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   ,                                                                |
|                |                                 |   operator: OR,                                                    |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_003 | "0011" xor "0010" xor "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: XOR,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   ,                                                                |
|                |                                 |   operator: XOR,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_004 | "0011" xnor "0010" xnor "1000"  | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: XNOR,                                                  |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   ,                                                                |
|                |                                 |   operator: XNOR,                                                  |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_005 | "0011" nand "0010"              | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: NAND,                                                  |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_006 | "0011" nor "0010"               | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: NOR,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_007 | "0011" <= "0010" and "1000"     | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     ),                                                             |
|                |                                 |     operator: LESS_EQUALS,                                         |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_008 | "0011" and "0010" >= "1000"     | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     ),                                                             |
|                |                                 |     operator: GREATER_EQUALS,                                      |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_009 | "0011" SRL "0010" and "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       ),                                                           |
|                |                                 |       operator: SRL,                                               |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_010 | "0011" and "0010" SRL "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       ),                                                           |
|                |                                 |       operator: SRL,                                               |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_011 | "0011" <= "0010" + "1000"       | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     ),                                                             |
|                |                                 |     operator: LESS_EQUALS,                                         |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         operator: ADD,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_012 | "0011" * "0010" and "1000"      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0011                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           ),                                                       |
|                |                                 |           operator: MUL,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 0010                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (string_literal                                      |
|                |                                 |                 1000                                               |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_013 | -42 and 48 or 4711              | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 42, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: AND,                                                   |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 48, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   ,                                                                |
|                |                                 |   operator: OR,                                                    |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 4711, hint: int                       |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_014 | 7**3 or 42                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             primary_lhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 7, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             primary_rhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 3, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   ),                                                               |
|                |                                 |   operator: OR,                                                    |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 42, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_015 | 42 - 5*2                        | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 42, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         operator: SUB,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 5, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           ),                                                       |
|                |                                 |           operator: MUL,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 2, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_016 | 42 - (5*2)                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 42, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         operator: SUB,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 5, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       ),                                           |
|                |                                 |                       operator: MUL,                               |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 2, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_017 | 42 + 10 - 2**3                  | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 42, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         operator: ADD,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 10, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         ,                                                          |
|                |                                 |         operator: SUB,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             primary_lhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 2, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             primary_rhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 3, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_018 | (42)*(42) + ((12 + 12)*(12-12)) | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 42, hint: int             |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           ),                                                       |
|                |                                 |           operator: MUL,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 42, hint: int             |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         ),                                                         |
|                |                                 |         operator: ADD,                                             |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (expression                                |
|                |                                 |                           (relation                                |
|                |                                 |                             (shift_expression                      |
|                |                                 |                               (simple_expression                   |
|                |                                 |                                 term: (term                        |
|                |                                 |                                   (primary<v>                      |
|                |                                 |                                     (literal<v>                    |
|                |                                 |                                       (numeric_literal<v>          |
|                |                                 |                                         (abstract_literal<v>       |
|                |                                 |                                           (decimal_literal         |
|                |                                 |                                             literal: 12, hint: int |
|                |                                 |                                           )                        |
|                |                                 |                                         )                          |
|                |                                 |                                       )                            |
|                |                                 |                                     )                              |
|                |                                 |                                   )                                |
|                |                                 |                                 ),                                 |
|                |                                 |                                 operator: ADD,                     |
|                |                                 |                                 (term                              |
|                |                                 |                                   (primary<v>                      |
|                |                                 |                                     (literal<v>                    |
|                |                                 |                                       (numeric_literal<v>          |
|                |                                 |                                         (abstract_literal<v>       |
|                |                                 |                                           (decimal_literal         |
|                |                                 |                                             literal: 12, hint: int |
|                |                                 |                                           )                        |
|                |                                 |                                         )                          |
|                |                                 |                                       )                            |
|                |                                 |                                     )                              |
|                |                                 |                                   )                                |
|                |                                 |                                 )                                  |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       ),                                           |
|                |                                 |                       operator: MUL,                               |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (expression                                |
|                |                                 |                           (relation                                |
|                |                                 |                             (shift_expression                      |
|                |                                 |                               (simple_expression                   |
|                |                                 |                                 term: (term                        |
|                |                                 |                                   (primary<v>                      |
|                |                                 |                                     (literal<v>                    |
|                |                                 |                                       (numeric_literal<v>          |
|                |                                 |                                         (abstract_literal<v>       |
|                |                                 |                                           (decimal_literal         |
|                |                                 |                                             literal: 12, hint: int |
|                |                                 |                                           )                        |
|                |                                 |                                         )                          |
|                |                                 |                                       )                            |
|                |                                 |                                     )                              |
|                |                                 |                                   )                                |
|                |                                 |                                 ),                                 |
|                |                                 |                                 operator: SUB,                     |
|                |                                 |                                 (term                              |
|                |                                 |                                   (primary<v>                      |
|                |                                 |                                     (literal<v>                    |
|                |                                 |                                       (numeric_literal<v>          |
|                |                                 |                                         (abstract_literal<v>       |
|                |                                 |                                           (decimal_literal         |
|                |                                 |                                             literal: 12, hint: int |
|                |                                 |                                           )                        |
|                |                                 |                                         )                          |
|                |                                 |                                       )                            |
|                |                                 |                                     )                              |
|                |                                 |                                   )                                |
|                |                                 |                                 )                                  |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_019 | -5 mod (-3)                     | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 5, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           ),                                                       |
|                |                                 |           operator: MOD,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 3, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_020 | -(5 mod (-3))                   | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 5, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       ),                                           |
|                |                                 |                       operator: MOD,                               |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (expression                                |
|                |                                 |                           (relation                                |
|                |                                 |                             (shift_expression                      |
|                |                                 |                               (simple_expression                   |
|                |                                 |                                 sign: SIGN_NEG,                    |
|                |                                 |                                 term: (term                        |
|                |                                 |                                   (primary<v>                      |
|                |                                 |                                     (literal<v>                    |
|                |                                 |                                       (numeric_literal<v>          |
|                |                                 |                                         (abstract_literal<v>       |
|                |                                 |                                           (decimal_literal         |
|                |                                 |                                             literal: 3, hint: int  |
|                |                                 |                                           )                        |
|                |                                 |                                         )                          |
|                |                                 |                                       )                            |
|                |                                 |                                     )                              |
|                |                                 |                                   )                                |
|                |                                 |                                 )                                  |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_021 | (-5) mod (-3)                   | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 5, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           ),                                                       |
|                |                                 |           operator: MOD,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 3, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_022 | -16 ** 2                        | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         term: (term                                                |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             primary_lhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 16, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             primary_rhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 2, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_023 | -(16 ** 2)                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         term: (term                                                |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (factor_binary_operation                     |
|                |                                 |                         primary_lhs: (literal<v>                   |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 16, hint: int             |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                         operator: EXPONENT,                        |
|                |                                 |                         primary_rhs: (literal<v>                   |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 2, hint: int              |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+
| expression_024 | (-16) ** 2                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         term: (term                                                |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             primary_lhs: (expression                               |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     term: (term                                    |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 16, hint: int             |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                       )                                            |
|                |                                 |                     )                                              |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             primary_rhs: (literal<v>                               |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 2, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |           )                                                        |
|                |                                 |         )                                                          |
|                |                                 |       )                                                            |
|                |                                 |     )                                                              |
|                |                                 |   )                                                                |
|                |                                 | )                                                                  |
|                |                                 |                                                                    |
+----------------+---------------------------------+--------------------------------------------------------------------+

==================
expression_failure
==================

+------------------------+--------------------------------+--------------------------------------+
| File                   | Input                          | Expected                             |
+------------------------+--------------------------------+--------------------------------------+
| expression_failure_001 | -- not valid VHDL              | In line 2:                           |
|                        | "0011" nand "0010" nand "1000" | Error! Expecting end of input here:  |
|                        |                                | "0011" nand "0010" nand "1000"       |
|                        |                                | ___________________^_                |
|                        |                                |                                      |
+------------------------+--------------------------------+--------------------------------------+
| expression_failure_002 | -- not valid VHDL              | In line 2:                           |
|                        | "0011" nor "0010" nor "1000"   | Error! Expecting end of input here:  |
|                        |                                | "0011" nor "0010" nor "1000"         |
|                        |                                | __________________^_                 |
|                        |                                |                                      |
+------------------------+--------------------------------+--------------------------------------+
| expression_failure_003 | -- not valid VHDL.             | In line 2:                           |
|                        | -5 mod -3                      | Error! Expecting end of input here:  |
|                        |                                | -5 mod -3                            |
|                        |                                | ___^_                                |
|                        |                                |                                      |
+------------------------+--------------------------------+--------------------------------------+

======
factor
======

+-------------------------+---------------------+------------------------------------+
| File                    | Input               | Expected                           |
+-------------------------+---------------------+------------------------------------+
| abs_001                 | abs 42              | (factor<v>                         |
|                         |                     |   (factor_unary_operation          |
|                         |                     |     operator: ABS,                 |
|                         |                     |     primary: (literal<v>           |
|                         |                     |       (numeric_literal<v>          |
|                         |                     |         (abstract_literal<v>       |
|                         |                     |           (decimal_literal         |
|                         |                     |             literal: 42, hint: int |
|                         |                     |           )                        |
|                         |                     |         )                          |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| based_literal_001       | 8#42#               | (factor<v>                         |
|                         |                     |   (primary<v>                      |
|                         |                     |     (literal<v>                    |
|                         |                     |       (numeric_literal<v>          |
|                         |                     |         (abstract_literal<v>       |
|                         |                     |           (based_literal           |
|                         |                     |             base: 8, number: 42    |
|                         |                     |           )                        |
|                         |                     |         )                          |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| basic_identifier_001    | FooBar              | (factor<v>                         |
|                         |                     |   (primary<v>                      |
|                         |                     |     (name<v>                       |
|                         |                     |       (simple_name                 |
|                         |                     |         FooBar                     |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| exponentiation_001      | X"42_FF" ** B"0111" | (factor<v>                         |
|                         |                     |   (factor_binary_operation         |
|                         |                     |     primary_lhs: (literal<v>       |
|                         |                     |       (bit_string_literal          |
|                         |                     |         base: HEX, literal: 42_FF  |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |     operator: EXPONENT,            |
|                         |                     |     primary_rhs: (literal<v>       |
|                         |                     |       (bit_string_literal          |
|                         |                     |         base: BIN, literal: 0111   |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| extended_identifier_001 | \BUS\               | (factor<v>                         |
|                         |                     |   (primary<v>                      |
|                         |                     |     (name<v>                       |
|                         |                     |       (simple_name                 |
|                         |                     |         \BUS\                      |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| not_001                 | not '0'             | (factor<v>                         |
|                         |                     |   (factor_unary_operation          |
|                         |                     |     operator: NOT,                 |
|                         |                     |     primary: (literal<v>           |
|                         |                     |       (enumeration_literal<v>      |
|                         |                     |         (character_literal         |
|                         |                     |           '0'                      |
|                         |                     |         )                          |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+

=============
function_call
=============

+-------------------+---------------------------------------------+-----------------------------------------------+
| File              | Input                                       | Expected                                      |
+-------------------+---------------------------------------------+-----------------------------------------------+
| function_call_001 | the_function_name ( actual_parameter_part ) | (function_call                                |
|                   |                                             |   the_function_name ( actual_parameter_part ) |
|                   |                                             | )                                             |
|                   |                                             |                                               |
+-------------------+---------------------------------------------+-----------------------------------------------+

==========
identifier
==========

+-------------------------+-----------------+-------------------+
| File                    | Input           | Expected          |
+-------------------------+-----------------+-------------------+
| basic_identifier_001    | X               | (identifier       |
|                         |                 |   X               |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_002    | X1              | (identifier       |
|                         |                 |   X1              |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_003    | COUNT           | (identifier       |
|                         |                 |   COUNT           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_004    | STORE_NEXT_ITEM | (identifier       |
|                         |                 |   STORE_NEXT_ITEM |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_005    | c_out           | (identifier       |
|                         |                 |   c_out           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_001 | \Bus\           | (identifier       |
|                         |                 |   \Bus\           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_002 | \Foo\\Bar\      | (identifier       |
|                         |                 |   \Foo\\Bar\      |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_003 | \Foo\\Bar\\Baz\ | (identifier       |
|                         |                 |   \Foo\\Bar\\Baz\ |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_004 | \a\\b\          | (identifier       |
|                         |                 |   \a\\b\          |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| keyword_null_001        | null_server     | (identifier       |
|                         |                 |   null_server     |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| keyword_null_002        | nullify         | (identifier       |
|                         |                 |   nullify         |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| keyword_null_003        | initiallynull   | (identifier       |
|                         |                 |   initiallynull   |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+

==================
identifier_failure
==================

+----------+-------+----------+
| File     | Input | Expected |
+----------+-------+----------+
| null_001 | null  |          |
|          |       |          |
|          |       |          |
+----------+-------+----------+
| null_002 | NULL  |          |
|          |       |          |
+----------+-------+----------+
| null_003 | Null  |          |
|          |       |          |
+----------+-------+----------+

===============
identifier_list
===============

+---------------------+---------------------------------------+---------------------+
| File                | Input                                 | Expected            |
+---------------------+---------------------------------------+---------------------+
| identifier_list_001 | foo, bar, baz                         | (identifier_list    |
|                     |                                       |   (identifier       |
|                     |                                       |     foo             |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     bar             |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     baz             |
|                     |                                       |   )                 |
|                     |                                       | )                   |
|                     |                                       |                     |
+---------------------+---------------------------------------+---------------------+
| identifier_list_002 | \foo\, \bar\, \baz\                   | (identifier_list    |
|                     |                                       |   (identifier       |
|                     |                                       |     \foo\           |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \bar\           |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \baz\           |
|                     |                                       |   )                 |
|                     |                                       | )                   |
|                     |                                       |                     |
+---------------------+---------------------------------------+---------------------+
| identifier_list_003 | foo, \bar\, baz, \Bus\                | (identifier_list    |
|                     |                                       |   (identifier       |
|                     |                                       |     foo             |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \bar\           |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     baz             |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \Bus\           |
|                     |                                       |   )                 |
|                     |                                       | )                   |
|                     |                                       |                     |
+---------------------+---------------------------------------+---------------------+
| identifier_list_004 | Foo, \Foo\\Bar\, \Foo\\Bar\\Baz\, \X\ | (identifier_list    |
|                     |                                       |   (identifier       |
|                     |                                       |     Foo             |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \Foo\\Bar\      |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \Foo\\Bar\\Baz\ |
|                     |                                       |   ),                |
|                     |                                       |   (identifier       |
|                     |                                       |     \X\             |
|                     |                                       |   )                 |
|                     |                                       | )                   |
|                     |                                       |                     |
+---------------------+---------------------------------------+---------------------+

=======
integer
=======

+-------------+--------------------+-------------------+
| File        | Input              | Expected          |
+-------------+--------------------+-------------------+
| integer_001 | 0                  | (std::string_view |
|             |                    |   0               |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_002 | 1                  | (std::string_view |
|             |                    |   1               |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_003 | 1_000              | (std::string_view |
|             |                    |   1_000           |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_004 | 00_1_000           | (std::string_view |
|             |                    |   00_1_000        |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_005 | 023                | (std::string_view |
|             |                    |   023             |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_006 | -- int32 max       | (std::string_view |
|             | 21_47_48_36_46     |   21_47_48_36_46  |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+
| integer_007 | -- overflows int32 | (std::string_view |
|             | 2_147_483_647      |   2_147_483_647   |
|             |                    | )                 |
|             |                    |                   |
+-------------+--------------------+-------------------+

===============
integer_failure
===============

+---------------------+-------+--------------------------------------+
| File                | Input | Expected                             |
+---------------------+-------+--------------------------------------+
| integer_failure_001 | _42   |                                      |
|                     |       |                                      |
|                     |       |                                      |
+---------------------+-------+--------------------------------------+
| integer_failure_002 | 42_   | In line 1:                           |
|                     |       | Error! Expecting end of input here:  |
|                     |       | 42_                                  |
|                     |       | __^_                                 |
|                     |       |                                      |
+---------------------+-------+--------------------------------------+

=======
literal
=======

+-------------------------+---------------+--------------------------------------------+
| File                    | Input         | Expected                                   |
+-------------------------+---------------+--------------------------------------------+
| based_literal_001       | 8#42#         | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (based_literal                       |
|                         |               |         base: 8, number: 42                |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| based_literal_002       | 16#42#E4      | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (based_literal                       |
|                         |               |         base: 16, number: 42, exp: E4      |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| based_literal_003       | 16#00_FF#     | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (based_literal                       |
|                         |               |         base: 16, number: 00_FF            |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| based_literal_004       | 016#0_FF#e-23 | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (based_literal                       |
|                         |               |         base: 016, number: 0_FF, exp: e-23 |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| basic_identifier_001    | X             | (literal<v>                                |
|                         |               |   (enumeration_literal<v>                  |
|                         |               |     (identifier                            |
|                         |               |       X                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| basic_identifier_002    | X2            | (literal<v>                                |
|                         |               |   (enumeration_literal<v>                  |
|                         |               |     (identifier                            |
|                         |               |       X2                                   |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| basic_identifier_003    | Bar           | (literal<v>                                |
|                         |               |   (enumeration_literal<v>                  |
|                         |               |     (identifier                            |
|                         |               |       Bar                                  |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| bit_string_literal_001  | B"1111"       | (literal<v>                                |
|                         |               |   (bit_string_literal                      |
|                         |               |     base: BIN, literal: 1111               |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| character_literal_001   | 'A'           | (literal<v>                                |
|                         |               |   (enumeration_literal<v>                  |
|                         |               |     (character_literal                     |
|                         |               |       'A'                                  |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| decimal_literal_001     | 42            | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (decimal_literal                     |
|                         |               |         literal: 42, hint: int             |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| decimal_literal_002     | 42e6          | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (decimal_literal                     |
|                         |               |         literal: 42e6, hint: int           |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| decimal_literal_003     | 42.42e-3      | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (abstract_literal<v>                   |
|                         |               |       (decimal_literal                     |
|                         |               |         literal: 42.42e-3, hint: double    |
|                         |               |       )                                    |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| extended_identifier_001 | \Foo\         | (literal<v>                                |
|                         |               |   (enumeration_literal<v>                  |
|                         |               |     (identifier                            |
|                         |               |       \Foo\                                |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| keyword_null            | NULL          | (literal<v>                                |
|                         |               |   (keyword                                 |
|                         |               |     NULL                                   |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| physical_literal_001    | 42 fs         | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (physical_literal                      |
|                         |               |       literal: (abstract_literal<v>        |
|                         |               |         (decimal_literal                   |
|                         |               |           literal: 42, hint: int           |
|                         |               |         )                                  |
|                         |               |       ),                                   |
|                         |               |       unit: fs                             |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| physical_literal_002    | 10#42# ms     | (literal<v>                                |
|                         |               |   (numeric_literal<v>                      |
|                         |               |     (physical_literal                      |
|                         |               |       literal: (abstract_literal<v>        |
|                         |               |         (based_literal                     |
|                         |               |           base: 10, number: 42             |
|                         |               |         )                                  |
|                         |               |       ),                                   |
|                         |               |       unit: ms                             |
|                         |               |     )                                      |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+
| string_literal_001      | "FooBar"      | (literal<v>                                |
|                         |               |   (string_literal                          |
|                         |               |     FooBar                                 |
|                         |               |   )                                        |
|                         |               | )                                          |
|                         |               |                                            |
+-------------------------+---------------+--------------------------------------------+

====
name
====

+-------------------------+--------+----------------+
| File                    | Input  | Expected       |
+-------------------------+--------+----------------+
| basic_identifier_001    | FooBar | (name<v>       |
|                         |        |   (simple_name |
|                         |        |     FooBar     |
|                         |        |   )            |
|                         |        | )              |
|                         |        |                |
+-------------------------+--------+----------------+
| extended_identifier_001 | \BUS\  | (name<v>       |
|                         |        |   (simple_name |
|                         |        |     \BUS\      |
|                         |        |   )            |
|                         |        | )              |
|                         |        |                |
+-------------------------+--------+----------------+

===============
numeric_literal
===============

+----------------------+-----------------+------------------------------------------+
| File                 | Input           | Expected                                 |
+----------------------+-----------------+------------------------------------------+
| based_literal_001    | 8#42#           | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (based_literal                       |
|                      |                 |       base: 8, number: 42                |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| based_literal_002    | 16#42#E4        | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (based_literal                       |
|                      |                 |       base: 16, number: 42, exp: E4      |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| based_literal_003    | 16#00_FF#       | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (based_literal                       |
|                      |                 |       base: 16, number: 00_FF            |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| based_literal_004    | 016#0_FF#e-23   | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (based_literal                       |
|                      |                 |       base: 016, number: 0_FF, exp: e-23 |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| decimal_literal_001  | 1               | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (decimal_literal                     |
|                      |                 |       literal: 1, hint: int              |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| decimal_literal_002  | 42e6            | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (decimal_literal                     |
|                      |                 |       literal: 42e6, hint: int           |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| decimal_literal_003  | 42.42e-3        | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (decimal_literal                     |
|                      |                 |       literal: 42.42e-3, hint: double    |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| decimal_literal_004  | 42.42e-3        | (numeric_literal<v>                      |
|                      |                 |   (abstract_literal<v>                   |
|                      |                 |     (decimal_literal                     |
|                      |                 |       literal: 42.42e-3, hint: double    |
|                      |                 |     )                                    |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| physical_literal_001 | 42 fs           | (numeric_literal<v>                      |
|                      |                 |   (physical_literal                      |
|                      |                 |     literal: (abstract_literal<v>        |
|                      |                 |       (decimal_literal                   |
|                      |                 |         literal: 42, hint: int           |
|                      |                 |       )                                  |
|                      |                 |     ),                                   |
|                      |                 |     unit: fs                             |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| physical_literal_002 | 10#42# ms       | (numeric_literal<v>                      |
|                      |                 |   (physical_literal                      |
|                      |                 |     literal: (abstract_literal<v>        |
|                      |                 |       (based_literal                     |
|                      |                 |         base: 10, number: 42             |
|                      |                 |       )                                  |
|                      |                 |     ),                                   |
|                      |                 |     unit: ms                             |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+
| physical_literal_003 | 2#1111_1111# ms | (numeric_literal<v>                      |
|                      |                 |   (physical_literal                      |
|                      |                 |     literal: (abstract_literal<v>        |
|                      |                 |       (based_literal                     |
|                      |                 |         base: 2, number: 1111_1111       |
|                      |                 |       )                                  |
|                      |                 |     ),                                   |
|                      |                 |     unit: ms                             |
|                      |                 |   )                                      |
|                      |                 | )                                        |
|                      |                 |                                          |
+----------------------+-----------------+------------------------------------------+

================
physical_literal
================

+---------------------+--------------------+---------------------------------------------+
| File                | Input              | Expected                                    |
+---------------------+--------------------+---------------------------------------------+
| based_literal_001   | 16#FF# ns          | (physical_literal                           |
|                     |                    |   literal: (abstract_literal<v>             |
|                     |                    |     (based_literal                          |
|                     |                    |       base: 16, number: FF                  |
|                     |                    |     )                                       |
|                     |                    |   ),                                        |
|                     |                    |   unit: ns                                  |
|                     |                    | )                                           |
|                     |                    |                                             |
+---------------------+--------------------+---------------------------------------------+
| based_literal_002   | 2#1111_1111# d     | (physical_literal                           |
|                     |                    |   literal: (abstract_literal<v>             |
|                     |                    |     (based_literal                          |
|                     |                    |       base: 2, number: 1111_1111            |
|                     |                    |     )                                       |
|                     |                    |   ),                                        |
|                     |                    |   unit: d                                   |
|                     |                    | )                                           |
|                     |                    |                                             |
+---------------------+--------------------+---------------------------------------------+
| based_literal_003   | 10#42# ms          | (physical_literal                           |
|                     |                    |   literal: (abstract_literal<v>             |
|                     |                    |     (based_literal                          |
|                     |                    |       base: 10, number: 42                  |
|                     |                    |     )                                       |
|                     |                    |   ),                                        |
|                     |                    |   unit: ms                                  |
|                     |                    | )                                           |
|                     |                    |                                             |
+---------------------+--------------------+---------------------------------------------+
| based_literal_004   | 016#AFFE.42#E+69 h | (physical_literal                           |
|                     |                    |   literal: (abstract_literal<v>             |
|                     |                    |     (based_literal                          |
|                     |                    |       base: 016, number: AFFE.42, exp: E+69 |
|                     |                    |     )                                       |
|                     |                    |   ),                                        |
|                     |                    |   unit: h                                   |
|                     |                    | )                                           |
|                     |                    |                                             |
+---------------------+--------------------+---------------------------------------------+
| decimal_literal_001 | 100 fs             | (physical_literal                           |
|                     |                    |   literal: (abstract_literal<v>             |
|                     |                    |     (decimal_literal                        |
|                     |                    |       literal: 100, hint: int               |
|                     |                    |     )                                       |
|                     |                    |   ),                                        |
|                     |                    |   unit: fs                                  |
|                     |                    | )                                           |
|                     |                    |                                             |
+---------------------+--------------------+---------------------------------------------+

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

+-------------------------+----------+----------------------------------+
| File                    | Input    | Expected                         |
+-------------------------+----------+----------------------------------+
| based_literal_001       | 8#42#    | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (numeric_literal<v>          |
|                         |          |       (abstract_literal<v>       |
|                         |          |         (based_literal           |
|                         |          |           base: 8, number: 42    |
|                         |          |         )                        |
|                         |          |       )                          |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| basic_identifier_001    | FooBar   | (primary<v>                      |
|                         |          |   (name<v>                       |
|                         |          |     (simple_name                 |
|                         |          |       FooBar                     |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| bit_string_literal_001  | B"1111"  | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (bit_string_literal          |
|                         |          |       base: BIN, literal: 1111   |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| character_literal_001   | 'A'      | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (enumeration_literal<v>      |
|                         |          |       (character_literal         |
|                         |          |         'A'                      |
|                         |          |       )                          |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| decimal_literal_001     | 42       | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (numeric_literal<v>          |
|                         |          |       (abstract_literal<v>       |
|                         |          |         (decimal_literal         |
|                         |          |           literal: 42, hint: int |
|                         |          |         )                        |
|                         |          |       )                          |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| extended_identifier_001 | \BUS\    | (primary<v>                      |
|                         |          |   (name<v>                       |
|                         |          |     (simple_name                 |
|                         |          |       \BUS\                      |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| keyword_null            | NULL     | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (keyword                     |
|                         |          |       NULL                       |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+
| string_literal_001      | "FooBar" | (primary<v>                      |
|                         |          |   (literal<v>                    |
|                         |          |     (string_literal              |
|                         |          |       FooBar                     |
|                         |          |     )                            |
|                         |          |   )                              |
|                         |          | )                                |
|                         |          |                                  |
+-------------------------+----------+----------------------------------+

========
relation
========

+--------------+-----------------------+------------------------------------------+
| File         | Input                 | Expected                                 |
+--------------+-----------------------+------------------------------------------+
| relation_001 | "0111" * 42 < '1'     | (relation                                |
|              |                       |   (shift_expression                      |
|              |                       |     (simple_expression                   |
|              |                       |       term: (term                        |
|              |                       |         (primary<v>                      |
|              |                       |           (literal<v>                    |
|              |                       |             (string_literal              |
|              |                       |               0111                       |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         ),                               |
|              |                       |         operator: MUL,                   |
|              |                       |         (primary<v>                      |
|              |                       |           (literal<v>                    |
|              |                       |             (numeric_literal<v>          |
|              |                       |               (abstract_literal<v>       |
|              |                       |                 (decimal_literal         |
|              |                       |                   literal: 42, hint: int |
|              |                       |                 )                        |
|              |                       |               )                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       )                                  |
|              |                       |     )                                    |
|              |                       |   ),                                     |
|              |                       |   operator: LESS,                        |
|              |                       |   (shift_expression                      |
|              |                       |     (simple_expression                   |
|              |                       |       term: (term                        |
|              |                       |         (primary<v>                      |
|              |                       |           (literal<v>                    |
|              |                       |             (enumeration_literal<v>      |
|              |                       |               (character_literal         |
|              |                       |                 '1'                      |
|              |                       |               )                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       )                                  |
|              |                       |     )                                    |
|              |                       |   )                                      |
|              |                       | )                                        |
|              |                       |                                          |
+--------------+-----------------------+------------------------------------------+
| relation_002 | a + b > c - not "101" | (relation                                |
|              |                       |   (shift_expression                      |
|              |                       |     (simple_expression                   |
|              |                       |       term: (term                        |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (simple_name                 |
|              |                       |               a                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       ),                                 |
|              |                       |       operator: ADD,                     |
|              |                       |       (term                              |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (simple_name                 |
|              |                       |               b                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       )                                  |
|              |                       |     )                                    |
|              |                       |   ),                                     |
|              |                       |   operator: GREATER,                     |
|              |                       |   (shift_expression                      |
|              |                       |     (simple_expression                   |
|              |                       |       term: (term                        |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (simple_name                 |
|              |                       |               c                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       ),                                 |
|              |                       |       operator: SUB,                     |
|              |                       |       (term                              |
|              |                       |         (factor_unary_operation          |
|              |                       |           operator: NOT,                 |
|              |                       |           primary: (literal<v>           |
|              |                       |             (string_literal              |
|              |                       |               101                        |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       )                                  |
|              |                       |     )                                    |
|              |                       |   )                                      |
|              |                       | )                                        |
|              |                       |                                          |
+--------------+-----------------------+------------------------------------------+

================
shift_expression
================

+----------------------------+-------------------+----------------------------------------+
| File                       | Input             | Expected                               |
+----------------------------+-------------------+----------------------------------------+
| shift_expression_names_001 | "1110_1110" sll 1 | (shift_expression                      |
|                            |                   |   (simple_expression                   |
|                            |                   |     term: (term                        |
|                            |                   |       (primary<v>                      |
|                            |                   |         (literal<v>                    |
|                            |                   |           (string_literal              |
|                            |                   |             1110_1110                  |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |       )                                |
|                            |                   |     )                                  |
|                            |                   |   ),                                   |
|                            |                   |   operator: SLL,                       |
|                            |                   |   (simple_expression                   |
|                            |                   |     term: (term                        |
|                            |                   |       (primary<v>                      |
|                            |                   |         (literal<v>                    |
|                            |                   |           (numeric_literal<v>          |
|                            |                   |             (abstract_literal<v>       |
|                            |                   |               (decimal_literal         |
|                            |                   |                 literal: 1, hint: int  |
|                            |                   |               )                        |
|                            |                   |             )                          |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |       )                                |
|                            |                   |     )                                  |
|                            |                   |   )                                    |
|                            |                   | )                                      |
|                            |                   |                                        |
+----------------------------+-------------------+----------------------------------------+
| shift_expression_names_002 | 66**42 ror abs 66 | (shift_expression                      |
|                            |                   |   (simple_expression                   |
|                            |                   |     term: (term                        |
|                            |                   |       (factor_binary_operation         |
|                            |                   |         primary_lhs: (literal<v>       |
|                            |                   |           (numeric_literal<v>          |
|                            |                   |             (abstract_literal<v>       |
|                            |                   |               (decimal_literal         |
|                            |                   |                 literal: 66, hint: int |
|                            |                   |               )                        |
|                            |                   |             )                          |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |         operator: EXPONENT,            |
|                            |                   |         primary_rhs: (literal<v>       |
|                            |                   |           (numeric_literal<v>          |
|                            |                   |             (abstract_literal<v>       |
|                            |                   |               (decimal_literal         |
|                            |                   |                 literal: 42, hint: int |
|                            |                   |               )                        |
|                            |                   |             )                          |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |       )                                |
|                            |                   |     )                                  |
|                            |                   |   ),                                   |
|                            |                   |   operator: ROR,                       |
|                            |                   |   (simple_expression                   |
|                            |                   |     term: (term                        |
|                            |                   |       (factor_unary_operation          |
|                            |                   |         operator: ABS,                 |
|                            |                   |         primary: (literal<v>           |
|                            |                   |           (numeric_literal<v>          |
|                            |                   |             (abstract_literal<v>       |
|                            |                   |               (decimal_literal         |
|                            |                   |                 literal: 66, hint: int |
|                            |                   |               )                        |
|                            |                   |             )                          |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |       )                                |
|                            |                   |     )                                  |
|                            |                   |   )                                    |
|                            |                   | )                                      |
|                            |                   |                                        |
+----------------------------+-------------------+----------------------------------------+

===========
signal_list
===========

+------------------+-----------------+----------------------+
| File             | Input           | Expected             |
+------------------+-----------------+----------------------+
| keyword_001      | others          | (signal_list<v>      |
|                  |                 |   (keyword           |
|                  |                 |     OTHERS           |
|                  |                 |   )                  |
|                  |                 | )                    |
|                  |                 |                      |
+------------------+-----------------+----------------------+
| keyword_002      | ALL             | (signal_list<v>      |
|                  |                 |   (keyword           |
|                  |                 |     ALL              |
|                  |                 |   )                  |
|                  |                 | )                    |
|                  |                 |                      |
+------------------+-----------------+----------------------+
| signal_names_001 | FooBar          | (signal_list<v>      |
|                  |                 |   (signal_list.names |
|                  |                 |     (simple_name     |
|                  |                 |       FooBar         |
|                  |                 |     )                |
|                  |                 |   )                  |
|                  |                 | )                    |
|                  |                 |                      |
+------------------+-----------------+----------------------+
| signal_names_002 | Foo, Bar, \BUS\ | (signal_list<v>      |
|                  |                 |   (signal_list.names |
|                  |                 |     (simple_name     |
|                  |                 |       Foo            |
|                  |                 |     ),               |
|                  |                 |     (simple_name     |
|                  |                 |       Bar            |
|                  |                 |     ),               |
|                  |                 |     (simple_name     |
|                  |                 |       \BUS\          |
|                  |                 |     )                |
|                  |                 |   )                  |
|                  |                 | )                    |
|                  |                 |                      |
+------------------+-----------------+----------------------+

=================
simple_expression
=================

+-----------------------+-------------------+--------------------------------------+
| File                  | Input             | Expected                             |
+-----------------------+-------------------+--------------------------------------+
| simple_expression_001 | not '1'           | (simple_expression                   |
|                       |                   |   term: (term                        |
|                       |                   |     (factor_unary_operation          |
|                       |                   |       operator: NOT,                 |
|                       |                   |       primary: (literal<v>           |
|                       |                   |         (enumeration_literal<v>      |
|                       |                   |           (character_literal         |
|                       |                   |             '1'                      |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     )                                |
|                       |                   |   )                                  |
|                       |                   | )                                    |
|                       |                   |                                      |
+-----------------------+-------------------+--------------------------------------+
| simple_expression_002 | 66**42 * 16#AFFE# | (simple_expression                   |
|                       |                   |   term: (term                        |
|                       |                   |     (factor_binary_operation         |
|                       |                   |       primary_lhs: (literal<v>       |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 66, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |       operator: EXPONENT,            |
|                       |                   |       primary_rhs: (literal<v>       |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 42, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     ),                               |
|                       |                   |     operator: MUL,                   |
|                       |                   |     (primary<v>                      |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (based_literal           |
|                       |                   |               base: 16, number: AFFE |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     )                                |
|                       |                   |   )                                  |
|                       |                   | )                                    |
|                       |                   |                                      |
+-----------------------+-------------------+--------------------------------------+
| simple_expression_003 | -42 * 66          | (simple_expression                   |
|                       | +18 * 88          |   sign: SIGN_NEG,                    |
|                       |                   |   term: (term                        |
|                       |                   |     (primary<v>                      |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 42, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     ),                               |
|                       |                   |     operator: MUL,                   |
|                       |                   |     (primary<v>                      |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 66, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     )                                |
|                       |                   |   ),                                 |
|                       |                   |   operator: ADD,                     |
|                       |                   |   (term                              |
|                       |                   |     (primary<v>                      |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 18, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     ),                               |
|                       |                   |     operator: MUL,                   |
|                       |                   |     (primary<v>                      |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 88, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |     )                                |
|                       |                   |   )                                  |
|                       |                   | )                                    |
|                       |                   |                                      |
+-----------------------+-------------------+--------------------------------------+

===========
simple_name
===========

+-------------------------+-----------------+-------------------+
| File                    | Input           | Expected          |
+-------------------------+-----------------+-------------------+
| basic_identifier_001    | X               | (simple_name      |
|                         |                 |   X               |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_002    | X1              | (simple_name      |
|                         |                 |   X1              |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_003    | COUNT           | (simple_name      |
|                         |                 |   COUNT           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_004    | STORE_NEXT_ITEM | (simple_name      |
|                         |                 |   STORE_NEXT_ITEM |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| basic_identifier_005    | c_out           | (simple_name      |
|                         |                 |   c_out           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_001 | \Bus\           | (simple_name      |
|                         |                 |   \Bus\           |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_002 | \Foo\\Bar\      | (simple_name      |
|                         |                 |   \Foo\\Bar\      |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_003 | \Foo\\Bar\\Baz\ | (simple_name      |
|                         |                 |   \Foo\\Bar\\Baz\ |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+
| extended_identifier_004 | \a\\b\          | (simple_name      |
|                         |                 |   \a\\b\          |
|                         |                 | )                 |
|                         |                 |                   |
+-------------------------+-----------------+-------------------+

==============
string_literal
==============

+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| File               | Input                                                            | Expected                                                         |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_001 | "Both S and Q equal to 1"                                        | (string_literal                                                  |
|                    |                                                                  |   Both S and Q equal to 1                                        |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_002 | "Characters such as $, %, and } are allowed in string literals." | (string_literal                                                  |
|                    |                                                                  |   Characters such as $, %, and } are allowed in string literals. |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_003 | "& ' ( ) * + , - . / : ; < = > | [ ]"                            | (string_literal                                                  |
|                    |                                                                  |   & ' ( ) * + , - . / : ; < = > | [ ]                            |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_004 | "Quotation: ""REPORT..."" is also allowed"                       | (string_literal                                                  |
|                    |                                                                  |   Quotation: "REPORT..." is also allowed                         |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_005 | %see \"LRM 13.10\", it's legal VHDL%                             | (string_literal                                                  |
|                    |                                                                  |   see \"LRM 13.10\", it's legal VHDL                             |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_006 | %Quotation: %%REPORT...%% is also allowed%                       | (string_literal                                                  |
|                    |                                                                  |   Quotation: %REPORT...% is also allowed                         |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_007 | -- empty string literal                                          | (string_literal                                                  |
|                    | ""                                                               |                                                                  |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_008 | -- string literals of length 1                                   | (string_literal                                                  |
|                    | " "                                                              |                                                                  |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_009 | --  string literals of length 1                                  | (string_literal                                                  |
|                    | "A"                                                              |   A                                                              |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+
| string_literal_010 | --  string literals of length 1                                  | (string_literal                                                  |
|                    | """"                                                             |   "                                                              |
|                    |                                                                  | )                                                                |
|                    |                                                                  |                                                                  |
+--------------------+------------------------------------------------------------------+------------------------------------------------------------------+

====
term
====

+------------+-------------------+------------------------------------+
| File       | Input             | Expected                           |
+------------+-------------------+------------------------------------+
| factor_001 | abs 42            | (term                              |
|            |                   |   (factor_unary_operation          |
|            |                   |     operator: ABS,                 |
|            |                   |     primary: (literal<v>           |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 42, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   )                                |
|            |                   | )                                  |
|            |                   |                                    |
+------------+-------------------+------------------------------------+
| term_001   | 42 * 42           | (term                              |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 42, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   ),                               |
|            |                   |   operator: MUL,                   |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 42, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   )                                |
|            |                   | )                                  |
|            |                   |                                    |
+------------+-------------------+------------------------------------+
| term_002   | 42 * 66 * 99      | (term                              |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 42, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   ),                               |
|            |                   |   operator: MUL,                   |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 66, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   ),                               |
|            |                   |   operator: MUL,                   |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 99, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   )                                |
|            |                   | )                                  |
|            |                   |                                    |
+------------+-------------------+------------------------------------+
| term_003   | 66**42 * 16#AFFE# | (term                              |
|            |                   |   (factor_binary_operation         |
|            |                   |     primary_lhs: (literal<v>       |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 66, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |     operator: EXPONENT,            |
|            |                   |     primary_rhs: (literal<v>       |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 42, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   ),                               |
|            |                   |   operator: MUL,                   |
|            |                   |   (primary<v>                      |
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (based_literal           |
|            |                   |             base: 16, number: AFFE |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |   )                                |
|            |                   | )                                  |
|            |                   |                                    |
+------------+-------------------+------------------------------------+

==========
use_clause
==========

+----------------+----------------------------------------------------------------------+----------------------+
| File           | Input                                                                | Expected             |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_001 | use MKS.MEASUREMENTS, STD.STANDARD;                                  | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       MKS            |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       MEASUREMENTS   |
|                |                                                                      |     )                |
|                |                                                                      |   ),                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       STD            |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       STANDARD       |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_002 | use ieee.std_logic_1164.all;                                         | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       ieee           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       std_logic_1164 |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (keyword         |
|                |                                                                      |       ALL            |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_003 | USE ieee.math_real.MATH_PI;                                          | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       ieee           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       math_real      |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       MATH_PI        |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_004 | use IEEE.Std_Logic_1164.Std_ulogic, IEEE.Std_Logic_1164.Rising_edge; | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       IEEE           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       Std_Logic_1164 |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       Std_ulogic     |
|                |                                                                      |     )                |
|                |                                                                      |   ),                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       IEEE           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       Std_Logic_1164 |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (simple_name     |
|                |                                                                      |       Rising_edge    |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
