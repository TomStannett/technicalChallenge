/**
 * Connection describing a two way link between two sockets
 *
 * Fields
 *
 *   Socket socket_1 socket obj describing endpoint 1
 *   Socket socket_2  socket obj describing  endpoint 1
 *
 * Methods
 * 
 *   Connection() default constructor, initalises two endpoints on home address
 *   Connection(Socket socket_1_, Socket socket_2_) initialisations connection on two Socket parameters
 *   Connection(boost::asio::ip::address socket_1_ip, int socket_1_port, boost::asio::ip::address socket_2_ip, int socket_2_port) initialisies connection by creation of two new sockets
 *   Connection(std::string socket_1_ip, int socket_1_port, std::string socket_2_ip, int socket_2_port) initialisies connection by creation of two new sockets using ip address strings
 *
 *   Socket getSocket1Address() const gets socket_1 address, returns Socket Object
 *   Socket getSocket2Address() const gets socket_2 address, returns Socket Object
 *
 *   void setSocket1Address(Socket socket_1_) sets socket_1 address
 *   void setSocket2Address(Socket socket_2_) sets socket_2 address
 *
 *   void print() prints both socket ips + ports in human readable format
 *   
 *   friend bool operator==(const Connection& a, const Connection& b) we are required to overload the == operator and the hash function to utilise an unordered_map keyed with a connection.
**/

#ifndef CONNECTION_H
#define CONNECTION_H

#include "Socket.hpp"
#include <boost/asio.hpp>

class Connection {
private:
    Socket socket_1;
    Socket socket_2;
public:
    // constructors
    Connection();
    Connection(Socket socket_1_, Socket socket_2_);
    Connection(boost::asio::ip::address socket_1_ip, int socket_1_port, boost::asio::ip::address socket_2_ip, int socket_2_port);
    Connection(std::string socket_1_ip, int socket_1_port, std::string socket_2_ip, int socket_2_port);

    // getters
    Socket getSocket1Address() const;
    Socket getSocket2Address() const;

    // setters
    void setSocket1Address(Socket socket_1_);
    void setSocket2Address(Socket socket_2_);

    void print();
    // we are required to overload the == operator and the hash function to utilise an unordered_map keyed with a connection.
    friend bool operator==(const Connection& a, const Connection& b);
};

#endif