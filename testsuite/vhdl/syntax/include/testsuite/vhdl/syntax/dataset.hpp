//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <testsuite/util/dataset_loader.hpp>

#include <boost/test/data/monomorphic.hpp>

#include <string_view>

namespace testsuite::vhdl::syntax {

class dataset : public testsuite::util::dataset_loader {
public:
    explicit dataset(std::string_view testcase_group);
    ~dataset() override;

    dataset() = delete;
    dataset(dataset const&) = delete;
    dataset(dataset&&) = delete;
    dataset& operator=(dataset const&) = delete;
    dataset& operator=(dataset&&) = delete;

private:
    struct compile_builtin : testsuite::util::dataset_loader::compile_builtin {
        compile_builtin() = default;
        ~compile_builtin() override;

        compile_builtin(compile_builtin&) = delete;
        compile_builtin(compile_builtin&&) = delete;
        compile_builtin operator=(compile_builtin&) = delete;
        compile_builtin operator=(compile_builtin&&) = delete;

        std::string_view source_dir() const override;
        std::string_view input_extension() const override;
        std::string_view expected_extension() const override;
    };
};

}  // namespace testsuite::vhdl::syntax

namespace boost::unit_test::data::monomorphic {

///
/// The registration of dataset as a proper dataset for Boost.Test.
///
template <>
struct is_dataset<testsuite::vhdl::syntax::dataset> : boost::mpl::true_ {
};

}  // namespace boost::unit_test::data::monomorphic
