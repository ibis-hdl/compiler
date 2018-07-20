/*
 * cxx_annotation_cache.cpp
 *
 *  Created on: 20.07.2018
 *      Author: olaf
 */

/*
 * https://wandbox.org/permlink/hNcp4xBtC2HnGc6w
 */
#if 0
 -------------------------------------------------------------------------------
<olux> Why does push_back compile and emplace_back not at https://wandbox.org/permlink/qZAsYsjj2pPE1oIw ?? It try to introduce move semantic due to dispatching.
<olux> I though the problem is due to variadic template args (hence the do... member), but this seems the cause
<dzejrou> tried passing (first, last) instead of ({first, last})?
<olux> yes, so variadic arguments of emplace_back 'unwind' the arguments?
<dzejrou> emplace_back passes its arguments directly to the constructor of the new object
<olux> even the value_type is a boost::iterator_range?
<dzejrou> so if the object takes first and last as arguments, emplace_back takes first, last as arguments
<dzejrou> sadly, I don't know anything about boost::iterator_range :/ you'd have to consult its documentation to find out what constructors it has
<dzejrou> apparently, boost::iterator_range won't accept {first, last} (whatever that leads to) as arguments
<olux> https://www.boost.org/doc/libs/1_54_0/libs/range/doc/html/range/reference/utilities/iterator_range.html - holding two iterators
<olux> mmhh, I see - ForwardRange
<olux> or ForwardTraversalIterator2
<olux> but the last isn't relavant
<dzejrou> it accepts: two iterators, lvalue reference to a range or const lvalue reference to a range
<dzejrou> I'm not sure what {first, last} would create in that context, but it's either an initializer list or a temporary of type iterator_range
<dzejrou> in either case, no constructor is suitable
<olux> I see, there is more magic behind ..
<dzejrou> actually, there is no magic at all
<olux> :)
<dzejrou> emplace_back is used for in-place construction (to avoid a temporary)
<olux> hence the arg by value
<dzejrou> you tried to use emplace_back as if it was push_back, but those member functions have different semantics and purposes
<CppCon> read cppreference.com
<olux> ok
<dzejrou> if you use emplace_back, you pass arguments to it as if you were constructing a new instance of that type
<olux> isn't what I do at do_annotate (copy-by-value)
<CppCon> do_eat_doughnuts()
<dzejrou> olux: you try to construct a boost::iterator_range instance with a temporary of the type boost::iterator_range
<dzejrou> if you look into the documentation you linked earlier, there is no such constructor in boost::iterator_range that'd suit that
<olux> At https://wandbox.org/permlink/uoGJEBZGlUmXUar6 I fixed this (I think)
<dzejrou> congratulations
<olux> At https://wandbox.org/permlink/J9XHDEdquDmriYar I try now zo use universal refernces; it compiles, but doesn't work correctly anymore. Obvously I haven't catched the move semantic et all. What wrong - how to fix?
* riksteri hat die Verbindung getrennt (Ping timeout: 264 seconds).
* AbleBacon hat die Verbindung getrennt (Quit: Leaving).
* AbleBacon (~AbleBacon@unaffiliated/ablebacon) ist beigetreten.
<dzejrou> afaik universal references won't work without templates
<dzejrou> though tbh I'm currently failing to find proof for my claim
* royal_screwup21 hat die Verbindung getrennt (Quit: http://www.kiwiirc.com/ - A hand crafted IRC client).
<dzejrou> the closest thing: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4164.pdf section 1.2, so it seems to be correct
<dzejrou> also, on line 78, you use is_base_of on NodeT, which is potentially (and actually) a reference, so it returns false_type (explaining why you don't get errors, if you use std::remove_reference_t<NodeT>, it will fail to compile because it returns std::true_type and there is no match)
<olux> interesting
<dzejrou> I now realise I'm in c++-basic, sorry if what I write seems too complex, I'm not too good at dumbing things down :/
<olux> I can follow you :)
<dzejrou> the gist of it is, once you fix the std::is_base_of problem, is that the std::false_type version accepts a forwarding reference (also known as universal references) but the std::true_type accepts only rvalue reference
<olux> would be is_covertible better approach? or does it suffer from same problem?
<dzejrou> better aproach is to use std::remove_reference_t imo
<dzejrou> std::is_convertible does not restrict itself to inheritance only
<dzejrou> however, then you're still left with the reference problem and I'm afraid that that is a design problem, not a language one
<CppCon> please make a TL,DR from all what happened during the last hours
<CppCon> LD
<dzejrou> olux: personal advice - you compile as C++17, use the beauty of if constexpr instead of those ugly overloads :)
<CppCon> for me: pass everything you can by value. avoid references and pointers as hell. no dangling shit problems :)
<olux> ok, how to use it here? I've used it never in such context
<CppCon> "I have C++17 here and I am not afraid to use it"
<dzejrou> if constexpr (std::is_base_of_v<X, Y>) { /* is derived */ } else { /* is not derived */ }
<olux> ah, inside function body
<olux> isn't it?
<dzejrou> this can be a template, which means you can use forwarding references
<dzejrou> yes
<dzejrou> no overloads, no do_ private functions
<dzejrou> KISS
<CppCon> :*
<dzejrou> ew
<olux> kooks beauty now - https://wandbox.org/permlink/PCOMlzHmYssEtV26 , but doen't work as expected
<olux> or remove-reference problem wtill there?
<dzejrou> go throught the past few comments again
<dzejrou> *through, and yes, NodeT might be (and is in this case) a reference
<dzejrou> and while X might be derived from Y, X&/X&& is not
<olux> Did I apply remove_reference wrong here https://wandbox.org/permlink/qwRvCenKlcdWqp56 ?
<dzejrou> yes
<dzejrou> std::remove_reference is a type that has a member typedef called "type" that you need, so you need to access is either by "typename std::remove_reference<X>::type" or (C++14 and later) by "std::remove_reference_t<X>"
<dzejrou> what you are asking in your code is basically "is this std::remove_reference instantiation derived from ast::position_tagged?"
<olux> before I've used std::is_base_of_v<ast::position_tagged, std::remove_reference<NodeT>::type> which did not compile; now I've got it hopefully - https://wandbox.org/permlink/hNcp4xBtC2HnGc6w; isn't it? Any further improvements?
<olux> ah, typename was mising before ...
<dzejrou> that's why the _t aliases (and _v aliases in C++17) are so cool and should be used all the time :)
<olux> yes, I have to read the error message more carefully, I assume there where a hint
<olux> unfornately on web there aren't so much source which uses _v, _t types
<olux> they are more clean
<dzejrou> there doesn't has to be, just check the documentation (cppreference.com) and see if the metafunction returns a value (in which case there is a _v suffix alias) or a type (in which case there is a _t alias)
<olux> yep, step learning curve for C++, especially C++17 :-)
<dzejrou> tbh, this "steep learning curve" might be caused by you tackling complex problems too early :/
* Karyon (~Karyon@unaffiliated/karyon) ist beigetreten.
<olux> maybe, I'm working on/with me ;) Anyway, thanks a lot!
<dzejrou> np
 -------------------------------------------------------------------------------
