/**
 * Socket describing IP address and port
 *
 * Fields
 *
 *  boost::asio::ip::address ip describes the ip address
 *  unsigned short port describes the port number, 16 bit unsigned integer
 * 
 * Methods
 * 
 *  Socket() default initialises to home IP
 *  Socket(boost::asio::ip::address ip_, int port_) initialises to supplied boost ip addr and int port
    Socket(std::string ip_, int port_)  initialises to supplied string ip addr and int port, converts string to boost addr inline

 *  boost::asio::ip::address* getIP() gets pointer to boost ip addr of obj
 *  int getPort() gets int port of obj

 *  void setIP(boost::asio::ip::address ip_) sets ip field with parameter
 *  void setPort(int port_) sets port field with parameter

 *  void print() prints socket ip + port in human readable format

 *  friend bool operator==(const Socket& a, const Socket&b) overloads == operator such that two sockets can be compared for similarity
 * 
 * this class can be naturally extended to provide a wrapper for the boost::asio::ip:tcp::socket class
 **/

#ifndef SOCKET_H
#define SOCKET_H

#include <boost/asio.hpp>

class Socket {
private:
    boost::asio::ip::address ip;
    unsigned short port;
public:
    Socket();
    Socket(boost::asio::ip::address ip_, unsigned short port_);
    Socket(std::string ip_, unsigned short port_);

    boost::asio::ip::address* getIP();
    int getPort();

    void setIP(boost::asio::ip::address ip_);
    void setPort(unsigned short port_);

    void print();

    friend bool operator==(const Socket& a, const Socket&b);
};

#endif