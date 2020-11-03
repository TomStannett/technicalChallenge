# technicalChallenge
## Code Challege 3 for DarkTrace

Libraries used: bootx86 for windows. Version 1.73.0
IDE: Visual Studio 16.7.7

### Notes
* Each .hpp has a commented boilerplate at the top explaining the fields and methods of the associated class
* I used an unordered_map in the Cache class to store Connection Objects and their associated lookup counts. The Connection objs were used as they key value for the map, and as such required a custom hash generator function. The motivation for this is that .find() (used in lookup and insert) runs in O(1) time for a good hash function and O(n) worst case. 
* Please find screenshots of results and UDI diagram in the images folder




