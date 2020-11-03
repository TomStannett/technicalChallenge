#include "CacheHash.hpp"
#include <boost/functional/hash.hpp>


std::size_t CacheHash::operator()(const Connection& c) const
{
    // get connection addresses
    Socket src = c.getSocket1Address();
    Socket dest = c.getSocket2Address();

    using boost::hash_value;
    using boost::hash_combine;

    // init hash
    std::size_t seed_1 = 0;
    std::size_t seed_2 = 0;

    // our hash set has two elements, c1 and c2, where c1 has the inverse addresses of c2
    // apply boost hash_combine (XOR + bit-shift)
    hash_combine(seed_1, hash_value(src.getIP()->to_string()));
    hash_combine(seed_1, hash_value(src.getPort()));
    hash_combine(seed_1, hash_value(dest.getIP()->to_string()));
    hash_combine(seed_1, hash_value(dest.getPort()));

    hash_combine(seed_2, hash_value(dest.getIP()->to_string()));
    hash_combine(seed_2, hash_value(dest.getPort()));
    hash_combine(seed_2, hash_value(src.getIP()->to_string()));
    hash_combine(seed_2, hash_value(src.getPort()));

    // Return the result.
    return seed_1 + seed_2;
}
