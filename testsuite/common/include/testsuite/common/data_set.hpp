#pragma once

#include <testsuite/common/namespace_alias.hpp>  // IWYU pragma: keep

#include <boost/test/data/monomorphic.hpp>

#include <string>
#include <tuple>
#include <vector>
#include <filesystem>

namespace testsuite {

///
/// @brief
///
/// Boost UTF [Datasets](
///  https://www.boost.org/doc/libs/1_75_0/libs/test/doc/html/boost_test/tests_organization/test_cases/test_case_generation/datasets.html)
///
/// FixMe: This code is related to testsuite/vhdl_parser. Make it universal, so that can be placed
/// into testsuite/common and the behavior can be replaced by overwriting the appropiate member
/// functions.
///
/// @todo FixMe (Seriously Error): ```warning: Call to virtual method 'dataset_loader::setup'
/// during construction bypasses virtual dispatch [clang-analyzer-optin.cplusplus.VirtualCall]
/// setup();```. This is bad design, see [Calling virtual functions inside constructors](
/// https://stackoverflow.com/questions/962132/calling-virtual-functions-inside-constructors)
///
/// @todo The path leaf of test data is still hard coded into the sources ('test_data'). It
/// shouldn't depend on it!
///

class dataset_loader {
public:
    using data_type = std::vector<std::string>;

public:
    // FixMe: arg 'path' is misleading!
    explicit dataset_loader(std::string const& path);

    virtual ~dataset_loader() {}
    dataset_loader(dataset_loader const&) = delete;
    dataset_loader(dataset_loader&&) = delete;
    dataset_loader& operator=(dataset_loader const&) = delete;
    dataset_loader& operator=(dataset_loader&&) = delete;

protected:
    virtual void setup();

public:  // Boost.UTF Dataset interface
    enum { arity = 3 };

    using sample = std::string;  // utf_data::make_delayed

    struct iterator {
        iterator(data_type::const_iterator input_iter_,          // input
                 data_type::const_iterator expected_iter_,       // expected aka 'gold'
                 data_type::const_iterator testcase_name_iter_)  // test name
            : input_iter{ input_iter_ }
            , expected_iter{ expected_iter_ }
            , testcase_name_iter{ testcase_name_iter_ }
        {
        }

        std::tuple<std::string, std::string, std::string> operator*() const
        {
            return std::tuple<std::string, std::string, std::string>(  // ---
                *input_iter, *expected_iter, *testcase_name_iter);
        }

        void operator++()
        {
            ++input_iter;
            ++expected_iter;
            ++testcase_name_iter;
        }

    private:
        data_type::const_iterator input_iter;
        data_type::const_iterator expected_iter;
        data_type::const_iterator testcase_name_iter;
    };

    utf_data::size_t size() const { return testfile_input.size(); }

    iterator begin() const
    {
        return iterator(testfile_input.begin(), testfile_expected.begin(), testfile_name.begin());
    }

private:
    void read_files(fs::path const& path);
    static std::string read_file(fs::path const& file_path);

private:
    data_type testfile_input;
    data_type testfile_expected;
    data_type testfile_name;

    fs::path source_dir;
    std::string input_extension;
    std::string expected_extension;
};

}  // namespace testsuite

namespace boost::unit_test::data::monomorphic {

template <>
struct is_dataset<testsuite::dataset_loader> : boost::mpl::true_ {
};

}  // namespace boost::unit_test::data::monomorphic
