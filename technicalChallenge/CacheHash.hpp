/**
 * CacheHash struct provides custom hasher for unordered_map
 *
 * std::size_t operator()(const Connection& c) const overloads hash call in unordered_set, such that we can use custom hash function.
 *
 * MOTIVATION: As we use a custom class for our key we require a custom hash, derived on the fields of that class.
 *      We use two seeds, seed_1 and seed_2 and add them together to avoid input order dependence: as connections are two way (implied by challenge brief), 
 *      connection c1 with  Add1 & Add2 is the same as connection c2 with Add2 & Add1. As such hasher must output same values -> as a bitshift is 
 *      used in boost's hash_combine, two different hashes would be produced for for c1 and c2, ruining our lookup and insert.
 *      JDK solves this problem thus: given set S = [e1, e2, ..., en] we apply the hash operator on each element ei. We can then
 *      define the hash of S as h(S) = h(e1) + h(e2) + ... h(en). src: https://stackoverflow.com/questions/30734848/order-independent-hash-algorithm
 **/

#ifndef CACHEHASH_H
#define CACHEHASH_H

#include "Connection.hpp"

struct CacheHash
{
    std::size_t operator()(const Connection& c) const;
};

#endif