#include "Connection.hpp"
#include "Socket.hpp"
#include "Cache.hpp"
#include "CacheHash.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/functional/hash.hpp>

// constructors
Cache::Cache(){

}
Cache::Cache(std::unordered_map<Connection,int, CacheHash> cache_) {
	cache = cache_;
}
Cache::Cache(Connection c_) {
    std::tuple<bool, int> ret = insert(c_);
	
}

std::tuple<bool, int>  Cache::insert(Connection c) {
    bool exists = false;
    
    // check if connection present, if not insert to cache if it is increment lookup.
    if (cache.find(c) == cache.end()) {
        cache.insert(std::pair<Connection, int>(c, 1));
        std::cout << "[Cache][INS]Adding connection: "; 
        c.print();
        std::cout << ", lookups: " << cache[c] << std::endl;
    }

    else {
        cache[c] += 1;
        std::cout << "[Cache][INS]Found Exisitng connection: ";
        c.print();
        std::cout << ", lookups: " << cache[c] << std::endl;
        exists = true;
    }

    return {exists, cache[c]};
}

std::tuple<bool, int,double> Cache::lookup(Connection c) {
    // check if connection present, if not insert to cache if it is increment lookup.
    // init values
    bool exists = false;
    int lookups = 0;

    auto t1 = std::chrono::high_resolution_clock::now();

    // check cache using find -> if not found return false and 0, if found return true and lookup value
    if (cache.find(c) == cache.end()) {
        std::cout << "[Cache][LKP]No Connection Found: ";
        c.print();
        std::cout << ", lookups: " << lookups << std::endl;
    }
    else {
        cache[c] += 1;
        std::cout << "[Cache][LKP]Found Exisitng connection: ";
        c.print();
        std::cout << ", lookups: " << cache[c] << std::endl;
        lookups = cache[c];
        exists = true;
    }

    // time lookup exec
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> dur = t2 - t1;
    double exec_t = dur.count();
    return {exists, lookups, exec_t};
}

void Cache::dump() {
    for (const auto& c : cache) {
        std::cout << "[CACHE][DMP]";
        c.first.getSocket1Address().print();
        std::cout << " <---> ";
        c.first.getSocket2Address().print();
        std::cout << ", lookups: " << c.second << std::endl;
    }
}