/*
 * cxx_ast_tagged_stats.cpp
 *
 *  Created on: 21.07.2018
 *      Author: olaf
 *
 * https://wandbox.org/permlink/K64boWhNZ4OORUdg
 */

#include <iostream>

#include <optional>
#include <string_view>
#include <map>
#include <vector>
#include <algorithm>

namespace ast {

struct position_tagged { };

struct foo : position_tagged { };
struct bar { };
struct baz : position_tagged { };

} // namespace ast



struct collect_worker
{
    typedef std::map<std::string_view, std::size_t> map_type;
    typedef map_type::iterator                      iterator_type;
    typedef map_type::value_type                    value_type;

    collect_worker(map_type& tagged_map_, map_type& untagged_map_)
    : tagged_map{ tagged_map_ }
    , untagged_map{ untagged_map_ }
    {}

    template<typename NodeT>
    void operator()(NodeT const&, std::string_view node_name) const {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>) {
            ++tagged_map[node_name];
        }
        else {
            ++untagged_map[node_name];
        }
    }

    map_type&                           tagged_map;
    map_type&                           untagged_map;
};


template<typename WorkerT>
struct visitor_base
{
    template <typename... WorkerArgs>
    visitor_base(WorkerArgs&&... args)
    : worker{ std::forward<WorkerArgs>(args)... }
    { }

    visitor_base(visitor_base const&) = delete;
    visitor_base const& operator=(visitor_base const&) = delete;

    void operator()(ast::foo const& node) const {
        static char const symbol[]{ "foo" };
        worker(node, symbol);
    }
    void operator()(ast::bar const& node) const {
        static char const symbol[]{ "bar" };
        worker(node, symbol);
    }
    void operator()(ast::baz const& node) const {
        static char const symbol[]{ "baz-baz" };
        worker(node, symbol);
    }

    WorkerT const                              worker;
};


///////////////////////////////////////////////////////////////////////////////
template<typename T>
struct is_vector : std::false_type { };

template<typename T>
struct is_vector<std::vector<T>> : std::true_type { };

template<typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;
///////////////////////////////////////////////////////////////////////////////
#if 0
int main()
{
    std::vector<int> i_vec;
    int i;
    std::cout << std::boolalpha << is_vector_v<decltype(i_vec)> << "\n";
    std::cout << std::boolalpha << is_vector_v<decltype(i)> << "\n";

}
#endif


template<typename KeyT, typename ValueT>
struct format
{
    format(std::map<KeyT, ValueT> const& map_)
    : map{ map_ }
    {}

    std::ostream& print(std::ostream& os) const
    {
        std::size_t const max_key_size = [this] {

			std::size_t size{ 0 };
			std::for_each(map.begin(), map.end(),
				[&size](auto const& pair) {
					size = std::max(size, pair.first.size());
				}
			);
			return    size;
        } ();

        std::string const padding(max_key_size, ' ');

        for (auto const& [key, value] : map) {
            os << key   << std::string_view(padding).substr(0, max_key_size - key.size())
               << " : " << value << "\n";
        }
        return os;
    }

    std::map<KeyT, ValueT> const&               map;
};

template<typename KeyT, typename ValueT>
std::ostream& operator<<(std::ostream& os, format<KeyT, ValueT> const& printer) {
    return printer.print(os);
}

template<typename KeyT, typename ValueT>
struct format2
{
    format2(std::vector<std::pair<KeyT, ValueT>> const& vec_)
    : vec{ vec_ }
    {}

    std::ostream& print(std::ostream& os) const
    {
        std::size_t const max_key_size = [this] {

			std::size_t size{ 0 };
			std::for_each(vec.begin(), vec.end(),
				[&size](auto const& pair) {
					size = std::max(size, pair.first.size());
				}
			);
			return size;
        } ();

        std::string const padding(max_key_size, ' ');

        for (auto const& [key, value] : vec) {
            os << key   << std::string_view(padding).substr(0, max_key_size - key.size())
               << " : " << value << "\n";
        }
        return os;
    }

    std::vector<std::pair<KeyT, ValueT>> const&     vec;
};

template<typename KeyT, typename ValueT>
std::ostream& operator<<(std::ostream& os, format2<KeyT, ValueT> const& printer) {
    return printer.print(os);
}


template<typename... KeyT, typename... ValueT>
auto as_vec(std::map<KeyT, ValueT> const&... maps)
{
    std::size_t const size = (maps.size() + ...);   // Fold expression

    using key_type = std::tuple_element_t<0, std::tuple<KeyT...>>;
    using value_type= std::tuple_element_t<0, std::tuple<ValueT...>>;

    typedef std::pair<key_type, value_type> 		pair_type;

	std::vector<pair_type> vec;
	vec.reserve(size);

    auto const push_back = [&vec](auto const& map) {
        std::copy(map.begin(), map.end(),
	        std::back_inserter<std::vector<pair_type>>(vec));
    };

    (push_back(maps), ...);  // Fold expression

    return vec;
}


