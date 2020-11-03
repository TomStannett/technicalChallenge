/**
 * Cache Class describing a cache storing connections objects and their frequency of lookup
 *
 * Fields
 *
 *   std::unordered_map<Connection, int, CacheHash> cache an unordered mapping using the Connection as a key and value the lookup count
 *   max_connections: maximum connections that can be stored in cache -> default = 10
 *   reject: flag, if set true incoming connections are rejected if cache full, if false, deletes least frequent entry
 *
 * Methods
 *
 *   Cache() default constructor, initalises blank map 
 *   Cache(std::unordered_map<Connection, int, CacheHash> cache_, int max_connections_, bool reject_) initialise by copying an exist map, and sets fields (if not specified defaults used)
 *   Cache(Connection c_, int max_connections_, bool reject_) initialise by inserting a new connection, and sets fields (if not specified defaults used)
 *
 * 	int getMaxConnections() getter for max_connections field
 *	void setMaxConnections(int max_connections_) setter for max_connections field
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
	int max_connections;
	bool reject;

public:
	Cache();
	Cache(std::unordered_map<Connection, int, CacheHash> cache_, int max_connections_, bool reject_);
	Cache(Connection c_, int max_connections_, bool reject_);

	// getters and setters
	int getMaxConnections();
	bool getReject();

	void setMaxConnections(int max_connections_);
	void setReject(bool reject_);

	// custom methods
	std::tuple<bool, int> insert(Connection c);
	std::tuple<bool, int, double> lookup(Connection c);
	void dump();

};

#endif