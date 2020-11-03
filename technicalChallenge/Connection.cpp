#include "Connection.hpp"
#include "Socket.hpp"
#include <iostream>


// Constructors
// default
Connection::Connection() {
	socket_1 = Socket();
	socket_2 = Socket();
}

Connection::Connection(Socket src_, Socket dest_) {
	socket_1 = src_;
	socket_2 = dest_;
}

Connection::Connection(boost::asio::ip::address src_ip, int src_port, boost::asio::ip::address dest_ip, int dest_port) {
	socket_1 = Socket(src_ip, src_port);
	socket_2 = Socket(dest_ip, dest_port);
}

Connection::Connection(std::string src_ip, int src_port, std::string dest_ip, int dest_port) {
	socket_1 = Socket(src_ip, src_port);
	socket_2 = Socket(dest_ip, dest_port);
}


// getters
Socket Connection::getSocket1Address() const{
	return socket_1;
}

Socket Connection::getSocket2Address() const{
	return socket_2;
}

// setters
void Connection::setSocket1Address(Socket src_) {
	socket_1 = src_;
}
void Connection::setSocket2Address(Socket dest_) {
	socket_2 = dest_;
}

void Connection::print(){
	std::cout << socket_1.getIP()->to_string() << ":" << socket_1.getPort() << " <---> " << socket_2.getIP()->to_string() << ":" << socket_2.getPort();
}

bool operator==(const Connection& a, const Connection& b) {
	return ((a.socket_1 == b.socket_1) && (a.socket_2 == b.socket_2)) || ((a.socket_1 == b.socket_2) && (a.socket_2 == b.socket_1));
}


