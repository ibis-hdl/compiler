
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

==============
attribute_name
==============

+--------------------+-------------------------------------------------------+---------------------------------------------------+
| File               | Input                                                 | Expected                                          |
+--------------------+-------------------------------------------------------+---------------------------------------------------+
| attribute_name_001 | --  The leftmost index bound of array REG.            | (attribute_name                                   |
|                    | REG'LEFT(1)                                           |   (prefix<v>                                      |
|                    |                                                       |     (name<v>                                      |
|                    |                                                       |       (identifier                                 |
|                    |                                                       |         REG                                       |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (attribute_designator                           |
|                    |                                                       |     (identifier                                   |
|                    |                                                       |       LEFT                                        |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (expression                                     |
|                    |                                                       |     (relation                                     |
|                    |                                                       |       (shift_expression                           |
|                    |                                                       |         (simple_expression                        |
|                    |                                                       |           (term                                   |
|                    |                                                       |             (primary<v>                           |
|                    |                                                       |               (literal<v>                         |
|                    |                                                       |                 (numeric_literal<v>               |
|                    |                                                       |                   (abstract_literal<v>            |
|                    |                                                       |                     (decimal_literal              |
|                    |                                                       |                       literal: 1, hint: int       |
|                    |                                                       |                     )                             |
|                    |                                                       |                   )                               |
|                    |                                                       |                 )                                 |
|                    |                                                       |               )                                   |
|                    |                                                       |             )                                     |
|                    |                                                       |           )                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       | )                                                 |
|                    |                                                       |                                                   |
+--------------------+-------------------------------------------------------+---------------------------------------------------+
| attribute_name_002 | --  The hierarchical path name of the port INPUT_PIN. | (attribute_name                                   |
|                    | INPUT_PIN'PATH_NAME                                   |   (prefix<v>                                      |
|                    |                                                       |     (name<v>                                      |
|                    |                                                       |       (identifier                                 |
|                    |                                                       |         INPUT_PIN                                 |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (attribute_designator                           |
|                    |                                                       |     (identifier                                   |
|                    |                                                       |       PATH_NAME                                   |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       | )                                                 |
|                    |                                                       |                                                   |
+--------------------+-------------------------------------------------------+---------------------------------------------------+
| attribute_name_003 | --  The signal CLK delayed by 5 ns.                   | (attribute_name                                   |
|                    | CLK'DELAYED(5 ns)                                     |   (prefix<v>                                      |
|                    |                                                       |     (name<v>                                      |
|                    |                                                       |       (identifier                                 |
|                    |                                                       |         CLK                                       |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (attribute_designator                           |
|                    |                                                       |     (identifier                                   |
|                    |                                                       |       DELAYED                                     |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (expression                                     |
|                    |                                                       |     (relation                                     |
|                    |                                                       |       (shift_expression                           |
|                    |                                                       |         (simple_expression                        |
|                    |                                                       |           (term                                   |
|                    |                                                       |             (primary<v>                           |
|                    |                                                       |               (literal<v>                         |
|                    |                                                       |                 (numeric_literal<v>               |
|                    |                                                       |                   (physical_literal               |
|                    |                                                       |                     literal: (abstract_literal<v> |
|                    |                                                       |                       (decimal_literal            |
|                    |                                                       |                         literal: 5, hint: int     |
|                    |                                                       |                       )                           |
|                    |                                                       |                     ),                            |
|                    |                                                       |                     unit: ns                      |
|                    |                                                       |                   )                               |
|                    |                                                       |                 )                                 |
|                    |                                                       |               )                                   |
|                    |                                                       |             )                                     |
|                    |                                                       |           )                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       | )                                                 |
|                    |                                                       |                                                   |
+--------------------+-------------------------------------------------------+---------------------------------------------------+
| attribute_name_004 | -- test for signature parser check                    | (attribute_name                                   |
|                    | Foo [A, B return C]'Buzz(42)                          |   (prefix<v>                                      |
|                    |                                                       |     (name<v>                                      |
|                    |                                                       |       (identifier                                 |
|                    |                                                       |         Foo                                       |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (signature                                      |
|                    |                                                       |     (signature.parameter_type(s)                  |
|                    |                                                       |       (name<v>                                    |
|                    |                                                       |         (identifier                               |
|                    |                                                       |           A                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       ),                                          |
|                    |                                                       |       (name<v>                                    |
|                    |                                                       |         (identifier                               |
|                    |                                                       |           B                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |     (signature.return_type                        |
|                    |                                                       |       (name<v>                                    |
|                    |                                                       |         (identifier                               |
|                    |                                                       |           C                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (attribute_designator                           |
|                    |                                                       |     (identifier                                   |
|                    |                                                       |       Buzz                                        |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       |   (expression                                     |
|                    |                                                       |     (relation                                     |
|                    |                                                       |       (shift_expression                           |
|                    |                                                       |         (simple_expression                        |
|                    |                                                       |           (term                                   |
|                    |                                                       |             (primary<v>                           |
|                    |                                                       |               (literal<v>                         |
|                    |                                                       |                 (numeric_literal<v>               |
|                    |                                                       |                   (abstract_literal<v>            |
|                    |                                                       |                     (decimal_literal              |
|                    |                                                       |                       literal: 42, hint: int      |
|                    |                                                       |                     )                             |
|                    |                                                       |                   )                               |
|                    |                                                       |                 )                                 |
|                    |                                                       |               )                                   |
|                    |                                                       |             )                                     |
|                    |                                                       |           )                                       |
|                    |                                                       |         )                                         |
|                    |                                                       |       )                                           |
|                    |                                                       |     )                                             |
|                    |                                                       |   )                                               |
|                    |                                                       | )                                                 |
|                    |                                                       |                                                   |
+--------------------+-------------------------------------------------------+---------------------------------------------------+

=======================
attribute_specification
=======================

+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| File                        | Input                                               | Expected                                                 |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_001 | attribute PIN_NO of CIN: signal is 10;              | (attribute_specification                                 |
|                             |                                                     |   (identifier                                            |
|                             |                                                     |     PIN_NO                                               |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (entity_designator                                 |
|                             |                                                     |         (entity_tag<v>                                   |
|                             |                                                     |           (identifier                                    |
|                             |                                                     |             CIN                                          |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       SIGNAL                                             |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (literal<v>                                |
|                             |                                                     |                 (numeric_literal<v>                      |
|                             |                                                     |                   (abstract_literal<v>                   |
|                             |                                                     |                     (decimal_literal                     |
|                             |                                                     |                       literal: 10, hint: int             |
|                             |                                                     |                     )                                    |
|                             |                                                     |                   )                                      |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_002 | -- even on LRM, this isn't a avalid expression:     | (attribute_specification                                 |
|                             | -- attribute LOCATION of ADDER1: label is (10,15);  |   (identifier                                            |
|                             | -- hence fixed to an expression:                    |     LOCATION                                             |
|                             | attribute LOCATION of ADDER1: label is (10 + 15);   |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (entity_designator                                 |
|                             |                                                     |         (entity_tag<v>                                   |
|                             |                                                     |           (identifier                                    |
|                             |                                                     |             ADDER1                                       |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       LABEL                                              |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (expression                                |
|                             |                                                     |                 (relation                                |
|                             |                                                     |                   (shift_expression                      |
|                             |                                                     |                     (simple_expression                   |
|                             |                                                     |                       (term                              |
|                             |                                                     |                         (primary<v>                      |
|                             |                                                     |                           (literal<v>                    |
|                             |                                                     |                             (numeric_literal<v>          |
|                             |                                                     |                               (abstract_literal<v>       |
|                             |                                                     |                                 (decimal_literal         |
|                             |                                                     |                                   literal: 10, hint: int |
|                             |                                                     |                                 )                        |
|                             |                                                     |                               )                          |
|                             |                                                     |                             )                            |
|                             |                                                     |                           )                              |
|                             |                                                     |                         )                                |
|                             |                                                     |                       ),                                 |
|                             |                                                     |                       operator: ADD,                     |
|                             |                                                     |                       (term                              |
|                             |                                                     |                         (primary<v>                      |
|                             |                                                     |                           (literal<v>                    |
|                             |                                                     |                             (numeric_literal<v>          |
|                             |                                                     |                               (abstract_literal<v>       |
|                             |                                                     |                                 (decimal_literal         |
|                             |                                                     |                                   literal: 15, hint: int |
|                             |                                                     |                                 )                        |
|                             |                                                     |                               )                          |
|                             |                                                     |                             )                            |
|                             |                                                     |                           )                              |
|                             |                                                     |                         )                                |
|                             |                                                     |                       )                                  |
|                             |                                                     |                     )                                    |
|                             |                                                     |                   )                                      |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_003 | -- even on LRM, this isn't a avalid expression:     | (attribute_specification                                 |
|                             | -- attribute LOCATION of others: label is (25,77);  |   (identifier                                            |
|                             | -- hence fixed to an expression:                    |     LOCATION                                             |
|                             | attribute LOCATION of others: label is (25 * 77);   |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (keyword                                           |
|                             |                                                     |         OTHERS                                           |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       LABEL                                              |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (expression                                |
|                             |                                                     |                 (relation                                |
|                             |                                                     |                   (shift_expression                      |
|                             |                                                     |                     (simple_expression                   |
|                             |                                                     |                       (term                              |
|                             |                                                     |                         (primary<v>                      |
|                             |                                                     |                           (literal<v>                    |
|                             |                                                     |                             (numeric_literal<v>          |
|                             |                                                     |                               (abstract_literal<v>       |
|                             |                                                     |                                 (decimal_literal         |
|                             |                                                     |                                   literal: 25, hint: int |
|                             |                                                     |                                 )                        |
|                             |                                                     |                               )                          |
|                             |                                                     |                             )                            |
|                             |                                                     |                           )                              |
|                             |                                                     |                         ),                               |
|                             |                                                     |                         operator: MUL,                   |
|                             |                                                     |                         (primary<v>                      |
|                             |                                                     |                           (literal<v>                    |
|                             |                                                     |                             (numeric_literal<v>          |
|                             |                                                     |                               (abstract_literal<v>       |
|                             |                                                     |                                 (decimal_literal         |
|                             |                                                     |                                   literal: 77, hint: int |
|                             |                                                     |                                 )                        |
|                             |                                                     |                               )                          |
|                             |                                                     |                             )                            |
|                             |                                                     |                           )                              |
|                             |                                                     |                         )                                |
|                             |                                                     |                       )                                  |
|                             |                                                     |                     )                                    |
|                             |                                                     |                   )                                      |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_004 |  attribute CAPACITANCE of all: signal is 15 pF;     | (attribute_specification                                 |
|                             |                                                     |   (identifier                                            |
|                             |                                                     |     CAPACITANCE                                          |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (keyword                                           |
|                             |                                                     |         ALL                                              |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       SIGNAL                                             |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (literal<v>                                |
|                             |                                                     |                 (numeric_literal<v>                      |
|                             |                                                     |                   (physical_literal                      |
|                             |                                                     |                     literal: (abstract_literal<v>        |
|                             |                                                     |                       (decimal_literal                   |
|                             |                                                     |                         literal: 15, hint: int           |
|                             |                                                     |                       )                                  |
|                             |                                                     |                     ),                                   |
|                             |                                                     |                     unit: pF                             |
|                             |                                                     |                   )                                      |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_005 | attribute IMPLEMENTATION of G1: group is "74LS152"; | (attribute_specification                                 |
|                             |                                                     |   (identifier                                            |
|                             |                                                     |     IMPLEMENTATION                                       |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (entity_designator                                 |
|                             |                                                     |         (entity_tag<v>                                   |
|                             |                                                     |           (identifier                                    |
|                             |                                                     |             G1                                           |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       GROUP                                              |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (literal<v>                                |
|                             |                                                     |                 (string_literal                          |
|                             |                                                     |                   74LS152                                |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+
| attribute_specification_006 | attribute RISING_DELAY of C2Q: group is 7.2 ns;     | (attribute_specification                                 |
|                             |                                                     |   (identifier                                            |
|                             |                                                     |     RISING_DELAY                                         |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (entity_specification                                  |
|                             |                                                     |     (entity_name_list<v>                                 |
|                             |                                                     |       (entity_designator                                 |
|                             |                                                     |         (entity_tag<v>                                   |
|                             |                                                     |           (identifier                                    |
|                             |                                                     |             C2Q                                          |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |     (keyword                                             |
|                             |                                                     |       GROUP                                              |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     |   (expression                                            |
|                             |                                                     |     (relation                                            |
|                             |                                                     |       (shift_expression                                  |
|                             |                                                     |         (simple_expression                               |
|                             |                                                     |           (term                                          |
|                             |                                                     |             (primary<v>                                  |
|                             |                                                     |               (literal<v>                                |
|                             |                                                     |                 (numeric_literal<v>                      |
|                             |                                                     |                   (physical_literal                      |
|                             |                                                     |                     literal: (abstract_literal<v>        |
|                             |                                                     |                       (decimal_literal                   |
|                             |                                                     |                         literal: 7.2, hint: double       |
|                             |                                                     |                       )                                  |
|                             |                                                     |                     ),                                   |
|                             |                                                     |                     unit: ns                             |
|                             |                                                     |                   )                                      |
|                             |                                                     |                 )                                        |
|                             |                                                     |               )                                          |
|                             |                                                     |             )                                            |
|                             |                                                     |           )                                              |
|                             |                                                     |         )                                                |
|                             |                                                     |       )                                                  |
|                             |                                                     |     )                                                    |
|                             |                                                     |   )                                                      |
|                             |                                                     | )                                                        |
|                             |                                                     |                                                          |
+-----------------------------+-----------------------------------------------------+----------------------------------------------------------+

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

==========
constraint
==========

+----------------------+----------------------------+------------------------------------------+
| File                 | Input                      | Expected                                 |
+----------------------+----------------------------+------------------------------------------+
| index_constraint_001 | -- list of discrete ranges | (constraint<v>                           |
|                      | (lhs, rhs)                 |   (index_constraint                      |
|                      |                            |     (discrete_range<v>                   |
|                      |                            |       (subtype_indication                |
|                      |                            |         (name<v>                         |
|                      |                            |           (identifier                    |
|                      |                            |             lhs                          |
|                      |                            |           )                              |
|                      |                            |         )                                |
|                      |                            |       )                                  |
|                      |                            |     ),                                   |
|                      |                            |     (discrete_range<v>                   |
|                      |                            |       (subtype_indication                |
|                      |                            |         (name<v>                         |
|                      |                            |           (identifier                    |
|                      |                            |             rhs                          |
|                      |                            |           )                              |
|                      |                            |         )                                |
|                      |                            |       )                                  |
|                      |                            |     )                                    |
|                      |                            |   )                                      |
|                      |                            | )                                        |
|                      |                            |                                          |
+----------------------+----------------------------+------------------------------------------+
| range_constraint_001 | RANGE 42 downto 0          | (constraint<v>                           |
|                      |                            |   (range<v>                              |
|                      |                            |     (simple_expression                   |
|                      |                            |       (term                              |
|                      |                            |         (primary<v>                      |
|                      |                            |           (literal<v>                    |
|                      |                            |             (numeric_literal<v>          |
|                      |                            |               (abstract_literal<v>       |
|                      |                            |                 (decimal_literal         |
|                      |                            |                   literal: 42, hint: int |
|                      |                            |                 )                        |
|                      |                            |               )                          |
|                      |                            |             )                            |
|                      |                            |           )                              |
|                      |                            |         )                                |
|                      |                            |       )                                  |
|                      |                            |     )                                    |
|                      |                            |     (keyword                             |
|                      |                            |       DOWNTO                             |
|                      |                            |     )                                    |
|                      |                            |     (simple_expression                   |
|                      |                            |       (term                              |
|                      |                            |         (primary<v>                      |
|                      |                            |           (literal<v>                    |
|                      |                            |             (numeric_literal<v>          |
|                      |                            |               (abstract_literal<v>       |
|                      |                            |                 (decimal_literal         |
|                      |                            |                   literal: 0, hint: int  |
|                      |                            |                 )                        |
|                      |                            |               )                          |
|                      |                            |             )                            |
|                      |                            |           )                              |
|                      |                            |         )                                |
|                      |                            |       )                                  |
|                      |                            |     )                                    |
|                      |                            |   )                                      |
|                      |                            | )                                        |
|                      |                            |                                          |
+----------------------+----------------------------+------------------------------------------+

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

==============
discrete_range
==============

+--------------------+-----------------------------------------------------+------------------------------------------+
| File               | Input                                               | Expected                                 |
+--------------------+-----------------------------------------------------+------------------------------------------+
| discrete_range_001 | -- range                                            | (discrete_range<v>                       |
|                    | 42 downto 0                                         |   (range<v>                              |
|                    |                                                     |     (simple_expression                   |
|                    |                                                     |       (term                              |
|                    |                                                     |         (primary<v>                      |
|                    |                                                     |           (literal<v>                    |
|                    |                                                     |             (numeric_literal<v>          |
|                    |                                                     |               (abstract_literal<v>       |
|                    |                                                     |                 (decimal_literal         |
|                    |                                                     |                   literal: 42, hint: int |
|                    |                                                     |                 )                        |
|                    |                                                     |               )                          |
|                    |                                                     |             )                            |
|                    |                                                     |           )                              |
|                    |                                                     |         )                                |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |     (keyword                             |
|                    |                                                     |       DOWNTO                             |
|                    |                                                     |     )                                    |
|                    |                                                     |     (simple_expression                   |
|                    |                                                     |       (term                              |
|                    |                                                     |         (primary<v>                      |
|                    |                                                     |           (literal<v>                    |
|                    |                                                     |             (numeric_literal<v>          |
|                    |                                                     |               (abstract_literal<v>       |
|                    |                                                     |                 (decimal_literal         |
|                    |                                                     |                   literal: 0, hint: int  |
|                    |                                                     |                 )                        |
|                    |                                                     |               )                          |
|                    |                                                     |             )                            |
|                    |                                                     |           )                              |
|                    |                                                     |         )                                |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |   )                                      |
|                    |                                                     | )                                        |
|                    |                                                     |                                          |
+--------------------+-----------------------------------------------------+------------------------------------------+
| discrete_range_002 | -- subtype_indication (with range constraint)       | (discrete_range<v>                       |
|                    | resolution_function_name type_mark RANGE constraint |   (subtype_indication                    |
|                    |                                                     |     (name<v>                             |
|                    |                                                     |       (identifier                        |
|                    |                                                     |         resolution_function_name         |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |     (name<v>                             |
|                    |                                                     |       (identifier                        |
|                    |                                                     |         type_mark                        |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |     (constraint<v>                       |
|                    |                                                     |       (range<v>                          |
|                    |                                                     |         (name<v>                         |
|                    |                                                     |           (identifier                    |
|                    |                                                     |             constraint                   |
|                    |                                                     |           )                              |
|                    |                                                     |         )                                |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |   )                                      |
|                    |                                                     | )                                        |
|                    |                                                     |                                          |
+--------------------+-----------------------------------------------------+------------------------------------------+
| discrete_range_003 | -- subtype_indication (with range_constraint)       | (discrete_range<v>                       |
|                    | type_mark RANGE constraint                          |   (subtype_indication                    |
|                    |                                                     |     (name<v>                             |
|                    |                                                     |       (identifier                        |
|                    |                                                     |         type_mark                        |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |     (constraint<v>                       |
|                    |                                                     |       (range<v>                          |
|                    |                                                     |         (name<v>                         |
|                    |                                                     |           (identifier                    |
|                    |                                                     |             constraint                   |
|                    |                                                     |           )                              |
|                    |                                                     |         )                                |
|                    |                                                     |       )                                  |
|                    |                                                     |     )                                    |
|                    |                                                     |   )                                      |
|                    |                                                     | )                                        |
|                    |                                                     |                                          |
+--------------------+-----------------------------------------------------+------------------------------------------+

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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_002 | "0011" or  "0010" or  "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_003 | "0011" xor "0010" xor "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_004 | "0011" xnor "0010" xnor "1000"  | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_005 | "0011" nand "0010"              | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_008 | "0011" and "0010" >= "1000"     | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_009 | "0011" SRL "0010" and "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_010 | "0011" and "0010" SRL "1000"    | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_011 | "0011" <= "0010" + "1000"       | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
| expression_013 | -42 and 48 or 4711              | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 7, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             (literal<v>                                            |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |         (term                                                      |
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
|                |                                 |                     (term                                          |
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
|                |                                 |         (term                                                      |
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
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 2, hint: int                          |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
|                |                                 |             (literal<v>                                            |
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
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     (term                                          |
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
|                |                                 |                     (term                                          |
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
|                |                                 |                     (term                                          |
|                |                                 |                       (primary<v>                                  |
|                |                                 |                         (expression                                |
|                |                                 |                           (relation                                |
|                |                                 |                             (shift_expression                      |
|                |                                 |                               (simple_expression                   |
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
|                |                                 |           operator: MOD,                                           |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     (term                                          |
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
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     (term                                          |
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
|                |                                 |                                 (term                              |
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
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     (term                                          |
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
|                |                                 |                     (term                                          |
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
|                |                                 |         (term                                                      |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             (literal<v>                                            |
|                |                                 |               (numeric_literal<v>                                  |
|                |                                 |                 (abstract_literal<v>                               |
|                |                                 |                   (decimal_literal                                 |
|                |                                 |                     literal: 16, hint: int                         |
|                |                                 |                   )                                                |
|                |                                 |                 )                                                  |
|                |                                 |               )                                                    |
|                |                                 |             )                                                      |
|                |                                 |             operator: EXPONENT,                                    |
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
| expression_023 | -(16 ** 2)                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         sign: SIGN_NEG,                                            |
|                |                                 |         (term                                                      |
|                |                                 |           (primary<v>                                              |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     (term                                          |
|                |                                 |                       (factor_binary_operation                     |
|                |                                 |                         (literal<v>                                |
|                |                                 |                           (numeric_literal<v>                      |
|                |                                 |                             (abstract_literal<v>                   |
|                |                                 |                               (decimal_literal                     |
|                |                                 |                                 literal: 16, hint: int             |
|                |                                 |                               )                                    |
|                |                                 |                             )                                      |
|                |                                 |                           )                                        |
|                |                                 |                         )                                          |
|                |                                 |                         operator: EXPONENT,                        |
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
| expression_024 | (-16) ** 2                      | (expression                                                        |
|                |                                 |   (relation                                                        |
|                |                                 |     (shift_expression                                              |
|                |                                 |       (simple_expression                                           |
|                |                                 |         (term                                                      |
|                |                                 |           (factor_binary_operation                                 |
|                |                                 |             (expression                                            |
|                |                                 |               (relation                                            |
|                |                                 |                 (shift_expression                                  |
|                |                                 |                   (simple_expression                               |
|                |                                 |                     sign: SIGN_NEG,                                |
|                |                                 |                     (term                                          |
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
|                         |                     |     (literal<v>                    |
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
|                         |                     |       (identifier                  |
|                         |                     |         FooBar                     |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |   )                                |
|                         |                     | )                                  |
|                         |                     |                                    |
+-------------------------+---------------------+------------------------------------+
| exponentiation_001      | X"42_FF" ** B"0111" | (factor<v>                         |
|                         |                     |   (factor_binary_operation         |
|                         |                     |     (literal<v>                    |
|                         |                     |       (bit_string_literal          |
|                         |                     |         base: HEX, literal: 42_FF  |
|                         |                     |       )                            |
|                         |                     |     )                              |
|                         |                     |     operator: EXPONENT,            |
|                         |                     |     (literal<v>                    |
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
|                         |                     |       (identifier                  |
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
|                         |                     |     (literal<v>                    |
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

+-------------------+---------------------------------------------+-----------------------------+
| File              | Input                                       | Expected                    |
+-------------------+---------------------------------------------+-----------------------------+
| function_call_001 | the_function_name ( actual_parameter_part ) | (function_call              |
|                   |                                             |   (name<v>                  |
|                   |                                             |     (identifier             |
|                   |                                             |       the_function_name     |
|                   |                                             |     )                       |
|                   |                                             |   )                         |
|                   |                                             |   ( actual_parameter_part ) |
|                   |                                             | )                           |
|                   |                                             |                             |
+-------------------+---------------------------------------------+-----------------------------+

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

================
index_constraint
================

+----------------------+---------------------------------------------------------+------------------------------------------------+
| File                 | Input                                                   | Expected                                       |
+----------------------+---------------------------------------------------------+------------------------------------------------+
| index_constraint_001 | -- list of discrete ranges                              | (index_constraint                              |
|                      | (lhs, rhs)                                              |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           lhs                                  |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   ),                                           |
|                      |                                                         |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           rhs                                  |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   )                                            |
|                      |                                                         | )                                              |
|                      |                                                         |                                                |
+----------------------+---------------------------------------------------------+------------------------------------------------+
| index_constraint_002 | -- list of discrete subtype indications                 | (index_constraint                              |
|                      | (type_mark, other_type_mark)                            |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           type_mark                            |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   ),                                           |
|                      |                                                         |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           other_type_mark                      |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   )                                            |
|                      |                                                         | )                                              |
|                      |                                                         |                                                |
+----------------------+---------------------------------------------------------+------------------------------------------------+
| index_constraint_003 | -- list of discrete subtype indications with constrains | (index_constraint                              |
|                      | (foo RANGE 42 downto 0, bar RANGE 69 to 99)             |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           foo                                  |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |       (constraint<v>                           |
|                      |                                                         |         (range<v>                              |
|                      |                                                         |           (simple_expression                   |
|                      |                                                         |             (term                              |
|                      |                                                         |               (primary<v>                      |
|                      |                                                         |                 (literal<v>                    |
|                      |                                                         |                   (numeric_literal<v>          |
|                      |                                                         |                     (abstract_literal<v>       |
|                      |                                                         |                       (decimal_literal         |
|                      |                                                         |                         literal: 42, hint: int |
|                      |                                                         |                       )                        |
|                      |                                                         |                     )                          |
|                      |                                                         |                   )                            |
|                      |                                                         |                 )                              |
|                      |                                                         |               )                                |
|                      |                                                         |             )                                  |
|                      |                                                         |           )                                    |
|                      |                                                         |           (keyword                             |
|                      |                                                         |             DOWNTO                             |
|                      |                                                         |           )                                    |
|                      |                                                         |           (simple_expression                   |
|                      |                                                         |             (term                              |
|                      |                                                         |               (primary<v>                      |
|                      |                                                         |                 (literal<v>                    |
|                      |                                                         |                   (numeric_literal<v>          |
|                      |                                                         |                     (abstract_literal<v>       |
|                      |                                                         |                       (decimal_literal         |
|                      |                                                         |                         literal: 0, hint: int  |
|                      |                                                         |                       )                        |
|                      |                                                         |                     )                          |
|                      |                                                         |                   )                            |
|                      |                                                         |                 )                              |
|                      |                                                         |               )                                |
|                      |                                                         |             )                                  |
|                      |                                                         |           )                                    |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   ),                                           |
|                      |                                                         |   (discrete_range<v>                           |
|                      |                                                         |     (subtype_indication                        |
|                      |                                                         |       (name<v>                                 |
|                      |                                                         |         (identifier                            |
|                      |                                                         |           bar                                  |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |       (constraint<v>                           |
|                      |                                                         |         (range<v>                              |
|                      |                                                         |           (simple_expression                   |
|                      |                                                         |             (term                              |
|                      |                                                         |               (primary<v>                      |
|                      |                                                         |                 (literal<v>                    |
|                      |                                                         |                   (numeric_literal<v>          |
|                      |                                                         |                     (abstract_literal<v>       |
|                      |                                                         |                       (decimal_literal         |
|                      |                                                         |                         literal: 69, hint: int |
|                      |                                                         |                       )                        |
|                      |                                                         |                     )                          |
|                      |                                                         |                   )                            |
|                      |                                                         |                 )                              |
|                      |                                                         |               )                                |
|                      |                                                         |             )                                  |
|                      |                                                         |           )                                    |
|                      |                                                         |           (keyword                             |
|                      |                                                         |             TO                                 |
|                      |                                                         |           )                                    |
|                      |                                                         |           (simple_expression                   |
|                      |                                                         |             (term                              |
|                      |                                                         |               (primary<v>                      |
|                      |                                                         |                 (literal<v>                    |
|                      |                                                         |                   (numeric_literal<v>          |
|                      |                                                         |                     (abstract_literal<v>       |
|                      |                                                         |                       (decimal_literal         |
|                      |                                                         |                         literal: 99, hint: int |
|                      |                                                         |                       )                        |
|                      |                                                         |                     )                          |
|                      |                                                         |                   )                            |
|                      |                                                         |                 )                              |
|                      |                                                         |               )                                |
|                      |                                                         |             )                                  |
|                      |                                                         |           )                                    |
|                      |                                                         |         )                                      |
|                      |                                                         |       )                                        |
|                      |                                                         |     )                                          |
|                      |                                                         |   )                                            |
|                      |                                                         | )                                              |
|                      |                                                         |                                                |
+----------------------+---------------------------------------------------------+------------------------------------------------+

============
indexed_name
============

+------------------+--------------------------------------------+------------------------------------------------+
| File             | Input                                      | Expected                                       |
+------------------+--------------------------------------------+------------------------------------------------+
| indexed_name_001 | --  An element of a one-dimensional array. | (indexed_name                                  |
|                  | REGISTER_ARRAY(5)                          |   (prefix<v>                                   |
|                  |                                            |     (name<v>                                   |
|                  |                                            |       (identifier                              |
|                  |                                            |         REGISTER_ARRAY                         |
|                  |                                            |       )                                        |
|                  |                                            |     )                                          |
|                  |                                            |   )                                            |
|                  |                                            |   (expression                                  |
|                  |                                            |     (relation                                  |
|                  |                                            |       (shift_expression                        |
|                  |                                            |         (simple_expression                     |
|                  |                                            |           (term                                |
|                  |                                            |             (primary<v>                        |
|                  |                                            |               (literal<v>                      |
|                  |                                            |                 (numeric_literal<v>            |
|                  |                                            |                   (abstract_literal<v>         |
|                  |                                            |                     (decimal_literal           |
|                  |                                            |                       literal: 5, hint: int    |
|                  |                                            |                     )                          |
|                  |                                            |                   )                            |
|                  |                                            |                 )                              |
|                  |                                            |               )                                |
|                  |                                            |             )                                  |
|                  |                                            |           )                                    |
|                  |                                            |         )                                      |
|                  |                                            |       )                                        |
|                  |                                            |     )                                          |
|                  |                                            |   )                                            |
|                  |                                            | )                                              |
|                  |                                            |                                                |
+------------------+--------------------------------------------+------------------------------------------------+
| indexed_name_002 | --  An element of a two-dimensional array. | (indexed_name                                  |
|                  | MEMORY_CELL(1024,7)                        |   (prefix<v>                                   |
|                  |                                            |     (name<v>                                   |
|                  |                                            |       (identifier                              |
|                  |                                            |         MEMORY_CELL                            |
|                  |                                            |       )                                        |
|                  |                                            |     )                                          |
|                  |                                            |   )                                            |
|                  |                                            |   (expression                                  |
|                  |                                            |     (relation                                  |
|                  |                                            |       (shift_expression                        |
|                  |                                            |         (simple_expression                     |
|                  |                                            |           (term                                |
|                  |                                            |             (primary<v>                        |
|                  |                                            |               (literal<v>                      |
|                  |                                            |                 (numeric_literal<v>            |
|                  |                                            |                   (abstract_literal<v>         |
|                  |                                            |                     (decimal_literal           |
|                  |                                            |                       literal: 1024, hint: int |
|                  |                                            |                     )                          |
|                  |                                            |                   )                            |
|                  |                                            |                 )                              |
|                  |                                            |               )                                |
|                  |                                            |             )                                  |
|                  |                                            |           )                                    |
|                  |                                            |         )                                      |
|                  |                                            |       )                                        |
|                  |                                            |     )                                          |
|                  |                                            |   ),                                           |
|                  |                                            |   (expression                                  |
|                  |                                            |     (relation                                  |
|                  |                                            |       (shift_expression                        |
|                  |                                            |         (simple_expression                     |
|                  |                                            |           (term                                |
|                  |                                            |             (primary<v>                        |
|                  |                                            |               (literal<v>                      |
|                  |                                            |                 (numeric_literal<v>            |
|                  |                                            |                   (abstract_literal<v>         |
|                  |                                            |                     (decimal_literal           |
|                  |                                            |                       literal: 7, hint: int    |
|                  |                                            |                     )                          |
|                  |                                            |                   )                            |
|                  |                                            |                 )                              |
|                  |                                            |               )                                |
|                  |                                            |             )                                  |
|                  |                                            |           )                                    |
|                  |                                            |         )                                      |
|                  |                                            |       )                                        |
|                  |                                            |     )                                          |
|                  |                                            |   )                                            |
|                  |                                            | )                                              |
|                  |                                            |                                                |
+------------------+--------------------------------------------+------------------------------------------------+

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

+-------------------------+--------+---------------+
| File                    | Input  | Expected      |
+-------------------------+--------+---------------+
| basic_identifier_001    | FooBar | (name<v>      |
|                         |        |   (identifier |
|                         |        |     FooBar    |
|                         |        |   )           |
|                         |        | )             |
|                         |        |               |
+-------------------------+--------+---------------+
| extended_identifier_001 | \BUS\  | (name<v>      |
|                         |        |   (identifier |
|                         |        |     \BUS\     |
|                         |        |   )           |
|                         |        | )             |
|                         |        |               |
+-------------------------+--------+---------------+

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
|                         |          |     (identifier                  |
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
|                         |          |     (identifier                  |
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

=====
range
=====

+-----------+----------------------+----------------------------------------+
| File      | Input                | Expected                               |
+-----------+----------------------+----------------------------------------+
| range_001 | range_attribute_name | (range<v>                              |
|           |                      |   (name<v>                             |
|           |                      |     (identifier                        |
|           |                      |       range_attribute_name             |
|           |                      |     )                                  |
|           |                      |   )                                    |
|           |                      | )                                      |
|           |                      |                                        |
+-----------+----------------------+----------------------------------------+
| range_002 | lhs To rhs           | (range<v>                              |
|           |                      |   (simple_expression                   |
|           |                      |     (term                              |
|           |                      |       (primary<v>                      |
|           |                      |         (name<v>                       |
|           |                      |           (identifier                  |
|           |                      |             lhs                        |
|           |                      |           )                            |
|           |                      |         )                              |
|           |                      |       )                                |
|           |                      |     )                                  |
|           |                      |   )                                    |
|           |                      |   (keyword                             |
|           |                      |     TO                                 |
|           |                      |   )                                    |
|           |                      |   (simple_expression                   |
|           |                      |     (term                              |
|           |                      |       (primary<v>                      |
|           |                      |         (name<v>                       |
|           |                      |           (identifier                  |
|           |                      |             rhs                        |
|           |                      |           )                            |
|           |                      |         )                              |
|           |                      |       )                                |
|           |                      |     )                                  |
|           |                      |   )                                    |
|           |                      | )                                      |
|           |                      |                                        |
+-----------+----------------------+----------------------------------------+
| range_003 | 31 downto 0          | (range<v>                              |
|           |                      |   (simple_expression                   |
|           |                      |     (term                              |
|           |                      |       (primary<v>                      |
|           |                      |         (literal<v>                    |
|           |                      |           (numeric_literal<v>          |
|           |                      |             (abstract_literal<v>       |
|           |                      |               (decimal_literal         |
|           |                      |                 literal: 31, hint: int |
|           |                      |               )                        |
|           |                      |             )                          |
|           |                      |           )                            |
|           |                      |         )                              |
|           |                      |       )                                |
|           |                      |     )                                  |
|           |                      |   )                                    |
|           |                      |   (keyword                             |
|           |                      |     DOWNTO                             |
|           |                      |   )                                    |
|           |                      |   (simple_expression                   |
|           |                      |     (term                              |
|           |                      |       (primary<v>                      |
|           |                      |         (literal<v>                    |
|           |                      |           (numeric_literal<v>          |
|           |                      |             (abstract_literal<v>       |
|           |                      |               (decimal_literal         |
|           |                      |                 literal: 0, hint: int  |
|           |                      |               )                        |
|           |                      |             )                          |
|           |                      |           )                            |
|           |                      |         )                              |
|           |                      |       )                                |
|           |                      |     )                                  |
|           |                      |   )                                    |
|           |                      | )                                      |
|           |                      |                                        |
+-----------+----------------------+----------------------------------------+

========
relation
========

+--------------+-----------------------+------------------------------------------+
| File         | Input                 | Expected                                 |
+--------------+-----------------------+------------------------------------------+
| relation_001 | "0111" * 42 < '1'     | (relation                                |
|              |                       |   (shift_expression                      |
|              |                       |     (simple_expression                   |
|              |                       |       (term                              |
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
|              |                       |       (term                              |
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
|              |                       |       (term                              |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (identifier                  |
|              |                       |               a                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       ),                                 |
|              |                       |       operator: ADD,                     |
|              |                       |       (term                              |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (identifier                  |
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
|              |                       |       (term                              |
|              |                       |         (primary<v>                      |
|              |                       |           (name<v>                       |
|              |                       |             (identifier                  |
|              |                       |               c                          |
|              |                       |             )                            |
|              |                       |           )                              |
|              |                       |         )                                |
|              |                       |       ),                                 |
|              |                       |       operator: SUB,                     |
|              |                       |       (term                              |
|              |                       |         (factor_unary_operation          |
|              |                       |           operator: NOT,                 |
|              |                       |           (literal<v>                    |
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
|                            |                   |     (term                              |
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
|                            |                   |     (term                              |
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
|                            |                   |     (term                              |
|                            |                   |       (factor_binary_operation         |
|                            |                   |         (literal<v>                    |
|                            |                   |           (numeric_literal<v>          |
|                            |                   |             (abstract_literal<v>       |
|                            |                   |               (decimal_literal         |
|                            |                   |                 literal: 66, hint: int |
|                            |                   |               )                        |
|                            |                   |             )                          |
|                            |                   |           )                            |
|                            |                   |         )                              |
|                            |                   |         operator: EXPONENT,            |
|                            |                   |         (literal<v>                    |
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
|                            |                   |     (term                              |
|                            |                   |       (factor_unary_operation          |
|                            |                   |         operator: ABS,                 |
|                            |                   |         (literal<v>                    |
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

===========================
signal_assignment_statement
===========================

+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| File                            | Input                                                          | Expected                                              |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_001 | Output_pin <= Input_pin after 10 ns;                           | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_002 | Output_pin <= inertial Input_pin after 10 ns;                  | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_003 | Output_pin <= reject 10 ns inertial Input_pin after 10 ns;     | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 10, hint: int      |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_004 | Output_pin <= reject 5 ns inertial Input_pin after 10 ns;      | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 5, hint: int       |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_005 | Output_pin <= reject 5 ns inertial Input_pin after 10 ns,      | (signal_assignment_statement                          |
|                                 |                                not Input_pin after 20 ns;      |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 5, hint: int       |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     ),                                                |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (factor_unary_operation               |
|                                 |                                                                |                   operator: NOT,                      |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 20, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_006 | Output_pin <= transport Input_pin after 10 ns;                 | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     TRANSPORT_DELAY                                   |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_007 | Output_pin <= transport Input_pin after 10 ns,                 | (signal_assignment_statement                          |
|                                 |                     not Input_pin after 20 ns;                 |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     TRANSPORT_DELAY                                   |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     ),                                                |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (factor_unary_operation               |
|                                 |                                                                |                   operator: NOT,                      |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 20, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_008 | Output_pin <= reject 0 ns inertial Input_pin after 10 ns;      | (signal_assignment_statement                          |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 0, hint: int       |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_009 | Output_pin <= reject 0 ns inertial Input_pin after 10 ns,      | (signal_assignment_statement                          |
|                                 |                                not Input_pin after 10 ns;      |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 0, hint: int       |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     ),                                                |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (factor_unary_operation               |
|                                 |                                                                |                   operator: NOT,                      |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_010 | my_label:                                                      | (signal_assignment_statement                          |
|                                 |     Output_pin <= Input_pin after 10 ns;                       |   (identifier                                         |
|                                 |                                                                |     my_label                                          |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+
| signal_assignment_statement_011 | my_assign:                                                     | (signal_assignment_statement                          |
|                                 |     Output_pin <= reject 5 ns inertial Input_pin after 10 ns,  |   (identifier                                         |
|                                 |                   not Input_pin after 20 ns;                   |     my_assign                                         |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (target<v>                                          |
|                                 |                                                                |     (name<v>                                          |
|                                 |                                                                |       (identifier                                     |
|                                 |                                                                |         Output_pin                                    |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (delay_mechanism                                    |
|                                 |                                                                |     INERTIAL_DELAY                                    |
|                                 |                                                                |     (expression                                       |
|                                 |                                                                |       (relation                                       |
|                                 |                                                                |         (shift_expression                             |
|                                 |                                                                |           (simple_expression                          |
|                                 |                                                                |             (term                                     |
|                                 |                                                                |               (primary<v>                             |
|                                 |                                                                |                 (literal<v>                           |
|                                 |                                                                |                   (numeric_literal<v>                 |
|                                 |                                                                |                     (physical_literal                 |
|                                 |                                                                |                       literal: (abstract_literal<v>   |
|                                 |                                                                |                         (decimal_literal              |
|                                 |                                                                |                           literal: 5, hint: int       |
|                                 |                                                                |                         )                             |
|                                 |                                                                |                       ),                              |
|                                 |                                                                |                       unit: ns                        |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                |   (waveform<v>                                        |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 10, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     ),                                                |
|                                 |                                                                |     (waveform_element                                 |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (factor_unary_operation               |
|                                 |                                                                |                   operator: NOT,                      |
|                                 |                                                                |                   (name<v>                            |
|                                 |                                                                |                     (identifier                       |
|                                 |                                                                |                       Input_pin                       |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |       (expression                                     |
|                                 |                                                                |         (relation                                     |
|                                 |                                                                |           (shift_expression                           |
|                                 |                                                                |             (simple_expression                        |
|                                 |                                                                |               (term                                   |
|                                 |                                                                |                 (primary<v>                           |
|                                 |                                                                |                   (literal<v>                         |
|                                 |                                                                |                     (numeric_literal<v>               |
|                                 |                                                                |                       (physical_literal               |
|                                 |                                                                |                         literal: (abstract_literal<v> |
|                                 |                                                                |                           (decimal_literal            |
|                                 |                                                                |                             literal: 20, hint: int    |
|                                 |                                                                |                           )                           |
|                                 |                                                                |                         ),                            |
|                                 |                                                                |                         unit: ns                      |
|                                 |                                                                |                       )                               |
|                                 |                                                                |                     )                                 |
|                                 |                                                                |                   )                                   |
|                                 |                                                                |                 )                                     |
|                                 |                                                                |               )                                       |
|                                 |                                                                |             )                                         |
|                                 |                                                                |           )                                           |
|                                 |                                                                |         )                                             |
|                                 |                                                                |       )                                               |
|                                 |                                                                |     )                                                 |
|                                 |                                                                |   )                                                   |
|                                 |                                                                | )                                                     |
|                                 |                                                                |                                                       |
+---------------------------------+----------------------------------------------------------------+-------------------------------------------------------+

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
|                  |                 |     (identifier      |
|                  |                 |       FooBar         |
|                  |                 |     )                |
|                  |                 |   )                  |
|                  |                 | )                    |
|                  |                 |                      |
+------------------+-----------------+----------------------+
| signal_names_002 | Foo, Bar, \BUS\ | (signal_list<v>      |
|                  |                 |   (signal_list.names |
|                  |                 |     (identifier      |
|                  |                 |       Foo            |
|                  |                 |     ),               |
|                  |                 |     (identifier      |
|                  |                 |       Bar            |
|                  |                 |     ),               |
|                  |                 |     (identifier      |
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
|                       |                   |   (term                              |
|                       |                   |     (factor_unary_operation          |
|                       |                   |       operator: NOT,                 |
|                       |                   |       (literal<v>                    |
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
|                       |                   |   (term                              |
|                       |                   |     (factor_binary_operation         |
|                       |                   |       (literal<v>                    |
|                       |                   |         (numeric_literal<v>          |
|                       |                   |           (abstract_literal<v>       |
|                       |                   |             (decimal_literal         |
|                       |                   |               literal: 66, hint: int |
|                       |                   |             )                        |
|                       |                   |           )                          |
|                       |                   |         )                            |
|                       |                   |       )                              |
|                       |                   |       operator: EXPONENT,            |
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
|                       |                   |   (term                              |
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

==================
subtype_indication
==================

+------------------------+----------------------------------------------------------------------+------------------------------------+
| File                   | Input                                                                | Expected                           |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_001 | resolution_function_name  type_mark  RANGE constraint                | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       resolution_function_name     |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (constraint<v>                   |
|                        |                                                                      |     (range<v>                      |
|                        |                                                                      |       (name<v>                     |
|                        |                                                                      |         (identifier                |
|                        |                                                                      |           constraint               |
|                        |                                                                      |         )                          |
|                        |                                                                      |       )                            |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_002 | resolution_function_name  type_mark                                  | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       resolution_function_name     |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_003 |   type_mark  RANGE constraint                                        | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (constraint<v>                   |
|                        |                                                                      |     (range<v>                      |
|                        |                                                                      |       (name<v>                     |
|                        |                                                                      |         (identifier                |
|                        |                                                                      |           constraint               |
|                        |                                                                      |         )                          |
|                        |                                                                      |       )                            |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_004 | type_mark                                                            | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_005 | resolution_function_name  type_mark  ( range_attribute_name  )       | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       resolution_function_name     |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (constraint<v>                   |
|                        |                                                                      |     (index_constraint              |
|                        |                                                                      |       (discrete_range<v>           |
|                        |                                                                      |         (subtype_indication        |
|                        |                                                                      |           (name<v>                 |
|                        |                                                                      |             (identifier            |
|                        |                                                                      |               range_attribute_name |
|                        |                                                                      |             )                      |
|                        |                                                                      |           )                        |
|                        |                                                                      |         )                          |
|                        |                                                                      |       )                            |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+
| subtype_indication_006 | resolution_function_name  type_mark  ( range_1_name, range_2_name  ) | (subtype_indication                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       resolution_function_name     |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (name<v>                         |
|                        |                                                                      |     (identifier                    |
|                        |                                                                      |       type_mark                    |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      |   (constraint<v>                   |
|                        |                                                                      |     (index_constraint              |
|                        |                                                                      |       (discrete_range<v>           |
|                        |                                                                      |         (subtype_indication        |
|                        |                                                                      |           (name<v>                 |
|                        |                                                                      |             (identifier            |
|                        |                                                                      |               range_1_name         |
|                        |                                                                      |             )                      |
|                        |                                                                      |           )                        |
|                        |                                                                      |         )                          |
|                        |                                                                      |       ),                           |
|                        |                                                                      |       (discrete_range<v>           |
|                        |                                                                      |         (subtype_indication        |
|                        |                                                                      |           (name<v>                 |
|                        |                                                                      |             (identifier            |
|                        |                                                                      |               range_2_name         |
|                        |                                                                      |             )                      |
|                        |                                                                      |           )                        |
|                        |                                                                      |         )                          |
|                        |                                                                      |       )                            |
|                        |                                                                      |     )                              |
|                        |                                                                      |   )                                |
|                        |                                                                      | )                                  |
|                        |                                                                      |                                    |
+------------------------+----------------------------------------------------------------------+------------------------------------+

====
term
====

+------------+-------------------+------------------------------------+
| File       | Input             | Expected                           |
+------------+-------------------+------------------------------------+
| factor_001 | abs 42            | (term                              |
|            |                   |   (factor_unary_operation          |
|            |                   |     operator: ABS,                 |
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
|            |                   |     (literal<v>                    |
|            |                   |       (numeric_literal<v>          |
|            |                   |         (abstract_literal<v>       |
|            |                   |           (decimal_literal         |
|            |                   |             literal: 66, hint: int |
|            |                   |           )                        |
|            |                   |         )                          |
|            |                   |       )                            |
|            |                   |     )                              |
|            |                   |     operator: EXPONENT,            |
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
|                |                                                                      |     (identifier      |
|                |                                                                      |       MKS            |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (identifier      |
|                |                                                                      |       MEASUREMENTS   |
|                |                                                                      |     )                |
|                |                                                                      |   ),                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       STD            |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (identifier      |
|                |                                                                      |       STANDARD       |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_002 | use ieee.std_logic_1164.all;                                         | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       ieee           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
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
|                |                                                                      |     (identifier      |
|                |                                                                      |       ieee           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       math_real      |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (identifier      |
|                |                                                                      |       MATH_PI        |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+
| use_clause_004 | use IEEE.Std_Logic_1164.Std_ulogic, IEEE.Std_Logic_1164.Rising_edge; | (use_clause          |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       IEEE           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       Std_Logic_1164 |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (identifier      |
|                |                                                                      |       Std_ulogic     |
|                |                                                                      |     )                |
|                |                                                                      |   ),                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       IEEE           |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (name<v>           |
|                |                                                                      |     (identifier      |
|                |                                                                      |       Std_Logic_1164 |
|                |                                                                      |     )                |
|                |                                                                      |   ).                 |
|                |                                                                      |   (suffix<v>         |
|                |                                                                      |     (identifier      |
|                |                                                                      |       Rising_edge    |
|                |                                                                      |     )                |
|                |                                                                      |   )                  |
|                |                                                                      | )                    |
|                |                                                                      |                      |
+----------------+----------------------------------------------------------------------+----------------------+

==============
wait_statement
==============

+--------------------+----------------------------------+-----------------------------------------------------+
| File               | Input                            | Expected                                            |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_001 | WAIT;                            | (wait_statement                                     |
|                    |                                  |                                                     |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_002 | wait_label: WAIT;                | (wait_statement                                     |
|                    |                                  |   (identifier                                       |
|                    |                                  |     wait_label                                      |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_003 | wait on A,B;                     | (wait_statement                                     |
|                    |                                  |   (sensitivity_clause                               |
|                    |                                  |     (sensitivity_list                               |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           A                                         |
|                    |                                  |         )                                           |
|                    |                                  |       ),                                            |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           B                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_004 | dummy: WAIT on X,Y,Z;            | (wait_statement                                     |
|                    |                                  |   (identifier                                       |
|                    |                                  |     dummy                                           |
|                    |                                  |   )(sensitivity_clause                              |
|                    |                                  |     (sensitivity_list                               |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           X                                         |
|                    |                                  |         )                                           |
|                    |                                  |       ),                                            |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           Y                                         |
|                    |                                  |         )                                           |
|                    |                                  |       ),                                            |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           Z                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_005 | wait until CLK='1';              | (wait_statement                                     |
|                    |                                  |   (condition_clause                                 |
|                    |                                  |     (condition                                      |
|                    |                                  |       (expression                                   |
|                    |                                  |         (relation                                   |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (name<v>                          |
|                    |                                  |                     (identifier                     |
|                    |                                  |                       CLK                           |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           ),                                        |
|                    |                                  |           operator: EQUAL,                          |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (literal<v>                       |
|                    |                                  |                     (enumeration_literal<v>         |
|                    |                                  |                       (character_literal            |
|                    |                                  |                         '1'                         |
|                    |                                  |                       )                             |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           )                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_006 | wait on A, B until CLK = '1';    | (wait_statement                                     |
|                    |                                  |   (sensitivity_clause                               |
|                    |                                  |     (sensitivity_list                               |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           A                                         |
|                    |                                  |         )                                           |
|                    |                                  |       ),                                            |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           B                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )(condition_clause                                |
|                    |                                  |     (condition                                      |
|                    |                                  |       (expression                                   |
|                    |                                  |         (relation                                   |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (name<v>                          |
|                    |                                  |                     (identifier                     |
|                    |                                  |                       CLK                           |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           ),                                        |
|                    |                                  |           operator: EQUAL,                          |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (literal<v>                       |
|                    |                                  |                     (enumeration_literal<v>         |
|                    |                                  |                       (character_literal            |
|                    |                                  |                         '1'                         |
|                    |                                  |                       )                             |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           )                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_007 | wait for 100 ns;                 | (wait_statement                                     |
|                    |                                  |   (timeout_clause                                   |
|                    |                                  |     (expression                                     |
|                    |                                  |       (relation                                     |
|                    |                                  |         (shift_expression                           |
|                    |                                  |           (simple_expression                        |
|                    |                                  |             (term                                   |
|                    |                                  |               (primary<v>                           |
|                    |                                  |                 (literal<v>                         |
|                    |                                  |                   (numeric_literal<v>               |
|                    |                                  |                     (physical_literal               |
|                    |                                  |                       literal: (abstract_literal<v> |
|                    |                                  |                         (decimal_literal            |
|                    |                                  |                           literal: 100, hint: int   |
|                    |                                  |                         )                           |
|                    |                                  |                       ),                            |
|                    |                                  |                       unit: ns                      |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           )                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+
| wait_statement_008 | Wait on EN until EN='1' for 1ms; | (wait_statement                                     |
|                    |                                  |   (sensitivity_clause                               |
|                    |                                  |     (sensitivity_list                               |
|                    |                                  |       (name<v>                                      |
|                    |                                  |         (identifier                                 |
|                    |                                  |           EN                                        |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )(condition_clause                                |
|                    |                                  |     (condition                                      |
|                    |                                  |       (expression                                   |
|                    |                                  |         (relation                                   |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (name<v>                          |
|                    |                                  |                     (identifier                     |
|                    |                                  |                       EN                            |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           ),                                        |
|                    |                                  |           operator: EQUAL,                          |
|                    |                                  |           (shift_expression                         |
|                    |                                  |             (simple_expression                      |
|                    |                                  |               (term                                 |
|                    |                                  |                 (primary<v>                         |
|                    |                                  |                   (literal<v>                       |
|                    |                                  |                     (enumeration_literal<v>         |
|                    |                                  |                       (character_literal            |
|                    |                                  |                         '1'                         |
|                    |                                  |                       )                             |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           )                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )(timeout_clause                                  |
|                    |                                  |     (expression                                     |
|                    |                                  |       (relation                                     |
|                    |                                  |         (shift_expression                           |
|                    |                                  |           (simple_expression                        |
|                    |                                  |             (term                                   |
|                    |                                  |               (primary<v>                           |
|                    |                                  |                 (literal<v>                         |
|                    |                                  |                   (numeric_literal<v>               |
|                    |                                  |                     (physical_literal               |
|                    |                                  |                       literal: (abstract_literal<v> |
|                    |                                  |                         (decimal_literal            |
|                    |                                  |                           literal: 1, hint: int     |
|                    |                                  |                         )                           |
|                    |                                  |                       ),                            |
|                    |                                  |                       unit: ms                      |
|                    |                                  |                     )                               |
|                    |                                  |                   )                                 |
|                    |                                  |                 )                                   |
|                    |                                  |               )                                     |
|                    |                                  |             )                                       |
|                    |                                  |           )                                         |
|                    |                                  |         )                                           |
|                    |                                  |       )                                             |
|                    |                                  |     )                                               |
|                    |                                  |   )                                                 |
|                    |                                  | )                                                   |
|                    |                                  |                                                     |
+--------------------+----------------------------------+-----------------------------------------------------+

========
waveform
========

+--------------+---------------------------------------+-----------------------------------------------------+
| File         | Input                                 | Expected                                            |
+--------------+---------------------------------------+-----------------------------------------------------+
| waveform_001 | NULL after 10 ns                      | (waveform<v>                                        |
|              |                                       |   (waveform_element                                 |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (keyword                          |
|              |                                       |                     NULL                            |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (numeric_literal<v>               |
|              |                                       |                     (physical_literal               |
|              |                                       |                       literal: (abstract_literal<v> |
|              |                                       |                         (decimal_literal            |
|              |                                       |                           literal: 10, hint: int    |
|              |                                       |                         )                           |
|              |                                       |                       ),                            |
|              |                                       |                       unit: ns                      |
|              |                                       |                     )                               |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |   )                                                 |
|              |                                       | )                                                   |
|              |                                       |                                                     |
+--------------+---------------------------------------+-----------------------------------------------------+
| waveform_002 |  "0000" after 2 ns, "1111" after 7 ns | (waveform<v>                                        |
|              |                                       |   (waveform_element                                 |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (string_literal                   |
|              |                                       |                     0000                            |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (numeric_literal<v>               |
|              |                                       |                     (physical_literal               |
|              |                                       |                       literal: (abstract_literal<v> |
|              |                                       |                         (decimal_literal            |
|              |                                       |                           literal: 2, hint: int     |
|              |                                       |                         )                           |
|              |                                       |                       ),                            |
|              |                                       |                       unit: ns                      |
|              |                                       |                     )                               |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |   ),                                                |
|              |                                       |   (waveform_element                                 |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (string_literal                   |
|              |                                       |                     1111                            |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |     (expression                                     |
|              |                                       |       (relation                                     |
|              |                                       |         (shift_expression                           |
|              |                                       |           (simple_expression                        |
|              |                                       |             (term                                   |
|              |                                       |               (primary<v>                           |
|              |                                       |                 (literal<v>                         |
|              |                                       |                   (numeric_literal<v>               |
|              |                                       |                     (physical_literal               |
|              |                                       |                       literal: (abstract_literal<v> |
|              |                                       |                         (decimal_literal            |
|              |                                       |                           literal: 7, hint: int     |
|              |                                       |                         )                           |
|              |                                       |                       ),                            |
|              |                                       |                       unit: ns                      |
|              |                                       |                     )                               |
|              |                                       |                   )                                 |
|              |                                       |                 )                                   |
|              |                                       |               )                                     |
|              |                                       |             )                                       |
|              |                                       |           )                                         |
|              |                                       |         )                                           |
|              |                                       |       )                                             |
|              |                                       |     )                                               |
|              |                                       |   )                                                 |
|              |                                       | )                                                   |
|              |                                       |                                                     |
+--------------+---------------------------------------+-----------------------------------------------------+

=============
xxx_signature
=============

+---------+-----------------------+----------+
| File    | Input                 | Expected |
+---------+-----------------------+----------+
| xxx_001 | [MVL, MVL return MVL] |          |
|         |                       |          |
|         |                       |          |
+---------+-----------------------+----------+
| xxx_002 | [return OpCode]       |          |
|         |                       |          |
|         |                       |          |
+---------+-----------------------+----------+
| xxx_003 |                       |          |
+---------+-----------------------+----------+
