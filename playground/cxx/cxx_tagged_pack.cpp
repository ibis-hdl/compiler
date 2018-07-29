/*
 * cxx_tagged_pack.cpp
 *
 *  Created on: 28.07.2018
 *      Author: olaf
 */

// https://wandbox.org/permlink/VxTEckWGUmuzLzLW

//#if defined(NDEBUG)
//#undef NDEBUG
//#endif

#include <cstdint>
#include <limits>
#include <iostream>
#include <iomanip>
#include <cassert>

#include <boost/io/ios_state.hpp>


struct tagged
{
    // packet layout (little endian)
    // | 63                            0|
    // +------------------+-------------+
    // | node_id          | file_id     |
    // +------------------+-------------+
    // |63    downto   16 | 15 downto 0 |
    // +------------------+-------------+
    typedef std::uint64_t                           tag_type;

    static constexpr tag_type MAX_ID = std::numeric_limits<tag_type>::max();

    static constexpr std::size_t size() noexcept { return sizeof(tag_type); }
    static constexpr std::size_t N_BITS  = sizeof(tag_type) * 8;

    static constexpr std::size_t NODE_BITS = 48;
    static constexpr std::size_t FILE_BITS = N_BITS - NODE_BITS;

    static constexpr std::size_t NODE_OFFSET = FILE_BITS;

    static constexpr tag_type MAX_NODE_ID = (1ull << NODE_BITS) - 1;
    static constexpr tag_type MAX_FILE_ID = (1ull << FILE_BITS) - 1;

    static constexpr tag_type MASK_NODE = MAX_NODE_ID << NODE_OFFSET;
    static constexpr tag_type MASK_FILE = MAX_FILE_ID;


    void set_file(std::size_t id) {
        assert(id < MAX_FILE_ID && "id out of range");
        id_pack = (id_pack & MASK_NODE) | id;
    }

    void set_node(std::size_t id) {
        assert(id < MAX_NODE_ID && "id out of range");
        id_pack = (id << NODE_OFFSET) | (id_pack & MASK_FILE);
    }

    void set(std::size_t file_id, std::size_t node_id) {
        assert(   file_id < MAX_FILE_ID
               && node_id < MAX_NODE_ID
               && "id out of range");
        id_pack = (node_id << NODE_OFFSET) | file_id;
    }

    std::size_t file_id() const {
        return id_pack & MASK_FILE;
    }

    std::size_t node_id() const {
        return (id_pack & MASK_NODE) >> NODE_OFFSET;
    }

    tag_type                                        id_pack{ MAX_ID };

};


std::ostream& operator<<(std::ostream& os, tagged const& tag)
{
    boost::io::ios_flags_saver  iosfs{os};

    os << "size:        " << tagged::size() << " bytes\n"
       << "N_BITS:      " << tagged::N_BITS << "\n"
       << "NODE_BITS:   " << tagged::NODE_BITS << "\n"
       << "FILE_BITS:   " << tagged::FILE_BITS << "\n"
       << "MAX_NODE_ID: " << "0x" << std::hex << tagged::MAX_NODE_ID << "\n"
       << "MAX_FILE_ID: " << "0x" << std::hex << tagged::MAX_FILE_ID << "\n"
       << "MASK_NODE:   " << "0x" << std::hex << tagged::MASK_NODE << "\n"
       << "MASK_FILE:   " << "0x" << std::hex << tagged::MASK_FILE << "\n"
       << std::dec
       << "NODE_OFFSET: " << tagged::NODE_OFFSET << std::dec << "\n"
    ;

    os << "ID<"
       << "pack:     "                            // 2 nibble = 1 byte!
       << "0x" << std:: setfill('0') << std::setw(2*tagged::size()) << std::hex
       << tag.id_pack << ", "
       << std::dec
       << "file: " << tag.file_id() << ", "
       << "node: " << tag.node_id()
       << ">\n";
    return os;
}


int main()
{
    tagged t;

    std::cout << t << "\n";

    t.set_node(1);
    t.set_file(2);
    std::cout << t << "\n";

    t.set_file(1);
    t.set_node(2);
    std::cout << t << "\n";

    t.set(0, 0);
    std::cout << t << "\n";

    t.set(0, 1);
    std::cout << t << "\n";

    t.set(1, 0);
    std::cout << t << "\n";

    t.set(0, tagged::MAX_NODE_ID); // without NDEBGUG will abort()

    std::cout << t << "\n";

    t.set(tagged::MAX_FILE_ID, 0); // without NDEBGUG will abort()
    std::cout << t << "\n";
}


