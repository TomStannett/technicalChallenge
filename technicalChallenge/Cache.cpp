#include "Connection.hpp"
#include "Socket.hpp"
#include "Cache.hpp"
#include "CacheHash.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/functional/hash.hpp>

// constructors
Cache::Cache() : max_connections(10), reject(true)  {}

Cache::Cache(std::unordered_map<Connection,int, CacheHash> cache_, int max_connections_ = 10, bool reject_ = true) : cache(cache_), max_connections(max_connections_), reject(reject_) {}

Cache::Cache(Connection c_, int max_connections_ = 10, bool reject_ = true) : max_connections(max_connections_), reject(reject_){
    std::tuple<bool, int> ret = insert(c_);
}


int Cache::getMaxConnections() {
    return max_connections;
}

bool Cache::getReject() {
    return reject;
}

void Cache::setMaxConnections(int max_connections_) {
     max_connections = max_connections_;
}

void Cache::setReject(bool reject_) {
    reject = reject_;
}

std::tuple<bool, int>  Cache::insert(Connection c) {
    bool exists = false;
    
    // fisrt check if cache full. If so check if reject selected 
    if (cache.size() == max_connections && reject) {
       std::cout << "[CACHE][INS]Cache Capacity Reached (" << max_connections << "). Rejected incoming connection." << std::endl;
    }
    else {
        // check again and if reject is off, if so remove least frequent element by using lookup number
        Connection min_conn;
        int min = INT_MAX;

        if (cache.size() == max_connections && !reject) {
            for (const auto& c : cache) {
                if (c.second < min) {
                    min_conn = c.first;
                    min = c.second;
                }
            }
            cache.erase(min_conn);
        }

        // Now add connection:
        // check if connection present, if not insert to cache if it is increment lookup.
        if (cache.find(c) == cache.end()) {
            cache.insert(std::pair<Connection, int>(c, 1));
            std::cout << "[Cache][INS]Adding connection: ";
            c.print();
            std::cout << ", lookups: " << cache[c] << std::endl;
        }

        // connection found already
        else {
            cache[c] += 1;
            std::cout << "[Cache][INS]Found Exisitng connection: ";
            c.print();
            std::cout << ", lookups: " << cache[c] << std::endl;
            exists = true;
        }
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