/*
 * data_set.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#include <testsuite/common/data_set.hpp>
#include <testsuite/common/cli_args.hpp>
#include <testsuite/common/detail/compile_builtin.hpp>

#include <cassert>
#include <algorithm>
#include <iterator>
#include <exception>
#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>

using testsuite::cli_args;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
BOOST_TEST_GLOBAL_FIXTURE(cli_args);

namespace testsuite {

/* The prefix for the test case root directory structure is runtime configurable.
 * For more information look at:
 * - [[Boost.Test] access to boost::unit_test::framework::master_test_suite().{argc, argv} outside
 * from BOOST_TEST]( https://groups.google.com/forum/#!topic/boost-developers-archive/wtnY9F2cWNI)
 * - [access to master_test_suite().{argc, argv}](
 *    https://svn.boost.org/trac10/ticket/12953)
 *
 * FixMe: dataset_name for messages
 * */
dataset_loader::dataset_loader(std::string const& path)
    : input_extension{ ".vhdl" }
    , expected_extension{ ".expected" }
{
    setup();

    BOOST_TEST_MESSAGE("INFO(dataset_loader) load test files from " << path);

    fs::path p = fs::path(source_dir) / path;
    read_files(p);

    if (testfile_input.empty()) {
        BOOST_TEST_MESSAGE("WARNING(dataset_loader): empty dataset in " << path);
    }

    BOOST_TEST_REQUIRE((testfile_input.size() == testfile_expected.size()  // ---
                        && testfile_name.size() == testfile_expected.size()),
                       "dataset_loader test vector size mismatch");
}

void dataset_loader::read_files(fs::path const& path_name)
{
    if (fs::exists(path_name) && fs::is_directory(path_name)) {
        // collect all files from directory ...
        // Note, std::set is a container that stores unique elements in sorted order.
        std::set<fs::path> dir_list;
        for (auto& entry : fs::directory_iterator(path_name)) {
            // recursion is not intended
            if (entry.is_regular_file()) {
                dir_list.insert(entry.path());
            }
        }

        // ... and iterate over them
        for (auto const& file : dir_list) {
            try {
                // pickup input files, expected files have the same base name
                if (file.extension() == input_extension) {
                    // create a representative test case name to render at the users and store it
                    testfile_name.emplace_back(
                        (file.parent_path().filename() / file.stem()).generic_string());

                    // to get the name of the expected file, just replace the extension of the input
                    // file with the corresponding expected file extension. Note, the implementation
                    // behavior differs between C++ Std and Boost.filesystem, hence the string copy
                    // of the input file name.
                    fs::path expect_file = file.generic_string();
                    expect_file.replace_extension(expected_extension);

                    // ... and store both test vectors; note read_file() may intentionally throw
                    testfile_input.emplace_back(read_file(file));
                    testfile_expected.emplace_back(read_file(expect_file));
                }
            }
            catch (std::exception const& e) {
                BOOST_ERROR("ERROR(dataset_loader) caught '" << e.what() << "' exception!");

                // try to recover from error and continue; simply assume no {file}.expected was
                // found. FixMe: This is a simple quick & dirty solution, if the order of emplacing
                // the dataset contents is changed above, pop_back() will crash!
                if (testfile_name.size() == testfile_input.size() &&
                    testfile_input.size() == testfile_expected.size() + 1) {
                    BOOST_TEST_MESSAGE("WARNING(dataset_loader) Remove test case file contents of '"
                                       << testfile_name.back() << "' from dataset");
                    testfile_name.pop_back();
                    testfile_input.pop_back();
                }
            }
            catch (...) {
                // mhh ...
                BOOST_ERROR("ERROR(dataset_loader) Caught unexpected exception !!!");
            }
        }
    }
    else {
        BOOST_ERROR("ERROR(dataset_loader) Directory: " << fs::canonical(path_name)
                                                        << " does not exist!");
    }
}

