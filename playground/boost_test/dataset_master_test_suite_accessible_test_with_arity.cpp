/*
 * dataset_master_test_suite_accessible_test_with_arity.cpp
 *
 * [#12953 assigned Feature Requests](https://svn.boost.org/trac10/ticket/12953)
 *
 *  Created on: 27.06.2018
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <vector>
#include <iostream>


class dataset_loader_arity3
{
public:
    typedef std::vector<std::string>                    data_type;

    data_type m_expected;
    data_type m_input;

    typedef std::string sample;
    enum { arity = 3 };

public:
    dataset_loader_arity3(std::string some_additional) : m_some_additional(some_additional)
    {
      int argc = boost::unit_test::framework::master_test_suite().argc;
      char** argv = boost::unit_test::framework::master_test_suite().argv;


      for(unsigned i = 1; i != argc; i++) {
        std::string current(argv[i]);
        std::cout << "current " << current << std::endl;
        if(current.find("--param1") != std::string::npos) {
          m_expected.push_back(current);
        }
        else {
          m_input.push_back(current);
        }
      }
    }

    struct iterator {
        iterator(
          data_type::const_iterator v_expected,
          data_type::const_iterator v_input,
          std::string additional)
        : m_input(v_input)
        , m_expected(v_expected)
        , m_additional(additional)
        {}

        std::tuple<std::string, std::string, std::string> operator*() const {
          return std::tuple<std::string, std::string, std::string>(
             *m_input,
             *m_expected,
             *m_input + " -" + m_additional + "- " + *m_expected);
        }
        void operator++()
        {
            ++m_input;
            ++m_expected;
        }
    private:
        data_type::const_iterator m_input, m_expected;
        std::string m_additional;
    };

    boost::unit_test::data::size_t size() const {
      return m_input.size();
    }

    // iterator
    iterator        begin() const   { return iterator(m_expected.begin(), m_input.begin(), m_some_additional); }

private:
    std::string m_some_additional;

};


namespace boost { namespace unit_test { namespace data {

namespace monomorphic {
  template <>
  struct is_dataset<dataset_loader_arity3> : boost::mpl::true_ {};
}
} } }


BOOST_DATA_TEST_CASE(master_access_make_ds_with_arity,
    boost::unit_test::data::make_delayed<dataset_loader_arity3>( "something-in-the-middle"),
    input, expected, additional)
{
    std::cout << "input: " << input << " -- expected: " << expected << " -- additional: " << additional << std::endl;
    BOOST_TEST(true);
}


