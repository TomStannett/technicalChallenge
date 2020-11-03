// technicalChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Socket.hpp"
#include "Connection.hpp"
#include "Cache.hpp"

#include <iostream>
#include <chrono>

// unit test as specified in design doc
void cacheUnitTest() {

    // instantiate sockets
    Socket S1("192.168.9.1", 10);
    Socket S2("192.168.9.2", 20);
    Socket S3("192.168.9.3", 30);
    Socket S4("192.168.9.4", 40);

    // instantiate cache w first insert
    Cache cache(Connection(S1, S2), 10, true);

    // instantiate lookup time test vector
    std::vector<double> lookup_times;

    
    // use return variable from r to get exec time
    std::tuple<bool, int, double> r = cache.lookup(Connection(S3, S1));
    lookup_times.push_back(std::get<2>(r));

    cache.insert(Connection(S1, S3));

    r =  cache.lookup(Connection(S2, S1));
    lookup_times.push_back(std::get<2>(r));

    cache.insert(Connection(S2, S1));
    cache.insert(Connection(S1, S2));

    r =  cache.lookup(Connection(S1, S2));
    lookup_times.push_back(std::get<2>(r));

    r =  cache.lookup(Connection(S1, S3));
    lookup_times.push_back(std::get<2>(r));

    r =  cache.lookup(Connection(S1, S4));
    lookup_times.push_back(std::get<2>(r));

    // disp lookup times
    std::cout << std::endl;
    std::cout << "Lookup times: ";
    double t_av = 0;
    for (auto t : lookup_times) {
        std::cout << std::to_string(t) << "us ";
        t_av += t;
    }
    t_av /= lookup_times.size();
    std::cout <<"Average: " << std::to_string(t_av) << "us." << std::endl;

    // dump cache
    std::cout << std::endl;
    cache.dump();
}

int main()
{
    // call unit test
    cacheUnitTest();
    return 0;
}

