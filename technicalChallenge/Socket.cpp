#include "Socket.hpp"
#include <boost/asio.hpp>
#include <iostream>


// constructors
// default
Socket::Socket() {
    boost::asio::ip::address boost_ip_ = boost::asio::ip::address::from_string("127.0.0.1");
    ip = boost_ip_;
    port = 0;
}

Socket::Socket(boost::asio::ip::address ip_, unsigned short port_) : ip(ip_), port(port_) {
}

Socket::Socket(std::string ip_, unsigned short port_) : port(port_) {
    ip = boost::asio::ip::address::from_string(ip_);
}


// getters
boost::asio::ip::address* Socket::getIP() {
    boost::asio::ip::address* ip_ptr = new boost::asio::ip::address(ip);
    return ip_ptr;
}


int Socket::getPort() {
    return port;
}

// setters
void Socket::setIP(boost::asio::ip::address ip_) {
    ip = ip_;
}

void Socket::setPort(unsigned short port_) {
    port = port_;
}

void Socket::print() {
    std::cout << ip.to_string() << ":" << port;
}

bool operator==(const Socket& a, const Socket& b){
    return ((a.ip == b.ip) && (a.port == b.port));
}

