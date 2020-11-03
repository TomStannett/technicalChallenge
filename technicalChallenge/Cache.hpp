/**
 * Cache Class describing a cache storing connections objects and their frequency of lookup
 *
 * Fields
 *
 *   std::unordered_map<Connection, int, CacheHash> cache an unordered mapping using the Connection as a key and value the lookup count
 *
 * Methods
 *
 *   Cache() default constructor, initalises blank map
 *   Cache(std::unordered_map<Connection, int, CacheHash> cache_) initialise by copying an exist map
 *   Cache(Connection c_) initialise by inserting a new connection
 *
 *   std::tuple<bool, int> insert(Connection c) insert new Connection c if one does not exist already, increment lookup
 *                         returns: did c exist already (bool), lookup number (int)
 *   std::tuple<bool, int, double> lookup(Connection c); search cache for Connection c, increment lookup if exists
 *						   returns: did c exist already (bool), lookup number (int), lookup exec time (double) - for debug
 *						   
 *
 *   void dump() dump contents of cache to console
 *
 *   An unordered map is used as optimal search speed O(1) and worst case O(n) - dependent on hash used
**/
#ifndef CACHE_H
#define CACHE_H

#include "Connection.hpp"
#include "Socket.hpp"
#include "CacheHash.hpp"
#include <unordered_map>

class Cache {
private:
	std::unordered_map<Connection, int, CacheHash> cache;

public:
	Cache();
	Cache(std::unordered_map<Connection, int, CacheHash> cache_);
	Cache(Connection c_);


	std::tuple<bool, int> insert(Connection c);
	std::tuple<bool, int, double> lookup(Connection c);
	void dump();

};

#endif