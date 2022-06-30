//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

namespace ibis::vhdl::parser {

//
// recursive parser rule IDs
//

struct configuration_item_class;
struct concurrent_statement_class;
struct constraint_class;
struct sequence_of_statements_class;
struct subprogram_declarative_item_class;

struct design_file_class;

//
// old
//

struct attribute_name_class;
struct expression_class;
struct function_call_class;
struct indexed_name_class;
struct literal_class;
struct name_class;
struct prefix_class;
struct primary_class;
struct range_class;
struct selected_name_class;
struct slice_name_class;

}  // namespace ibis::vhdl::parser
