//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/util/dataset_loader.hpp>
#include <testsuite/util/cli_args.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>  // BOOST_TEST_MESSAGE()
#include <boost/test/utils/lazy_ostream.hpp>

#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <string>
#include <utility>

#include <boost/test/framework.hpp>  // for master_test_suite

#include <testsuite/namespace_alias.hpp>

namespace testsuite::util {

dataset_loader::dataset_loader(std::string_view testcase_group_)
    : loader_name{ "dataset_loader<" + std::string(testcase_group_) + ">" }
    , testcase_group{ testcase_group_ }
{
}

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
dataset_loader::~dataset_loader() = default;

// Quiet compiler warning: ... has no out-of-line virtual method definitions; its vtable will be
// emitted in every translation unit [-Wweak-vtables]
dataset_loader::compile_builtin::~compile_builtin() = default;

void dataset_loader::set_builtin(std::unique_ptr<compile_builtin> other)
{
    builtin = std::move(other);

    int const argc = boost::unit_test::framework::master_test_suite().argc;
    char** argv = boost::unit_test::framework::master_test_suite().argv;

    cli_args::parse_cli(argc, argv);
    check_args();
    // cli_args::print_settings();

    BOOST_TEST_MESSAGE(name() << ": load test files for " << testcase_group);

    fs::path const path = fs::path(option.source_dir) / testcase_group;
    read_files(path);

    if (dataset.input.empty()) {
        BOOST_TEST_MESSAGE(name() << " WARNING: empty dataset in " << testcase_group);
    }
}

void dataset_loader::check_args() const
{
    //
    // the source directory of the test case where the input and expected files are located
    //
    if (cli_args::source_dir().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <source_dir> "
                                  << builtin->source_dir());
        option.source_dir = builtin->source_dir();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <source_dir> "  // --
                                  << cli_args::source_dir());
        option.source_dir = cli_args::source_dir();
    }

    //
    // file extension of input files
    //
    if (cli_args::input_extension().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <input_extension> "
                                  << builtin->input_extension());
        option.input_extension = builtin->input_extension();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <input_extension> "
                                  << cli_args::input_extension());
        option.input_extension = cli_args::input_extension();
    }

    //
    // file extension of expected files
    //
    if (cli_args::expected_extension().empty()) {
        BOOST_TEST_MESSAGE(name() << ": use compiled builtin <expected_extension> "
                                  << builtin->expected_extension());
        option.expected_extension = builtin->expected_extension();
    }
    else {
        BOOST_TEST_MESSAGE(name() << ": use command line <expected_extension> "
                                  << cli_args::expected_extension());
        option.expected_extension = cli_args::expected_extension();
    }

    //
    // check post conditions
    //
    if (option.source_dir.empty()) {
        throw std::logic_error("empty cli parameter <source_dir>");
    }
    if (option.input_extension.empty()) {
        throw std::logic_error("empty cli parameter <input_extension>");
    }
    if (option.expected_extension.empty()) {
        throw std::logic_error("empty cli parameter <expected_extension>");
    }
}

// ToDo warning: function 'read_files' has cognitive complexity of 30 (threshold 25)
// [readability-function-cognitive-complexity]
void dataset_loader::read_files(fs::path const& path_name) const
{
    if (fs::exists(path_name) && fs::is_directory(path_name)) {
        // collect all files from directory ...
        // Note, std::set is a container that stores unique elements in sorted order.
        std::set<fs::path> dir_list{};
        for (auto const& entry : fs::directory_iterator(path_name)) {
            // recursion is not intended
            if (entry.is_regular_file()) {
                dir_list.insert(entry.path());
            }
        }

        // ... and iterate over them
        for (auto const& file : dir_list) {
            try {
                // pickup input files, expected files have the same base name
                if (file.extension() == option.input_extension) {
                    // create a representative test case name to render at the users and store it
                    dataset.name.emplace_back(
                        (file.parent_path().filename() / file.stem()).generic_string());

                    // to get the name of the expected file, just replace the extension of the input
                    // file with the corresponding expected file extension. Note, the implementation
                    // behavior differs between C++ Std and Boost.filesystem, hence the string copy
                    // of the input file name.
                    fs::path expect_file = file.generic_string();
                    expect_file.replace_extension(option.expected_extension);

                    // ... and store both test vectors; note read_file() may intentionally throw
                    dataset.input.emplace_back(read_file(file));
                    dataset.expected.emplace_back(read_file(expect_file));
                }
            }
            catch ([[maybe_unused]] std::exception const& e) {
                // BOOST_TEST_MESSAGE(name() << ": caught '" << e.what() << "' exception!");

                // try to recover from error and continue; simply assume no {file}.expected was
                // found. FixMe: This is a simple quick & dirty solution, if the order of emplacing
                // the dataset contents is changed above, pop_back() will crash!
                if (dataset.name.size() == dataset.input.size() &&
                    dataset.input.size() == dataset.expected.size() + 1) {
                    BOOST_TEST_MESSAGE(name() << " NOTICE: Remove test case file contents of '"
                                              << dataset.name.back() << "' from dataset");
                    dataset.name.pop_back();
                    dataset.input.pop_back();
                }
            }
            catch (...) {
                BOOST_ERROR(name() << ": Caught unexpected exception !!!");
            }
        }
    }
    else {
        BOOST_ERROR(name() << ": Directory: " << fs::path{ path_name }.make_preferred()
                           << " does not exist!");
    }
}

std::string dataset_loader::read_file(fs::path const& file_path) const
{
    auto const preferred_fname = [](fs::path const& path) {
        return fs::path{ path }.make_preferred();
    };

    BOOST_TEST_MESSAGE(name() << ": read file " << preferred_fname(file_path));

    if (!fs::exists(file_path)) {
        BOOST_TEST_MESSAGE(name() << ": file " << preferred_fname(file_path) << " doesn't exist!");
        throw std::ios_base::failure{ "file not exist" };
    }

    std::ifstream ifs{ file_path };

    if (!ifs.is_open()) {
        BOOST_TEST_MESSAGE(name() << ": unable to open " << preferred_fname(file_path));
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << ifs.rdbuf();

    if (ifs.fail() && !ifs.eof()) {
        BOOST_TEST_MESSAGE(name() << ": reading " << preferred_fname(file_path) << " failed!");
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}

std::string_view dataset_loader::name() const { return loader_name; }

utf_data::size_t dataset_loader::size() const { return dataset.input.size(); }

dataset_loader::iterator dataset_loader::begin() const
{
    return { dataset.input.begin(), dataset.expected.begin(), dataset.name.begin() };
}

// ----------------------------------------------------------------------------
// Nested dataset loader Iterator class implementation
// ----------------------------------------------------------------------------

dataset_loader::iterator::iterator(iterator_type input_iter_, iterator_type expected_iter_,
                                   iterator_type testcase_name_iter_)
    : input_iter{ input_iter_ }
    , expected_iter{ expected_iter_ }
    , testcase_name_iter{ testcase_name_iter_ }
{
}

std::tuple<std::string, std::string, std::string> dataset_loader::iterator::operator*() const
{
    return { *input_iter, *expected_iter, *testcase_name_iter };
}

void dataset_loader::iterator::operator++()
{
    ++input_iter;
    ++expected_iter;
    ++testcase_name_iter;
}

}  // namespace testsuite::util