struct ascending_tag {};
struct descending_tag {};

template<typename KeyT, typename ValueT, typename Tag> struct predicate { };

template<typename KeyT, typename ValueT> struct predicate<KeyT, ValueT, ascending_tag>
{
    typedef std::pair<KeyT, ValueT>                 pair_type;

    bool operator()(pair_type const& lhs, pair_type const& rhs) const {
        if (lhs.second != rhs.second)
            return lhs.second < rhs.second; // sort-by-value
        return lhs.first < rhs.first;       // sort-by-key otherwise
    };
};

template<typename KeyT, typename ValueT> struct predicate<KeyT, ValueT, descending_tag>
{
    typedef std::pair<KeyT, ValueT>                 pair_type;

    bool operator()(pair_type const& lhs, pair_type const& rhs) const {
        if (lhs.second != rhs.second)
            return lhs.second > rhs.second; // sort-by-value
        return lhs.first < rhs.first;       // sort-by-key otherwise
    };
};



template<typename Tag>
struct map_sort
{
template<typename... KeyT, typename... ValueT>
auto operator()(std::map<KeyT, ValueT> const&... maps)
{
	auto vec = as_vec(std::map<KeyT, ValueT>(maps)...);

    using key_type = std::tuple_element_t<0, std::tuple<KeyT...>>;
    using value_type= std::tuple_element_t<0, std::tuple<ValueT...>>;
	using predicate_ = predicate<key_type, value_type, Tag>;

	std::sort(vec.begin(), vec.end(), predicate_{});

	return vec;
}
};


int main()
{
    ast::foo foo;
    ast::bar bar;
    ast::baz baz;

    collect_worker::map_type tagged_map;
    collect_worker::map_type untagged_map;

    visitor_base<collect_worker> collect(tagged_map, untagged_map);
    collect(foo);
    collect(foo);
    collect(bar);
    collect(baz);

    std::cout << format(tagged_map) << "\n";
    std::cout << format(untagged_map) << "\n";

    auto node_list = as_vec(tagged_map, untagged_map);
    auto sorted = map_sort<ascending_tag>{}(tagged_map, untagged_map);

    std::cout << "sorted:\n";
    std::cout << format2(sorted) << "\n";
}

#if 0
// *** Map sort ***
// https://wandbox.org/permlink/3nfdAXnFp4CNjLfL

#include <iostream>

#include <optional>
#include <string_view>
#include <map>
#include <vector>
#include <algorithm>

struct tag_data
{
    typedef std::map<std::string, std::size_t>      map_type;
    typedef map_type::iterator                      iterator_type;
    typedef map_type::value_type                    value_type;

    void tagged(std::string const& node_name) {
        ++tagged_map[node_name];
    }

    void untagged(std::string const& node_name) {
        ++untagged_map[node_name];
    }

    map_type                                        tagged_map;
    map_type                                        untagged_map;
};


struct ascending_tag {};
struct descending_tag {};

template<typename KeyT, typename ValueT, typename Tag> struct predicate { };

template<typename KeyT, typename ValueT> struct predicate<KeyT, ValueT, ascending_tag>
{
    typedef std::pair<KeyT, ValueT>                 pair_type;

    bool operator()(pair_type const& lhs, pair_type const& rhs) const {
        if (lhs.second != rhs.second)
            return lhs.second < rhs.second; // sort-by-value
        return lhs.first < rhs.first;       // sort-by-key otherwise
    };
};

template<typename KeyT, typename ValueT> struct predicate<KeyT, ValueT, descending_tag>
{
    typedef std::pair<KeyT, ValueT>                 pair_type;

    bool operator()(pair_type const& lhs, pair_type const& rhs) const {
        if (lhs.second != rhs.second)
            return lhs.second > rhs.second; // sort-by-value
        return lhs.first < rhs.first;       // sort-by-key otherwise
    };
};


// ToDo:
// - variadic template of sort() to allow sort(map1,  map2)
template< typename Tag, typename KeyT, typename ValueT>
auto map_sort(std::map<KeyT, ValueT> const& map)
{
	typedef KeyT                      				key_type;
	typedef ValueT                     				mapped_type;
	typedef std::pair<key_type, mapped_type> 		pair_type;

	std::vector<pair_type> vec;
	vec.reserve(map.size());

	std::copy(map.begin(), map.end(),
			  std::back_inserter<std::vector<pair_type>>(vec));

	using predicate_ = predicate<key_type, mapped_type, Tag>;
	std::sort(vec.begin(), vec.end(), predicate_{});

	return vec;
}



int main()
{
    tag_data data;
    data.tagged("foo");
    data.tagged("foo");
    data.tagged("boo");
    data.untagged("baz");

    auto const sorted = map_sort<descending_tag>(data.tagged_map);

    for (auto const& [key, value] : sorted) {
        std::cout << key << " : " << value << "\n";
    }
}
#endif
