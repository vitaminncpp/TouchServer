#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Network.h"


class UDPSender
{
private:
	SOCKET sock;
	WSAData wsaData;
	sockaddr_in toSend;
	unsigned short port;

public:
	UDPSender();
	UDPSender(unsigned short int port);
	UDPSender(IPv4 ip);
	UDPSender(IPv4 ip, unsigned short int port);
	~UDPSender();


public:
	int Bind(IPv4 ip, unsigned short int port);
	int Bind(IPv4 ip);
	int Bind(unsigned short int port);


public:
	int Send(const char* data,int size,int flags=0 );
	int Send(const char* data, int size, IPv4 ip, int flags = 0);
	int Send(const char* data, int size, IPv4 ip, unsigned short int port, int flags = 0);
	int Send(const char* data, int size, sockaddr_in toSend, int flags = 0);
};