std::string dataset_loader::read_file(fs::path const& file_path)
{
    auto const preferred_fname = [](fs::path const& path) {
        return fs::path{ path }.make_preferred();
    };

    BOOST_TEST_MESSAGE("INFO(dataset_loader) read file " << preferred_fname(file_path));

    if (!fs::exists(file_path)) {
        BOOST_TEST_MESSAGE("WARNING(dataset_loader) file " << preferred_fname(file_path)
                                                           << " doesn't exist!");
        throw std::ios_base::failure{ "file not exist" };
    }

    std::ifstream ifs{ file_path };

    if (!ifs.is_open()) {
        BOOST_TEST_MESSAGE("WARNING(dataset_loader) unable to open " << preferred_fname(file_path));
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << ifs.rdbuf();

    if (ifs.fail() && !ifs.eof()) {
        BOOST_TEST_MESSAGE("WARNING(dataset_loader) reading " << preferred_fname(file_path)
                                                              << " failed!");
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}

void dataset_loader::setup()
{
    std::string_view const dataset_name{ "dataset_loader<setup>" };

    BOOST_TEST_MESSAGE("INFO(" << dataset_name << ") enter");

    // FixMe: Unfortunately the code below crash on using cli_args fixtures. The error message
    // "Boost.Test framework internal error: unknown reason" isn't helpful here. Hence we stick
    // at the old implementation way which was intended to be replaced by cli_args fixture.
    // Further, for each test the constructor, and hence this setup function, is called every
    // test, so implement an caching of variables.
    if constexpr (false) {
        //
        // the source directory of the test case where the input and expected files are located
        //
        if (cli_args::source_dir().empty()) {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use compiled builtin <source_dir> "
                        << compile_def_source_dir);
            source_dir = compile_def_source_dir;
        }
        else {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use command line <source_dir> "
                        << cli_args::source_dir());
            source_dir = cli_args::source_dir();
        }

        //
        // file extension of input files
        //
        if (cli_args::input_extension().empty()) {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use compiled builtin <input_extension> "
                        << compile_def_input_extension);
            input_extension = compile_def_input_extension;
        }
        else {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use command line <input_extension> "
                        << cli_args::input_extension());
            input_extension = cli_args::input_extension();
        }

        //
        // file extension of expected files
        //
        if (cli_args::expected_extension().empty()) {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use compiled builtin <expected_extension> "
                        << compile_def_expected_extension);
            expected_extension = compile_def_expected_extension;
        }
        else {
            BOOST_TEST_MESSAGE(  // --
                "INFO(" << dataset_name << ") use command line <expected_extension> "
                        << cli_args::expected_extension());
            expected_extension = cli_args::expected_extension();
        }
    }
    // old cli parse way, which doesn't crash
    else {
        auto parse_for = [](std::string_view arg, std::string_view str, std::string& value) {
            auto const pos = str.find(arg);

            if (pos == std::string::npos) {
                return false;
            }

            value = str.substr(pos + arg.size());
            return true;
        };

        unsigned const argc = boost::unit_test::framework::master_test_suite().argc;
        char** const argv = boost::unit_test::framework::master_test_suite().argv;

        // compile time defaults
        source_dir = compile_def_source_dir;
        input_extension = compile_def_input_extension;
        expected_extension = compile_def_expected_extension;

        // overwrite defaults with command line arguments if any
        for (unsigned i = 0; i != argc; i++) {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            std::string_view const argv_sv{ argv[i] };

            if (parse_for("--source-dir=", argv_sv, source_dir)) {
                BOOST_TEST_MESSAGE(  // --
                    "INFO(" << dataset_name << ") use command line <source_dir> " << source_dir);
            }

            if (parse_for("--input-extension=", argv_sv, input_extension)) {
                BOOST_TEST_MESSAGE(  // --
                    "INFO(" << dataset_name << ") use command line <input_extension> "
                            << input_extension);
            }

            if (parse_for("--expected-extension=", argv_sv, expected_extension)) {
                BOOST_TEST_MESSAGE(  // --
                    "INFO(" << dataset_name << ") use command line <expected_extension> "
                            << expected_extension);
            }
        }
    }  // if constexpr

    // post condition
    BOOST_TEST_REQUIRE(!source_dir.empty());
    BOOST_TEST_REQUIRE(!input_extension.empty());
    BOOST_TEST_REQUIRE(!expected_extension.empty());

    BOOST_TEST_MESSAGE("INFO(" << dataset_name << ") leave");
}

}  // namespace testsuite
