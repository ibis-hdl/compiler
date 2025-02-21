//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstddef>  // FixMe [Bug] work around for Clang19 libc++ && Boost 1.86
#include <boost/test/data/size.hpp>

#include <filesystem>
#include <memory>
#include <string_view>
#include <string>
#include <tuple>
#include <vector>

#include <testsuite/namespace_alias.hpp>

namespace testsuite {
namespace fs = std::filesystem;
}

namespace testsuite::util {

///
/// @brief The class implements Boost.Test [Datasets](
/// https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/tests_organization/test_cases/test_case_generation/datasets.html)
/// for tests using modified [Data-driven test cases parametrized from the command line](
///  https://www.boost.org/doc/libs/1_73_0/libs/test/doc/html/boost_test/runtime_config/custom_command_line_arguments.html)
/// approach..
///
/// A dataset holds:
///
/// - one or more input files.
/// - one or more corescondending expected file.
/// - the bundled basename of these pair of files, aka name of test_case.
///
/// The data for input and expected are linked to the corresponding testdata file
/// name and provided as iterator.
///
/// This class can serve as a base class for other concrete use cases or other
/// source paths by deriving from the compile builtin class, overriding the
/// path implementation and setting it in the
/// constructor:
///
/// @code{.cpp}
/// struct dataset : public testsuite::util::dataset_loader {
///     explicit dataset(std::string_view testcase_group)
///         : testsuite::util::dataset_loader(testcase_group) {
///         builtin = std::make_unique<dataset::compile_builtin>();
///     }
///     ~dataset() = default;
///
///     struct compile_builtin : dataset_loader::compile_builtin {
///         virtual std::string_view source_dir() const override;
///         virtual std::string_view input_extension() const override;
///         virtual std::string_view expected_extension() const override;
///     };
/// };
///
/// // indicating that the specified type is a dataset.
/// namespace boost::unit_test::data::monomorphic {
/// template <>
/// struct is_dataset<testsuite::vhdl::parser::dataset> : boost::mpl::true_ { };
/// }
/// @endcode
///
/// @note: The official Boost.Test documentation recommends to use a global fixture
/// to get the CLI arguments. Unfortunately, with use of delayed dataset the constructor
/// of the loader, where the data is loaded, is called before the instantiation of this
/// global fixture. Hence only the builtin defaults are used. Further, the
/// dataset_loader class cannot be used as fixture. Therefore this implementation way
/// is taken here.
///
/// @see [Coliru, to show the concept](https://coliru.stacked-crooked.com/a/4fefddb54abb4340)
///
class dataset_loader {
public:
    ///
    /// @brief Construct a new dataset loader object.
    ///
    /// @param testcase_group The name of the top-level directory where the test
    /// data files reside. When using the CLI or the compiled builtin source path
    /// for the source directory, these files are loaded from there.
    /// At the same time this is the group name of the parent test.
    ///
    explicit dataset_loader(std::string_view testcase_group);
    virtual ~dataset_loader();

    dataset_loader() = delete;
    dataset_loader(dataset_loader const&) = delete;
    dataset_loader(dataset_loader&&) = delete;
    dataset_loader& operator=(dataset_loader const&) = delete;
    dataset_loader& operator=(dataset_loader&&) = delete;

    //
    //  Boost.UTF Dataset interface
    //
public:
    /// Implements interface of the dataset.
    enum { arity = 3 };

    ///
    /// Iterator API for Boost.Test dataset interface.
    ///
    /// @todo Check on right place on same size of all dataset vectors, like
    /// @code{.cpp}
    /// BOOST_TEST_REQUIRE((dataset.input.size() == dataset.expected.size()
    ///                 && dataset.name.size() == dataset.expected.size()),
    ///                "dataset_loader test vector size mismatch");
    /// @endcode
    ///
    struct iterator {
        using iterator_type = std::vector<std::string>::const_iterator;

        ///
        /// @brief Construct a new iterator object
        ///
        /// @param input_iter_ The origin input to proceed.
        /// @param expected_iter_ The expected result, aka 'gold'.
        /// @param testcase_name_iter_ The test name self.
        ///
        iterator(iterator_type input_iter_, iterator_type expected_iter_,
                 iterator_type testcase_name_iter_);

        std::tuple<std::string, std::string, std::string> operator*() const;

        void operator++();

    private:
        iterator_type input_iter;
        iterator_type expected_iter;
        iterator_type testcase_name_iter;
    };

    /// Size of the complete dataset. Implements interface of the dataset.
    utf_data::size_t size() const;

    ///
    /// Dataset interface which implements the iterator API for Boost.Test
    ///
    /// Internally the CLI arguments are tested for appropriate options and if not
    /// available replaced with the compile builtin values. Then the actual dataset
    /// files are loaded and the iterator object is returned with this data.
    ///
    /// @return iterator holding the dataset contents.
    ///
    iterator begin() const;

protected:
    ///
    /// The compiled builtin defaults, used if no CLI argument was given.
    ///
    // NOLINTNEXTLINE(cppcoreguidelines-special-member-functions) -- due to abstract class!
    struct compile_builtin {
        compile_builtin() = default;
        virtual ~compile_builtin();

        compile_builtin(compile_builtin&) = delete;
        compile_builtin(compile_builtin&&) = delete;

        virtual std::string_view source_dir() const = 0;
        virtual std::string_view input_extension() const = 0;
        virtual std::string_view expected_extension() const = 0;
    };

    ///
    /// Set the builtin object
    ///
    /// @param other The builtin object intended to replace the current one.
    ///
    void set_builtin(std::unique_ptr<compile_builtin> other);

private:
    /// Parse CLI arguments and if not given replace them with compile builtin values.
    void check_args() const;

    /// Internal name for logging, holds the testcase_group argument in its name.
    std::string_view name() const;

private:
    /// Loads the files below the testcase_group constructor argument relative
    /// to the source directory.
    void read_files(fs::path const& path) const;

    /// Read a given single file into std::string.
    std::string read_file(fs::path const& file_path) const;

private:
    // std::string test_case_pathname;
    std::string const loader_name;
    std::string const testcase_group;

    /// The options from parsed CLI arguments or compiled builtin options.
    struct options {
        fs::path source_dir;
        std::string input_extension;
        std::string expected_extension;
    };

    /// designated initializers for @ref options
    options mutable option{ {}, ".vhdl", ".expected" };

    /// The dataset loaded from file system using the options given.
    struct test_dataset {
        std::vector<std::string> input;
        std::vector<std::string> expected;
        std::vector<std::string> name;
    };
    test_dataset mutable dataset;

private:
    std::unique_ptr<compile_builtin> builtin;
};

}  // namespace testsuite::util
