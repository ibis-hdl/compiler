/*
 * data_set.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_DATA_SET_HPP_
#define TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_DATA_SET_HPP_

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <filesystem>

#include <testsuite/common/namespace_alias.hpp>  // IWYU pragma: keep

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

    std::string source_dir;
    std::string input_extension;
    std::string expected_extension;
};

}  // namespace testsuite

namespace boost {
namespace unit_test {
namespace data {

namespace monomorphic {

template <>
struct is_dataset<testsuite::dataset_loader> : boost::mpl::true_ {
};

}  // namespace monomorphic

}  // namespace data
}  // namespace unit_test
}  // namespace boost

#endif /* TESTSUITE_COMMON_INCLUDE_TESTSUITE_COMMON_DATA_SET_HPP_ */
