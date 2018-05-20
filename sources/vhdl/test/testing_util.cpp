/*
 * testing_util.cpp
 *
 *  Created on: 19.05.2018
 *      Author: olaf
 */

#include "testing_util.hpp"
#include "test_case_path.hpp"


namespace x3_test {


test_case_result_writer::test_case_result_writer(fs::path const& test_case)
/* The prefix for the test case output root directory structure is (unfortunately)
 * hard coded. I didn't found a way to give these as command line argument
 * to the boost.test runner. */
: m_dest_dir{ BT_TEST_CASE_WRITE_PATH }
, m_test_case{ test_case }
{ }


bool test_case_result_writer::create_directory(fs::path const& write_path)
{
    try {
        if(   !boost::filesystem::exists(write_path)
           || !boost::filesystem::is_directory(write_path)
        ) {
            cout << "create directories " << write_path << '\n';
            return fs::create_directories(write_path);
        }
    }
    catch(fs::filesystem_error const& e) {
        cerr << "creating directory "
             << write_path
             << " failed with:\n"
                << e.code().message()
                << "\n";
        return false;
    }

    return true;
}


bool test_case_result_writer::write_file(fs::path const& filename, std::string const& contents)
{
    cout << "Write to " << filename << "\n";

    try {
        if(fs::exists(filename)) {
            fs::remove(filename);
        }
    }
    catch(fs::filesystem_error const& e) {
        cerr << "remove of older file "
             << filename
             << " failed with:\n"
             << e.code().message()
             << "\n";
        return false;
    }

    try {
        fs::ofstream ofs{ filename };
        ofs << contents;
    }
    catch(fs::filesystem_error const& e) {
        cerr << "writing to "
             << filename
             << " failed with:\n"
             << e.code().message()
             << "\n";
        return false;
    }

    return true;
}


void test_case_result_writer::write(std::string const& parse_result)
{
    fs::path const full_pathname = m_dest_dir / "test_case" / m_test_case;
    fs::path const write_path = full_pathname.parent_path();

    if(!create_directory(write_path)) {
        return;
    }

    fs::path const filename = full_pathname.filename().replace_extension(".parsed");

    write_file(write_path / filename, parse_result);
}


} // namespace x3_test

