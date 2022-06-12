#pragma once
#include "Network.h"

class UDPReceiver
{
	private:
		SOCKET sock;
		WSAData wsaData;
		sockaddr_in toRecv;
		unsigned short port;
		int addrSize;

	public:
		UDPReceiver();
		UDPReceiver(unsigned short int port);
		UDPReceiver(IPv4 ip);
		UDPReceiver(IPv4 ip, unsigned short int port);
		~UDPReceiver();


	public:
		int Bind(IPv4 ip, unsigned short int port);
		int Bind(IPv4 ip);
		int Bind(unsigned short int port);


	public:
		int Recv(char* data, int size, int flags = 0);
		int Recv(char* data, int size, IPv4 ip, int flags = 0);
		int Recv(char* data, int size, IPv4 ip, unsigned short int port, int flags = 0);
	};

