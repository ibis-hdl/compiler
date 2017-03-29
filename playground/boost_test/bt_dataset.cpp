#define BOOST_TEST_MODULE "My Test Suite"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <vector>
#include <iostream>



namespace my_test {


struct dataset_loader
{
    typedef std::vector<std::string>                    dataset_type;

    class data_set;

    data_set input() const;
    data_set expect() const;

    dataset_loader()
	: m_input{ "foo", "bar" }
    , m_expected{ "foo", "baz" }
    { }

    dataset_type     m_input;
    dataset_type     m_expected;
};

struct dataset_loader::data_set
{
	typedef dataset_type::const_iterator	iterator;

    data_set(dataset_type const& data)
    : m_data{ data }
    { }

    // boost.test dataset API
    enum { arity = 1 };
    using sample = dataset_type::value_type;
    boost::unit_test::data::size_t size() const { return m_data.size(); }
    iterator begin() const { return m_data.begin(); }

    dataset_type const& m_data;
};

dataset_loader::data_set dataset_loader::input() const
{
    return data_set(m_input);
}

dataset_loader::data_set dataset_loader::expect() const
{
    return data_set(m_expected);
}


} // namespace my_test


namespace boost { namespace unit_test { namespace data { namespace monomorphic {
	  // registering fibonacci_dataset as a proper dataset
	  template <>
	  struct is_dataset<my_test::dataset_loader::data_set> : boost::mpl::true_ {};
}}}}


BOOST_AUTO_TEST_SUITE( basic_productions )

using ::boost::unit_test::data::monomorphic::operator^;


::my_test::dataset_loader my_dataset;


BOOST_DATA_TEST_CASE(cool_test,
my_dataset.input() ^ my_dataset.expect(),
    input, expect)
{
      BOOST_TEST(input == expect);
}


BOOST_AUTO_TEST_SUITE_END()


