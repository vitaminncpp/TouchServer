#include "UDPSender.h"
#include "NetworkException.h"
#pragma comment (lib,"ws2_32.lib")


#define DEFAULT_PORT 10117

UDPSender::UDPSender(unsigned short int port) {
	this->port = port;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}

}


UDPSender::UDPSender(IPv4 ip,unsigned short int port) {
	this->port = port;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}
	
	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	toSend.sin_port = htons(port);
}

UDPSender::UDPSender(IPv4 ip) {
	this->port = DEFAULT_PORT;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}
	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	toSend.sin_port = this->port;
}

UDPSender::UDPSender() {
	this->port = DEFAULT_PORT;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}
	
}

UDPSender::~UDPSender() {
	if (sock != INVALID_SOCKET) {
		closesocket(sock);
	}
	WSACleanup();
}

int UDPSender::Bind(IPv4 ip, unsigned short int port) {
	this->port = port;
	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	toSend.sin_port = htons(port);
	return 0;
}

int UDPSender::Bind(IPv4 ip) {
	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	toSend.sin_port = htons(port);
	return 0;
}

int UDPSender::Bind(unsigned short int port) {
	this->port = port;
	toSend.sin_port = htons(port);
	return 0;
}


int UDPSender::Send(const char* data,int size,int flags) {
	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&toSend), sizeof(toSend));
	if (ret < 0) {
		LOG_ERR;
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;
}


int UDPSender::Send(const char* data, int size, IPv4 ip, int flags) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	add.sin_port = htons(port);
	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
	if (ret < 0) {
		LOG_ERR;
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;
}

int UDPSender::Send(const char* data, int size, IPv4 ip, unsigned short int port, int flags) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	add.sin_port = htons(port);
	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
	if (ret < 0) {
		LOG_ERR;
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;
}

int UDPSender::Send(const char* data, int size, sockaddr_in toSend, int flags = 0) {
	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&toSend), sizeof(toSend));
	if (ret < 0) {
		LOG_ERR;
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;
}