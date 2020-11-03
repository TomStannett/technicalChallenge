# technicalChallenge
## Code Challege 3 for DarkTrace

Libraries used: bootx86 for windows. Version 1.73.0
IDE: Visual Studio 16.7.7

### Notes
* Each .hpp has a commented boilerplate at the top explaining the fields and methods of the associated class
* I used an unordered_map in the Cache class to store Connection Objects and their associated lookup counts. The Connection objs were used as they key value for the map, and as such required a custom hash generator function. The motivation for this is that .find() (used in lookup and insert) runs in O(1) time for a good hash function and O(n) worst case.
* The reject flag in Cache allows one to either: reject incoming packets if a hard limit (max_connections) is reached -> true, or replace entry with most infrequent lookup -> false.
* I have coded the order of the rejection such that a new incoming connection still gets added to the lookup, if it exists already in the cache and if the cache is full. I did not know whether I intepreted the design docs correctly, as i took that to count as a lookup and for the iterator to increase. To make it so the iterator does not increase, the if statement can simply be moved above the execution block.
* I have used a custom Socket class to act as a wrapper around boost::asio. To me this seems more extendable and readable.
* Please find screenshots of results and UDI diagram in the images folder




