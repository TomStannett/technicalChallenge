#include "Connection.hpp"
#include "Socket.hpp"
#include <iostream>


// Constructors
// default
Connection::Connection() {
	socket_1 = Socket();
	socket_2 = Socket();
}

Connection::Connection(Socket socket_1_, Socket socket_2_) {
	socket_1 = socket_1_;
	socket_2 = socket_2_;
}

Connection::Connection(boost::asio::ip::address socket_1_ip, unsigned short socket_1_port, boost::asio::ip::address socket_2_ip, unsigned short socket_2_port) {
	socket_1 = Socket(socket_1_ip, socket_1_port);
	socket_2 = Socket(socket_2_ip, socket_2_port);
}

Connection::Connection(std::string socket_1_ip, unsigned short socket_1_port, std::string socket_2_ip, unsigned short socket_2_port) {
	socket_1 = Socket(socket_1_ip, socket_1_port);
	socket_2 = Socket(socket_2_ip, socket_2_port);
}


// getters
Socket Connection::getSocket1Address() const{
	return socket_1;
}

Socket Connection::getSocket2Address() const{
	return socket_2;
}

// setters
void Connection::setSocket1Address(Socket socket_1_) {
	socket_1 = socket_1_;
}
void Connection::setSocket2Address(Socket socket_2_) {
	socket_2 = socket_2_;
}

void Connection::print(){
	std::cout << socket_1.getIP()->to_string() << ":" << socket_1.getPort() << " <---> " << socket_2.getIP()->to_string() << ":" << socket_2.getPort();
}

bool operator==(const Connection& a, const Connection& b) {
	return ((a.socket_1 == b.socket_1) && (a.socket_2 == b.socket_2)) || ((a.socket_1 == b.socket_2) && (a.socket_2 == b.socket_1));
}