#endif

#include <boost/range/iterator_range.hpp>
#include <vector>
#include <tuple>
#include <optional>

#include <type_traits>
#include <boost/type_traits/is_base_of.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <boost/type_index.hpp>

namespace ast {

struct position_tagged
{
    typedef std::size_t                             tag_type;

    static constexpr tag_type MAX_ID = std::numeric_limits<tag_type>::max();

    tag_type pos_id{ MAX_ID };
};

struct node_tagged : position_tagged
{
    int dummy;
};


struct node_none
{
    int dummy;
};

}


template <typename IteratorT, typename ContainerT = std::vector<boost::iterator_range<IteratorT>>>
class position_cache
{
public:

    typedef IteratorT                               iterator_type;
    typedef ContainerT                              container_type;
    typedef typename container_type::value_type     range_type;

public:
    template <typename NodeT>
    void annotate(NodeT&& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_cache::annotate<"
                      << boost::typeindex::type_id<decltype(node)>().pretty_name()
                      << "> with ID = "
                      << positions.size() << "\n";

            /* ToDo: maybe better throw range_exception since it's an implementation
             * limitation. */
            assert(positions.size() < ast::position_tagged::MAX_ID &&
                   "Insufficient range of numeric IDs for AST tagging");
            node.pos_id = positions.size();
            positions.emplace_back( first, last );
        }
        else { /* ignore */ }
    }

public:
    // This will catch all nodes inheriting from position_tagged
    range_type position_of(ast::position_tagged const& node) const
    {
        std::cout << "position_of(ast::position_tagged const& node) const" << "\n";
        return positions[node.pos_id];
    }

    // This will catch all nodes except those inheriting from position_tagged
    // returns an empty position
    template <typename NodeT>
    range_type position_of(NodeT const&) const
    {
        std::cout << "position_of(NodeT const&) const" << "\n";
        return range_type{};
    }

private:
    container_type                                  positions;
};

template<typename IteratorT>
struct writer {
    typedef IteratorT                               iterator_type;

    writer(position_cache<iterator_type>& position_cache_)
    : cache{ position_cache_ }
    {}

    template <typename NodeT>
    void annotate(NodeT&& node, iterator_type const& first, iterator_type const& last)
    {
        cache.annotate(std::forward<NodeT>(node), first, last);
    }

    position_cache<iterator_type>&                   cache;
};

int main()
{
    using iterator_type = std::string::const_iterator;
    std::string input{ "Hello World" };

    position_cache<iterator_type> cache{};

    ast::node_tagged node_tagged{};
    ast::node_none none{};

    writer w{ cache };

    w.annotate(node_tagged, input.begin(), input.end());
    w.annotate(none, input.begin(), input.end());
}


