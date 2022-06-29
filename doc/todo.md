ToDo
====

Obviously the intend is to get the parser working and hence the project. Even the compiler requires
C++20, the tools inside [Microsofts Devcontainer](https://github.com/Microsoft/vscode-dev-containers)
are not the latest, hence still sticking with C++17 and limited C++20 support (e.g. C++20
std::source_location isn't supported by all compiler used, also `std::format` and `std::range`).

## Boost.Spirit X3

The X3 rules are from start of the project in 2017, so `grammar_def.h` requires
rework. The headers are generated from EBNF using a python script. Only recursive
rules require the template engine of BOOST_SPIRIT_{DECLARE, DEFINE}.

These days there is are two branches `next-x3-grammar` and `next-x3-grammar-v2` (the last is the
current). Also, there is a branch `next-cpp20-numeric-convert` which affects parsing and will
replace the old approach of ast's sub project numeric_convert.

## Unit testing

The old approach from 2017 tests the VHDL grammar very 'simple', using instances for each rule to
test. This increases the compile time for each test, see `testsuite/librules/rules_{a-z}` instances.

A bigger problem rises from use of Spirit X3 self. Code parts using boost 1.68 worked in 2017, using
1.78 fails in 2022. Hence a behavior validation test bench is required for Spirit self to locate
errors easier (hopefully).

Problems known are:

  - alias_declaration_00{1...5}
  - entity_aspect/entity_aspect_002.input
  - type_declaration_failure/*
  - interface_constant_declaration/interface_constant_declaration_006.input
  - type_conversion/type_conversion_001.input
  - wait_statement/wait_statement_00x.input
  - binding_indication/binding_indication_00{0,1}.input entity name rule
    (is work.foo -> name)
  - allocator_003 (http://vhdl.renerta.com/source/vhd00004.htm)
  - component_configuration_000; configuration_declaration_000,
    architecture_body -> must be: work.foo
    reason is related to rule name, where no selected_name is active!!!

In 2021 boost was bumped to v1.73 and following *test_vhdl_parser_rule* tests failed:

  - test_case_name = aggregate/aggregate_001;
  - test_case_name = aggregate/aggregate_002;
  - test_case_name = aggregate/aggregate_003;
  - test_case_name = aggregate/aggregate_006;
  - test_case_name = attribute_specification/attribute_specification_001;
  - test_case_name = use_clause/use_clause_000;

Starting with boost 1.78 `test_vhdl_syntax` fails with respect to human readable error location and
marker. Probably run into [X3 3.0.10 error_handler where() is wrong #712](
https://github.com/boostorg/spirit/issues/712).

New approach (partially seen at branch `next-x3-grammar-v2`) uses the frontend API `parse()`,
allowing testing units within contexts, e.g. packages.

## App Logging

There are several needs to log to the user. The VHDL assert and report messages are obvious. Next
are messages of warning and errors from VHDL compiler self. Further internal and debugging messages,
maybe by use of boost.log or spdlog.

Generally, a lot of information go trough std::cerr without prefix or even using colorizing. E.g. on
stacktrace_{gdb.boost} it's not clear what comes from what.

Maybe retire the `ibis/color` support and use `{fmt}` color support - which would make them non
replaceable with std::format. Future C++ standards will show the way.

## CMake build and Conan (v2)

Consider use of CMake's [Unity Build Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE).

More serious is the up coming conan v2. Used [cmake-conan](https://github.com/conan-io/cmake-conan)
isn't supported in 2022 any more. The way to use is *CMakeDeps* generator using  plain
`conanfile.txt` with *CMakeDeps*, CMakeToolchain (and even the new [layout]). This will take
time ... The problem behind is related to CMake's `find_package( .... OPTIONAL ...)` command which
makes the optionals required (and hence results into configure error).

## Sources (`main` branch) related

- **FixMe**: Before main's init() there is no text style/color functionality even in the
  stacktrace_{gdb,boost} functions.

- position_cache got warnings by compiling with `-Weverything`
  regards to `.line_number()` and `.get_line_start`: IIRC deduction guide, Investigate!

- Write git hooks for checking using clang-{tidy,format} et al. Note, that not
  everywhere clang-format may be installed. The git hooks should capture
  - PCH with and without, declarations are hidden in the PCH headers, so if one isn't using
    PCH it results into compile errors.
  - release and debug mode, later one triggers more tests, even using MS compiler.
  - and of course, Linux and Windows, Clang, GNU C++ and MS VC.

- AST printer: move ast_printer into ast_walker, printer breaks down into simple class
  like ast_stats. Fix by this the non const-ness of the ast_printer - this simplifies const
  correctness at other places.

  - use for recursive depth counting a class with ctor/dtor increment/decrement
    capabilities - recursive_depth_{counter,guard} - as context i.e.

  -  ast_stats.cpp:
    - ast_stats sort order - use enum sort::{ascending, descending}
    - worker collector{ count_map, untagged_nodes } fix to
      worker stats_worker{ count_map, untagged_nodes };

- we have buildinfo_static.hpp.in, buildinfo.hpp.in using git info and date/time
  would be useful, for an idea look at blender sources. But this clearly future work.

## Documentation

Switch from MarkDown to ReStructuredText. At this state, Doxygen miss some MarkDown
and ReStructuredText features, Sphinx multi projects and doesn't seems to support
Doxygen's Todo tags/list.

Check [LSST DM Developer Guide](https://developer.lsst.io/index.html) for styles
and recommendations.

## Others

Get a logo, e.g. ibis as mascot with assets

