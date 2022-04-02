#include <iostream>
#include <string>
#include <exception>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Network.h"
#include "NetworkException.h"
#include "UDPSocket.h"
#pragma comment (lib,"ws2_32.lib")

#ifdef DEBUG
#define LOG_ERR std::cerr << "Error At : " << __FILE__ << " : " << __LINE__ << std::endl
#else
#define LOG_ERR  
#endif


UDPSocket::UDPSocket() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}
	this->sizeOfRecvAddr = sizeof(toRecv);


}



UDPSocket::UDPSocket(unsigned short port) {
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
	this->sizeOfRecvAddr = sizeof(toRecv);
	this->port = port;
	

	toRecv.sin_port = htons(port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.s_addr = ADDR_ANY;
	this->sizeOfRecvAddr = sizeof(toRecv);

	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}

}

UDPSocket::UDPSocket(IPv4& ip) {

	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };

}



UDPSocket::UDPSocket(IPv4& ip, unsigned short port) {

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		LOG_ERR;
		throw NetworkException("WSA Startup failed", __FILE__, __LINE__);
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		LOG_ERR;
		throw NetworkException("Socket Open Failed", __FILE__, __LINE__);
	}

	this->port = port;
	toSend.sin_family = AF_INET;
	toSend.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };



	toRecv.sin_port = htons(port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.s_addr = htonl(INADDR_ANY);

	this->sizeOfRecvAddr = sizeof(toRecv);

	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}

}

UDPSocket::~UDPSocket() noexcept {
	if (sock != INVALID_SOCKET) {
		closesocket(sock);
	}
	WSACleanup();
}
int UDPSocket::Bind(unsigned short port) {
	this->port = port;
	toSend.sin_port = htons(port);
	toSend.sin_family = AF_INET;
	toSend.sin_addr.s_addr = ADDR_ANY;

	toRecv.sin_port = htons(port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.s_addr = ADDR_ANY;
	this->sizeOfRecvAddr = sizeof(toRecv);



	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}
	return ret;
}

int UDPSocket::Bind(IPv4& ip, unsigned short port) {
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


	toRecv.sin_port = htons(port);
	toRecv.sin_family = AF_INET;
	toRecv.sin_addr.s_addr = ADDR_ANY;
	this->sizeOfRecvAddr = sizeof(toRecv);

	int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&toRecv), sizeof(toRecv));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Socket Bind Failed", __FILE__, __LINE__);
	}

	return ret;
}


int UDPSocket::Send(IPv4& ip, const char* data, int size, int flags) {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_un_b = { ip.s_b1,ip.s_b2,ip.s_b3,ip.s_b4 };
	add.sin_port = htons(sport);

	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
	if (ret < 0) {
		LOG_ERR;
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;

}

int UDPSocket::Send(const char* data, int size, int flags) {
	int ret = sendto(sock, data, size, flags, reinterpret_cast<SOCKADDR*>(&toSend), sizeof(toSend));
	if (ret < 0) {
		LOG_ERR;
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
		throw NetworkException("Data Send Failed", __FILE__, __LINE__);
	}
	return ret;

}


int UDPSocket::Recv(char buff[], int size, int flags) {

	int ret = recvfrom(sock, buff, size, flags, reinterpret_cast<SOCKADDR*>(&toRecv), &this->sizeOfRecvAddr);

	if (ret < 0) {
		throw NetworkException("Data Receive Failed", __FILE__, __LINE__);
	}
	buff[ret] = 0;
	return 0;
}

int UDPSocket::SetSourcePort(unsigned short port) {
	this->sport = port;
	toSend.sin_port = htons(this->sport);
	return this->sport;
}
