/*
 * data_set.cpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#include <testsuite/data_set.hpp>

#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <cassert>


namespace testsuite {


#if defined(_WIN32) || defined(_WIN64)
    static constexpr std::wostream& cerr{ std::wcerr };
#else
    static constexpr std::ostream& cerr{ std::cerr };
#endif


/** Helper function to format all file path related messages unified. */
static inline
fs::path pretty_filepath(fs::path file_path) {
    return fs::canonical(file_path.make_preferred());
}


/* The prefix for the test case root directory structure is (unfortunately)
 * hard coded. I didn't found a way to give these as command line argument
 * to the boost.test runner.
 * For more information about this problem look at:
 * - [[Boost.Test] access to boost::unit_test::framework::master_test_suite().{argc, argv} outside from BOOST_TEST](
 *    https://groups.google.com/forum/#!topic/boost-developers-archive/wtnY9F2cWNI)
 * - [access to master_test_suite().{argc, argv}](
 *    https://svn.boost.org/trac10/ticket/12953)
 * */
dataset_loader::dataset_loader(std::string const& path)
: input_extension{ ".vhdl" }
, expected_extension{ ".expected" }
{
    // FixMe: Doesn't abort() as expected
    BOOST_TEST_REQUIRE(parse_command_line(),
                       "--source-prefix= must be given");

    BOOST_TEST_INFO("dataset_loader load test files from " << path);
    fs::path p = fs::path(source_dir_prefix) / path;
    p.make_preferred();
    read_files(p);

    if(testfile_input.empty()) {
        std::cerr << "WARNING: no data in dataset " << path << "\n";
    }


    BOOST_TEST_REQUIRE(testfile_input.size() == testfile_expected.size(),
                       "dataset_loader test vector size mismatch");
}


void dataset_loader::read_files(fs::path const& path)
{
    try {
        if(fs::exists(path) && fs::is_directory(path)) {

            std::vector<fs::path> dir_list { };
            std::copy(
                fs::directory_iterator(path),
                fs::directory_iterator(),
                std::back_inserter(dir_list)
            );

            std::sort(dir_list.begin(), dir_list.end());

            for(auto const& file_ : dir_list) {

                auto const file = fs::canonical(file_);

                if (fs::extension(file) == input_extension) {

                    testfile_name.emplace_back(
                        (file.parent_path().filename() / file.stem()).generic_string()
                    );
                    cerr << "INFO: read " << file << "\n";

                    fs::path const input_file  = file;
                    fs::path const expect_file = fs::change_extension(file, expected_extension);

                    testfile_input.emplace_back(   read_file(input_file ));
                    testfile_expected.emplace_back(read_file(expect_file));
                }
            }
        }
        else {
            /* FixMe: boost.fs throws on canonical(), since path doesn't exist
             * This behavior isn't with C++17 filesystem */
            cerr << "ERROR: Directory: " << fs::absolute(path)
                 << " does not exist!\n";
        }
    }
    catch(std::exception const& e) {
        cerr << "ERROR: Caught \"" << e.what() << "\" exception!\n";
        /* try to recover from error and continue; probably no {file}.expected
         * was found. */
        if(   testfile_name.size() == testfile_input.size()
           && testfile_input.size()    == testfile_expected.size() + 1
          ) {
            cerr << "WARNING: Remove test files at "
                 << pretty_filepath(testfile_name.back())
                 << " from data set\n";
            testfile_name.pop_back();
            testfile_input.pop_back();
        }
    }
    catch(...) {
        cerr << "ERROR: Caught unexpected exception!!!\n";

    }
}


std::string dataset_loader::read_file(fs::path const& file_path)
{
    fs::ifstream file{ file_path };

    if(!file) {
        cerr << "ERROR: unable to open " << pretty_filepath(file_path) << "!\n";
        throw std::ios_base::failure{ "file open error" };
    }

    std::ostringstream ss{};
    ss << file.rdbuf();

    if(file.fail() && !file.eof()) {
        cerr << "ERROR: unable to open " << pretty_filepath(file_path) << "\n";
        throw std::ios_base::failure{ "rdbuf() read error" };
    }

    return ss.str();
}


bool dataset_loader::parse_for(std::string const& arg, std::string const& str, std::string& value)
{
    auto const pos = str.find(arg);

    if(pos == std::string::npos) {
        return false;
    }

    value = str.substr(pos + arg.size());
    return true;
}


bool dataset_loader::parse_command_line()
{
    unsigned const argc = boost::unit_test::framework::master_test_suite().argc;
    char** const argv = boost::unit_test::framework::master_test_suite().argv;

    bool source_prefix_arg{ false };

    for(unsigned i = 0; i != argc; i++) {
        //std::cout << "ArgValue[" << i << "]: " << argv[i] << "\n";

        if(parse_for("--source-prefix=", argv[i], source_dir_prefix)) {
            std::cout << "--source-prefix = " << source_dir_prefix << "\n";
            source_prefix_arg = true;
        }

        if(parse_for("--input-extension=", argv[i], input_extension)) {
            std::cout << "--input-extension=" << input_extension << "\n";
        }

        if(parse_for("--expected-extension=", argv[i], expected_extension)) {
            std::cout << "--expected-extension=" << expected_extension << "\n";
        }

    }

    if(!source_prefix_arg) {
        std::cerr << "ERROR(testsuite::dataset_loader) "
                  << argv[0] << " --source-prefix= must be given\n";
        return false;
    }

    return true;
}


} // namespace testsuite



