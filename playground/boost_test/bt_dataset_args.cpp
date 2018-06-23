/*
 * bt_dataset_args.cpp
 *
 *  Created on: 23.06.2018
 *      Author: olaf
 */

//------------------------------------------------------------------------------

#define BOOST_TEST_MODULE "Cool Test Suite"
#include <boost/test/included/unit_test.hpp>


//------------------------------------------------------------------------------

#include <boost/test/data/test_case.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>


namespace testsuite {

namespace fs = boost::filesystem;

struct app_mock
{
    int const                                       argc;
    char** const                                    argv;

    app_mock()
    : argc(boost::unit_test::framework::master_test_suite().argc)
    , argv(boost::unit_test::framework::master_test_suite().argv)
    { }
};


BOOST_AUTO_TEST_CASE( app_mocker )
{
     app_mock app;
}


class dataset_loader
{
public:
    typedef std::vector<fs::path>                       pathname_type;
    typedef std::vector<std::string>                    data_type;

public:
    pathname_type const& test_case_name() const { return m_test_case; }
    data_type const& input() const { return m_input; }
    data_type const& expect() const { return m_expected; }

public:
    dataset_loader(fs::path const& path);

private:
    void read_files(fs::path const& path);

private:
    pathname_type                                       m_test_case;
    data_type                                           m_input;
    data_type                                           m_expected;
    std::string                                         input_extension;
    std::string                                         expected_extension;
};

} // namespace testsuite



namespace testsuite {

dataset_loader::dataset_loader(fs::path const& path)
: input_extension{".input" }
, expected_extension{ ".expected" }
{
    BOOST_TEST_INFO("dataset_loader load test files from " << path);

    auto const argc{boost::unit_test::framework::master_test_suite().argc};
    auto const argv{boost::unit_test::framework::master_test_suite().argv};

    std::cout << "ArgCount = " << argc << '\n';
    for(unsigned i = 0; i != argc; i++) {
        std::cout << "ArgValue = " << argv[i] << '\n';
    }

    app_mock m;
    std::cout << "Mock ArgCount = " << m.argc << '\n';
    for(int i = 0; i != m.argc; i++) {
        std::cout << "Mock ArgValue = " << m.argv[i] << '\n';
    }

    read_files(path);
}


void dataset_loader::read_files(fs::path const& path)
{
    // real code suppressed, cmd line args for load prefix and extensions required
    BOOST_TEST_INFO("read files " << path << input_extension);
}


} // namespace testsuite

//------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( concrete_testsuite )

using ::boost::unit_test::data::monomorphic::operator^;


struct concrete_dataset : public testsuite::dataset_loader
{
    concrete_dataset()
    : dataset_loader{ "test_case/number_42" }
    { }
} const concrete_dataset;


BOOST_DATA_TEST_CASE(cool_test,
    concrete_dataset.input() ^ concrete_dataset.expect(),
    input, expect)
{
    // ...
    BOOST_TEST(input == expect);
}


BOOST_AUTO_TEST_SUITE_END()

