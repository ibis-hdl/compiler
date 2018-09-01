/*
 * data_set.hpp
 *
 *  Created on: 22.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_
#define TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <boost/filesystem.hpp>

#include <string>
#include <tuple>
#include <vector>

#include <testsuite/namespace_alias.hpp>            // IWYU pragma: keep


namespace testsuite {


class dataset_loader
{
public:
    typedef std::vector<std::string>                data_type;

public:
    dataset_loader(std::string const& path);

public: // Boost.UTF API
    enum { arity = 3 };

    typedef std::string                             sample; // utf_data::make_delayed

    struct iterator
    {
        iterator(
            data_type::const_iterator input_iter_,
            data_type::const_iterator expected_iter_,
            data_type::const_iterator testcase_name_iter_)
        : input_iter{ input_iter_ }
        , expected_iter{ expected_iter_ }
        , testcase_name_iter{ testcase_name_iter_ }
        { }

        std::tuple<std::string, std::string, std::string> operator*() const {
            return std::tuple<std::string, std::string, std::string>(
                    *input_iter, *expected_iter, *testcase_name_iter);
        }

        void operator++() {
            ++input_iter;
            ++expected_iter;
            ++testcase_name_iter;
        }

    private:
        data_type::const_iterator                   input_iter;
        data_type::const_iterator                   expected_iter;
        data_type::const_iterator                   testcase_name_iter;
    };

    utf_data::size_t size() const {
        return testfile_input.size();
    }

    iterator begin() const {
        return iterator(
            testfile_input.begin(),
            testfile_expected.begin(),
            testfile_name.begin());
    }

private:
    void read_files(fs::path const& path);
    std::string read_file(fs::path const& file_path);

private:
    bool parse_for(std::string const& arg, std::string const& string, std::string& value);
    bool parse_command_line();

private:
    std::string                                     source_dir;

    data_type                                       testfile_input;
    data_type                                       testfile_expected;
    data_type                                       testfile_name;

    std::string                                     input_extension;
    std::string                                     expected_extension;
};


} // namespace testsuite


namespace boost { namespace unit_test { namespace data {

namespace monomorphic {

template <>
struct is_dataset<testsuite::dataset_loader> : boost::mpl::true_ {};

}

} } }


#endif /* TESTSUITE_COMMON_INCLUDE_TESTSUITE_DATA_SET_HPP_ */
