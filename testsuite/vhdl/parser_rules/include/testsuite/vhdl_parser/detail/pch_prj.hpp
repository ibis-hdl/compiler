#pragma once

#include <eda/util/pretty_typename.hpp>
#include <eda/vhdl/ast/ast_printer.hpp>
#include <eda/vhdl/ast_fwd.hpp>
#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/ast/node/based_literal.hpp>
#include <eda/vhdl/ast/node/bit_string_literal.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>
#include <eda/vhdl/ast/numeric_convert.hpp>
#include <eda/vhdl/ast/position_cache.hpp>
#include <eda/vhdl/parser/grammar_decl.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/iterator_type.hpp>
#include <eda/vhdl/parser/parser_config.hpp>
#include <eda/vhdl/parser/skipper.hpp>
#include <eda/vhdl/type.hpp>

#include <testsuite/common/namespace_alias.hpp>
#include <testsuite/common/data_set.hpp>
#include <testsuite/common/failure_diagnostic_fixture.hpp>

#include <testsuite/vhdl/rules.hpp>

#include <testsuite/vhdl_parser/testing_parser.hpp>
